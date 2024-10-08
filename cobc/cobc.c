/* cobc.c
 * Copyright (C) 2001-2009 Keisuke Nishida
 * Copyright (C) 2007-2009 Roger While
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, 51 Franklin Street, Fifth Floor
 * Boston, MA 02110-1301 USA
 */

#include "config.h"
#include "defaults.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <setjmp.h>
#ifdef	HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef	HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <time.h>
#include <sys/stat.h>
#ifdef  HAVE_SIGNAL_H
#include <signal.h>
#endif

#ifdef _WIN32
#include <windows.h>		/* for GetTempPath, GetTempFileName */
#endif

#ifdef	HAVE_KPATHSEA_GETOPT_H
#include <kpathsea/getopt.h>
#else
#ifdef	HAVE_GETOPT_H
#include <getopt.h>
#else
#include "lib/getopt.h"
#endif
#endif

#ifdef	HAVE_LOCALE_H
#include <locale.h>
#endif

#include <tarstamp.h>

#include "cobc.h"
#include "tree.h"

/* Compile level */
enum cb_compile_level {
	CB_LEVEL_PREPROCESS = 1,
	CB_LEVEL_TRANSLATE,
	CB_LEVEL_COMPILE,
	CB_LEVEL_ASSEMBLE,
	CB_LEVEL_MODULE,
	CB_LEVEL_LIBRARY,
	CB_LEVEL_EXECUTABLE
};

/*
 * Global variables
 */

int	cb_source_format = CB_FORMAT_FIXED;

#ifdef	COB_EBCDIC_MACHINE
int	cb_display_sign = COB_DISPLAY_SIGN_EBCDIC;	/* 1 */
#else
int	cb_display_sign = COB_DISPLAY_SIGN_ASCII;	/* 0 */
#endif

#undef	COB_EXCEPTION
#define	COB_EXCEPTION(code,tag,name,critical) {name, 0x##code, 0},
struct cb_exception cb_exception_table[] = {
	{NULL, 0, 0},		/* CB_EC_ZERO */
#include <libcob/exception.def>
	{NULL, 0, 0}		/* CB_EC_MAX */
};
#undef	COB_EXCEPTION

#undef	CB_FLAG
#define	CB_FLAG(var,name,doc)		int var = 0;
#include "flag.def"
#undef	CB_FLAG

#undef	CB_WARNDEF
#define	CB_WARNDEF(var,name,wall,doc)	int var = 0;
#include "warning.def"
#undef	CB_WARNDEF

#ifdef  _MSC_VER
#define PATHSEPS ";"
#else
#define PATHSEPS ":"
#endif

int			cb_id = 1;
int			cb_attr_id = 1;
int			cb_literal_id = 1;
int			cb_field_id = 1;
int			cb_storage_id = 1;
int			cb_flag_main = 0;

int			errorcount = 0;
int			warningcount = 0;
int			alt_ebcdic = 0;
int			optimize_flag = 0;

char			*cb_source_file = NULL;
char			*cb_oc_build_stamp = NULL;
char			*source_name;
char			*demangle_name;
int			cb_source_line = 0;

FILE			*cb_storage_file;
char			*cb_storage_file_name;

FILE			*cb_listing_file = NULL;
FILE			*cb_depend_file = NULL;
char			*cb_depend_target = NULL;
struct cb_text_list	*cb_depend_list = NULL;
struct cb_text_list	*cb_include_list = NULL;
struct cb_text_list	*cb_extension_list = NULL;

int			cb_saveargc;
char			**cb_saveargv;

const char		*cob_config_dir;

/*
 * Local variables
 */

static const char	*const cob_csyns[] = {
	"NULL",
	"L_initextern",
	"LRET_initextern",
#ifndef __GNUC__
	"P_switch",
#endif
	"alignof",
	"asm",
	"auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"exit_program",
	"extern",
	"float",
	"for",
	"frame_pointer",
	"frame_stack",
	"goto",
	"if",
	"inline",
	"int",
	"long",
	"offsetof",
	"register",
	"restrict",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"typeof",
	"union",
	"unsigned",
	"void",
	"volatile",
	"_Bool",
	"_Complex",
	"_Imaginary"
};

#define COB_NUM_CSYNS	sizeof(cob_csyns) / sizeof(char *)

static enum cb_compile_level	cb_compile_level = 0;
static enum cb_compile_level	local_level = 0;

static size_t		iparams = 0;
static int		iargs;
static char		*cobcpy = NULL;
static char		*save_temps_dir = NULL;

static jmp_buf		cob_jmpbuf;

static int		wants_nonfinal = 0;
static int		cb_flag_module = 0;
static int		cb_flag_library = 0;
static int		save_temps = 0;
static int		save_csrc = 0;
static int		verbose_output = 0;
static int		cob_iteration = 0;
#ifndef _WIN32
static pid_t		cob_process_id = 0;
#endif

static int		strip_output = 0;
static int		gflag_set = 0;

static char		*output_name;

static const char	*cob_tmpdir;			/* /tmp */

static struct filename	*file_list;

/* NOTE fcopts MUST have at least one leading space */
#if defined (__GNUC__) && (__GNUC__ >= 3)
static const char fcopts[] = " -finline-functions -fno-gcse -freorder-blocks ";
#elif defined(__xlc__)
static const char fcopts[] = " -Q -qro -qroconst ";
#else
static const char fcopts[] = " ";
#endif

#if defined (__GNUC__) && (__GNUC__ >= 3)
static const char	gccpipe[] = "-pipe";
#else
static const char	gccpipe[] = "\0";
#endif

#ifdef	HAVE_SIGNAL_H
typedef void (*cob_sighandler_t) (int);
static cob_sighandler_t		hupsig = NULL;
static cob_sighandler_t		intsig = NULL;
static cob_sighandler_t		qutsig = NULL;
#endif

static const char short_options[] = "hVvECScbmxOgwo:t:I:L:l:D:";

static const struct option long_options[] = {
	{"help", no_argument, NULL, 'h'},
	{"version", no_argument, NULL, 'V'},
/* getopt_long_only has a problem with eg. -xv - remove
	{"verbose", no_argument, NULL, 'v'},
*/
	{"list-reserved", no_argument, NULL, 'R'},
	{"list-intrinsics", no_argument, NULL, 'Q'},
	{"list-mnemonics", no_argument, NULL, 'q'},
	{"save-temps", optional_argument, NULL, '_'},
	{"std", required_argument, NULL, '$'},
	{"conf", required_argument, NULL, '&'},
	{"debug", no_argument, NULL, 'd'},
	{"ext", required_argument, NULL, 'e'},
	{"free", no_argument, &cb_source_format, CB_FORMAT_FREE},
	{"fixed", no_argument, &cb_source_format, CB_FORMAT_FIXED},
	{"static", no_argument, &cb_flag_static_call, 1},
	{"dynamic", no_argument, &cb_flag_static_call, 0},
	{"O2", no_argument, NULL, '2'},
	{"Os", no_argument, NULL, 's'},
	{"MT", required_argument, NULL, '%'},
	{"MF", required_argument, NULL, '@'},
#undef	CB_FLAG
#define	CB_FLAG(var,name,doc)			\
	{"f"name, no_argument, &var, 1},	\
	{"fno-"name, no_argument, &var, 0},
#include "flag.def"
#undef	CB_FLAG
	{"Wall", no_argument, NULL, 'W'},
	{"W", no_argument, NULL, 'Z'},
#undef	CB_WARNDEF
#define	CB_WARNDEF(var,name,wall,doc)		\
	{"W"name, no_argument, &var, 1},	\
	{"Wno-"name, no_argument, &var, 0},
#include "warning.def"
#undef	CB_WARNDEF
	{NULL, 0, NULL, 0}
};

static const char	*cob_cc;				/* gcc */
static char		cob_cflags[COB_SMALL_BUFF];		/* -I... */
static char		cob_libs[COB_MEDIUM_BUFF];		/* -L... -lcob */
static char		cob_define_flags[COB_SMALL_BUFF];	/* -D... */
static const char	*cob_ldflags;
static const char	*cob_copy_dir;

/* cobc functions */

/*
 * Global functions
 */

void
cobc_abort (const char *filename, const int linenum)
{
	fprintf (stderr, "%s:%d: Internal compiler error\n", filename, linenum);
	(void)longjmp (cob_jmpbuf, 1);
}

void
cobc_tree_cast_error (cb_tree x, const char *filen, const int linenum, const int tagnum)
{
	fprintf (stderr, "%s:%d: Invalid type cast from '%s'\n",
		filen, linenum, x ? cb_name (x) : "null");
	fprintf (stderr, "Tag 1 %d Tag 2 %d\n", x ? CB_TREE_TAG(x) : 0,
		tagnum);
	(void)longjmp (cob_jmpbuf, 1);
}

void *
cobc_malloc (const size_t size)
{
	void *mptr;

	mptr = calloc (1, size);
	if (!mptr) {
		fprintf (stderr, "Cannot allocate %d bytes of memory - Aborting\n", (int)size);
		fflush (stderr);
		(void)longjmp (cob_jmpbuf, 1);
	}
	return mptr;
}

void *
cobc_realloc (void *prevptr, const size_t size)
{
	void *mptr;

	mptr = realloc (prevptr, size);
	if (!mptr) {
		fprintf (stderr, "Cannot reallocate %d bytes of memory - Aborting\n", (int)size);
		fflush (stderr);
		(void)longjmp (cob_jmpbuf, 1);
	}
	return mptr;
}

struct cb_text_list *
cb_text_list_add (struct cb_text_list *list, const char *text)
{
	struct cb_text_list *p;
	struct cb_text_list *l;

	p = cobc_malloc (sizeof (struct cb_text_list));
	p->text = strdup (text);
	p->next = NULL;
	if (!list) {
		return p;
	} else {
		for (l = list; l->next; l = l->next) { ; }
		l->next = p;
		return list;
	}
}

size_t
cobc_check_valid_name (char *name)
{
	size_t	n;

	for (n = 0; n < COB_NUM_CSYNS; ++n) {
		if (!strcmp (name, cob_csyns[n])) {
			return 1;
		}
	}
	return 0;
}

/*
 * Local functions
 */

static void
cobc_init_var (char *var, const char *env, const char *def)
{
	char *p = getenv (env);

	if (p) {
		strcpy (var, p);
	} else {
		strcpy (var, def);
	}
}

static void
cobc_check_action (const char *name)
{
	struct stat		st;
	char			buff[COB_SMALL_BUFF];

	if (name && !stat (name, &st)) {
		if (!save_temps) {
			unlink (name);
		} else if (save_temps_dir) {
			memset(buff, 0, sizeof(buff));
			snprintf(buff, sizeof(buff), "%s/%s", save_temps_dir,
     			         name);
			(void)rename (name, buff);
		}
	}
}

static void
cobc_clean_up (int status)
{
	struct filename		*fn;
	struct local_filename	*lf;
	int			i;
	char			buff[COB_SMALL_BUFF];

	if (cb_listing_file) {
		fclose (cb_listing_file);
		cb_listing_file = NULL;
	}
	for (fn = file_list; fn; fn = fn->next) {
		if (fn->need_preprocess
		    && (status || cb_compile_level > CB_LEVEL_PREPROCESS)) {
			cobc_check_action (fn->preprocess);
		}
		if (!save_csrc && fn->need_translate
		    && (status || cb_compile_level > CB_LEVEL_TRANSLATE)) {
			cobc_check_action (fn->translate);
			cobc_check_action (fn->trstorage);
			if (fn->localfile) {
				for (lf = fn->localfile; lf; lf = lf->next) {
					cobc_check_action (lf->local_name);
				}
			} else if (fn->translate) {
				/* If we get syntax errors, we do not
				   know the number of local include files */
				memset (buff, 0, sizeof(buff));
				for (i = 0; i < 30; i++) {
					if (i) {
						snprintf(buff, sizeof(buff),
							 "%s.l%d.h",
							 fn->translate, i);
					} else {
						snprintf(buff, sizeof(buff),
							 "%s.l.h",
							 fn->translate);
					}
					unlink (buff);
				}
			}
		}
		if (fn->need_assemble
		    && (status || cb_compile_level > CB_LEVEL_ASSEMBLE)) {
			cobc_check_action (fn->object);
		}
	}
}

static void
cobc_terminate (const char *str)
{
	fprintf (stderr, "cobc: ");
	fflush (stderr);
	perror (str);
	cobc_clean_up (1);
	exit (1);
}

#ifdef	HAVE_SIGNAL_H
static void
cobc_sig_handler (int sig)
{
	save_temps = 0;
	cobc_clean_up (1);
	switch (sig) {
#ifdef	SIGHUP
	case SIGHUP:
		if ((hupsig != SIG_IGN) && (hupsig != SIG_DFL)) {
			(*hupsig) (SIGHUP);
		}
		break;
#endif
	case SIGINT:
		if ((intsig != SIG_IGN) && (intsig != SIG_DFL)) {
			(*intsig) (SIGINT);
		}
		break;
#ifdef	SIGQUIT
	case SIGQUIT:
		if ((qutsig != SIG_IGN) && (qutsig != SIG_DFL)) {
			(*qutsig) (SIGQUIT);
		}
		break;
#endif
	}
	exit (sig);
}
#endif

/*
 * Command line
 */

static void
cobc_print_version (void)
{
	printf ("cobc (%s) %s.%d\n",
		PACKAGE_NAME, PACKAGE_VERSION, PATCH_LEVEL);
	puts ("Copyright (C) 2001-2009 Keisuke Nishida / Roger While");
	printf ("Built    %s\nPackaged %s\n", cb_oc_build_stamp, octardate);
}

static void
cobc_print_usage (void)
{
	printf ("Usage: cobc [options] file...\n\n");
	puts (_("Options:"));
	puts (_("  --help                Display this message"));
	puts (_("  --version, -V         Display compiler version"));
	puts (_("  -v                    Display the programs invoked by the compiler"));
	puts (_("  -x                    Build an executable program"));
	puts (_("  -m                    Build a dynamically loadable module (default)"));
	puts (_("  -std=<dialect>        Compile for a specific dialect :"));
	puts (_("                          cobol2002   Cobol 2002"));
	puts (_("                          cobol85     Cobol 85"));
	puts (_("                          ibm         IBM Compatible"));
	puts (_("                          mvs         MVS Compatible"));
	puts (_("                          bs2000      BS2000 Compatible"));
	puts (_("                          mf          Micro Focus Compatible"));
	puts (_("                          default     When not specified"));
	puts (_("                        See config/default.conf and config/*.conf"));
	puts (_("  -free                 Use free source format"));
	puts (_("  -fixed                Use fixed source format (default)"));
	puts (_("  -O, -O2, -Os          Enable optimization"));
	puts (_("  -g                    Produce debugging information in the output"));
	puts (_("  -debug                Enable all run-time error checking"));
	puts (_("  -o <file>             Place the output into <file>"));
	puts (_("  -b                    Combine all input files into a single"));
	puts (_("                        dynamically loadable module"));
	puts (_("  -E                    Preprocess only; do not compile, assemble or link"));
	puts (_("  -C                    Translation only; convert COBOL to C"));
	puts (_("  -S                    Compile only; output assembly file"));
	puts (_("  -c                    Compile and assemble, but do not link"));
	puts (_("  -t <file>             Generate and place a program listing into <file>"));
	puts (_("  -I <directory>        Add <directory> to copy/include search path"));
	puts (_("  -L <directory>        Add <directory> to library search path"));
	puts (_("  -l <lib>              Link the library <lib>"));
	puts (_("  -D <define>           Pass <define> to the C compiler"));
	puts (_("  -conf=<file>          User defined dialect configuration - See -std="));
	puts (_("  --list-reserved       Display reserved words"));
	puts (_("  --list-intrinsics     Display intrinsic functions"));
	puts (_("  --list-mnemonics      Display mnemonic names"));
	puts (_("  -save-temps(=<dir>)   Save intermediate files (default current directory)"));
	puts (_("  -MT <target>          Set target file used in dependency list"));
	puts (_("  -MF <file>            Place dependency list into <file>"));
	puts (_("  -ext <extension>      Add default file extension"));
	puts ("");
	puts (_("  -W                    Enable ALL warnings"));
	puts (_("  -Wall                 Enable all warnings except as noted below"));
#undef	CB_WARNDEF
#define	CB_WARNDEF(var,name,wall,doc)		\
	printf ("  -W%-19s %s", name, gettext (doc)); \
	if (!wall) { \
		puts (_(" (NOT set with -Wall)")); \
	} else { \
		printf ("\n"); \
	}
#include "warning.def"
#undef	CB_WARNDEF
	puts ("");
#undef	CB_FLAG
#define	CB_FLAG(var,name,doc)			\
	if (strcmp (name, "static-call"))	\
		printf ("  -f%-19s %s\n", name, gettext (doc));
#include "flag.def"
#undef	CB_FLAG
	puts ("");
}

static void
cobc_options_error (void)
{
	fprintf (stderr, "Only one of options 'E', 'S', 'C' 'c' may be specified\n");
	exit (1);
}

static int
process_command_line (int argc, char *argv[])
{
	int			c, idx;
	enum cob_exception_id	i;
	struct stat		st;
	char			ext[COB_MINI_BUFF];

	/* Enable default I/O exceptions */
	CB_EXCEPTION_ENABLE (COB_EC_I_O) = 1;

	while ((c = getopt_long_only (argc, argv, short_options, long_options, &idx)) >= 0) {
		switch (c) {
		case 0:
			break;
		case '?':
			exit (1);
		case 'h':
			cobc_print_usage ();
			exit (0);
		case 'V':
			cobc_print_version ();
			exit (0);
		case 'R':
			cb_list_reserved ();
			exit (0);
		case 'Q':
			cb_list_intrinsics ();
			exit (0);
		case 'q':
			cb_list_mnemonics ();
			exit (0);

		case 'E':
			if (wants_nonfinal) {
				cobc_options_error ();
			}
			wants_nonfinal = 1;
			cb_compile_level = CB_LEVEL_PREPROCESS;
			break;
		case 'C':
			if (wants_nonfinal) {
				cobc_options_error ();
			}
			wants_nonfinal = 1;
			cb_compile_level = CB_LEVEL_TRANSLATE;
			break;
		case 'S':
			if (wants_nonfinal) {
				cobc_options_error ();
			}
			wants_nonfinal = 1;
			cb_compile_level = CB_LEVEL_COMPILE;
			break;
		case 'c':
			if (wants_nonfinal) {
				cobc_options_error ();
			}
			wants_nonfinal = 1;
			cb_compile_level = CB_LEVEL_ASSEMBLE;
			break;
		case 'b':
			if (cb_flag_main || cb_flag_module) {
				fprintf (stderr, "Only one of options 'm', 'x', 'b' may be specified\n");
				exit (1);
			}
			cb_flag_library = 1;
			break;
		case 'm':
			if (cb_flag_main || cb_flag_library) {
				fprintf (stderr, "Only one of options 'm', 'x', 'b' may be specified\n");
				exit (1);
			}
			cb_flag_module = 1;
			break;
		case 'x':
			if (cb_flag_module || cb_flag_library) {
				fprintf (stderr, "Only one of options 'm', 'x', 'b' may be specified\n");
				exit (1);
			}
			cb_flag_main = 1;
			break;
		case 'v':
			verbose_output = 1;
			break;
		case 'o':
			output_name = strdup (optarg);
			break;

		case 'O':
			strcat (cob_cflags, " -O");
			strcat (cob_cflags, fcopts);
			strcat (cob_cflags, COB_EXTRA_FLAGS);
			optimize_flag = 1;
			break;

		case '2':	/* -O2 */
			strip_output = 1;
#if defined(__hpux) && !defined(__GNUC__)
			strcat (cob_cflags, " -O");
#else
			strcat (cob_cflags, " -O2");
#endif
			strcat (cob_cflags, fcopts);
			strcat (cob_cflags, COB_EXTRA_FLAGS);
			optimize_flag = 2;
			break;

		case 's':	/* -Os */
			strip_output = 1;
#if defined(__hpux) && !defined(__GNUC__)
			strcat (cob_cflags, " -O");
#else
			strcat (cob_cflags, " -Os");
#endif
			strcat (cob_cflags, fcopts);
			strcat (cob_cflags, COB_EXTRA_FLAGS);
			optimize_flag = 2;
			break;

		case 'g':
			save_csrc = 1;
			gflag_set = 1;
			cb_flag_stack_check = 1;
			cb_flag_source_location = 1;
#ifndef _MSC_VER
			strcat (cob_cflags, " -g");
#endif
			break;

		case '$':	/* -std */
			snprintf (ext, COB_MINI_MAX, "%s.conf", optarg);
			if (cb_load_std (ext) != 0) {
				fprintf (stderr, _("Invalid option -std=%s\n"), optarg);
				exit (1);
			}
			break;

		case '&':	/* -conf */
			if (cb_load_conf (optarg, 1, 0) != 0) {
				exit (1);
			}
			break;

		case 'd':	/* -debug */
			/* Turn on all exception conditions */
			for (i = 1; i < COB_EC_MAX; i++) {
				CB_EXCEPTION_ENABLE (i) = 1;
			}
			cb_flag_source_location = 1;
			cb_flag_stack_check = 1;
			break;

		case '_':	/* --save-temps */
			save_temps = 1;
			if (optarg) {
				if (stat (optarg, &st) != 0 || !(S_ISDIR (st.st_mode))) {
					fprintf (stderr, "Warning - '%s' is not a directory, defaulting to current directory\n", optarg);
					fflush (stderr);
				} else {
					save_temps_dir = optarg;
				}
			}
			break;

		case 't':
			cb_listing_file = fopen (optarg, "w");
			if (!cb_listing_file) {
				perror (optarg);
			}
			break;

		case 'D':	/* -D */
#ifdef _MSC_VER
			strcat (cob_define_flags, "/D \"");
			strcat (cob_define_flags, optarg);
			strcat (cob_define_flags, "\" ");
#else
			strcat (cob_define_flags, "-D");
			strcat (cob_define_flags, optarg);
			strcat (cob_define_flags, " ");
#endif
			break;

		case '%':	/* -MT */
			cb_depend_target = strdup (optarg);
			break;

		case '@':	/* -MF */
			cb_depend_file = fopen (optarg, "w");
			if (!cb_depend_file) {
				perror (optarg);
			}
			break;

		case 'I':
#ifdef _MSC_VER
			strcat (cob_define_flags, "/I \"");
			strcat (cob_define_flags, optarg);
			strcat (cob_define_flags, "\" ");
#else
			strcat (cob_define_flags, "-I");
			strcat (cob_define_flags, optarg);
			strcat (cob_define_flags, " ");
#endif
			cb_include_list = cb_text_list_add (cb_include_list, optarg);
			break;

		case 'L':
			strcat (cob_libs, " -L");
			strcat (cob_libs, optarg);
			break;

		case 'l':
			strcat (cob_libs, " -l");
			strcat (cob_libs, optarg);
			break;

		case 'e':
			snprintf (ext, COB_MINI_MAX, ".%s", optarg);
			cb_extension_list = cb_text_list_add (cb_extension_list, ext);
			break;

		case 'w':
#undef	CB_WARNDEF
#define	CB_WARNDEF(var,name,wall,doc)	var = 0;
#include "warning.def"
#undef	CB_WARNDEF
			break;

		case 'W':
#undef	CB_WARNDEF
#define	CB_WARNDEF(var,name,wall,doc)	if (wall) var = 1;
#include "warning.def"
#undef	CB_WARNDEF
			break;

		case 'Z':
#undef	CB_WARNDEF
#define	CB_WARNDEF(var,name,wall,doc)	var = 1;
#include "warning.def"
#undef	CB_WARNDEF
			break;

		default:
			ABORT ();
		}
	}

	if (cb_config_name == NULL) {
		if (cb_load_std ("default.conf") != 0) {
			fprintf (stderr, "Error: failed to load the initial config file\n");
			exit (1);
		}
	}

	if (cb_flag_fold_copy_lower && cb_flag_fold_copy_upper) {
		fprintf (stderr, "Error: Invalid option combination\n");
		exit (1);
	}

#ifdef	__GNUC__
	strcat (cob_cflags, " -Wno-unused -fsigned-char");
#ifdef	HAVE_PSIGN_OPT
	strcat (cob_cflags, " -Wno-pointer-sign");
#endif
#endif

	if (gflag_set) {
		strip_output = 0;
		optimize_flag = 0;
	}
	if (cb_flag_traceall) {
		cb_flag_trace = 1;
		cb_flag_source_location = 1;
	}
	if (cb_flag_source_location) {
		optimize_flag = 0;
	}
#if defined (__GNUC__) && (__GNUC__ >= 3)
	if (strip_output) {
		strcat (cob_cflags, " -fomit-frame-pointer");
	}
#endif

	/* default extension list */
	cb_extension_list = cb_text_list_add (cb_extension_list, ".CPY");
	cb_extension_list = cb_text_list_add (cb_extension_list, ".CBL");
	cb_extension_list = cb_text_list_add (cb_extension_list, ".COB");
	cb_extension_list = cb_text_list_add (cb_extension_list, ".cpy");
	cb_extension_list = cb_text_list_add (cb_extension_list, ".cbl");
	cb_extension_list = cb_text_list_add (cb_extension_list, ".cob");
	cb_extension_list = cb_text_list_add (cb_extension_list, "");

	return optind;
}

static void 
process_env_copy_path (void) 
{
	char	*value;
	char	*token;

	cobcpy = getenv ("COBCPY");
	if (cobcpy == NULL || strlen (cobcpy) == 0) {
		/* env. not defined: nothing to do */
		cobcpy = NULL;
		return;
	}
	
	/* clone value to avoid memory corruption */
	value = strdup (cobcpy);

	/* tokenizing for path sep. */
	token = strtok (value, PATHSEPS);
	while (token) {
		cb_include_list = cb_text_list_add (cb_include_list, token);
		token = strtok (NULL, PATHSEPS);
	}

	/* release memory of clone */
	free (value);
	return;
}

static void
file_basename (const char *filename, char *buff)
{
	const char	*startp;
	const char	*endp;
	size_t		len;

	/* Remove directory name */
	startp = strrchr (filename, '/');
	if (startp) {
		startp++;
	} else {
		startp = filename;
	}

	/* Remove extension */
	endp = strrchr (filename, '.');
	if (endp > startp) {
		len = endp - startp;
	} else {
		len = strlen (startp);
	}

	/* Copy base name */
	strncpy (buff, startp, len);
	buff[len] = '\0';
}

static const char *
file_extension (const char *filename)
{
	const char *p;

	p = strrchr (filename, '.');
	if (p) {
		return p + 1;
	} else {
		return "";
	}
}

static char *
cobc_temp_name (const char *ext)
{
	char	buff[COB_MEDIUM_BUFF];
#ifdef _WIN32
	char	temp[MAX_PATH];

	GetTempPath (MAX_PATH, temp);
	GetTempFileName (temp, "cob", 0, buff);
	DeleteFile (buff);
	strcpy (buff + strlen (buff) - 4, ext);	/* replace ".tmp" by EXT */
#else
	snprintf(buff, sizeof(buff), "%s/cob%d_%d%s", cob_tmpdir,
	 	 cob_process_id, cob_iteration, ext);
#endif
	return strdup (buff);
}

static struct filename *
process_filename (const char *filename)
{
	const char	*extension;
	struct filename	*fn;
	struct filename	*ffn;
	struct stat	st;
	char		basename[COB_SMALL_BUFF];

	if (stat (filename, &st) != 0) {
		cobc_terminate (filename);
	}
	file_basename (filename, basename);
	if (cobc_check_valid_name (basename)) {
		fprintf (stderr, "Invalid file base name - %s\n", basename);
		return NULL;
	}
	fn = cobc_malloc (sizeof (struct filename));
	fn->need_preprocess = 1;
	fn->need_translate = 1;
	fn->need_assemble = 1;
	fn->next = NULL;

	if (!file_list) {
		file_list = fn;
	} else {
		for (ffn = file_list; ffn->next; ffn = ffn->next)
			;
		ffn->next = fn;
	}

	fn->demangle_source =  cb_encode_program_id (basename);
	extension = file_extension (filename);

	/* Check input file type */
	if (strcmp (extension, "i") == 0) {
		/* already preprocessed */
		fn->need_preprocess = 0;
	} else if (strcmp (extension, "c") == 0 || strcmp (extension, "s") == 0) {
		/* already compiled */
		fn->need_preprocess = 0;
		fn->need_translate = 0;
#ifdef _MSC_VER
	} else if (strcmp (extension, "obj") == 0 ||
		   strcmp (extension, "lib") == 0) {
#else
	} else if (strcmp (extension, "o") == 0) {
#endif
		/* already assembled */
		fn->need_preprocess = 0;
		fn->need_translate = 0;
		fn->need_assemble = 0;
	}

	/* Set source filename */
	fn->source = cobc_malloc (strlen (filename) + 3);
	strcpy (fn->source, filename);

	/* Set preprocess filename */
	if (!fn->need_preprocess) {
		fn->preprocess = strdup (fn->source);
	} else if (output_name && cb_compile_level == CB_LEVEL_PREPROCESS) {
		fn->preprocess = strdup (output_name);
	} else if (save_temps) {
		size_t len = (strlen(basename) + 5UL);
		fn->preprocess = cobc_malloc(len);
		snprintf(fn->preprocess, len, "%s.i", basename);
	} else {
		fn->preprocess = cobc_temp_name (".cob");
	}

	/* Set translate filename */
	if (!fn->need_translate) {
		fn->translate = strdup (fn->source);
	} else if (output_name && cb_compile_level == CB_LEVEL_TRANSLATE) {
		fn->translate = strdup (output_name);
	} else if (save_csrc || save_temps ||
		   cb_compile_level == CB_LEVEL_TRANSLATE) {
     		size_t len = (strlen(basename) + 5UL);
		fn->translate = cobc_malloc(len);
		snprintf(fn->translate, len, "%s.c", basename);
	} else {
		fn->translate = cobc_temp_name (".c");
	}

	/* Set storage filename */
	if (fn->need_translate) {
		size_t len = (strlen(fn->translate) + 5UL);
		fn->trstorage = cobc_malloc(len);
		snprintf(fn->trstorage, len, "%s.h", fn->translate);
	}

	/* Set object filename */
	if (!fn->need_assemble) {
		fn->object = strdup (fn->source);
	} else if (output_name && cb_compile_level == CB_LEVEL_ASSEMBLE) {
		fn->object = strdup (output_name);
	} else if (save_temps || cb_compile_level == CB_LEVEL_ASSEMBLE) {
		size_t len = (strlen(basename) + 5UL);
		fn->object = cobc_malloc(len);
#ifdef	_MSC_VER
		snprintf(fn->object, len, "%s.obj", basename);
#else
		snprintf(fn->object, len, "%s.o", basename);
#endif
	} else {
#ifdef	_MSC_VER
		size_t len = (strlen(basename) + 5UL);
		fn->object = cobc_malloc(len);
		snprintf(fn->object, len, "%s.obj", basename);
#else
		fn->object = cobc_temp_name (".o");
#endif
	}

	cob_iteration++;

	return fn;
}

static int
process (const char *cmd)
{
	char	*p;
	char	*buffptr;
	size_t	clen;
	int	ret;
	char	buff[COB_MEDIUM_BUFF];

	if (strchr (cmd, '$') == NULL) {
		if (verbose_output) {
			fprintf (stderr, "%s\n", (char *)cmd);
		}
		return system (cmd);
	}
	clen = strlen (cmd) + 32;
	if (clen > COB_MEDIUM_BUFF) {
		buffptr = cobc_malloc (clen);
	} else {
		buffptr = buff;
	}
	p = buffptr;
	/* quote '$' */
	for (; *cmd; cmd++) {
		if (*cmd == '$') {
			p += sprintf (p, "\\$");
		} else {
			*p++ = *cmd;
		}
	}
	*p = 0;

	if (verbose_output) {
		fprintf (stderr, "%s\n", buffptr);
	}
	ret = system (buffptr);
	if (buffptr != buff) {
		free (buffptr);
	}
	return ret;
}

static int
preprocess (struct filename *fn)
{
	struct cb_text_list	*l;
	int			i;
	char			line[COB_MEDIUM_BUFF];

	errorcount = 0;

	if (output_name || cb_compile_level > CB_LEVEL_PREPROCESS) {
		ppout = fopen (fn->preprocess, "w");
		if (!ppout) {
			cobc_terminate (fn->preprocess);
		}
	} else {
		ppout = stdout;
	}

	if (ppopen (fn->source, NULL) != 0) {
		if (ppout != stdout) {
			fclose (ppout);
			if (fn->preprocess) {
				unlink (fn->preprocess);
			}
		}
		exit (1);
	}

	if (verbose_output) {
		fprintf (stderr, "preprocessing %s into %s\n", fn->source, fn->preprocess);
	}

	ppparse ();

	if (ppout != stdout) {
		fclose (ppout);
		if (cb_listing_file) {
			ppout = fopen (fn->preprocess, "r");
			if (ppout) {
				memset (line, 0, sizeof (line));
				fprintf (cb_listing_file,
					"# Generated by %s.%d\n",
					PACKAGE_STRING, PATCH_LEVEL);
				fprintf (cb_listing_file,
					"# Built        %s\n", cb_oc_build_stamp);
				fprintf (cb_listing_file,
					"# Packaged     %s\n", octardate);
				fprintf (cb_listing_file,
					"# Environment\n");
				fprintf (cb_listing_file,
					"#  TMPDIR :    %s\n", cob_tmpdir);
				fprintf (cb_listing_file,
					"#  COBCPY :    %s\n",
					cobcpy != NULL ? cobcpy : "is not set");
				fprintf (cb_listing_file,
					"# Command :    ");
				for (i = 0; i < cb_saveargc; i++) {
					fprintf (cb_listing_file, "%s ", cb_saveargv[i]);
				}
				fprintf (cb_listing_file, "\n#\n");
				while (fgets (line, COB_MEDIUM_BUFF, ppout) != NULL) {
					if (cb_source_format != CB_FORMAT_FIXED) {
						fprintf (cb_listing_file,
							"%s", line);
					} else {
						if (line[0] == '\n') {
							fprintf (cb_listing_file,
								"%s", line);
						} else if (line[0] == ' ' &&
							   line[1] == '\n') {
							fprintf (cb_listing_file,
								"\n");
						} else if (line[0] == ' ') {
							fprintf (cb_listing_file,
								"          %s", line);
						} else if (line[0] == '#') {
							fprintf (cb_listing_file,
								"%s", line);
						} else if (line[0] == 0) {
							fprintf (cb_listing_file,
								"%s", line);
						} else {
							fprintf (cb_listing_file,
								"       %s", line);
						}
					}
					memset (line, 0, sizeof (line));
				}
				fclose (ppout);
			}
		}
	}
	fclose (ppin);

	if (errorcount > 0) {
		return -1;
	}

	/* Output dependency list */
	if (cb_depend_file) {
		if (!cb_depend_target) {
			fputs (_("-MT must be given to specify target file\n"), stderr);
			exit (1);
		}
		fprintf (cb_depend_file, "%s: \\\n", cb_depend_target);
		for (l = cb_depend_list; l; l = l->next) {
			fprintf (cb_depend_file, " %s%s\n", l->text, l->next ? " \\" : "");
		}
		for (l = cb_depend_list; l; l = l->next) {
			fprintf (cb_depend_file, "%s:\n", l->text);
		}
		fclose (cb_depend_file);
	}

	return 0;
}

static struct cb_program *
program_list_reverse (struct cb_program *p)
{
	struct cb_program	*next;
	struct cb_program	*last = NULL;

	for (; p; p = next) {
		next = p->next_program;
		p->next_program = last;
		last = p;
	}
	return last;
}

static int
process_translate (struct filename *fn)
{
	struct cb_program	*p;
	struct cb_program	*q;
	struct cb_program	*r;
	struct handler_struct	*hstr1;
	struct handler_struct	*hstr2;
	struct local_filename	*lf;
	int			ret;
	int			i;

	/* initialize */
	cb_source_file = NULL;
	cb_source_line = 0;
	cb_init_constants ();
	cb_init_reserved ();

	/* open the input file */
	yyin = fopen (fn->preprocess, "r");
	if (!yyin) {
		cobc_terminate (fn->preprocess);
	}

	/* parse */
	ret = yyparse ();
	fclose (yyin);
	if (ret) {
		return ret;
	}
	if (cb_flag_syntax_only || current_program->entry_list == NULL) {
		return 0;
	}

	/* Set up USE GLOBAL handlers */
	p = current_program;
	for (q = p; q; q = q->next_program) {
		q->global_file_list = cb_list_reverse (q->global_file_list);
		if (q->nested_level) {
			for (r = q->next_program; r; r = r->next_program) {
				if (r->nested_level >= q->nested_level) {
					continue;
				}
				for (i = COB_OPEN_INPUT; i <= COB_OPEN_EXTEND; i++) {
					hstr1 = &q->global_handler[i];
					hstr2 = &r->global_handler[i];
					if (!hstr1->handler_label &&
					    hstr2->handler_label &&
					    hstr2->handler_label->is_global) {
						hstr1->handler_label = hstr2->handler_label;
						hstr1->handler_prog = r;
					}
				}
				if (!r->nested_level) {
					break;
				}
			}
		}
	}

	if (verbose_output) {
		fprintf (stderr, "translating %s into %s\n", fn->preprocess, fn->translate);
	}

	/* open the output file */
	yyout = fopen (fn->translate, "w");
	if (!yyout) {
		cobc_terminate (fn->translate);
	}

	/* open the common storage file */
	cb_storage_file_name = fn->trstorage;
	cb_storage_file = fopen (cb_storage_file_name, "w");
	if (!cb_storage_file) {
		cobc_terminate (cb_storage_file_name);
	}

	p = program_list_reverse (current_program);

	/* set up local storage files */
	ret = 1;
	for (q = p; q; q = q->next_program, ret++) {
		size_t len;
		lf = cobc_malloc(sizeof(struct local_filename));
  		len = (strlen(fn->translate) + 9UL);
		lf->local_name = cobc_malloc(len);
		if (q == p && !q->next_program) {
			snprintf(lf->local_name, len, "%s.l.h", fn->translate);
		} else {
			snprintf(lf->local_name, len, "%s.l%d.h", fn->translate,
      			         ret);
		}
		lf->local_fp = fopen (lf->local_name, "w");
		if (!lf->local_fp) {
			cobc_terminate (lf->local_name);
		}
		q->local_storage_file = lf->local_fp;
		q->local_storage_name = lf->local_name;
		lf->next = fn->localfile;
		fn->localfile = lf;
	}

	/* translate to C */
	codegen (p, 0);

	/* close the files */
	fclose (cb_storage_file);
	fclose (yyout);
	for (q = p; q; q = q->next_program) {
		fclose (q->local_storage_file);
	}
	return 0;
}

static int
process_compile (struct filename *fn)
{
	char buff[COB_MEDIUM_BUFF];
	char name[COB_MEDIUM_BUFF];

	if (output_name) {
		strcpy (name, output_name);
	} else {
		file_basename (fn->source, name);
#ifndef _MSC_VER
		strcat (name, ".s");
#endif
	}
#ifdef _MSC_VER
	snprintf(buff, sizeof(buff), gflag_set ?
		"%s /c %s %s /Od /MDd /Zi /FR /c /Fa%s /Fo%s %s" :
		"%s /c %s %s /MD /c /Fa%s /Fo%s %s",
			cob_cc, cob_cflags, cob_define_flags, name,
			name, fn->translate);
#else
	snprintf(buff, sizeof(buff), "%s %s -S -o %s %s %s %s", cob_cc,
		 gccpipe, name, cob_cflags, cob_define_flags, fn->translate);
#endif
	return process (buff);
}

static int
process_assemble (struct filename *fn)
{
	char buff[COB_MEDIUM_BUFF];

#ifdef _MSC_VER
	snprintf(buff, sizeof(buff), gflag_set ?
		"%s /c %s %s /Od /MDd /Zi /FR /Fo%s %s" :
		"%s /c %s %s /MD /Fo%s %s",
			cob_cc, cob_cflags, cob_define_flags,
			fn->object, fn->translate);
#else
	if (cb_compile_level == CB_LEVEL_MODULE ||
	    cb_compile_level == CB_LEVEL_LIBRARY) {
		snprintf(buff, sizeof(buff), "%s %s -c %s %s %s -o %s %s",
			 cob_cc, gccpipe, cob_cflags, cob_define_flags,
			 COB_PIC_FLAGS, fn->object, fn->translate);
	} else {
		snprintf(buff, sizeof(buff), "%s %s -c %s %s -o %s %s",
			 cob_cc, gccpipe, cob_cflags, cob_define_flags,
			 fn->object, fn->translate);
	}
#endif
	return process (buff);
}

static int
process_module_direct (struct filename *fn)
{
	int	ret;
	char	buff[COB_MEDIUM_BUFF];
	char	name[COB_MEDIUM_BUFF];

	if (output_name) {
		strcpy (name, output_name);
#ifndef _MSC_VER
		if (strchr (output_name, '.') == NULL) {
			strcat (name, ".");
			strcat (name, COB_MODULE_EXT);
		}
#endif
	} else {
		file_basename (fn->source, name);
#ifndef _MSC_VER
		strcat (name, ".");
		strcat (name, COB_MODULE_EXT);
#endif
	}
#ifdef _MSC_VER
	snprintf(buff, sizeof(buff), gflag_set ?
		"%s %s %s /Od /MDd /LDd /Zi /FR /Fe%s /Fo%s %s %s %s" :
		"%s %s %s /MD /LD /Fe%s /Fo%s %s %s %s",
			cob_cc, cob_cflags, cob_define_flags, name, name,
			cob_ldflags, fn->translate, cob_libs);
	ret = process (buff);
#if _MSC_VER >= 1400
	/* Embedding manifest */
	if (ret == 0) {
		snprintf(buff, sizeof(buff), "mt /manifest %s.dll.manifest /outputresource:%s.dll;#2", name, name);
		ret = process (buff);
	}
#endif
#else	/* _MSC_VER */
	snprintf(buff, sizeof(buff), "%s %s %s %s %s %s %s %s -o %s %s %s",
		 cob_cc, gccpipe, cob_cflags, cob_define_flags, COB_SHARED_OPT,
		 cob_ldflags, COB_PIC_FLAGS, COB_EXPORT_DYN, name,
		 fn->translate, cob_libs);
	ret = process (buff);
#ifdef	COB_STRIP_CMD
	if (strip_output && ret == 0) {
		snprintf(buff, sizeof(buff), "%s %s", COB_STRIP_CMD, name);
		ret = process (buff);
	}
#endif
#endif	/* _MSC_VER */
	return ret;
}

static int
process_module (struct filename *fn)
{
	int	ret;
	char	buff[COB_MEDIUM_BUFF];
	char	name[COB_MEDIUM_BUFF];

	if (output_name) {
		strcpy (name, output_name);
#ifndef _MSC_VER
		if (strchr (output_name, '.') == NULL) {
			strcat (name, ".");
			strcat (name, COB_MODULE_EXT);
		}
#endif
	} else {
		file_basename (fn->source, name);
		strcat (name, ".");
		strcat (name, COB_MODULE_EXT);
	}
#ifdef _MSC_VER
	snprintf(buff, sizeof(buff), gflag_set ?
		"%s /Od /MDd /LDd /Zi /FR /Fe%s %s %s %s" :
		"%s /MD /LD /Fe%s %s %s %s",
			cob_cc, name, cob_ldflags, fn->object, cob_libs);
	ret = process (buff);
#if _MSC_VER >= 1400
	/* Embedding manifest */
	if (ret == 0) {
		snprintf(buff, sizeof(buff), "mt /manifest %s.dll.manifest /outputresource:%s.dll;#2", name, name);
		ret = process (buff);
	}
#endif
#else	/* _MSC_VER */
	snprintf(buff, sizeof(buff), "%s %s %s %s %s %s -o %s %s %s",
		 cob_cc, gccpipe, COB_SHARED_OPT, cob_ldflags, COB_PIC_FLAGS,
		 COB_EXPORT_DYN, name, fn->object, cob_libs);
	ret = process (buff);
#ifdef	COB_STRIP_CMD
	if (strip_output && ret == 0) {
		snprintf(buff, sizeof(buff), "%s %s", COB_STRIP_CMD, name);
		ret = process (buff);
	}
#endif
#endif	/* _MSC_VER */
	return ret;
}

static int
process_library (struct filename *l)
{
	char		*buffptr;
	char		*objsptr;
	struct filename	*f;
	size_t		bufflen;
	int		ret;
	char		buff[COB_MEDIUM_BUFF];
	char		name[COB_MEDIUM_BUFF];
	char		objs[COB_MEDIUM_BUFF] = "\0";

	bufflen = 0;
	for (f = l; f; f = f->next) {
		bufflen += strlen (f->object) + 2;
	}
	if (bufflen >= COB_MEDIUM_BUFF) {
		objsptr = cobc_malloc (bufflen);
	} else {
		objsptr = objs;
	}
	for (f = l; f; f = f->next) {
		strcat (objsptr, f->object);
		strcat (objsptr, " ");
	}

	if (output_name) {
		strcpy (name, output_name);
#ifndef _MSC_VER
		if (strchr (output_name, '.') == NULL) {
			strcat (name, ".");
			strcat (name, COB_MODULE_EXT);
		}
#endif
	} else {
		file_basename (l->source, name);
#ifndef _MSC_VER
		strcat (name, ".");
		strcat (name, COB_MODULE_EXT);
#endif
	}

	bufflen = strlen (cob_cc) + strlen (gccpipe) + strlen (cob_ldflags)
			+ strlen (COB_EXPORT_DYN) + strlen (COB_SHARED_OPT)
			+ strlen (name) + strlen (objsptr) + strlen (cob_libs)
			+ strlen (COB_PIC_FLAGS) + 16;
	if (bufflen >= COB_MEDIUM_BUFF) {
		buffptr = cobc_malloc (bufflen);
	} else {
		buffptr = buff;
	}

#ifdef _MSC_VER
	snprintf(buff, sizeof(buff), gflag_set ?
		"%s /Od /MDd /LDd /Zi /FR /Fe%s %s %s %s" :
		"%s /MD /LD /Fe%s %s %s %s",
			cob_cc, name, cob_ldflags, objsptr, cob_libs);
	ret = process (buff);
#if _MSC_VER >= 1400
	/* Embedding manifest */
	if (ret == 0) {
		snprintf(buff, sizeof(buff), "mt /manifest %s.dll.manifest /outputresource:%s.dll;#2", name, name);
		ret = process (buff);
	}
#endif
#else	/* _MSC_VER */
	sprintf (buffptr, "%s %s %s %s %s %s -o %s %s %s",
		 cob_cc, gccpipe, COB_SHARED_OPT, cob_ldflags, COB_PIC_FLAGS,
		 COB_EXPORT_DYN, name, objsptr, cob_libs);
	ret = process (buffptr);
#ifdef	COB_STRIP_CMD
	if (strip_output && ret == 0) {
		snprintf(buff, sizeof(buff), "%s %s", COB_STRIP_CMD, name);
		ret = process (buff);
	}
#endif
#endif	/* _MSC_VER */
	return ret;
}

static int
process_link (struct filename *l)
{
	char		*buffptr;
	char		*objsptr;
	struct filename	*f;
	size_t		bufflen;
	int		ret;
	char		buff[COB_MEDIUM_BUFF];
	char		name[COB_MEDIUM_BUFF];
	char		objs[COB_MEDIUM_BUFF] = "\0";

	bufflen = 0;
	for (f = l; f; f = f->next) {
		bufflen += strlen (f->object) + 2;
	}
	if (bufflen >= COB_MEDIUM_BUFF) {
		objsptr = cobc_malloc (bufflen);
	} else {
		objsptr = objs;
	}
	for (f = l; f; f = f->next) {
		strcat (objsptr, f->object);
		strcat (objsptr, " ");
	}

	if (output_name) {
		strcpy (name, output_name);
	} else {
		file_basename (l->source, name);
	}

	bufflen = strlen (cob_cc) + strlen (gccpipe) + strlen (cob_ldflags)
			+ strlen (COB_EXPORT_DYN) + strlen (name)
			+ strlen (objsptr) + strlen (cob_libs) + 16;
	if (bufflen >= COB_MEDIUM_BUFF) {
		buffptr = cobc_malloc (bufflen);
	} else {
		buffptr = buff;
	}
#ifdef _MSC_VER
	snprintf(buff, sizeof(buff), gflag_set ?
		"%s /Od /MDd /Zi /FR /Fe%s %s %s %s" :
		"%s /MD /Fe%s %s %s %s",
			cob_cc, name, cob_ldflags, objsptr, cob_libs);
	ret = process (buff);
#if _MSC_VER >= 1400
	/* Embedding manifest */
	if (ret == 0) {
		snprintf(buff, sizeof(buff), "mt /manifest %s.exe.manifest /outputresource:%s.exe;#2", name, name);
		ret = process (buff);
	}
#endif
#else	/* _MSC_VER */
	sprintf (buffptr, "%s %s %s %s -o %s %s %s",
		 cob_cc, gccpipe, cob_ldflags, COB_EXPORT_DYN, name,
		 objsptr, cob_libs);

	ret = process (buffptr);
#ifdef	__hpux
	if (ret == 0) {
		snprintf(buff, sizeof(buff), "chatr -s +s enable %s%s 1>/dev/null 2>&1", name, COB_EXEEXT);
		process (buff);
	}
#endif
#ifdef	COB_STRIP_CMD
	if (strip_output && ret == 0) {
		snprintf(buff, sizeof(buff), "%s %s%s", COB_STRIP_CMD, name, COB_EXEEXT);
		ret = process (buff);
	}
#endif
#endif	/* _MSC_VER */
	return ret;
}

int
main (int argc, char *argv[])
{
	struct filename		*fn;
	char			*p;
	int			status = 1;
	int			year;
	int			day;
	char			month[32];
	char			buff[COB_SMALL_BUFF];

#ifdef	HAVE_SIGNAL_H
	if ((intsig = signal (SIGINT, cobc_sig_handler)) == SIG_IGN) {
		(void)signal (SIGINT, SIG_IGN);
	}
#ifdef	SIGHUP
	if ((hupsig = signal (SIGHUP, cobc_sig_handler)) == SIG_IGN) {
		(void)signal (SIGHUP, SIG_IGN);
	}
#endif
#ifdef	SIGQUIT
	if ((qutsig = signal (SIGQUIT, cobc_sig_handler)) == SIG_IGN) {
		(void)signal (SIGQUIT, SIG_IGN);
	}
#endif
#endif

	cb_saveargc = argc;
	cb_saveargv = argv;

#ifdef	HAVE_SETLOCALE
	setlocale (LC_ALL, "");
#endif

#ifdef	ENABLE_NLS
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
#endif

#ifndef _WIN32
	cob_process_id = getpid ();
#endif

	/* Initialize global variables */
	memset (buff, 0, sizeof(buff));
	memset (month, 0, sizeof(month));
	day = 0;
	year = 0;
	sscanf (__DATE__, "%s %d %d", month, &day, &year);
	if (day && year) {
		snprintf(buff, sizeof(buff), "%s %2.2d %4.4d %s", month, day, year, __TIME__);
	} else {
		snprintf(buff, sizeof(buff), "%s %s", __DATE__, __TIME__);
	}
	cb_oc_build_stamp = cobc_malloc (strlen (buff) + 1);
	strcpy (cb_oc_build_stamp, buff);

	output_name = NULL;

	if ((p = getenv ("TMPDIR")) != NULL) {
		cob_tmpdir = p;
	} else if ((p = getenv ("TMP")) != NULL) {
		cob_tmpdir = p;
		snprintf(buff, sizeof(buff), "TMPDIR=%s", p);
		p = strdup (buff);
		putenv (p);
	} else {
		cob_tmpdir = "/tmp";
		putenv ((char *)"TMPDIR=/tmp");
	}
	cob_cc = getenv ("COB_CC");
	if (cob_cc == NULL) {
		cob_cc = COB_CC;
	}
	cobc_init_var (cob_cflags, "COB_CFLAGS", COB_CFLAGS);
	cobc_init_var (cob_libs, "COB_LIBS", COB_LIBS);
	cob_ldflags = getenv ("COB_LDFLAGS");
	if (cob_ldflags == NULL) {
		cob_ldflags = COB_LDFLAGS;
	}
	cob_config_dir = getenv ("COB_CONFIG_DIR");
	if (cob_config_dir == NULL) {
		cob_config_dir = COB_CONFIG_DIR;
	}
	cob_copy_dir = getenv ("COB_COPY_DIR");
	if (cob_copy_dir == NULL) {
		cob_copy_dir = COB_COPY_DIR;
	}
	memset (cob_define_flags, 0, sizeof (cob_define_flags));

	p = getenv ("COB_LDADD");
	if (p) {
		strcat (cob_libs, " ");
		strcat (cob_libs, p);
	}
	p = getenv ("COB_EBCDIC");
	if (p && (*p == 'F' || *p == 'f')) {
		alt_ebcdic = 1;
	}

	/* Process command line arguments */
	iargs = process_command_line (argc, argv);

	/* Check the filename */
	if (iargs == argc) {
		fprintf (stderr, "cobc: No input files\n");
		exit (1);
	}

	/* processes COBCPY environment variable */
	process_env_copy_path ();

	cb_include_list = cb_text_list_add (cb_include_list, cob_copy_dir);
	
	file_list = NULL;

	if (setjmp (cob_jmpbuf) != 0) {
		fprintf (stderr, "Aborting compile of %s at line %d\n",
			 cb_source_file, cb_source_line);
		fflush (stderr);
		if (yyout) {
			fflush (yyout);
		}
		if (cb_storage_file) {
			fflush (cb_storage_file);
		}
		status = 1;
		cobc_clean_up (status);
		return status;
	}

	/* Defaults are set here */
	if (!cb_flag_syntax_only) {
		if (!wants_nonfinal) {
			if (cb_flag_main) {
				cb_compile_level = CB_LEVEL_EXECUTABLE;
			}
			if (cb_flag_module) {
				cb_compile_level = CB_LEVEL_MODULE;
			}
			if (cb_flag_library) {
				cb_compile_level = CB_LEVEL_LIBRARY;
			}
		}
		if (cb_compile_level == 0 && !wants_nonfinal) {
			cb_compile_level = CB_LEVEL_MODULE;
			cb_flag_module = 1;
		}
		if (wants_nonfinal && cb_compile_level != CB_LEVEL_PREPROCESS &&
		    !cb_flag_main && !cb_flag_module && !cb_flag_library) {
			cb_flag_module = 1;
		}
	} else {
			cb_compile_level = CB_LEVEL_TRANSLATE;
	}

	if (output_name && cb_compile_level < CB_LEVEL_LIBRARY &&
	    (argc - iargs) > 1) {
		fprintf (stderr, "cobc: -o option invalid in this combination\n");
		exit (1);
	}
	if (cb_flag_sign_ascii && cb_flag_sign_ebcdic) {
		fprintf (stderr, "Only one of -fsign-ascii or -fsign-ebcdic may be specified\n");
		exit (1);
	}
	if (cb_flag_sign_ascii) {
		cb_display_sign = COB_DISPLAY_SIGN_ASCII;
	}
	if (cb_flag_sign_ebcdic) {
		cb_display_sign = COB_DISPLAY_SIGN_EBCDIC;
	}
	if (cb_flag_notrunc) {
		cb_binary_truncate = 0;
		cb_pretty_display = 0;
	}

	while (iargs < argc) {
		fn = process_filename (argv[iargs++]);
		if (!fn) {
			status = 1;
			cobc_clean_up (status);
			return status;
		}
		/* Preprocess */
		if (cb_compile_level >= CB_LEVEL_PREPROCESS && fn->need_preprocess) {
			if (preprocess (fn) != 0) {
				cobc_clean_up (status);
				return status;
			}
		}
	}
	for (fn = file_list; fn; fn = fn->next) {
		cb_id = 1;
		cb_attr_id = 1;
		cb_literal_id = 1;
		cb_field_id = 1;
		cb_storage_id = 1;
		iparams++;
		demangle_name = fn->demangle_source;
		if (iparams > 1 && cb_compile_level == CB_LEVEL_EXECUTABLE &&
		    !cb_flag_syntax_only) {
			local_level = cb_compile_level;
			cb_flag_main = 0;
			cb_compile_level = CB_LEVEL_ASSEMBLE;
		}
		/* Translate */
		if (cb_compile_level >= CB_LEVEL_TRANSLATE && fn->need_translate) {
			if (process_translate (fn) != 0) {
				cobc_clean_up (status);
				return status;
			}
		}
		if (cb_flag_syntax_only) {
			continue;
		}

		/* Compile */
		if (cb_compile_level == CB_LEVEL_COMPILE) {
			if (process_compile (fn) != 0) {
				cobc_clean_up (status);
				return status;
			}
		}

		/* Build module */
		if (cb_compile_level == CB_LEVEL_MODULE && fn->need_assemble) {
			if (process_module_direct (fn) != 0) {
				cobc_clean_up (status);
				return status;
			}
		} else {
			/* Assemble */
			if (cb_compile_level >= CB_LEVEL_ASSEMBLE && fn->need_assemble) {
				if (process_assemble (fn) != 0) {
					cobc_clean_up (status);
					return status;
				}
			}

			/* Build module */
			if (cb_compile_level == CB_LEVEL_MODULE) {
				if (process_module (fn) != 0) {
					cobc_clean_up (status);
					return status;
				}
			}
		}
	}

	if (!cb_flag_syntax_only) {
		/* Link */
		if (local_level == CB_LEVEL_EXECUTABLE) {
			cb_compile_level = CB_LEVEL_EXECUTABLE;
			cb_flag_main = 1;
		}
		if (cb_compile_level == CB_LEVEL_LIBRARY) {
			if (process_library (file_list) != 0) {
				cobc_clean_up (status);
				return status;
			}
		} else if (cb_compile_level == CB_LEVEL_EXECUTABLE) {
			if (process_link (file_list) != 0) {
				cobc_clean_up (status);
				return status;
			}
		}
	}

	/* We have successfully completed */
	status = 0;
	cobc_clean_up (status);

	return status;
}
