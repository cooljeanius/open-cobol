/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 26 "parser.y"

#include "config.h"

#include <stdlib.h>
#include <string.h>

#include "cobc.h"
#include "tree.h"

#define yyerror			cb_error
#define YYDEBUG			1
#define YYERROR_VERBOSE		1

#define PENDING(x)		cb_warning (_("'%s' not implemented"), x)

#define emit_statement(x) \
  current_program->exec_list = cb_cons (x, current_program->exec_list)

#define push_expr(type, node) \
  current_expr = cb_build_list (cb_int (type), node, current_expr)

#define TERM_NONE		0
#define TERM_ACCEPT		1
#define TERM_ADD		2
#define TERM_CALL		3
#define TERM_COMPUTE		4
#define TERM_DELETE		5
#define TERM_DISPLAY		6
#define TERM_DIVIDE		7
#define TERM_EVALUATE		8
#define TERM_IF			9
#define TERM_MULTIPLY		10
#define TERM_PERFORM		11
#define TERM_READ		12
#define TERM_RECEIVE		13
#define TERM_RETURN		14
#define TERM_REWRITE		15
#define TERM_SEARCH		16
#define TERM_START		17
#define TERM_STRING		18
#define TERM_SUBTRACT		19
#define TERM_UNSTRING		20
#define TERM_WRITE		21
#define TERM_MAX		22

/* Global variables */

struct cb_program		*current_program = NULL;
struct cb_statement		*current_statement = NULL;
struct cb_label			*current_section = NULL;
struct cb_label			*current_paragraph = NULL;
size_t				functions_are_all = 0;
int				non_const_word = 0;

/* Local variables */

static struct cb_statement	*main_statement;

static cb_tree			current_expr;
static struct cb_field		*current_field;
static struct cb_field		*description_field;
static struct cb_file		*current_file;

static enum cb_storage		current_storage;

static size_t			check_unreached = 0;
static int			call_mode;
static int			size_mode;

static cb_tree			perform_stack = NULL;
static cb_tree			qualifier = NULL;

static cb_tree			fgc;
static cb_tree			bgc;
static cb_tree			scroll;
static cb_tree			save_tree_1;
static cb_tree			save_tree_2;
static cb_tree			dummy_tree;
static size_t			in_declaratives = 0;
static size_t			current_linage = 0;
static size_t			prog_end = 0;
static size_t			use_global_ind = 0;
static size_t			samearea = 1;
static size_t			organized_seen = 0;
static size_t			inspect_keyword = 0;
static int			next_label_id = 0;
static int			eval_level = 0;
static int			eval_inc = 0;
static int			eval_inc2 = 0;
static int			depth = 0;
static int			dispattrs = 0;
static struct cb_file		*linage_file;
static cb_tree			next_label_list = NULL;
static char			*stack_progid[32];
static int			term_array[TERM_MAX];
static int			eval_check[64][64];

/* Static functions */

static void
BEGIN_STATEMENT (const char *name, const size_t term)
{
	if (cb_warn_unreachable && check_unreached) {
		cb_warning (_("Unreachable statement"));
	}
	current_statement = cb_build_statement ((char *)name);
	CB_TREE (current_statement)->source_file = (unsigned char *)cb_source_file;
	CB_TREE (current_statement)->source_line = cb_source_line;
	emit_statement (CB_TREE (current_statement));
	if (term) {
		term_array[term]++;
	}
	main_statement = current_statement;
}

static void
BEGIN_IMPLICIT_STATEMENT (void)
{
	current_statement = cb_build_statement (NULL);
	main_statement->body = cb_list_add (main_statement->body,
					    CB_TREE (current_statement));
}

static void
emit_entry (const char *name, const int encode, cb_tree using_list)
{
	cb_tree		l;
	cb_tree		label;
	cb_tree		x;
	struct cb_field	*f;
	int		parmnum;
	char		buff[256];

	sprintf (buff, "E$%s", name);
	label = cb_build_label (cb_build_reference (buff), NULL);
	if (encode) {
		CB_LABEL (label)->name = (unsigned char *)(cb_encode_program_id (name));
		CB_LABEL (label)->orig_name = (unsigned char *)name;
	} else {
		CB_LABEL (label)->name = (unsigned char *)name;
		CB_LABEL (label)->orig_name = (unsigned char *)current_program->orig_source_name;
	}
	CB_LABEL (label)->need_begin = 1;
	CB_LABEL (label)->is_entry = 1;
	emit_statement (label);

	parmnum = 1;
	for (l = using_list; l; l = CB_CHAIN (l)) {
		x = CB_VALUE (l);
		if (x != cb_error_node && cb_ref (x) != cb_error_node) {
			f = CB_FIELD (cb_ref (x));
			if (f->level != 01 && f->level != 77) {
				cb_error_x (x, _("'%s' not level 01 or 77"), cb_name (x));
			}
			if (!current_program->flag_chained) {
				if (f->storage != CB_STORAGE_LINKAGE) {
					cb_error_x (x, _("'%s' is not in LINKAGE SECTION"), cb_name (x));
				}
				if (f->flag_item_based || f->flag_external) {
					cb_error_x (x, _("'%s' can not be BASED/EXTERNAL"), cb_name (x));
				}
				f->flag_is_pdiv_parm = 1;
			} else {
				if (f->storage != CB_STORAGE_WORKING) {
					cb_error_x (x, _("'%s' is not in WORKING-STORAGE SECTION"), cb_name (x));
				}
				f->flag_chained = 1;
				f->param_num = parmnum;
				parmnum++;
			}
			if (f->redefines) {
				cb_error_x (x, _("'%s' REDEFINES field not allowed here"), cb_name (x));
			}
		}
	}

	/* Check dangling LINKAGE items */
	if (cb_warn_linkage) {
		for (f = current_program->linkage_storage; f; f = f->sister) {
			for (l = using_list; l; l = CB_CHAIN (l)) {
				x = CB_VALUE (l);
				if (x != cb_error_node && cb_ref (x) != cb_error_node) {
					if (f == CB_FIELD (cb_ref (x))) {
						break;
					}
				}
			}
			if (!l && !f->redefines) {
				cb_warning (_("LINKAGE item '%s' is not a PROCEDURE USING parameter"), f->name);
			}
		}
	}

	for (l = current_program->entry_list; l; l = CB_CHAIN (l)) {
		if (strcmp ((const char *)name, (const char *)(CB_LABEL(CB_PURPOSE(l))->name)) == 0) {
			cb_error_x (CB_TREE (current_statement), _("ENTRY '%s' duplicated"), name);
		}
	}

	current_program->entry_list = cb_list_append (current_program->entry_list,
							cb_build_pair (label, using_list));
}

static void
terminator_warning (const size_t termid)
{
	check_unreached = 0;
	if (cb_warn_terminator && term_array[termid]) {
		cb_warning_x (CB_TREE (current_statement),
			_("%s statement not terminated by END-%s"),
			current_statement->name, current_statement->name);
	}
	if (term_array[termid]) {
		term_array[termid]--;
	}
}

static void
terminator_error (void)
{
	check_unreached = 0;
	cb_error_x (CB_TREE (current_statement),
			_("%s statement not terminated by END-%s"),
			current_statement->name, current_statement->name);
}

static void
terminator_clear (const size_t termid)
{
	check_unreached = 0;
	if (term_array[termid]) {
		term_array[termid]--;
	}
}

static int
literal_value (cb_tree x)
{
	if (x == cb_space) {
		return ' ';
	} else if (x == cb_zero) {
		return '0';
	} else if (x == cb_quote) {
		return '"';
	} else if (x == cb_null) {
		return 0;
	} else if (CB_TREE_CLASS (x) == CB_CLASS_NUMERIC) {
		return cb_get_int (x);
	} else {
		return CB_LITERAL (x)->data[0];
	}
}

static void
setup_use_file (struct cb_file *fileptr)
{
	struct cb_file	*newptr;

	if (fileptr->organization == COB_ORG_SORT) {
		cb_error (_("USE statement invalid for SORT file"));
	}
	if (fileptr->global) {
		newptr = cobc_malloc (sizeof(struct cb_file));
		*newptr = *fileptr;
		newptr->handler = current_section;
		newptr->handler_prog = current_program;
		if (!use_global_ind) {
			current_program->local_file_list =
				cb_list_add (current_program->local_file_list,
					     CB_TREE (newptr));
		} else {
			current_program->global_file_list =
				cb_list_add (current_program->global_file_list,
					     CB_TREE (newptr));
		}
	} else {
		fileptr->handler = current_section;
	}
}


#line 353 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ACCEPT = 3,                     /* ACCEPT  */
  YYSYMBOL_ACCESS = 4,                     /* ACCESS  */
  YYSYMBOL_ADD = 5,                        /* ADD  */
  YYSYMBOL_ADDRESS = 6,                    /* ADDRESS  */
  YYSYMBOL_ADVANCING = 7,                  /* ADVANCING  */
  YYSYMBOL_AFTER = 8,                      /* AFTER  */
  YYSYMBOL_ALL = 9,                        /* ALL  */
  YYSYMBOL_ALLOCATE = 10,                  /* ALLOCATE  */
  YYSYMBOL_ALPHABET = 11,                  /* ALPHABET  */
  YYSYMBOL_ALPHABETIC = 12,                /* ALPHABETIC  */
  YYSYMBOL_ALPHABETIC_LOWER = 13,          /* "ALPHABETIC-LOWER"  */
  YYSYMBOL_ALPHABETIC_UPPER = 14,          /* "ALPHABETIC-UPPER"  */
  YYSYMBOL_ALPHANUMERIC = 15,              /* ALPHANUMERIC  */
  YYSYMBOL_ALPHANUMERIC_EDITED = 16,       /* "ALPHANUMERIC-EDITED"  */
  YYSYMBOL_ALSO = 17,                      /* ALSO  */
  YYSYMBOL_ALTER = 18,                     /* ALTER  */
  YYSYMBOL_ALTERNATE = 19,                 /* ALTERNATE  */
  YYSYMBOL_AND = 20,                       /* AND  */
  YYSYMBOL_ANY = 21,                       /* ANY  */
  YYSYMBOL_ARE = 22,                       /* ARE  */
  YYSYMBOL_AREA = 23,                      /* AREA  */
  YYSYMBOL_ARGUMENT_NUMBER = 24,           /* "ARGUMENT-NUMBER"  */
  YYSYMBOL_ARGUMENT_VALUE = 25,            /* "ARGUMENT-VALUE"  */
  YYSYMBOL_AS = 26,                        /* AS  */
  YYSYMBOL_ASCENDING = 27,                 /* ASCENDING  */
  YYSYMBOL_ASSIGN = 28,                    /* ASSIGN  */
  YYSYMBOL_AT = 29,                        /* AT  */
  YYSYMBOL_AUTO = 30,                      /* AUTO  */
  YYSYMBOL_AUTOMATIC = 31,                 /* AUTOMATIC  */
  YYSYMBOL_BACKGROUND_COLOR = 32,          /* "BACKGROUND-COLOR"  */
  YYSYMBOL_BASED = 33,                     /* BASED  */
  YYSYMBOL_BEFORE = 34,                    /* BEFORE  */
  YYSYMBOL_BELL = 35,                      /* BELL  */
  YYSYMBOL_BINARY = 36,                    /* BINARY  */
  YYSYMBOL_BINARY_C_LONG = 37,             /* "BINARY-C-LONG"  */
  YYSYMBOL_BINARY_CHAR = 38,               /* "BINARY-CHAR"  */
  YYSYMBOL_BINARY_DOUBLE = 39,             /* "BINARY-DOUBLE"  */
  YYSYMBOL_BINARY_LONG = 40,               /* "BINARY-LONG"  */
  YYSYMBOL_BINARY_SHORT = 41,              /* "BINARY-SHORT"  */
  YYSYMBOL_BLANK = 42,                     /* BLANK  */
  YYSYMBOL_BLANK_LINE = 43,                /* "BLANK-LINE"  */
  YYSYMBOL_BLANK_SCREEN = 44,              /* "BLANK-SCREEN"  */
  YYSYMBOL_BLINK = 45,                     /* BLINK  */
  YYSYMBOL_BLOCK = 46,                     /* BLOCK  */
  YYSYMBOL_BOTTOM = 47,                    /* BOTTOM  */
  YYSYMBOL_BY = 48,                        /* BY  */
  YYSYMBOL_BYTE_LENGTH = 49,               /* "BYTE-LENGTH"  */
  YYSYMBOL_CALL = 50,                      /* CALL  */
  YYSYMBOL_CANCEL = 51,                    /* CANCEL  */
  YYSYMBOL_CH = 52,                        /* CH  */
  YYSYMBOL_CHAINING = 53,                  /* CHAINING  */
  YYSYMBOL_CHARACTER = 54,                 /* CHARACTER  */
  YYSYMBOL_CHARACTERS = 55,                /* CHARACTERS  */
  YYSYMBOL_CLASS = 56,                     /* CLASS  */
  YYSYMBOL_CLOSE = 57,                     /* CLOSE  */
  YYSYMBOL_CODE = 58,                      /* CODE  */
  YYSYMBOL_CODE_SET = 59,                  /* "CODE-SET"  */
  YYSYMBOL_COLLATING = 60,                 /* COLLATING  */
  YYSYMBOL_COL = 61,                       /* COL  */
  YYSYMBOL_COLS = 62,                      /* COLS  */
  YYSYMBOL_COLUMN = 63,                    /* COLUMN  */
  YYSYMBOL_COLUMNS = 64,                   /* COLUMNS  */
  YYSYMBOL_COMMA = 65,                     /* COMMA  */
  YYSYMBOL_COMMAND_LINE = 66,              /* "COMMAND-LINE"  */
  YYSYMBOL_COMMA_DELIM = 67,               /* "comma delimiter"  */
  YYSYMBOL_COMMIT = 68,                    /* COMMIT  */
  YYSYMBOL_COMMON = 69,                    /* COMMON  */
  YYSYMBOL_COMP = 70,                      /* COMP  */
  YYSYMBOL_COMPUTE = 71,                   /* COMPUTE  */
  YYSYMBOL_COMP_1 = 72,                    /* "COMP-1"  */
  YYSYMBOL_COMP_2 = 73,                    /* "COMP-2"  */
  YYSYMBOL_COMP_3 = 74,                    /* "COMP-3"  */
  YYSYMBOL_COMP_4 = 75,                    /* "COMP-4"  */
  YYSYMBOL_COMP_5 = 76,                    /* "COMP-5"  */
  YYSYMBOL_COMP_X = 77,                    /* "COMP-X"  */
  YYSYMBOL_CONCATENATE_FUNC = 78,          /* "FUNCTION CONCATENATE"  */
  YYSYMBOL_CONFIGURATION = 79,             /* CONFIGURATION  */
  YYSYMBOL_CONSTANT = 80,                  /* CONSTANT  */
  YYSYMBOL_CONTAINS = 81,                  /* CONTAINS  */
  YYSYMBOL_CONTENT = 82,                   /* CONTENT  */
  YYSYMBOL_CONTINUE = 83,                  /* CONTINUE  */
  YYSYMBOL_CONTROL = 84,                   /* CONTROL  */
  YYSYMBOL_CONTROLS = 85,                  /* CONTROLS  */
  YYSYMBOL_CONTROL_FOOTING = 86,           /* "CONTROL FOOTING"  */
  YYSYMBOL_CONTROL_HEADING = 87,           /* "CONTROL HEADING"  */
  YYSYMBOL_CONVERTING = 88,                /* CONVERTING  */
  YYSYMBOL_CORRESPONDING = 89,             /* CORRESPONDING  */
  YYSYMBOL_COUNT = 90,                     /* COUNT  */
  YYSYMBOL_CRT = 91,                       /* CRT  */
  YYSYMBOL_CURRENCY = 92,                  /* CURRENCY  */
  YYSYMBOL_CURRENT_DATE_FUNC = 93,         /* "FUNCTION CURRENT-DATE"  */
  YYSYMBOL_CURSOR = 94,                    /* CURSOR  */
  YYSYMBOL_CYCLE = 95,                     /* CYCLE  */
  YYSYMBOL_DATA = 96,                      /* DATA  */
  YYSYMBOL_DATE = 97,                      /* DATE  */
  YYSYMBOL_DAY = 98,                       /* DAY  */
  YYSYMBOL_DAY_OF_WEEK = 99,               /* "DAY-OF-WEEK"  */
  YYSYMBOL_DE = 100,                       /* DE  */
  YYSYMBOL_DEBUGGING = 101,                /* DEBUGGING  */
  YYSYMBOL_DECIMAL_POINT = 102,            /* "DECIMAL-POINT"  */
  YYSYMBOL_DECLARATIVES = 103,             /* DECLARATIVES  */
  YYSYMBOL_DEFAULT = 104,                  /* DEFAULT  */
  YYSYMBOL_DELETE = 105,                   /* DELETE  */
  YYSYMBOL_DELIMITED = 106,                /* DELIMITED  */
  YYSYMBOL_DELIMITER = 107,                /* DELIMITER  */
  YYSYMBOL_DEPENDING = 108,                /* DEPENDING  */
  YYSYMBOL_DESCENDING = 109,               /* DESCENDING  */
  YYSYMBOL_DETAIL = 110,                   /* DETAIL  */
  YYSYMBOL_DISK = 111,                     /* DISK  */
  YYSYMBOL_DISPLAY = 112,                  /* DISPLAY  */
  YYSYMBOL_DIVIDE = 113,                   /* DIVIDE  */
  YYSYMBOL_DIVISION = 114,                 /* DIVISION  */
  YYSYMBOL_DOWN = 115,                     /* DOWN  */
  YYSYMBOL_DUPLICATES = 116,               /* DUPLICATES  */
  YYSYMBOL_DYNAMIC = 117,                  /* DYNAMIC  */
  YYSYMBOL_EBCDIC = 118,                   /* EBCDIC  */
  YYSYMBOL_ELSE = 119,                     /* ELSE  */
  YYSYMBOL_END = 120,                      /* END  */
  YYSYMBOL_END_ACCEPT = 121,               /* "END-ACCEPT"  */
  YYSYMBOL_END_ADD = 122,                  /* "END-ADD"  */
  YYSYMBOL_END_CALL = 123,                 /* "END-CALL"  */
  YYSYMBOL_END_COMPUTE = 124,              /* "END-COMPUTE"  */
  YYSYMBOL_END_DELETE = 125,               /* "END-DELETE"  */
  YYSYMBOL_END_DISPLAY = 126,              /* "END-DISPLAY"  */
  YYSYMBOL_END_DIVIDE = 127,               /* "END-DIVIDE"  */
  YYSYMBOL_END_EVALUATE = 128,             /* "END-EVALUATE"  */
  YYSYMBOL_END_FUNCTION = 129,             /* "END FUNCTION"  */
  YYSYMBOL_END_IF = 130,                   /* "END-IF"  */
  YYSYMBOL_END_MULTIPLY = 131,             /* "END-MULTIPLY"  */
  YYSYMBOL_END_PERFORM = 132,              /* "END-PERFORM"  */
  YYSYMBOL_END_PROGRAM = 133,              /* "END PROGRAM"  */
  YYSYMBOL_END_READ = 134,                 /* "END-READ"  */
  YYSYMBOL_END_RETURN = 135,               /* "END-RETURN"  */
  YYSYMBOL_END_REWRITE = 136,              /* "END-REWRITE"  */
  YYSYMBOL_END_SEARCH = 137,               /* "END-SEARCH"  */
  YYSYMBOL_END_START = 138,                /* "END-START"  */
  YYSYMBOL_END_STRING = 139,               /* "END-STRING"  */
  YYSYMBOL_END_SUBTRACT = 140,             /* "END-SUBTRACT"  */
  YYSYMBOL_END_UNSTRING = 141,             /* "END-UNSTRING"  */
  YYSYMBOL_END_WRITE = 142,                /* "END-WRITE"  */
  YYSYMBOL_ENTRY = 143,                    /* ENTRY  */
  YYSYMBOL_ENVIRONMENT = 144,              /* ENVIRONMENT  */
  YYSYMBOL_ENVIRONMENT_NAME = 145,         /* "ENVIRONMENT-NAME"  */
  YYSYMBOL_ENVIRONMENT_VALUE = 146,        /* "ENVIRONMENT-VALUE"  */
  YYSYMBOL_EOL = 147,                      /* EOL  */
  YYSYMBOL_EOP = 148,                      /* EOP  */
  YYSYMBOL_EOS = 149,                      /* EOS  */
  YYSYMBOL_EQUAL = 150,                    /* EQUAL  */
  YYSYMBOL_EQUALS = 151,                   /* EQUALS  */
  YYSYMBOL_ERASE = 152,                    /* ERASE  */
  YYSYMBOL_ERROR = 153,                    /* ERROR  */
  YYSYMBOL_ESCAPE = 154,                   /* ESCAPE  */
  YYSYMBOL_EVALUATE = 155,                 /* EVALUATE  */
  YYSYMBOL_EVENT_STATUS = 156,             /* "EVENT-STATUS"  */
  YYSYMBOL_EXCEPTION = 157,                /* EXCEPTION  */
  YYSYMBOL_EXCLUSIVE = 158,                /* EXCLUSIVE  */
  YYSYMBOL_EXIT = 159,                     /* EXIT  */
  YYSYMBOL_EXTEND = 160,                   /* EXTEND  */
  YYSYMBOL_EXTERNAL = 161,                 /* EXTERNAL  */
  YYSYMBOL_FD = 162,                       /* FD  */
  YYSYMBOL_FILE_CONTROL = 163,             /* "FILE-CONTROL"  */
  YYSYMBOL_FILE_ID = 164,                  /* "FILE-ID"  */
  YYSYMBOL_FILLER = 165,                   /* FILLER  */
  YYSYMBOL_FINAL = 166,                    /* FINAL  */
  YYSYMBOL_FIRST = 167,                    /* FIRST  */
  YYSYMBOL_FOOTING = 168,                  /* FOOTING  */
  YYSYMBOL_FOR = 169,                      /* FOR  */
  YYSYMBOL_FOREGROUND_COLOR = 170,         /* "FOREGROUND-COLOR"  */
  YYSYMBOL_FOREVER = 171,                  /* FOREVER  */
  YYSYMBOL_FREE = 172,                     /* FREE  */
  YYSYMBOL_FROM = 173,                     /* FROM  */
  YYSYMBOL_FULL = 174,                     /* FULL  */
  YYSYMBOL_FUNCTION = 175,                 /* FUNCTION  */
  YYSYMBOL_FUNCTION_ID = 176,              /* "FUNCTION-ID"  */
  YYSYMBOL_FUNCTION_NAME = 177,            /* "FUNCTION"  */
  YYSYMBOL_GE = 178,                       /* GE  */
  YYSYMBOL_GENERATE = 179,                 /* GENERATE  */
  YYSYMBOL_GIVING = 180,                   /* GIVING  */
  YYSYMBOL_GLOBAL = 181,                   /* GLOBAL  */
  YYSYMBOL_GO = 182,                       /* GO  */
  YYSYMBOL_GOBACK = 183,                   /* GOBACK  */
  YYSYMBOL_GREATER = 184,                  /* GREATER  */
  YYSYMBOL_GROUP = 185,                    /* GROUP  */
  YYSYMBOL_HEADING = 186,                  /* HEADING  */
  YYSYMBOL_HIGHLIGHT = 187,                /* HIGHLIGHT  */
  YYSYMBOL_HIGH_VALUE = 188,               /* "HIGH-VALUE"  */
  YYSYMBOL_IDENTIFICATION = 189,           /* IDENTIFICATION  */
  YYSYMBOL_IF = 190,                       /* IF  */
  YYSYMBOL_IGNORE = 191,                   /* IGNORE  */
  YYSYMBOL_IGNORING = 192,                 /* IGNORING  */
  YYSYMBOL_IN = 193,                       /* IN  */
  YYSYMBOL_INDEX = 194,                    /* INDEX  */
  YYSYMBOL_INDEXED = 195,                  /* INDEXED  */
  YYSYMBOL_INDICATE = 196,                 /* INDICATE  */
  YYSYMBOL_INITIALIZE = 197,               /* INITIALIZE  */
  YYSYMBOL_INITIALIZED = 198,              /* INITIALIZED  */
  YYSYMBOL_INITIATE = 199,                 /* INITIATE  */
  YYSYMBOL_INPUT = 200,                    /* INPUT  */
  YYSYMBOL_INPUT_OUTPUT = 201,             /* "INPUT-OUTPUT"  */
  YYSYMBOL_INSPECT = 202,                  /* INSPECT  */
  YYSYMBOL_INTO = 203,                     /* INTO  */
  YYSYMBOL_INTRINSIC = 204,                /* INTRINSIC  */
  YYSYMBOL_INVALID = 205,                  /* INVALID  */
  YYSYMBOL_INVALID_KEY = 206,              /* "INVALID KEY"  */
  YYSYMBOL_IS = 207,                       /* IS  */
  YYSYMBOL_I_O = 208,                      /* "I-O"  */
  YYSYMBOL_I_O_CONTROL = 209,              /* "I-O-CONTROL"  */
  YYSYMBOL_JUSTIFIED = 210,                /* JUSTIFIED  */
  YYSYMBOL_KEY = 211,                      /* KEY  */
  YYSYMBOL_LABEL = 212,                    /* LABEL  */
  YYSYMBOL_LAST = 213,                     /* LAST  */
  YYSYMBOL_LAST_DETAIL = 214,              /* "LAST DETAIL"  */
  YYSYMBOL_LE = 215,                       /* LE  */
  YYSYMBOL_LEADING = 216,                  /* LEADING  */
  YYSYMBOL_LEFT = 217,                     /* LEFT  */
  YYSYMBOL_LENGTH = 218,                   /* LENGTH  */
  YYSYMBOL_LESS = 219,                     /* LESS  */
  YYSYMBOL_LIMIT = 220,                    /* LIMIT  */
  YYSYMBOL_LIMITS = 221,                   /* LIMITS  */
  YYSYMBOL_LINAGE = 222,                   /* LINAGE  */
  YYSYMBOL_LINAGE_COUNTER = 223,           /* "LINAGE-COUNTER"  */
  YYSYMBOL_LINE = 224,                     /* LINE  */
  YYSYMBOL_LINES = 225,                    /* LINES  */
  YYSYMBOL_LINKAGE = 226,                  /* LINKAGE  */
  YYSYMBOL_LITERAL = 227,                  /* "Literal"  */
  YYSYMBOL_LOCALE = 228,                   /* LOCALE  */
  YYSYMBOL_LOCALE_DT_FUNC = 229,           /* "FUNCTION LOCALE"  */
  YYSYMBOL_LOCAL_STORAGE = 230,            /* "LOCAL-STORAGE"  */
  YYSYMBOL_LOCK = 231,                     /* LOCK  */
  YYSYMBOL_LOWER_CASE_FUNC = 232,          /* "FUNCTION LOWER-CASE"  */
  YYSYMBOL_LOWLIGHT = 233,                 /* LOWLIGHT  */
  YYSYMBOL_LOW_VALUE = 234,                /* "LOW-VALUE"  */
  YYSYMBOL_MANUAL = 235,                   /* MANUAL  */
  YYSYMBOL_MEMORY = 236,                   /* MEMORY  */
  YYSYMBOL_MERGE = 237,                    /* MERGE  */
  YYSYMBOL_MINUS = 238,                    /* MINUS  */
  YYSYMBOL_MNEMONIC_NAME = 239,            /* "MNEMONIC NAME"  */
  YYSYMBOL_MODE = 240,                     /* MODE  */
  YYSYMBOL_MOVE = 241,                     /* MOVE  */
  YYSYMBOL_MULTIPLE = 242,                 /* MULTIPLE  */
  YYSYMBOL_MULTIPLY = 243,                 /* MULTIPLY  */
  YYSYMBOL_NATIONAL = 244,                 /* NATIONAL  */
  YYSYMBOL_NATIONAL_EDITED = 245,          /* "NATIONAL-EDITED"  */
  YYSYMBOL_NATIVE = 246,                   /* NATIVE  */
  YYSYMBOL_NE = 247,                       /* NE  */
  YYSYMBOL_NEGATIVE = 248,                 /* NEGATIVE  */
  YYSYMBOL_NEXT = 249,                     /* NEXT  */
  YYSYMBOL_NEXT_SENTENCE = 250,            /* "NEXT SENTENCE"  */
  YYSYMBOL_NO = 251,                       /* NO  */
  YYSYMBOL_NOT = 252,                      /* NOT  */
  YYSYMBOL_NOT_END = 253,                  /* "NOT END"  */
  YYSYMBOL_NOT_EOP = 254,                  /* "NOT EOP"  */
  YYSYMBOL_NOT_EXCEPTION = 255,            /* "NOT EXCEPTION"  */
  YYSYMBOL_NOT_INVALID_KEY = 256,          /* "NOT INVALID KEY"  */
  YYSYMBOL_NOT_OVERFLOW = 257,             /* "NOT OVERFLOW"  */
  YYSYMBOL_NOT_SIZE_ERROR = 258,           /* "NOT SIZE ERROR"  */
  YYSYMBOL_NO_ADVANCING = 259,             /* "NO ADVANCING"  */
  YYSYMBOL_NUMBER = 260,                   /* NUMBER  */
  YYSYMBOL_NUMBERS = 261,                  /* NUMBERS  */
  YYSYMBOL_NUMERIC = 262,                  /* NUMERIC  */
  YYSYMBOL_NUMERIC_EDITED = 263,           /* "NUMERIC-EDITED"  */
  YYSYMBOL_NUMVALC_FUNC = 264,             /* "FUNCTION NUMVALC"  */
  YYSYMBOL_OBJECT_COMPUTER = 265,          /* "OBJECT-COMPUTER"  */
  YYSYMBOL_OCCURS = 266,                   /* OCCURS  */
  YYSYMBOL_OF = 267,                       /* OF  */
  YYSYMBOL_OFF = 268,                      /* OFF  */
  YYSYMBOL_OMITTED = 269,                  /* OMITTED  */
  YYSYMBOL_ON = 270,                       /* ON  */
  YYSYMBOL_ONLY = 271,                     /* ONLY  */
  YYSYMBOL_OPEN = 272,                     /* OPEN  */
  YYSYMBOL_OPTIONAL = 273,                 /* OPTIONAL  */
  YYSYMBOL_OR = 274,                       /* OR  */
  YYSYMBOL_ORDER = 275,                    /* ORDER  */
  YYSYMBOL_ORGANIZATION = 276,             /* ORGANIZATION  */
  YYSYMBOL_OTHER = 277,                    /* OTHER  */
  YYSYMBOL_OUTPUT = 278,                   /* OUTPUT  */
  YYSYMBOL_OVERFLOW = 279,                 /* OVERFLOW  */
  YYSYMBOL_OVERLINE = 280,                 /* OVERLINE  */
  YYSYMBOL_PACKED_DECIMAL = 281,           /* "PACKED-DECIMAL"  */
  YYSYMBOL_PADDING = 282,                  /* PADDING  */
  YYSYMBOL_PAGE = 283,                     /* PAGE  */
  YYSYMBOL_PAGE_FOOTING = 284,             /* "PAGE FOOTING"  */
  YYSYMBOL_PAGE_HEADING = 285,             /* "PAGE HEADING"  */
  YYSYMBOL_PARAGRAPH = 286,                /* PARAGRAPH  */
  YYSYMBOL_PERFORM = 287,                  /* PERFORM  */
  YYSYMBOL_PICTURE = 288,                  /* PICTURE  */
  YYSYMBOL_PLUS = 289,                     /* PLUS  */
  YYSYMBOL_POINTER = 290,                  /* POINTER  */
  YYSYMBOL_POSITION = 291,                 /* POSITION  */
  YYSYMBOL_POSITIVE = 292,                 /* POSITIVE  */
  YYSYMBOL_PRESENT = 293,                  /* PRESENT  */
  YYSYMBOL_PREVIOUS = 294,                 /* PREVIOUS  */
  YYSYMBOL_PRINTER = 295,                  /* PRINTER  */
  YYSYMBOL_PRINTING = 296,                 /* PRINTING  */
  YYSYMBOL_PROCEDURE = 297,                /* PROCEDURE  */
  YYSYMBOL_PROCEDURES = 298,               /* PROCEDURES  */
  YYSYMBOL_PROCEED = 299,                  /* PROCEED  */
  YYSYMBOL_PROGRAM = 300,                  /* PROGRAM  */
  YYSYMBOL_PROGRAM_ID = 301,               /* "PROGRAM-ID"  */
  YYSYMBOL_PROGRAM_NAME = 302,             /* "Program name"  */
  YYSYMBOL_PROGRAM_POINTER = 303,          /* "PROGRAM-POINTER"  */
  YYSYMBOL_PROMPT = 304,                   /* PROMPT  */
  YYSYMBOL_QUOTE = 305,                    /* QUOTE  */
  YYSYMBOL_RANDOM = 306,                   /* RANDOM  */
  YYSYMBOL_RD = 307,                       /* RD  */
  YYSYMBOL_READ = 308,                     /* READ  */
  YYSYMBOL_RECORD = 309,                   /* RECORD  */
  YYSYMBOL_RECORDING = 310,                /* RECORDING  */
  YYSYMBOL_RECORDS = 311,                  /* RECORDS  */
  YYSYMBOL_RECURSIVE = 312,                /* RECURSIVE  */
  YYSYMBOL_REDEFINES = 313,                /* REDEFINES  */
  YYSYMBOL_REEL = 314,                     /* REEL  */
  YYSYMBOL_REFERENCE = 315,                /* REFERENCE  */
  YYSYMBOL_RELATIVE = 316,                 /* RELATIVE  */
  YYSYMBOL_RELEASE = 317,                  /* RELEASE  */
  YYSYMBOL_REMAINDER = 318,                /* REMAINDER  */
  YYSYMBOL_REMOVAL = 319,                  /* REMOVAL  */
  YYSYMBOL_RENAMES = 320,                  /* RENAMES  */
  YYSYMBOL_REPLACING = 321,                /* REPLACING  */
  YYSYMBOL_REPORT = 322,                   /* REPORT  */
  YYSYMBOL_REPORTING = 323,                /* REPORTING  */
  YYSYMBOL_REPORTS = 324,                  /* REPORTS  */
  YYSYMBOL_REPORT_FOOTING = 325,           /* "REPORT FOOTING"  */
  YYSYMBOL_REPORT_HEADING = 326,           /* "REPORT HEADING"  */
  YYSYMBOL_REPOSITORY = 327,               /* REPOSITORY  */
  YYSYMBOL_REQUIRED = 328,                 /* REQUIRED  */
  YYSYMBOL_RESERVE = 329,                  /* RESERVE  */
  YYSYMBOL_RETURN = 330,                   /* RETURN  */
  YYSYMBOL_RETURNING = 331,                /* RETURNING  */
  YYSYMBOL_REVERSE_FUNC = 332,             /* "FUNCTION REVERSE"  */
  YYSYMBOL_REVERSE_VIDEO = 333,            /* "REVERSE-VIDEO"  */
  YYSYMBOL_REWIND = 334,                   /* REWIND  */
  YYSYMBOL_REWRITE = 335,                  /* REWRITE  */
  YYSYMBOL_RIGHT = 336,                    /* RIGHT  */
  YYSYMBOL_ROLLBACK = 337,                 /* ROLLBACK  */
  YYSYMBOL_ROUNDED = 338,                  /* ROUNDED  */
  YYSYMBOL_RUN = 339,                      /* RUN  */
  YYSYMBOL_SAME = 340,                     /* SAME  */
  YYSYMBOL_SCREEN = 341,                   /* SCREEN  */
  YYSYMBOL_SCREEN_CONTROL = 342,           /* "SCREEN-CONTROL"  */
  YYSYMBOL_SCROLL = 343,                   /* SCROLL  */
  YYSYMBOL_SD = 344,                       /* SD  */
  YYSYMBOL_SEARCH = 345,                   /* SEARCH  */
  YYSYMBOL_SECTION = 346,                  /* SECTION  */
  YYSYMBOL_SECURE = 347,                   /* SECURE  */
  YYSYMBOL_SEGMENT_LIMIT = 348,            /* "SEGMENT-LIMIT"  */
  YYSYMBOL_SELECT = 349,                   /* SELECT  */
  YYSYMBOL_SEMI_COLON = 350,               /* "semi-colon"  */
  YYSYMBOL_SENTENCE = 351,                 /* SENTENCE  */
  YYSYMBOL_SEPARATE = 352,                 /* SEPARATE  */
  YYSYMBOL_SEQUENCE = 353,                 /* SEQUENCE  */
  YYSYMBOL_SEQUENTIAL = 354,               /* SEQUENTIAL  */
  YYSYMBOL_SET = 355,                      /* SET  */
  YYSYMBOL_SHARING = 356,                  /* SHARING  */
  YYSYMBOL_SIGN = 357,                     /* SIGN  */
  YYSYMBOL_SIGNED = 358,                   /* SIGNED  */
  YYSYMBOL_SIGNED_INT = 359,               /* "SIGNED-INT"  */
  YYSYMBOL_SIGNED_LONG = 360,              /* "SIGNED-LONG"  */
  YYSYMBOL_SIGNED_SHORT = 361,             /* "SIGNED-SHORT"  */
  YYSYMBOL_SIZE = 362,                     /* SIZE  */
  YYSYMBOL_SIZE_ERROR = 363,               /* "SIZE ERROR"  */
  YYSYMBOL_SORT = 364,                     /* SORT  */
  YYSYMBOL_SORT_MERGE = 365,               /* "SORT-MERGE"  */
  YYSYMBOL_SOURCE = 366,                   /* SOURCE  */
  YYSYMBOL_SOURCE_COMPUTER = 367,          /* "SOURCE-COMPUTER"  */
  YYSYMBOL_SPACE = 368,                    /* SPACE  */
  YYSYMBOL_SPECIAL_NAMES = 369,            /* "SPECIAL-NAMES"  */
  YYSYMBOL_STANDARD = 370,                 /* STANDARD  */
  YYSYMBOL_STANDARD_1 = 371,               /* "STANDARD-1"  */
  YYSYMBOL_STANDARD_2 = 372,               /* "STANDARD-2"  */
  YYSYMBOL_START = 373,                    /* START  */
  YYSYMBOL_STATUS = 374,                   /* STATUS  */
  YYSYMBOL_STOP = 375,                     /* STOP  */
  YYSYMBOL_STRING = 376,                   /* STRING  */
  YYSYMBOL_SUBSTITUTE_FUNC = 377,          /* "FUNCTION SUBSTITUTE"  */
  YYSYMBOL_SUBSTITUTE_CASE_FUNC = 378,     /* "FUNCTION SUBSTITUTE-CASE"  */
  YYSYMBOL_SUBTRACT = 379,                 /* SUBTRACT  */
  YYSYMBOL_SUM = 380,                      /* SUM  */
  YYSYMBOL_SUPPRESS = 381,                 /* SUPPRESS  */
  YYSYMBOL_SYMBOLIC = 382,                 /* SYMBOLIC  */
  YYSYMBOL_SYNCHRONIZED = 383,             /* SYNCHRONIZED  */
  YYSYMBOL_TALLYING = 384,                 /* TALLYING  */
  YYSYMBOL_TAPE = 385,                     /* TAPE  */
  YYSYMBOL_TERMINATE = 386,                /* TERMINATE  */
  YYSYMBOL_TEST = 387,                     /* TEST  */
  YYSYMBOL_THAN = 388,                     /* THAN  */
  YYSYMBOL_THEN = 389,                     /* THEN  */
  YYSYMBOL_THRU = 390,                     /* THRU  */
  YYSYMBOL_TIME = 391,                     /* TIME  */
  YYSYMBOL_TIMES = 392,                    /* TIMES  */
  YYSYMBOL_TO = 393,                       /* TO  */
  YYSYMBOL_TOK_FALSE = 394,                /* "FALSE"  */
  YYSYMBOL_TOK_FILE = 395,                 /* "FILE"  */
  YYSYMBOL_TOK_INITIAL = 396,              /* "INITIAL"  */
  YYSYMBOL_TOK_NULL = 397,                 /* "NULL"  */
  YYSYMBOL_TOK_TRUE = 398,                 /* "TRUE"  */
  YYSYMBOL_TOP = 399,                      /* TOP  */
  YYSYMBOL_TRAILING = 400,                 /* TRAILING  */
  YYSYMBOL_TRANSFORM = 401,                /* TRANSFORM  */
  YYSYMBOL_TRIM_FUNCTION = 402,            /* "FUNCTION TRIM"  */
  YYSYMBOL_TYPE = 403,                     /* TYPE  */
  YYSYMBOL_UNDERLINE = 404,                /* UNDERLINE  */
  YYSYMBOL_UNIT = 405,                     /* UNIT  */
  YYSYMBOL_UNLOCK = 406,                   /* UNLOCK  */
  YYSYMBOL_UNSIGNED = 407,                 /* UNSIGNED  */
  YYSYMBOL_UNSIGNED_INT = 408,             /* "UNSIGNED-INT"  */
  YYSYMBOL_UNSIGNED_LONG = 409,            /* "UNSIGNED-LONG"  */
  YYSYMBOL_UNSIGNED_SHORT = 410,           /* "UNSIGNED-SHORT"  */
  YYSYMBOL_UNSTRING = 411,                 /* UNSTRING  */
  YYSYMBOL_UNTIL = 412,                    /* UNTIL  */
  YYSYMBOL_UP = 413,                       /* UP  */
  YYSYMBOL_UPDATE = 414,                   /* UPDATE  */
  YYSYMBOL_UPON = 415,                     /* UPON  */
  YYSYMBOL_UPON_ARGUMENT_NUMBER = 416,     /* "UPON ARGUMENT-NUMBER"  */
  YYSYMBOL_UPON_COMMAND_LINE = 417,        /* "UPON COMMAND-LINE"  */
  YYSYMBOL_UPON_ENVIRONMENT_NAME = 418,    /* "UPON ENVIRONMENT-NAME"  */
  YYSYMBOL_UPON_ENVIRONMENT_VALUE = 419,   /* "UPON ENVIRONMENT-VALUE"  */
  YYSYMBOL_UPPER_CASE_FUNC = 420,          /* "FUNCTION UPPER-CASE"  */
  YYSYMBOL_USAGE = 421,                    /* USAGE  */
  YYSYMBOL_USE = 422,                      /* USE  */
  YYSYMBOL_USING = 423,                    /* USING  */
  YYSYMBOL_VALUE = 424,                    /* VALUE  */
  YYSYMBOL_VARYING = 425,                  /* VARYING  */
  YYSYMBOL_WAIT = 426,                     /* WAIT  */
  YYSYMBOL_WHEN = 427,                     /* WHEN  */
  YYSYMBOL_WHEN_COMPILED_FUNC = 428,       /* "FUNCTION WHEN-COMPILED"  */
  YYSYMBOL_WITH = 429,                     /* WITH  */
  YYSYMBOL_WORD = 430,                     /* "Identifier"  */
  YYSYMBOL_WORDS = 431,                    /* WORDS  */
  YYSYMBOL_WORKING_STORAGE = 432,          /* "WORKING-STORAGE"  */
  YYSYMBOL_WRITE = 433,                    /* WRITE  */
  YYSYMBOL_YYYYDDD = 434,                  /* YYYYDDD  */
  YYSYMBOL_YYYYMMDD = 435,                 /* YYYYMMDD  */
  YYSYMBOL_ZERO = 436,                     /* ZERO  */
  YYSYMBOL_437_ = 437,                     /* '+'  */
  YYSYMBOL_438_ = 438,                     /* '-'  */
  YYSYMBOL_439_ = 439,                     /* '*'  */
  YYSYMBOL_440_ = 440,                     /* '/'  */
  YYSYMBOL_UNARY_SIGN = 441,               /* UNARY_SIGN  */
  YYSYMBOL_442_ = 442,                     /* '^'  */
  YYSYMBOL_443_ = 443,                     /* '.'  */
  YYSYMBOL_444_ = 444,                     /* '='  */
  YYSYMBOL_445_ = 445,                     /* '('  */
  YYSYMBOL_446_ = 446,                     /* ')'  */
  YYSYMBOL_447_ = 447,                     /* '>'  */
  YYSYMBOL_448_ = 448,                     /* '<'  */
  YYSYMBOL_449_ = 449,                     /* ':'  */
  YYSYMBOL_450_ = 450,                     /* '&'  */
  YYSYMBOL_YYACCEPT = 451,                 /* $accept  */
  YYSYMBOL_start = 452,                    /* start  */
  YYSYMBOL_453_1 = 453,                    /* $@1  */
  YYSYMBOL_nested_list = 454,              /* nested_list  */
  YYSYMBOL_source_element = 455,           /* source_element  */
  YYSYMBOL_program_definition = 456,       /* program_definition  */
  YYSYMBOL_457_2 = 457,                    /* $@2  */
  YYSYMBOL_458_3 = 458,                    /* $@3  */
  YYSYMBOL_program_mandatory = 459,        /* program_mandatory  */
  YYSYMBOL_460_4 = 460,                    /* $@4  */
  YYSYMBOL_461_5 = 461,                    /* $@5  */
  YYSYMBOL_function_definition = 462,      /* function_definition  */
  YYSYMBOL_463_6 = 463,                    /* $@6  */
  YYSYMBOL_464_7 = 464,                    /* $@7  */
  YYSYMBOL_nested_prog = 465,              /* nested_prog  */
  YYSYMBOL_end_program = 466,              /* end_program  */
  YYSYMBOL_end_mandatory = 467,            /* end_mandatory  */
  YYSYMBOL_end_function = 468,             /* end_function  */
  YYSYMBOL_identification_division = 469,  /* identification_division  */
  YYSYMBOL_470_8 = 470,                    /* $@8  */
  YYSYMBOL_function_division = 471,        /* function_division  */
  YYSYMBOL_program_name = 472,             /* program_name  */
  YYSYMBOL_as_literal = 473,               /* as_literal  */
  YYSYMBOL_program_type = 474,             /* program_type  */
  YYSYMBOL_program_type_clause = 475,      /* program_type_clause  */
  YYSYMBOL__init_or_recurs = 476,          /* _init_or_recurs  */
  YYSYMBOL_environment_division = 477,     /* environment_division  */
  YYSYMBOL_configuration_section = 478,    /* configuration_section  */
  YYSYMBOL_configuration_list = 479,       /* configuration_list  */
  YYSYMBOL_configuration_paragraph = 480,  /* configuration_paragraph  */
  YYSYMBOL_source_computer_paragraph = 481, /* source_computer_paragraph  */
  YYSYMBOL_source_computer_entry = 482,    /* source_computer_entry  */
  YYSYMBOL_with_debugging_mode = 483,      /* with_debugging_mode  */
  YYSYMBOL_computer_name = 484,            /* computer_name  */
  YYSYMBOL_object_computer_paragraph = 485, /* object_computer_paragraph  */
  YYSYMBOL_object_computer_entry = 486,    /* object_computer_entry  */
  YYSYMBOL_object_clauses_list = 487,      /* object_clauses_list  */
  YYSYMBOL_object_clauses = 488,           /* object_clauses  */
  YYSYMBOL_object_computer_memory = 489,   /* object_computer_memory  */
  YYSYMBOL_object_char_or_word = 490,      /* object_char_or_word  */
  YYSYMBOL_object_computer_sequence = 491, /* object_computer_sequence  */
  YYSYMBOL_object_computer_segment = 492,  /* object_computer_segment  */
  YYSYMBOL_repository_paragraph = 493,     /* repository_paragraph  */
  YYSYMBOL_opt_repository = 494,           /* opt_repository  */
  YYSYMBOL_repository_list = 495,          /* repository_list  */
  YYSYMBOL_repository_name = 496,          /* repository_name  */
  YYSYMBOL_repository_literal_list = 497,  /* repository_literal_list  */
  YYSYMBOL_special_names_paragraph = 498,  /* special_names_paragraph  */
  YYSYMBOL_opt_special_names = 499,        /* opt_special_names  */
  YYSYMBOL_special_name_list = 500,        /* special_name_list  */
  YYSYMBOL_special_name = 501,             /* special_name  */
  YYSYMBOL_mnemonic_name_clause = 502,     /* mnemonic_name_clause  */
  YYSYMBOL_503_9 = 503,                    /* $@9  */
  YYSYMBOL_special_name_mnemonic_on_off = 504, /* special_name_mnemonic_on_off  */
  YYSYMBOL_on_or_off = 505,                /* on_or_off  */
  YYSYMBOL_alphabet_name_clause = 506,     /* alphabet_name_clause  */
  YYSYMBOL_507_10 = 507,                   /* $@10  */
  YYSYMBOL_alphabet_definition = 508,      /* alphabet_definition  */
  YYSYMBOL_alphabet_literal_list = 509,    /* alphabet_literal_list  */
  YYSYMBOL_alphabet_literal = 510,         /* alphabet_literal  */
  YYSYMBOL_511_11 = 511,                   /* @11  */
  YYSYMBOL_alphabet_also_sequence = 512,   /* alphabet_also_sequence  */
  YYSYMBOL_alphabet_lits = 513,            /* alphabet_lits  */
  YYSYMBOL_alphabet_also_literal = 514,    /* alphabet_also_literal  */
  YYSYMBOL_symbolic_characters_clause = 515, /* symbolic_characters_clause  */
  YYSYMBOL_symbolic_characters_list = 516, /* symbolic_characters_list  */
  YYSYMBOL_char_list = 517,                /* char_list  */
  YYSYMBOL_integer_list = 518,             /* integer_list  */
  YYSYMBOL_class_name_clause = 519,        /* class_name_clause  */
  YYSYMBOL_class_item_list = 520,          /* class_item_list  */
  YYSYMBOL_class_item = 521,               /* class_item  */
  YYSYMBOL_locale_clause = 522,            /* locale_clause  */
  YYSYMBOL_currency_sign_clause = 523,     /* currency_sign_clause  */
  YYSYMBOL_decimal_point_clause = 524,     /* decimal_point_clause  */
  YYSYMBOL_cursor_clause = 525,            /* cursor_clause  */
  YYSYMBOL_crt_status_clause = 526,        /* crt_status_clause  */
  YYSYMBOL_screen_control = 527,           /* screen_control  */
  YYSYMBOL_event_status = 528,             /* event_status  */
  YYSYMBOL_input_output_section = 529,     /* input_output_section  */
  YYSYMBOL_530_12 = 530,                   /* $@12  */
  YYSYMBOL_531_13 = 531,                   /* $@13  */
  YYSYMBOL_file_control_paragraph = 532,   /* file_control_paragraph  */
  YYSYMBOL_file_control_sequence = 533,    /* file_control_sequence  */
  YYSYMBOL_file_control_entry = 534,       /* file_control_entry  */
  YYSYMBOL_535_14 = 535,                   /* $@14  */
  YYSYMBOL_select_clause_sequence = 536,   /* select_clause_sequence  */
  YYSYMBOL_select_clause = 537,            /* select_clause  */
  YYSYMBOL_assign_clause = 538,            /* assign_clause  */
  YYSYMBOL__device = 539,                  /* _device  */
  YYSYMBOL__ext_clause = 540,              /* _ext_clause  */
  YYSYMBOL_assignment_name = 541,          /* assignment_name  */
  YYSYMBOL_access_mode_clause = 542,       /* access_mode_clause  */
  YYSYMBOL_access_mode = 543,              /* access_mode  */
  YYSYMBOL_alternative_record_key_clause = 544, /* alternative_record_key_clause  */
  YYSYMBOL_collating_sequence_clause = 545, /* collating_sequence_clause  */
  YYSYMBOL_file_status_clause = 546,       /* file_status_clause  */
  YYSYMBOL_file_or_sort = 547,             /* file_or_sort  */
  YYSYMBOL_lock_mode_clause = 548,         /* lock_mode_clause  */
  YYSYMBOL_lock_mode = 549,                /* lock_mode  */
  YYSYMBOL_lock_with = 550,                /* lock_with  */
  YYSYMBOL_lock_records = 551,             /* lock_records  */
  YYSYMBOL_organization_clause = 552,      /* organization_clause  */
  YYSYMBOL_organization = 553,             /* organization  */
  YYSYMBOL_padding_character_clause = 554, /* padding_character_clause  */
  YYSYMBOL_record_delimiter_clause = 555,  /* record_delimiter_clause  */
  YYSYMBOL_record_key_clause = 556,        /* record_key_clause  */
  YYSYMBOL_opt_splitk = 557,               /* opt_splitk  */
  YYSYMBOL_relative_key_clause = 558,      /* relative_key_clause  */
  YYSYMBOL_reserve_clause = 559,           /* reserve_clause  */
  YYSYMBOL_sharing_clause = 560,           /* sharing_clause  */
  YYSYMBOL_sharing_option = 561,           /* sharing_option  */
  YYSYMBOL_i_o_control_paragraph = 562,    /* i_o_control_paragraph  */
  YYSYMBOL_opt_i_o_control = 563,          /* opt_i_o_control  */
  YYSYMBOL_i_o_control_list = 564,         /* i_o_control_list  */
  YYSYMBOL_i_o_control_clause = 565,       /* i_o_control_clause  */
  YYSYMBOL_same_clause = 566,              /* same_clause  */
  YYSYMBOL_same_option = 567,              /* same_option  */
  YYSYMBOL_multiple_file_tape_clause = 568, /* multiple_file_tape_clause  */
  YYSYMBOL_multiple_file_list = 569,       /* multiple_file_list  */
  YYSYMBOL_multiple_file = 570,            /* multiple_file  */
  YYSYMBOL_multiple_file_position = 571,   /* multiple_file_position  */
  YYSYMBOL_data_division = 572,            /* data_division  */
  YYSYMBOL_file_section = 573,             /* file_section  */
  YYSYMBOL_574_15 = 574,                   /* $@15  */
  YYSYMBOL_575_16 = 575,                   /* $@16  */
  YYSYMBOL_file_description_sequence = 576, /* file_description_sequence  */
  YYSYMBOL_file_description = 577,         /* file_description  */
  YYSYMBOL_file_description_sequence_without_type = 578, /* file_description_sequence_without_type  */
  YYSYMBOL_file_type = 579,                /* file_type  */
  YYSYMBOL_file_description_entry = 580,   /* file_description_entry  */
  YYSYMBOL_581_17 = 581,                   /* @17  */
  YYSYMBOL_file_description_clause_sequence = 582, /* file_description_clause_sequence  */
  YYSYMBOL_file_description_clause = 583,  /* file_description_clause  */
  YYSYMBOL_block_contains_clause = 584,    /* block_contains_clause  */
  YYSYMBOL__records_or_characters = 585,   /* _records_or_characters  */
  YYSYMBOL_record_clause = 586,            /* record_clause  */
  YYSYMBOL_record_depending = 587,         /* record_depending  */
  YYSYMBOL_opt_from_integer = 588,         /* opt_from_integer  */
  YYSYMBOL_opt_to_integer = 589,           /* opt_to_integer  */
  YYSYMBOL_label_records_clause = 590,     /* label_records_clause  */
  YYSYMBOL_label_option = 591,             /* label_option  */
  YYSYMBOL_value_of_clause = 592,          /* value_of_clause  */
  YYSYMBOL_valueof_name = 593,             /* valueof_name  */
  YYSYMBOL_data_records_clause = 594,      /* data_records_clause  */
  YYSYMBOL_linage_clause = 595,            /* linage_clause  */
  YYSYMBOL_linage_sequence = 596,          /* linage_sequence  */
  YYSYMBOL_linage_lines = 597,             /* linage_lines  */
  YYSYMBOL_linage_footing = 598,           /* linage_footing  */
  YYSYMBOL_linage_top = 599,               /* linage_top  */
  YYSYMBOL_linage_bottom = 600,            /* linage_bottom  */
  YYSYMBOL_recording_mode_clause = 601,    /* recording_mode_clause  */
  YYSYMBOL_code_set_clause = 602,          /* code_set_clause  */
  YYSYMBOL_report_clause = 603,            /* report_clause  */
  YYSYMBOL_working_storage_section = 604,  /* working_storage_section  */
  YYSYMBOL_605_18 = 605,                   /* $@18  */
  YYSYMBOL_record_description_list = 606,  /* record_description_list  */
  YYSYMBOL_record_description_list_1 = 607, /* record_description_list_1  */
  YYSYMBOL_608_19 = 608,                   /* $@19  */
  YYSYMBOL_record_description_list_2 = 609, /* record_description_list_2  */
  YYSYMBOL_data_description = 610,         /* data_description  */
  YYSYMBOL_611_20 = 611,                   /* $@20  */
  YYSYMBOL_level_number = 612,             /* level_number  */
  YYSYMBOL_entry_name = 613,               /* entry_name  */
  YYSYMBOL_const_name = 614,               /* const_name  */
  YYSYMBOL_const_global = 615,             /* const_global  */
  YYSYMBOL_lit_or_length = 616,            /* lit_or_length  */
  YYSYMBOL_constant_entry = 617,           /* constant_entry  */
  YYSYMBOL_data_description_clause_sequence = 618, /* data_description_clause_sequence  */
  YYSYMBOL_data_description_clause = 619,  /* data_description_clause  */
  YYSYMBOL_redefines_clause = 620,         /* redefines_clause  */
  YYSYMBOL_external_clause = 621,          /* external_clause  */
  YYSYMBOL_as_extname = 622,               /* as_extname  */
  YYSYMBOL_global_clause = 623,            /* global_clause  */
  YYSYMBOL_picture_clause = 624,           /* picture_clause  */
  YYSYMBOL_usage_clause = 625,             /* usage_clause  */
  YYSYMBOL_usage = 626,                    /* usage  */
  YYSYMBOL_sign_clause = 627,              /* sign_clause  */
  YYSYMBOL_occurs_clause = 628,            /* occurs_clause  */
  YYSYMBOL_occurs_to_integer = 629,        /* occurs_to_integer  */
  YYSYMBOL_occurs_depending = 630,         /* occurs_depending  */
  YYSYMBOL_occurs_keys = 631,              /* occurs_keys  */
  YYSYMBOL_occurs_key_list = 632,          /* occurs_key_list  */
  YYSYMBOL_ascending_or_descending = 633,  /* ascending_or_descending  */
  YYSYMBOL_occurs_indexed = 634,           /* occurs_indexed  */
  YYSYMBOL_occurs_index_list = 635,        /* occurs_index_list  */
  YYSYMBOL_occurs_index = 636,             /* occurs_index  */
  YYSYMBOL_justified_clause = 637,         /* justified_clause  */
  YYSYMBOL_synchronized_clause = 638,      /* synchronized_clause  */
  YYSYMBOL_left_or_right = 639,            /* left_or_right  */
  YYSYMBOL_blank_clause = 640,             /* blank_clause  */
  YYSYMBOL_based_clause = 641,             /* based_clause  */
  YYSYMBOL_value_clause = 642,             /* value_clause  */
  YYSYMBOL_643_21 = 643,                   /* $@21  */
  YYSYMBOL_value_item_list = 644,          /* value_item_list  */
  YYSYMBOL_value_item = 645,               /* value_item  */
  YYSYMBOL_false_is = 646,                 /* false_is  */
  YYSYMBOL_renames_clause = 647,           /* renames_clause  */
  YYSYMBOL_any_length_clause = 648,        /* any_length_clause  */
  YYSYMBOL_local_storage_section = 649,    /* local_storage_section  */
  YYSYMBOL_650_22 = 650,                   /* $@22  */
  YYSYMBOL_linkage_section = 651,          /* linkage_section  */
  YYSYMBOL_652_23 = 652,                   /* $@23  */
  YYSYMBOL_report_section = 653,           /* report_section  */
  YYSYMBOL_654_24 = 654,                   /* $@24  */
  YYSYMBOL_opt_report_description_list = 655, /* opt_report_description_list  */
  YYSYMBOL_report_description_list = 656,  /* report_description_list  */
  YYSYMBOL_report_description_entry = 657, /* report_description_entry  */
  YYSYMBOL_report_description_options = 658, /* report_description_options  */
  YYSYMBOL_report_description_option = 659, /* report_description_option  */
  YYSYMBOL_control_clause = 660,           /* control_clause  */
  YYSYMBOL_control_field_list = 661,       /* control_field_list  */
  YYSYMBOL__final = 662,                   /* _final  */
  YYSYMBOL_identifier_list = 663,          /* identifier_list  */
  YYSYMBOL_page_limit_clause = 664,        /* page_limit_clause  */
  YYSYMBOL_heading_clause = 665,           /* heading_clause  */
  YYSYMBOL_first_detail = 666,             /* first_detail  */
  YYSYMBOL_last_heading = 667,             /* last_heading  */
  YYSYMBOL_last_detail = 668,              /* last_detail  */
  YYSYMBOL_footing_clause = 669,           /* footing_clause  */
  YYSYMBOL_page_line_column = 670,         /* page_line_column  */
  YYSYMBOL_line_or_lines = 671,            /* line_or_lines  */
  YYSYMBOL_report_group_description_list = 672, /* report_group_description_list  */
  YYSYMBOL_report_group_description_entry = 673, /* report_group_description_entry  */
  YYSYMBOL_report_group_options = 674,     /* report_group_options  */
  YYSYMBOL_report_group_option = 675,      /* report_group_option  */
  YYSYMBOL_type_clause = 676,              /* type_clause  */
  YYSYMBOL_type_option = 677,              /* type_option  */
  YYSYMBOL_next_group_clause = 678,        /* next_group_clause  */
  YYSYMBOL_column_clause = 679,            /* column_clause  */
  YYSYMBOL_sum_clause_list = 680,          /* sum_clause_list  */
  YYSYMBOL_sum_clause = 681,               /* sum_clause  */
  YYSYMBOL_ref_id_exp = 682,               /* ref_id_exp  */
  YYSYMBOL_present_when_condition = 683,   /* present_when_condition  */
  YYSYMBOL_varying_clause = 684,           /* varying_clause  */
  YYSYMBOL_line_clause = 685,              /* line_clause  */
  YYSYMBOL_line_keyword_clause = 686,      /* line_keyword_clause  */
  YYSYMBOL_report_line_integer_list = 687, /* report_line_integer_list  */
  YYSYMBOL_line_or_plus = 688,             /* line_or_plus  */
  YYSYMBOL__numbers = 689,                 /* _numbers  */
  YYSYMBOL_source_clause = 690,            /* source_clause  */
  YYSYMBOL_group_indicate_clause = 691,    /* group_indicate_clause  */
  YYSYMBOL__indicate = 692,                /* _indicate  */
  YYSYMBOL_report_name = 693,              /* report_name  */
  YYSYMBOL_screen_section = 694,           /* screen_section  */
  YYSYMBOL_695_25 = 695,                   /* $@25  */
  YYSYMBOL_696_26 = 696,                   /* $@26  */
  YYSYMBOL_opt_screen_description_list = 697, /* opt_screen_description_list  */
  YYSYMBOL_screen_description_list = 698,  /* screen_description_list  */
  YYSYMBOL_screen_description = 699,       /* screen_description  */
  YYSYMBOL_700_27 = 700,                   /* $@27  */
  YYSYMBOL_screen_options = 701,           /* screen_options  */
  YYSYMBOL_screen_option = 702,            /* screen_option  */
  YYSYMBOL_screen_line_plus_minus = 703,   /* screen_line_plus_minus  */
  YYSYMBOL_screen_col_plus_minus = 704,    /* screen_col_plus_minus  */
  YYSYMBOL_screen_occurs_clause = 705,     /* screen_occurs_clause  */
  YYSYMBOL_procedure_division = 706,       /* procedure_division  */
  YYSYMBOL_707_28 = 707,                   /* $@28  */
  YYSYMBOL_708_29 = 708,                   /* $@29  */
  YYSYMBOL_procedure_using_chaining = 709, /* procedure_using_chaining  */
  YYSYMBOL_710_30 = 710,                   /* $@30  */
  YYSYMBOL_711_31 = 711,                   /* $@31  */
  YYSYMBOL_procedure_param_list = 712,     /* procedure_param_list  */
  YYSYMBOL_procedure_param = 713,          /* procedure_param  */
  YYSYMBOL_procedure_type = 714,           /* procedure_type  */
  YYSYMBOL_size_optional = 715,            /* size_optional  */
  YYSYMBOL_procedure_optional = 716,       /* procedure_optional  */
  YYSYMBOL_procedure_returning = 717,      /* procedure_returning  */
  YYSYMBOL_procedure_declaratives = 718,   /* procedure_declaratives  */
  YYSYMBOL_719_32 = 719,                   /* $@32  */
  YYSYMBOL_procedure_list = 720,           /* procedure_list  */
  YYSYMBOL_procedure = 721,                /* procedure  */
  YYSYMBOL_section_header = 722,           /* section_header  */
  YYSYMBOL_paragraph_header = 723,         /* paragraph_header  */
  YYSYMBOL_invalid_statement = 724,        /* invalid_statement  */
  YYSYMBOL_section_name = 725,             /* section_name  */
  YYSYMBOL_opt_segment = 726,              /* opt_segment  */
  YYSYMBOL_statement_list = 727,           /* statement_list  */
  YYSYMBOL_728_33 = 728,                   /* @33  */
  YYSYMBOL_729_34 = 729,                   /* @34  */
  YYSYMBOL_statements = 730,               /* statements  */
  YYSYMBOL_731_35 = 731,                   /* $@35  */
  YYSYMBOL_statement = 732,                /* statement  */
  YYSYMBOL_accept_statement = 733,         /* accept_statement  */
  YYSYMBOL_734_36 = 734,                   /* $@36  */
  YYSYMBOL_accept_body = 735,              /* accept_body  */
  YYSYMBOL_opt_at_line_column = 736,       /* opt_at_line_column  */
  YYSYMBOL_line_number = 737,              /* line_number  */
  YYSYMBOL_column_number = 738,            /* column_number  */
  YYSYMBOL_opt_accp_attr = 739,            /* opt_accp_attr  */
  YYSYMBOL_accp_attrs = 740,               /* accp_attrs  */
  YYSYMBOL_accp_attr = 741,                /* accp_attr  */
  YYSYMBOL_end_accept = 742,               /* end_accept  */
  YYSYMBOL_add_statement = 743,            /* add_statement  */
  YYSYMBOL_744_37 = 744,                   /* $@37  */
  YYSYMBOL_add_body = 745,                 /* add_body  */
  YYSYMBOL_add_to = 746,                   /* add_to  */
  YYSYMBOL_end_add = 747,                  /* end_add  */
  YYSYMBOL_allocate_statement = 748,       /* allocate_statement  */
  YYSYMBOL_749_38 = 749,                   /* $@38  */
  YYSYMBOL_allocate_body = 750,            /* allocate_body  */
  YYSYMBOL_allocate_returning = 751,       /* allocate_returning  */
  YYSYMBOL_alter_statement = 752,          /* alter_statement  */
  YYSYMBOL_alter_options = 753,            /* alter_options  */
  YYSYMBOL__proceed_to = 754,              /* _proceed_to  */
  YYSYMBOL_call_statement = 755,           /* call_statement  */
  YYSYMBOL_756_39 = 756,                   /* $@39  */
  YYSYMBOL_call_using = 757,               /* call_using  */
  YYSYMBOL_758_40 = 758,                   /* $@40  */
  YYSYMBOL_call_param_list = 759,          /* call_param_list  */
  YYSYMBOL_call_param = 760,               /* call_param  */
  YYSYMBOL_call_type = 761,                /* call_type  */
  YYSYMBOL_call_returning = 762,           /* call_returning  */
  YYSYMBOL_call_on_exception = 763,        /* call_on_exception  */
  YYSYMBOL_764_41 = 764,                   /* $@41  */
  YYSYMBOL_call_not_on_exception = 765,    /* call_not_on_exception  */
  YYSYMBOL_766_42 = 766,                   /* $@42  */
  YYSYMBOL_end_call = 767,                 /* end_call  */
  YYSYMBOL_cancel_statement = 768,         /* cancel_statement  */
  YYSYMBOL_769_43 = 769,                   /* $@43  */
  YYSYMBOL_cancel_list = 770,              /* cancel_list  */
  YYSYMBOL_close_statement = 771,          /* close_statement  */
  YYSYMBOL_772_44 = 772,                   /* $@44  */
  YYSYMBOL_close_list = 773,               /* close_list  */
  YYSYMBOL_close_option = 774,             /* close_option  */
  YYSYMBOL_reel_or_unit = 775,             /* reel_or_unit  */
  YYSYMBOL_compute_statement = 776,        /* compute_statement  */
  YYSYMBOL_777_45 = 777,                   /* $@45  */
  YYSYMBOL_compute_body = 778,             /* compute_body  */
  YYSYMBOL_end_compute = 779,              /* end_compute  */
  YYSYMBOL_comp_equal = 780,               /* comp_equal  */
  YYSYMBOL_commit_statement = 781,         /* commit_statement  */
  YYSYMBOL_continue_statement = 782,       /* continue_statement  */
  YYSYMBOL_delete_statement = 783,         /* delete_statement  */
  YYSYMBOL_784_46 = 784,                   /* $@46  */
  YYSYMBOL_end_delete = 785,               /* end_delete  */
  YYSYMBOL_display_statement = 786,        /* display_statement  */
  YYSYMBOL_787_47 = 787,                   /* $@47  */
  YYSYMBOL_display_body = 788,             /* display_body  */
  YYSYMBOL_display_upon = 789,             /* display_upon  */
  YYSYMBOL_with_clause = 790,              /* with_clause  */
  YYSYMBOL_disp_attrs = 791,               /* disp_attrs  */
  YYSYMBOL_disp_attr = 792,                /* disp_attr  */
  YYSYMBOL_end_display = 793,              /* end_display  */
  YYSYMBOL_divide_statement = 794,         /* divide_statement  */
  YYSYMBOL_795_48 = 795,                   /* $@48  */
  YYSYMBOL_divide_body = 796,              /* divide_body  */
  YYSYMBOL_end_divide = 797,               /* end_divide  */
  YYSYMBOL_entry_statement = 798,          /* entry_statement  */
  YYSYMBOL_799_49 = 799,                   /* $@49  */
  YYSYMBOL_evaluate_statement = 800,       /* evaluate_statement  */
  YYSYMBOL_801_50 = 801,                   /* $@50  */
  YYSYMBOL_evaluate_subject_list = 802,    /* evaluate_subject_list  */
  YYSYMBOL_evaluate_subject = 803,         /* evaluate_subject  */
  YYSYMBOL_evaluate_condition_list = 804,  /* evaluate_condition_list  */
  YYSYMBOL_evaluate_case_list = 805,       /* evaluate_case_list  */
  YYSYMBOL_evaluate_case = 806,            /* evaluate_case  */
  YYSYMBOL_807_51 = 807,                   /* $@51  */
  YYSYMBOL_evaluate_other = 808,           /* evaluate_other  */
  YYSYMBOL_809_52 = 809,                   /* $@52  */
  YYSYMBOL_evaluate_when_list = 810,       /* evaluate_when_list  */
  YYSYMBOL_evaluate_object_list = 811,     /* evaluate_object_list  */
  YYSYMBOL_evaluate_object = 812,          /* evaluate_object  */
  YYSYMBOL_opt_evaluate_thru_expr = 813,   /* opt_evaluate_thru_expr  */
  YYSYMBOL_end_evaluate = 814,             /* end_evaluate  */
  YYSYMBOL_exit_statement = 815,           /* exit_statement  */
  YYSYMBOL_816_53 = 816,                   /* $@53  */
  YYSYMBOL_exit_body = 817,                /* exit_body  */
  YYSYMBOL_free_statement = 818,           /* free_statement  */
  YYSYMBOL_819_54 = 819,                   /* $@54  */
  YYSYMBOL_generate_statement = 820,       /* generate_statement  */
  YYSYMBOL_821_55 = 821,                   /* $@55  */
  YYSYMBOL_goto_statement = 822,           /* goto_statement  */
  YYSYMBOL_823_56 = 823,                   /* $@56  */
  YYSYMBOL_goto_depending = 824,           /* goto_depending  */
  YYSYMBOL_goback_statement = 825,         /* goback_statement  */
  YYSYMBOL_826_57 = 826,                   /* $@57  */
  YYSYMBOL_if_statement = 827,             /* if_statement  */
  YYSYMBOL_828_58 = 828,                   /* $@58  */
  YYSYMBOL_829_59 = 829,                   /* $@59  */
  YYSYMBOL_if_else_sentence = 830,         /* if_else_sentence  */
  YYSYMBOL_831_60 = 831,                   /* $@60  */
  YYSYMBOL_end_if = 832,                   /* end_if  */
  YYSYMBOL_initialize_statement = 833,     /* initialize_statement  */
  YYSYMBOL_834_61 = 834,                   /* $@61  */
  YYSYMBOL_initialize_filler = 835,        /* initialize_filler  */
  YYSYMBOL_initialize_value = 836,         /* initialize_value  */
  YYSYMBOL_initialize_replacing = 837,     /* initialize_replacing  */
  YYSYMBOL_initialize_replacing_list = 838, /* initialize_replacing_list  */
  YYSYMBOL_initialize_replacing_item = 839, /* initialize_replacing_item  */
  YYSYMBOL_initialize_category = 840,      /* initialize_category  */
  YYSYMBOL_initialize_default = 841,       /* initialize_default  */
  YYSYMBOL_initiate_statement = 842,       /* initiate_statement  */
  YYSYMBOL_843_62 = 843,                   /* $@62  */
  YYSYMBOL_inspect_statement = 844,        /* inspect_statement  */
  YYSYMBOL_845_63 = 845,                   /* $@63  */
  YYSYMBOL_send_identifier = 846,          /* send_identifier  */
  YYSYMBOL_inspect_list = 847,             /* inspect_list  */
  YYSYMBOL_inspect_item = 848,             /* inspect_item  */
  YYSYMBOL_inspect_tallying = 849,         /* inspect_tallying  */
  YYSYMBOL_850_64 = 850,                   /* $@64  */
  YYSYMBOL_tallying_list = 851,            /* tallying_list  */
  YYSYMBOL_tallying_item = 852,            /* tallying_item  */
  YYSYMBOL_inspect_replacing = 853,        /* inspect_replacing  */
  YYSYMBOL_replacing_list = 854,           /* replacing_list  */
  YYSYMBOL_replacing_item = 855,           /* replacing_item  */
  YYSYMBOL_rep_keyword = 856,              /* rep_keyword  */
  YYSYMBOL_replacing_region = 857,         /* replacing_region  */
  YYSYMBOL_inspect_converting = 858,       /* inspect_converting  */
  YYSYMBOL_inspect_region = 859,           /* inspect_region  */
  YYSYMBOL__initial = 860,                 /* _initial  */
  YYSYMBOL_merge_statement = 861,          /* merge_statement  */
  YYSYMBOL_862_65 = 862,                   /* $@65  */
  YYSYMBOL_move_statement = 863,           /* move_statement  */
  YYSYMBOL_864_66 = 864,                   /* $@66  */
  YYSYMBOL_move_body = 865,                /* move_body  */
  YYSYMBOL_multiply_statement = 866,       /* multiply_statement  */
  YYSYMBOL_867_67 = 867,                   /* $@67  */
  YYSYMBOL_multiply_body = 868,            /* multiply_body  */
  YYSYMBOL_end_multiply = 869,             /* end_multiply  */
  YYSYMBOL_open_statement = 870,           /* open_statement  */
  YYSYMBOL_871_68 = 871,                   /* $@68  */
  YYSYMBOL_open_list = 872,                /* open_list  */
  YYSYMBOL_open_mode = 873,                /* open_mode  */
  YYSYMBOL_open_sharing = 874,             /* open_sharing  */
  YYSYMBOL_open_option = 875,              /* open_option  */
  YYSYMBOL_perform_statement = 876,        /* perform_statement  */
  YYSYMBOL_877_69 = 877,                   /* $@69  */
  YYSYMBOL_perform_body = 878,             /* perform_body  */
  YYSYMBOL_879_70 = 879,                   /* $@70  */
  YYSYMBOL_end_perform = 880,              /* end_perform  */
  YYSYMBOL_perform_procedure = 881,        /* perform_procedure  */
  YYSYMBOL_perform_option = 882,           /* perform_option  */
  YYSYMBOL_perform_test = 883,             /* perform_test  */
  YYSYMBOL_perform_varying_list = 884,     /* perform_varying_list  */
  YYSYMBOL_perform_varying = 885,          /* perform_varying  */
  YYSYMBOL_read_statement = 886,           /* read_statement  */
  YYSYMBOL_887_71 = 887,                   /* $@71  */
  YYSYMBOL_read_into = 888,                /* read_into  */
  YYSYMBOL_with_lock = 889,                /* with_lock  */
  YYSYMBOL_read_key = 890,                 /* read_key  */
  YYSYMBOL_read_handler = 891,             /* read_handler  */
  YYSYMBOL_end_read = 892,                 /* end_read  */
  YYSYMBOL_release_statement = 893,        /* release_statement  */
  YYSYMBOL_894_72 = 894,                   /* $@72  */
  YYSYMBOL_return_statement = 895,         /* return_statement  */
  YYSYMBOL_896_73 = 896,                   /* $@73  */
  YYSYMBOL_end_return = 897,               /* end_return  */
  YYSYMBOL_rewrite_statement = 898,        /* rewrite_statement  */
  YYSYMBOL_899_74 = 899,                   /* $@74  */
  YYSYMBOL_write_lock = 900,               /* write_lock  */
  YYSYMBOL_end_rewrite = 901,              /* end_rewrite  */
  YYSYMBOL_rollback_statement = 902,       /* rollback_statement  */
  YYSYMBOL_search_statement = 903,         /* search_statement  */
  YYSYMBOL_904_75 = 904,                   /* $@75  */
  YYSYMBOL_search_body = 905,              /* search_body  */
  YYSYMBOL_906_76 = 906,                   /* $@76  */
  YYSYMBOL_search_varying = 907,           /* search_varying  */
  YYSYMBOL_search_at_end = 908,            /* search_at_end  */
  YYSYMBOL_909_77 = 909,                   /* $@77  */
  YYSYMBOL_search_whens = 910,             /* search_whens  */
  YYSYMBOL_search_when = 911,              /* search_when  */
  YYSYMBOL_912_78 = 912,                   /* $@78  */
  YYSYMBOL_end_search = 913,               /* end_search  */
  YYSYMBOL_set_statement = 914,            /* set_statement  */
  YYSYMBOL_915_79 = 915,                   /* $@79  */
  YYSYMBOL_set_body = 916,                 /* set_body  */
  YYSYMBOL_set_environment = 917,          /* set_environment  */
  YYSYMBOL_set_to = 918,                   /* set_to  */
  YYSYMBOL_set_up_down = 919,              /* set_up_down  */
  YYSYMBOL_up_or_down = 920,               /* up_or_down  */
  YYSYMBOL_set_to_on_off_sequence = 921,   /* set_to_on_off_sequence  */
  YYSYMBOL_set_to_on_off = 922,            /* set_to_on_off  */
  YYSYMBOL_set_to_true_false_sequence = 923, /* set_to_true_false_sequence  */
  YYSYMBOL_set_to_true_false = 924,        /* set_to_true_false  */
  YYSYMBOL_sort_statement = 925,           /* sort_statement  */
  YYSYMBOL_926_80 = 926,                   /* $@80  */
  YYSYMBOL_sort_body = 927,                /* sort_body  */
  YYSYMBOL_928_81 = 928,                   /* $@81  */
  YYSYMBOL_sort_key_list = 929,            /* sort_key_list  */
  YYSYMBOL_opt_key_list = 930,             /* opt_key_list  */
  YYSYMBOL_sort_duplicates = 931,          /* sort_duplicates  */
  YYSYMBOL_sort_collating = 932,           /* sort_collating  */
  YYSYMBOL_sort_input = 933,               /* sort_input  */
  YYSYMBOL_sort_output = 934,              /* sort_output  */
  YYSYMBOL_start_statement = 935,          /* start_statement  */
  YYSYMBOL_936_82 = 936,                   /* $@82  */
  YYSYMBOL_937_83 = 937,                   /* @83  */
  YYSYMBOL_start_key = 938,                /* start_key  */
  YYSYMBOL_start_op = 939,                 /* start_op  */
  YYSYMBOL_end_start = 940,                /* end_start  */
  YYSYMBOL_stop_statement = 941,           /* stop_statement  */
  YYSYMBOL_942_84 = 942,                   /* $@84  */
  YYSYMBOL_stop_returning = 943,           /* stop_returning  */
  YYSYMBOL_string_statement = 944,         /* string_statement  */
  YYSYMBOL_945_85 = 945,                   /* $@85  */
  YYSYMBOL_string_item_list = 946,         /* string_item_list  */
  YYSYMBOL_string_item = 947,              /* string_item  */
  YYSYMBOL_opt_with_pointer = 948,         /* opt_with_pointer  */
  YYSYMBOL_end_string = 949,               /* end_string  */
  YYSYMBOL_subtract_statement = 950,       /* subtract_statement  */
  YYSYMBOL_951_86 = 951,                   /* $@86  */
  YYSYMBOL_subtract_body = 952,            /* subtract_body  */
  YYSYMBOL_end_subtract = 953,             /* end_subtract  */
  YYSYMBOL_suppress_statement = 954,       /* suppress_statement  */
  YYSYMBOL__printing = 955,                /* _printing  */
  YYSYMBOL_terminate_statement = 956,      /* terminate_statement  */
  YYSYMBOL_957_87 = 957,                   /* $@87  */
  YYSYMBOL_transform_statement = 958,      /* transform_statement  */
  YYSYMBOL_959_88 = 959,                   /* $@88  */
  YYSYMBOL_unlock_statement = 960,         /* unlock_statement  */
  YYSYMBOL_961_89 = 961,                   /* $@89  */
  YYSYMBOL_opt_record = 962,               /* opt_record  */
  YYSYMBOL_unstring_statement = 963,       /* unstring_statement  */
  YYSYMBOL_964_90 = 964,                   /* $@90  */
  YYSYMBOL_unstring_delimited = 965,       /* unstring_delimited  */
  YYSYMBOL_unstring_delimited_list = 966,  /* unstring_delimited_list  */
  YYSYMBOL_unstring_delimited_item = 967,  /* unstring_delimited_item  */
  YYSYMBOL_unstring_into = 968,            /* unstring_into  */
  YYSYMBOL_unstring_into_item = 969,       /* unstring_into_item  */
  YYSYMBOL_unstring_into_delimiter = 970,  /* unstring_into_delimiter  */
  YYSYMBOL_unstring_into_count = 971,      /* unstring_into_count  */
  YYSYMBOL_unstring_tallying = 972,        /* unstring_tallying  */
  YYSYMBOL_end_unstring = 973,             /* end_unstring  */
  YYSYMBOL_use_statement = 974,            /* use_statement  */
  YYSYMBOL_use_exception = 975,            /* use_exception  */
  YYSYMBOL_use_global = 976,               /* use_global  */
  YYSYMBOL_use_exception_target = 977,     /* use_exception_target  */
  YYSYMBOL__after = 978,                   /* _after  */
  YYSYMBOL__standard = 979,                /* _standard  */
  YYSYMBOL_exception_or_error = 980,       /* exception_or_error  */
  YYSYMBOL_exception_or_overflow = 981,    /* exception_or_overflow  */
  YYSYMBOL_not_exception_or_overflow = 982, /* not_exception_or_overflow  */
  YYSYMBOL__procedure = 983,               /* _procedure  */
  YYSYMBOL_use_debugging = 984,            /* use_debugging  */
  YYSYMBOL_use_debugging_target = 985,     /* use_debugging_target  */
  YYSYMBOL_use_reporting = 986,            /* use_reporting  */
  YYSYMBOL_write_statement = 987,          /* write_statement  */
  YYSYMBOL_988_91 = 988,                   /* $@91  */
  YYSYMBOL_write_from = 989,               /* write_from  */
  YYSYMBOL_write_option = 990,             /* write_option  */
  YYSYMBOL_before_or_after = 991,          /* before_or_after  */
  YYSYMBOL_write_handler = 992,            /* write_handler  */
  YYSYMBOL_end_write = 993,                /* end_write  */
  YYSYMBOL_on_accp_exception = 994,        /* on_accp_exception  */
  YYSYMBOL_on_disp_exception = 995,        /* on_disp_exception  */
  YYSYMBOL_opt_on_exception = 996,         /* opt_on_exception  */
  YYSYMBOL_997_92 = 997,                   /* $@92  */
  YYSYMBOL_opt_not_on_exception = 998,     /* opt_not_on_exception  */
  YYSYMBOL_999_93 = 999,                   /* $@93  */
  YYSYMBOL_on_size_error = 1000,           /* on_size_error  */
  YYSYMBOL_opt_on_size_error = 1001,       /* opt_on_size_error  */
  YYSYMBOL_1002_94 = 1002,                 /* $@94  */
  YYSYMBOL_opt_not_on_size_error = 1003,   /* opt_not_on_size_error  */
  YYSYMBOL_1004_95 = 1004,                 /* $@95  */
  YYSYMBOL_on_overflow = 1005,             /* on_overflow  */
  YYSYMBOL_opt_on_overflow = 1006,         /* opt_on_overflow  */
  YYSYMBOL_1007_96 = 1007,                 /* $@96  */
  YYSYMBOL_opt_not_on_overflow = 1008,     /* opt_not_on_overflow  */
  YYSYMBOL_1009_97 = 1009,                 /* $@97  */
  YYSYMBOL_at_end = 1010,                  /* at_end  */
  YYSYMBOL_at_end_sentence = 1011,         /* at_end_sentence  */
  YYSYMBOL_1012_98 = 1012,                 /* $@98  */
  YYSYMBOL_not_at_end_sentence = 1013,     /* not_at_end_sentence  */
  YYSYMBOL_1014_99 = 1014,                 /* $@99  */
  YYSYMBOL_at_eop = 1015,                  /* at_eop  */
  YYSYMBOL_at_eop_sentence = 1016,         /* at_eop_sentence  */
  YYSYMBOL_1017_100 = 1017,                /* $@100  */
  YYSYMBOL_not_at_eop_sentence = 1018,     /* not_at_eop_sentence  */
  YYSYMBOL_1019_101 = 1019,                /* $@101  */
  YYSYMBOL_opt_invalid_key = 1020,         /* opt_invalid_key  */
  YYSYMBOL_invalid_key = 1021,             /* invalid_key  */
  YYSYMBOL_invalid_key_sentence = 1022,    /* invalid_key_sentence  */
  YYSYMBOL_1023_102 = 1023,                /* $@102  */
  YYSYMBOL_not_invalid_key_sentence = 1024, /* not_invalid_key_sentence  */
  YYSYMBOL_1025_103 = 1025,                /* $@103  */
  YYSYMBOL__opt_scroll_lines = 1026,       /* _opt_scroll_lines  */
  YYSYMBOL_condition = 1027,               /* condition  */
  YYSYMBOL_expr = 1028,                    /* expr  */
  YYSYMBOL_partial_expr = 1029,            /* partial_expr  */
  YYSYMBOL_1030_104 = 1030,                /* $@104  */
  YYSYMBOL_expr_tokens = 1031,             /* expr_tokens  */
  YYSYMBOL_expr_token = 1032,              /* expr_token  */
  YYSYMBOL_eq = 1033,                      /* eq  */
  YYSYMBOL_gt = 1034,                      /* gt  */
  YYSYMBOL_lt = 1035,                      /* lt  */
  YYSYMBOL_ge = 1036,                      /* ge  */
  YYSYMBOL_le = 1037,                      /* le  */
  YYSYMBOL_exp_list = 1038,                /* exp_list  */
  YYSYMBOL_e_sep = 1039,                   /* e_sep  */
  YYSYMBOL_exp = 1040,                     /* exp  */
  YYSYMBOL_linage_counter = 1041,          /* linage_counter  */
  YYSYMBOL_arithmetic_x_list = 1042,       /* arithmetic_x_list  */
  YYSYMBOL_arithmetic_x = 1043,            /* arithmetic_x  */
  YYSYMBOL_record_name = 1044,             /* record_name  */
  YYSYMBOL_table_name = 1045,              /* table_name  */
  YYSYMBOL_file_name_list = 1046,          /* file_name_list  */
  YYSYMBOL_file_name = 1047,               /* file_name  */
  YYSYMBOL_mnemonic_name_list = 1048,      /* mnemonic_name_list  */
  YYSYMBOL_mnemonic_name = 1049,           /* mnemonic_name  */
  YYSYMBOL_procedure_name_list = 1050,     /* procedure_name_list  */
  YYSYMBOL_procedure_name = 1051,          /* procedure_name  */
  YYSYMBOL_label = 1052,                   /* label  */
  YYSYMBOL_integer_label = 1053,           /* integer_label  */
  YYSYMBOL_reference_list = 1054,          /* reference_list  */
  YYSYMBOL_reference = 1055,               /* reference  */
  YYSYMBOL_opt_reference = 1056,           /* opt_reference  */
  YYSYMBOL_reference_or_literal = 1057,    /* reference_or_literal  */
  YYSYMBOL_undefined_word = 1058,          /* undefined_word  */
  YYSYMBOL_target_x_list = 1059,           /* target_x_list  */
  YYSYMBOL_target_x = 1060,                /* target_x  */
  YYSYMBOL_x_list = 1061,                  /* x_list  */
  YYSYMBOL_x = 1062,                       /* x  */
  YYSYMBOL_arith_x = 1063,                 /* arith_x  */
  YYSYMBOL_prog_or_entry = 1064,           /* prog_or_entry  */
  YYSYMBOL_alnum_or_id = 1065,             /* alnum_or_id  */
  YYSYMBOL_simple_value = 1066,            /* simple_value  */
  YYSYMBOL_simple_all_value = 1067,        /* simple_all_value  */
  YYSYMBOL_id_or_lit = 1068,               /* id_or_lit  */
  YYSYMBOL_id_or_lit_or_func = 1069,       /* id_or_lit_or_func  */
  YYSYMBOL_num_id_or_lit = 1070,           /* num_id_or_lit  */
  YYSYMBOL_identifier = 1071,              /* identifier  */
  YYSYMBOL_identifier_1 = 1072,            /* identifier_1  */
  YYSYMBOL_qualified_word = 1073,          /* qualified_word  */
  YYSYMBOL_subref = 1074,                  /* subref  */
  YYSYMBOL_refmod = 1075,                  /* refmod  */
  YYSYMBOL_integer = 1076,                 /* integer  */
  YYSYMBOL_literal = 1077,                 /* literal  */
  YYSYMBOL_basic_literal = 1078,           /* basic_literal  */
  YYSYMBOL_basic_value = 1079,             /* basic_value  */
  YYSYMBOL_function = 1080,                /* function  */
  YYSYMBOL_func_refmod = 1081,             /* func_refmod  */
  YYSYMBOL_func_args = 1082,               /* func_args  */
  YYSYMBOL_list_func_args = 1083,          /* list_func_args  */
  YYSYMBOL_trim_args = 1084,               /* trim_args  */
  YYSYMBOL_numvalc_args = 1085,            /* numvalc_args  */
  YYSYMBOL_locale_dt_args = 1086,          /* locale_dt_args  */
  YYSYMBOL_not_const_word = 1087,          /* not_const_word  */
  YYSYMBOL_flag_all = 1088,                /* flag_all  */
  YYSYMBOL_flag_duplicates = 1089,         /* flag_duplicates  */
  YYSYMBOL_flag_initialized = 1090,        /* flag_initialized  */
  YYSYMBOL_flag_next = 1091,               /* flag_next  */
  YYSYMBOL_flag_not = 1092,                /* flag_not  */
  YYSYMBOL_flag_optional = 1093,           /* flag_optional  */
  YYSYMBOL_flag_rounded = 1094,            /* flag_rounded  */
  YYSYMBOL_flag_separate = 1095,           /* flag_separate  */
  YYSYMBOL_in_of = 1096,                   /* in_of  */
  YYSYMBOL_records = 1097,                 /* records  */
  YYSYMBOL_with_dups = 1098,               /* with_dups  */
  YYSYMBOL_coll_sequence = 1099,           /* coll_sequence  */
  YYSYMBOL__advancing = 1100,              /* _advancing  */
  YYSYMBOL__are = 1101,                    /* _are  */
  YYSYMBOL__area = 1102,                   /* _area  */
  YYSYMBOL__as = 1103,                     /* _as  */
  YYSYMBOL__at = 1104,                     /* _at  */
  YYSYMBOL__binary = 1105,                 /* _binary  */
  YYSYMBOL__by = 1106,                     /* _by  */
  YYSYMBOL__character = 1107,              /* _character  */
  YYSYMBOL__characters = 1108,             /* _characters  */
  YYSYMBOL__contains = 1109,               /* _contains  */
  YYSYMBOL__data = 1110,                   /* _data  */
  YYSYMBOL__file = 1111,                   /* _file  */
  YYSYMBOL__for = 1112,                    /* _for  */
  YYSYMBOL__from = 1113,                   /* _from  */
  YYSYMBOL__in = 1114,                     /* _in  */
  YYSYMBOL__is = 1115,                     /* _is  */
  YYSYMBOL__is_are = 1116,                 /* _is_are  */
  YYSYMBOL__key = 1117,                    /* _key  */
  YYSYMBOL__line_or_lines = 1118,          /* _line_or_lines  */
  YYSYMBOL__lines = 1119,                  /* _lines  */
  YYSYMBOL__mode = 1120,                   /* _mode  */
  YYSYMBOL__number = 1121,                 /* _number  */
  YYSYMBOL__of = 1122,                     /* _of  */
  YYSYMBOL__on = 1123,                     /* _on  */
  YYSYMBOL__in_order = 1124,               /* _in_order  */
  YYSYMBOL__other = 1125,                  /* _other  */
  YYSYMBOL__program = 1126,                /* _program  */
  YYSYMBOL__record = 1127,                 /* _record  */
  YYSYMBOL__right = 1128,                  /* _right  */
  YYSYMBOL__set = 1129,                    /* _set  */
  YYSYMBOL__sign = 1130,                   /* _sign  */
  YYSYMBOL__sign_is = 1131,                /* _sign_is  */
  YYSYMBOL__size = 1132,                   /* _size  */
  YYSYMBOL__status = 1133,                 /* _status  */
  YYSYMBOL__tape = 1134,                   /* _tape  */
  YYSYMBOL__than = 1135,                   /* _than  */
  YYSYMBOL__then = 1136,                   /* _then  */
  YYSYMBOL__times = 1137,                  /* _times  */
  YYSYMBOL__to = 1138,                     /* _to  */
  YYSYMBOL__when = 1139,                   /* _when  */
  YYSYMBOL__with = 1140                    /* _with  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   5462

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  451
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  690
/* YYNRULES -- Number of rules.  */
#define YYNRULES  1518
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  2240

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   692


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int16 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   450,     2,
     445,   446,   439,   437,     2,   438,   443,   440,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,   449,     2,
     448,   444,   447,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,   442,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   441
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   757,   757,   757,   799,   800,   804,   805,   810,   811,
     809,   819,   820,   818,   828,   829,   827,   834,   835,   836,
     839,   840,   864,   888,   918,   917,   958,  1002,  1003,  1007,
    1008,  1011,  1012,  1016,  1023,  1030,  1034,  1038,  1050,  1051,
    1061,  1062,  1071,  1072,  1076,  1077,  1078,  1079,  1088,  1091,
    1092,  1093,  1094,  1098,  1105,  1114,  1117,  1118,  1119,  1120,
    1124,  1125,  1129,  1130,  1131,  1135,  1142,  1143,  1147,  1154,
    1166,  1169,  1170,  1174,  1175,  1179,  1183,  1190,  1191,  1201,
    1204,  1205,  1209,  1210,  1214,  1215,  1216,  1217,  1218,  1219,
    1220,  1221,  1222,  1223,  1224,  1231,  1242,  1241,  1254,  1255,
    1263,  1264,  1272,  1271,  1283,  1284,  1285,  1286,  1287,  1295,
    1296,  1301,  1302,  1304,  1303,  1315,  1316,  1320,  1321,  1322,
    1323,  1324,  1325,  1329,  1330,  1331,  1332,  1333,  1334,  1341,
    1352,  1364,  1365,  1369,  1370,  1377,  1386,  1387,  1391,  1392,
    1406,  1421,  1488,  1499,  1506,  1513,  1519,  1526,  1527,  1531,
    1530,  1540,  1539,  1555,  1556,  1559,  1560,  1565,  1564,  1585,
    1586,  1590,  1591,  1592,  1593,  1594,  1595,  1596,  1597,  1598,
    1599,  1600,  1601,  1602,  1609,  1613,  1619,  1620,  1621,  1624,
    1625,  1629,  1633,  1634,  1641,  1648,  1652,  1653,  1654,  1661,
    1686,  1696,  1705,  1707,  1708,  1714,  1718,  1719,  1720,  1723,
    1724,  1725,  1729,  1733,  1734,  1740,  1741,  1745,  1754,  1763,
    1772,  1787,  1797,  1804,  1811,  1812,  1813,  1819,  1826,  1833,
    1837,  1838,  1839,  1847,  1848,  1851,  1852,  1856,  1857,  1861,
    1862,  1868,  1893,  1894,  1895,  1896,  1902,  1909,  1910,  1914,
    1917,  1918,  1926,  1927,  1941,  1942,  1942,  1945,  1944,  1957,
    1958,  1962,  1974,  1983,  1987,  1988,  1998,  1997,  2015,  2016,
    2020,  2027,  2034,  2035,  2036,  2037,  2038,  2039,  2040,  2041,
    2042,  2049,  2053,  2053,  2053,  2059,  2071,  2096,  2120,  2121,
    2128,  2129,  2133,  2134,  2141,  2148,  2149,  2156,  2160,  2169,
    2170,  2176,  2186,  2204,  2205,  2209,  2210,  2211,  2215,  2222,
    2229,  2239,  2246,  2264,  2268,  2279,  2280,  2280,  2291,  2292,
    2296,  2296,  2313,  2314,  2316,  2320,  2322,  2321,  2353,  2358,
    2363,  2369,  2378,  2386,  2387,  2395,  2396,  2397,  2401,  2421,
    2425,  2434,  2435,  2436,  2437,  2438,  2439,  2440,  2441,  2442,
    2443,  2444,  2445,  2446,  2447,  2454,  2476,  2498,  2499,  2511,
    2531,  2538,  2539,  2543,  2544,  2545,  2546,  2547,  2548,  2549,
    2550,  2551,  2552,  2553,  2554,  2559,  2564,  2565,  2566,  2567,
    2568,  2569,  2570,  2571,  2572,  2573,  2574,  2575,  2576,  2577,
    2578,  2579,  2580,  2581,  2582,  2590,  2598,  2606,  2613,  2618,
    2629,  2646,  2647,  2650,  2651,  2658,  2682,  2683,  2700,  2701,
    2704,  2705,  2712,  2713,  2718,  2728,  2735,  2738,  2739,  2740,
    2747,  2754,  2779,  2779,  2784,  2785,  2789,  2790,  2793,  2794,
    2807,  2819,  2839,  2853,  2855,  2854,  2874,  2875,  2875,  2888,
    2890,  2889,  2901,  2902,  2906,  2907,  2916,  2923,  2926,  2930,
    2934,  2935,  2936,  2943,  2944,  2948,  2951,  2951,  2954,  2955,
    2961,  2966,  2967,  2970,  2971,  2974,  2975,  2978,  2979,  2982,
    2983,  2987,  2988,  2989,  2993,  2994,  2997,  2998,  3002,  3006,
    3007,  3011,  3012,  3013,  3014,  3015,  3016,  3017,  3018,  3019,
    3020,  3021,  3022,  3023,  3024,  3025,  3026,  3030,  3034,  3035,
    3036,  3037,  3038,  3039,  3040,  3044,  3048,  3049,  3050,  3054,
    3055,  3059,  3063,  3068,  3072,  3076,  3080,  3081,  3085,  3086,
    3090,  3091,  3092,  3095,  3095,  3095,  3098,  3102,  3105,  3105,
    3108,  3115,  3116,  3117,  3116,  3134,  3135,  3139,  3140,  3145,
    3147,  3146,  3182,  3183,  3187,  3188,  3189,  3190,  3191,  3192,
    3193,  3194,  3195,  3196,  3197,  3198,  3199,  3200,  3201,  3202,
    3203,  3207,  3211,  3215,  3219,  3220,  3221,  3222,  3223,  3224,
    3225,  3226,  3233,  3237,  3247,  3250,  3254,  3258,  3262,  3270,
    3273,  3277,  3281,  3285,  3293,  3306,  3308,  3318,  3307,  3345,
    3347,  3346,  3353,  3352,  3361,  3362,  3367,  3374,  3376,  3380,
    3390,  3392,  3400,  3408,  3437,  3468,  3470,  3480,  3485,  3496,
    3497,  3497,  3524,  3525,  3529,  3530,  3531,  3532,  3548,  3552,
    3564,  3595,  3632,  3644,  3647,  3648,  3657,  3661,  3657,  3674,
    3674,  3692,  3696,  3697,  3698,  3699,  3700,  3701,  3702,  3703,
    3704,  3705,  3706,  3707,  3708,  3709,  3710,  3711,  3712,  3713,
    3714,  3715,  3716,  3717,  3718,  3719,  3720,  3721,  3722,  3723,
    3724,  3725,  3726,  3727,  3728,  3729,  3730,  3731,  3732,  3733,
    3734,  3735,  3736,  3737,  3738,  3739,  3740,  3741,  3742,  3743,
    3744,  3767,  3766,  3779,  3783,  3787,  3791,  3795,  3799,  3803,
    3807,  3811,  3815,  3819,  3823,  3827,  3831,  3835,  3839,  3843,
    3850,  3851,  3852,  3853,  3854,  3855,  3859,  3863,  3864,  3867,
    3868,  3872,  3873,  3877,  3878,  3879,  3880,  3881,  3882,  3883,
    3884,  3888,  3892,  3896,  3901,  3902,  3903,  3904,  3905,  3906,
    3910,  3911,  3920,  3920,  3926,  3930,  3934,  3940,  3941,  3945,
    3946,  3955,  3955,  3960,  3964,  3971,  3972,  3981,  3987,  3988,
    3992,  3992,  4000,  4000,  4010,  4012,  4011,  4020,  4021,  4026,
    4033,  4040,  4042,  4046,  4054,  4065,  4066,  4067,  4072,  4076,
    4075,  4087,  4091,  4090,  4101,  4102,  4111,  4111,  4115,  4116,
    4128,  4128,  4132,  4133,  4144,  4145,  4146,  4147,  4148,  4151,
    4151,  4159,  4159,  4165,  4172,  4173,  4176,  4176,  4183,  4196,
    4209,  4209,  4220,  4221,  4231,  4230,  4243,  4247,  4251,  4255,
    4259,  4266,  4267,  4268,  4269,  4270,  4274,  4275,  4276,  4280,
    4281,  4286,  4287,  4288,  4289,  4290,  4291,  4292,  4293,  4294,
    4295,  4299,  4303,  4307,  4312,  4313,  4317,  4318,  4327,  4327,
    4333,  4337,  4341,  4345,  4349,  4356,  4357,  4366,  4366,  4388,
    4387,  4406,  4407,  4412,  4421,  4426,  4434,  4444,  4445,  4451,
    4450,  4463,  4467,  4466,  4478,  4479,  4484,  4485,  4490,  4519,
    4520,  4521,  4524,  4525,  4529,  4530,  4539,  4539,  4544,  4545,
    4553,  4570,  4587,  4605,  4630,  4630,  4643,  4643,  4656,  4656,
    4665,  4669,  4682,  4682,  4695,  4697,  4695,  4705,  4710,  4714,
    4713,  4724,  4725,  4734,  4734,  4742,  4743,  4747,  4748,  4749,
    4753,  4754,  4759,  4760,  4765,  4769,  4770,  4771,  4772,  4773,
    4774,  4775,  4779,  4780,  4789,  4789,  4802,  4801,  4811,  4812,
    4813,  4817,  4818,  4822,  4823,  4824,  4830,  4830,  4835,  4836,
    4840,  4841,  4842,  4843,  4844,  4845,  4851,  4855,  4856,  4860,
    4865,  4869,  4870,  4871,  4872,  4873,  4877,  4903,  4912,  4913,
    4917,  4917,  4925,  4925,  4935,  4935,  4940,  4944,  4956,  4956,
    4962,  4966,  4973,  4974,  4983,  4983,  4987,  4988,  5002,  5003,
    5004,  5005,  5009,  5010,  5014,  5015,  5016,  5028,  5028,  5033,
    5038,  5037,  5047,  5054,  5055,  5059,  5064,  5073,  5076,  5080,
    5085,  5092,  5099,  5100,  5104,  5105,  5110,  5122,  5122,  5145,
    5146,  5150,  5151,  5155,  5159,  5163,  5167,  5174,  5175,  5178,
    5179,  5180,  5184,  5185,  5194,  5194,  5209,  5209,  5220,  5221,
    5230,  5230,  5241,  5242,  5246,  5253,  5254,  5263,  5276,  5276,
    5282,  5287,  5286,  5297,  5298,  5302,  5304,  5303,  5314,  5315,
    5320,  5319,  5330,  5331,  5340,  5340,  5345,  5346,  5347,  5348,
    5349,  5355,  5364,  5368,  5377,  5384,  5385,  5391,  5392,  5396,
    5405,  5406,  5410,  5414,  5426,  5426,  5432,  5431,  5448,  5451,
    5467,  5468,  5471,  5472,  5476,  5477,  5482,  5487,  5495,  5507,
    5512,  5520,  5536,  5537,  5536,  5557,  5558,  5562,  5563,  5564,
    5565,  5566,  5570,  5571,  5580,  5580,  5585,  5592,  5593,  5594,
    5603,  5603,  5612,  5613,  5617,  5618,  5619,  5623,  5624,  5628,
    5629,  5638,  5638,  5644,  5648,  5652,  5659,  5660,  5669,  5676,
    5677,  5685,  5685,  5698,  5698,  5714,  5714,  5723,  5725,  5726,
    5735,  5735,  5745,  5746,  5751,  5752,  5757,  5764,  5765,  5770,
    5777,  5778,  5782,  5783,  5787,  5788,  5792,  5793,  5802,  5803,
    5804,  5808,  5832,  5835,  5843,  5853,  5858,  5863,  5868,  5875,
    5876,  5879,  5880,  5884,  5884,  5888,  5888,  5892,  5892,  5895,
    5896,  5900,  5907,  5908,  5912,  5924,  5924,  5935,  5936,  5941,
    5944,  5948,  5952,  5959,  5960,  5963,  5964,  5965,  5969,  5970,
    5983,  5991,  5998,  6000,  5999,  6009,  6011,  6010,  6025,  6032,
    6034,  6033,  6043,  6045,  6044,  6060,  6066,  6068,  6067,  6077,
    6079,  6078,  6094,  6099,  6104,  6114,  6113,  6125,  6124,  6140,
    6145,  6150,  6160,  6159,  6171,  6170,  6185,  6186,  6190,  6195,
    6200,  6210,  6209,  6221,  6220,  6237,  6240,  6252,  6259,  6266,
    6266,  6276,  6277,  6278,  6282,  6284,  6285,  6287,  6288,  6289,
    6290,  6291,  6293,  6294,  6295,  6296,  6297,  6298,  6300,  6301,
    6302,  6304,  6305,  6306,  6307,  6308,  6311,  6312,  6315,  6315,
    6315,  6316,  6316,  6317,  6317,  6318,  6318,  6319,  6319,  6324,
    6325,  6328,  6329,  6330,  6334,  6335,  6336,  6337,  6338,  6339,
    6340,  6341,  6342,  6353,  6365,  6380,  6381,  6386,  6392,  6398,
    6418,  6422,  6438,  6452,  6453,  6458,  6464,  6465,  6470,  6479,
    6480,  6481,  6485,  6496,  6497,  6501,  6509,  6510,  6514,  6515,
    6521,  6541,  6542,  6546,  6547,  6551,  6552,  6556,  6557,  6558,
    6559,  6560,  6561,  6562,  6563,  6564,  6568,  6569,  6570,  6571,
    6572,  6573,  6574,  6578,  6579,  6583,  6584,  6588,  6589,  6593,
    6594,  6605,  6606,  6610,  6611,  6612,  6616,  6617,  6618,  6626,
    6630,  6631,  6632,  6633,  6637,  6638,  6642,  6650,  6654,  6666,
    6678,  6679,  6689,  6690,  6694,  6695,  6696,  6697,  6698,  6699,
    6700,  6708,  6712,  6716,  6720,  6724,  6728,  6732,  6736,  6740,
    6744,  6748,  6752,  6759,  6760,  6761,  6765,  6766,  6770,  6771,
    6776,  6783,  6790,  6800,  6807,  6817,  6824,  6838,  6848,  6849,
    6853,  6854,  6858,  6859,  6863,  6864,  6865,  6869,  6870,  6874,
    6875,  6879,  6880,  6884,  6885,  6892,  6892,  6893,  6893,  6894,
    6894,  6895,  6895,  6897,  6897,  6898,  6898,  6899,  6899,  6900,
    6900,  6901,  6901,  6902,  6902,  6903,  6903,  6904,  6904,  6905,
    6905,  6906,  6906,  6907,  6907,  6908,  6908,  6909,  6909,  6910,
    6910,  6911,  6911,  6912,  6912,  6913,  6913,  6913,  6914,  6914,
    6915,  6915,  6915,  6916,  6916,  6917,  6917,  6918,  6918,  6919,
    6919,  6920,  6920,  6921,  6921,  6921,  6922,  6922,  6923,  6923,
    6924,  6924,  6925,  6925,  6926,  6926,  6927,  6927,  6928,  6928,
    6928,  6929,  6929,  6930,  6930,  6931,  6931,  6932,  6932,  6933,
    6933,  6934,  6934,  6935,  6935,  6937,  6937,  6938,  6938
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ACCEPT", "ACCESS",
  "ADD", "ADDRESS", "ADVANCING", "AFTER", "ALL", "ALLOCATE", "ALPHABET",
  "ALPHABETIC", "\"ALPHABETIC-LOWER\"", "\"ALPHABETIC-UPPER\"",
  "ALPHANUMERIC", "\"ALPHANUMERIC-EDITED\"", "ALSO", "ALTER", "ALTERNATE",
  "AND", "ANY", "ARE", "AREA", "\"ARGUMENT-NUMBER\"", "\"ARGUMENT-VALUE\"",
  "AS", "ASCENDING", "ASSIGN", "AT", "AUTO", "AUTOMATIC",
  "\"BACKGROUND-COLOR\"", "BASED", "BEFORE", "BELL", "BINARY",
  "\"BINARY-C-LONG\"", "\"BINARY-CHAR\"", "\"BINARY-DOUBLE\"",
  "\"BINARY-LONG\"", "\"BINARY-SHORT\"", "BLANK", "\"BLANK-LINE\"",
  "\"BLANK-SCREEN\"", "BLINK", "BLOCK", "BOTTOM", "BY", "\"BYTE-LENGTH\"",
  "CALL", "CANCEL", "CH", "CHAINING", "CHARACTER", "CHARACTERS", "CLASS",
  "CLOSE", "CODE", "\"CODE-SET\"", "COLLATING", "COL", "COLS", "COLUMN",
  "COLUMNS", "COMMA", "\"COMMAND-LINE\"", "\"comma delimiter\"", "COMMIT",
  "COMMON", "COMP", "COMPUTE", "\"COMP-1\"", "\"COMP-2\"", "\"COMP-3\"",
  "\"COMP-4\"", "\"COMP-5\"", "\"COMP-X\"", "\"FUNCTION CONCATENATE\"",
  "CONFIGURATION", "CONSTANT", "CONTAINS", "CONTENT", "CONTINUE",
  "CONTROL", "CONTROLS", "\"CONTROL FOOTING\"", "\"CONTROL HEADING\"",
  "CONVERTING", "CORRESPONDING", "COUNT", "CRT", "CURRENCY",
  "\"FUNCTION CURRENT-DATE\"", "CURSOR", "CYCLE", "DATA", "DATE", "DAY",
  "\"DAY-OF-WEEK\"", "DE", "DEBUGGING", "\"DECIMAL-POINT\"",
  "DECLARATIVES", "DEFAULT", "DELETE", "DELIMITED", "DELIMITER",
  "DEPENDING", "DESCENDING", "DETAIL", "DISK", "DISPLAY", "DIVIDE",
  "DIVISION", "DOWN", "DUPLICATES", "DYNAMIC", "EBCDIC", "ELSE", "END",
  "\"END-ACCEPT\"", "\"END-ADD\"", "\"END-CALL\"", "\"END-COMPUTE\"",
  "\"END-DELETE\"", "\"END-DISPLAY\"", "\"END-DIVIDE\"",
  "\"END-EVALUATE\"", "\"END FUNCTION\"", "\"END-IF\"", "\"END-MULTIPLY\"",
  "\"END-PERFORM\"", "\"END PROGRAM\"", "\"END-READ\"", "\"END-RETURN\"",
  "\"END-REWRITE\"", "\"END-SEARCH\"", "\"END-START\"", "\"END-STRING\"",
  "\"END-SUBTRACT\"", "\"END-UNSTRING\"", "\"END-WRITE\"", "ENTRY",
  "ENVIRONMENT", "\"ENVIRONMENT-NAME\"", "\"ENVIRONMENT-VALUE\"", "EOL",
  "EOP", "EOS", "EQUAL", "EQUALS", "ERASE", "ERROR", "ESCAPE", "EVALUATE",
  "\"EVENT-STATUS\"", "EXCEPTION", "EXCLUSIVE", "EXIT", "EXTEND",
  "EXTERNAL", "FD", "\"FILE-CONTROL\"", "\"FILE-ID\"", "FILLER", "FINAL",
  "FIRST", "FOOTING", "FOR", "\"FOREGROUND-COLOR\"", "FOREVER", "FREE",
  "FROM", "FULL", "FUNCTION", "\"FUNCTION-ID\"", "\"FUNCTION\"", "GE",
  "GENERATE", "GIVING", "GLOBAL", "GO", "GOBACK", "GREATER", "GROUP",
  "HEADING", "HIGHLIGHT", "\"HIGH-VALUE\"", "IDENTIFICATION", "IF",
  "IGNORE", "IGNORING", "IN", "INDEX", "INDEXED", "INDICATE", "INITIALIZE",
  "INITIALIZED", "INITIATE", "INPUT", "\"INPUT-OUTPUT\"", "INSPECT",
  "INTO", "INTRINSIC", "INVALID", "\"INVALID KEY\"", "IS", "\"I-O\"",
  "\"I-O-CONTROL\"", "JUSTIFIED", "KEY", "LABEL", "LAST",
  "\"LAST DETAIL\"", "LE", "LEADING", "LEFT", "LENGTH", "LESS", "LIMIT",
  "LIMITS", "LINAGE", "\"LINAGE-COUNTER\"", "LINE", "LINES", "LINKAGE",
  "\"Literal\"", "LOCALE", "\"FUNCTION LOCALE\"", "\"LOCAL-STORAGE\"",
  "LOCK", "\"FUNCTION LOWER-CASE\"", "LOWLIGHT", "\"LOW-VALUE\"", "MANUAL",
  "MEMORY", "MERGE", "MINUS", "\"MNEMONIC NAME\"", "MODE", "MOVE",
  "MULTIPLE", "MULTIPLY", "NATIONAL", "\"NATIONAL-EDITED\"", "NATIVE",
  "NE", "NEGATIVE", "NEXT", "\"NEXT SENTENCE\"", "NO", "NOT",
  "\"NOT END\"", "\"NOT EOP\"", "\"NOT EXCEPTION\"", "\"NOT INVALID KEY\"",
  "\"NOT OVERFLOW\"", "\"NOT SIZE ERROR\"", "\"NO ADVANCING\"", "NUMBER",
  "NUMBERS", "NUMERIC", "\"NUMERIC-EDITED\"", "\"FUNCTION NUMVALC\"",
  "\"OBJECT-COMPUTER\"", "OCCURS", "OF", "OFF", "OMITTED", "ON", "ONLY",
  "OPEN", "OPTIONAL", "OR", "ORDER", "ORGANIZATION", "OTHER", "OUTPUT",
  "OVERFLOW", "OVERLINE", "\"PACKED-DECIMAL\"", "PADDING", "PAGE",
  "\"PAGE FOOTING\"", "\"PAGE HEADING\"", "PARAGRAPH", "PERFORM",
  "PICTURE", "PLUS", "POINTER", "POSITION", "POSITIVE", "PRESENT",
  "PREVIOUS", "PRINTER", "PRINTING", "PROCEDURE", "PROCEDURES", "PROCEED",
  "PROGRAM", "\"PROGRAM-ID\"", "\"Program name\"", "\"PROGRAM-POINTER\"",
  "PROMPT", "QUOTE", "RANDOM", "RD", "READ", "RECORD", "RECORDING",
  "RECORDS", "RECURSIVE", "REDEFINES", "REEL", "REFERENCE", "RELATIVE",
  "RELEASE", "REMAINDER", "REMOVAL", "RENAMES", "REPLACING", "REPORT",
  "REPORTING", "REPORTS", "\"REPORT FOOTING\"", "\"REPORT HEADING\"",
  "REPOSITORY", "REQUIRED", "RESERVE", "RETURN", "RETURNING",
  "\"FUNCTION REVERSE\"", "\"REVERSE-VIDEO\"", "REWIND", "REWRITE",
  "RIGHT", "ROLLBACK", "ROUNDED", "RUN", "SAME", "SCREEN",
  "\"SCREEN-CONTROL\"", "SCROLL", "SD", "SEARCH", "SECTION", "SECURE",
  "\"SEGMENT-LIMIT\"", "SELECT", "\"semi-colon\"", "SENTENCE", "SEPARATE",
  "SEQUENCE", "SEQUENTIAL", "SET", "SHARING", "SIGN", "SIGNED",
  "\"SIGNED-INT\"", "\"SIGNED-LONG\"", "\"SIGNED-SHORT\"", "SIZE",
  "\"SIZE ERROR\"", "SORT", "\"SORT-MERGE\"", "SOURCE",
  "\"SOURCE-COMPUTER\"", "SPACE", "\"SPECIAL-NAMES\"", "STANDARD",
  "\"STANDARD-1\"", "\"STANDARD-2\"", "START", "STATUS", "STOP", "STRING",
  "\"FUNCTION SUBSTITUTE\"", "\"FUNCTION SUBSTITUTE-CASE\"", "SUBTRACT",
  "SUM", "SUPPRESS", "SYMBOLIC", "SYNCHRONIZED", "TALLYING", "TAPE",
  "TERMINATE", "TEST", "THAN", "THEN", "THRU", "TIME", "TIMES", "TO",
  "\"FALSE\"", "\"FILE\"", "\"INITIAL\"", "\"NULL\"", "\"TRUE\"", "TOP",
  "TRAILING", "TRANSFORM", "\"FUNCTION TRIM\"", "TYPE", "UNDERLINE",
  "UNIT", "UNLOCK", "UNSIGNED", "\"UNSIGNED-INT\"", "\"UNSIGNED-LONG\"",
  "\"UNSIGNED-SHORT\"", "UNSTRING", "UNTIL", "UP", "UPDATE", "UPON",
  "\"UPON ARGUMENT-NUMBER\"", "\"UPON COMMAND-LINE\"",
  "\"UPON ENVIRONMENT-NAME\"", "\"UPON ENVIRONMENT-VALUE\"",
  "\"FUNCTION UPPER-CASE\"", "USAGE", "USE", "USING", "VALUE", "VARYING",
  "WAIT", "WHEN", "\"FUNCTION WHEN-COMPILED\"", "WITH", "\"Identifier\"",
  "WORDS", "\"WORKING-STORAGE\"", "WRITE", "YYYYDDD", "YYYYMMDD", "ZERO",
  "'+'", "'-'", "'*'", "'/'", "UNARY_SIGN", "'^'", "'.'", "'='", "'('",
  "')'", "'>'", "'<'", "':'", "'&'", "$accept", "start", "$@1",
  "nested_list", "source_element", "program_definition", "$@2", "$@3",
  "program_mandatory", "$@4", "$@5", "function_definition", "$@6", "$@7",
  "nested_prog", "end_program", "end_mandatory", "end_function",
  "identification_division", "$@8", "function_division", "program_name",
  "as_literal", "program_type", "program_type_clause", "_init_or_recurs",
  "environment_division", "configuration_section", "configuration_list",
  "configuration_paragraph", "source_computer_paragraph",
  "source_computer_entry", "with_debugging_mode", "computer_name",
  "object_computer_paragraph", "object_computer_entry",
  "object_clauses_list", "object_clauses", "object_computer_memory",
  "object_char_or_word", "object_computer_sequence",
  "object_computer_segment", "repository_paragraph", "opt_repository",
  "repository_list", "repository_name", "repository_literal_list",
  "special_names_paragraph", "opt_special_names", "special_name_list",
  "special_name", "mnemonic_name_clause", "$@9",
  "special_name_mnemonic_on_off", "on_or_off", "alphabet_name_clause",
  "$@10", "alphabet_definition", "alphabet_literal_list",
  "alphabet_literal", "@11", "alphabet_also_sequence", "alphabet_lits",
  "alphabet_also_literal", "symbolic_characters_clause",
  "symbolic_characters_list", "char_list", "integer_list",
  "class_name_clause", "class_item_list", "class_item", "locale_clause",
  "currency_sign_clause", "decimal_point_clause", "cursor_clause",
  "crt_status_clause", "screen_control", "event_status",
  "input_output_section", "$@12", "$@13", "file_control_paragraph",
  "file_control_sequence", "file_control_entry", "$@14",
  "select_clause_sequence", "select_clause", "assign_clause", "_device",
  "_ext_clause", "assignment_name", "access_mode_clause", "access_mode",
  "alternative_record_key_clause", "collating_sequence_clause",
  "file_status_clause", "file_or_sort", "lock_mode_clause", "lock_mode",
  "lock_with", "lock_records", "organization_clause", "organization",
  "padding_character_clause", "record_delimiter_clause",
  "record_key_clause", "opt_splitk", "relative_key_clause",
  "reserve_clause", "sharing_clause", "sharing_option",
  "i_o_control_paragraph", "opt_i_o_control", "i_o_control_list",
  "i_o_control_clause", "same_clause", "same_option",
  "multiple_file_tape_clause", "multiple_file_list", "multiple_file",
  "multiple_file_position", "data_division", "file_section", "$@15",
  "$@16", "file_description_sequence", "file_description",
  "file_description_sequence_without_type", "file_type",
  "file_description_entry", "@17", "file_description_clause_sequence",
  "file_description_clause", "block_contains_clause",
  "_records_or_characters", "record_clause", "record_depending",
  "opt_from_integer", "opt_to_integer", "label_records_clause",
  "label_option", "value_of_clause", "valueof_name", "data_records_clause",
  "linage_clause", "linage_sequence", "linage_lines", "linage_footing",
  "linage_top", "linage_bottom", "recording_mode_clause",
  "code_set_clause", "report_clause", "working_storage_section", "$@18",
  "record_description_list", "record_description_list_1", "$@19",
  "record_description_list_2", "data_description", "$@20", "level_number",
  "entry_name", "const_name", "const_global", "lit_or_length",
  "constant_entry", "data_description_clause_sequence",
  "data_description_clause", "redefines_clause", "external_clause",
  "as_extname", "global_clause", "picture_clause", "usage_clause", "usage",
  "sign_clause", "occurs_clause", "occurs_to_integer", "occurs_depending",
  "occurs_keys", "occurs_key_list", "ascending_or_descending",
  "occurs_indexed", "occurs_index_list", "occurs_index",
  "justified_clause", "synchronized_clause", "left_or_right",
  "blank_clause", "based_clause", "value_clause", "$@21",
  "value_item_list", "value_item", "false_is", "renames_clause",
  "any_length_clause", "local_storage_section", "$@22", "linkage_section",
  "$@23", "report_section", "$@24", "opt_report_description_list",
  "report_description_list", "report_description_entry",
  "report_description_options", "report_description_option",
  "control_clause", "control_field_list", "_final", "identifier_list",
  "page_limit_clause", "heading_clause", "first_detail", "last_heading",
  "last_detail", "footing_clause", "page_line_column", "line_or_lines",
  "report_group_description_list", "report_group_description_entry",
  "report_group_options", "report_group_option", "type_clause",
  "type_option", "next_group_clause", "column_clause", "sum_clause_list",
  "sum_clause", "ref_id_exp", "present_when_condition", "varying_clause",
  "line_clause", "line_keyword_clause", "report_line_integer_list",
  "line_or_plus", "_numbers", "source_clause", "group_indicate_clause",
  "_indicate", "report_name", "screen_section", "$@25", "$@26",
  "opt_screen_description_list", "screen_description_list",
  "screen_description", "$@27", "screen_options", "screen_option",
  "screen_line_plus_minus", "screen_col_plus_minus",
  "screen_occurs_clause", "procedure_division", "$@28", "$@29",
  "procedure_using_chaining", "$@30", "$@31", "procedure_param_list",
  "procedure_param", "procedure_type", "size_optional",
  "procedure_optional", "procedure_returning", "procedure_declaratives",
  "$@32", "procedure_list", "procedure", "section_header",
  "paragraph_header", "invalid_statement", "section_name", "opt_segment",
  "statement_list", "@33", "@34", "statements", "$@35", "statement",
  "accept_statement", "$@36", "accept_body", "opt_at_line_column",
  "line_number", "column_number", "opt_accp_attr", "accp_attrs",
  "accp_attr", "end_accept", "add_statement", "$@37", "add_body", "add_to",
  "end_add", "allocate_statement", "$@38", "allocate_body",
  "allocate_returning", "alter_statement", "alter_options", "_proceed_to",
  "call_statement", "$@39", "call_using", "$@40", "call_param_list",
  "call_param", "call_type", "call_returning", "call_on_exception", "$@41",
  "call_not_on_exception", "$@42", "end_call", "cancel_statement", "$@43",
  "cancel_list", "close_statement", "$@44", "close_list", "close_option",
  "reel_or_unit", "compute_statement", "$@45", "compute_body",
  "end_compute", "comp_equal", "commit_statement", "continue_statement",
  "delete_statement", "$@46", "end_delete", "display_statement", "$@47",
  "display_body", "display_upon", "with_clause", "disp_attrs", "disp_attr",
  "end_display", "divide_statement", "$@48", "divide_body", "end_divide",
  "entry_statement", "$@49", "evaluate_statement", "$@50",
  "evaluate_subject_list", "evaluate_subject", "evaluate_condition_list",
  "evaluate_case_list", "evaluate_case", "$@51", "evaluate_other", "$@52",
  "evaluate_when_list", "evaluate_object_list", "evaluate_object",
  "opt_evaluate_thru_expr", "end_evaluate", "exit_statement", "$@53",
  "exit_body", "free_statement", "$@54", "generate_statement", "$@55",
  "goto_statement", "$@56", "goto_depending", "goback_statement", "$@57",
  "if_statement", "$@58", "$@59", "if_else_sentence", "$@60", "end_if",
  "initialize_statement", "$@61", "initialize_filler", "initialize_value",
  "initialize_replacing", "initialize_replacing_list",
  "initialize_replacing_item", "initialize_category", "initialize_default",
  "initiate_statement", "$@62", "inspect_statement", "$@63",
  "send_identifier", "inspect_list", "inspect_item", "inspect_tallying",
  "$@64", "tallying_list", "tallying_item", "inspect_replacing",
  "replacing_list", "replacing_item", "rep_keyword", "replacing_region",
  "inspect_converting", "inspect_region", "_initial", "merge_statement",
  "$@65", "move_statement", "$@66", "move_body", "multiply_statement",
  "$@67", "multiply_body", "end_multiply", "open_statement", "$@68",
  "open_list", "open_mode", "open_sharing", "open_option",
  "perform_statement", "$@69", "perform_body", "$@70", "end_perform",
  "perform_procedure", "perform_option", "perform_test",
  "perform_varying_list", "perform_varying", "read_statement", "$@71",
  "read_into", "with_lock", "read_key", "read_handler", "end_read",
  "release_statement", "$@72", "return_statement", "$@73", "end_return",
  "rewrite_statement", "$@74", "write_lock", "end_rewrite",
  "rollback_statement", "search_statement", "$@75", "search_body", "$@76",
  "search_varying", "search_at_end", "$@77", "search_whens", "search_when",
  "$@78", "end_search", "set_statement", "$@79", "set_body",
  "set_environment", "set_to", "set_up_down", "up_or_down",
  "set_to_on_off_sequence", "set_to_on_off", "set_to_true_false_sequence",
  "set_to_true_false", "sort_statement", "$@80", "sort_body", "$@81",
  "sort_key_list", "opt_key_list", "sort_duplicates", "sort_collating",
  "sort_input", "sort_output", "start_statement", "$@82", "@83",
  "start_key", "start_op", "end_start", "stop_statement", "$@84",
  "stop_returning", "string_statement", "$@85", "string_item_list",
  "string_item", "opt_with_pointer", "end_string", "subtract_statement",
  "$@86", "subtract_body", "end_subtract", "suppress_statement",
  "_printing", "terminate_statement", "$@87", "transform_statement",
  "$@88", "unlock_statement", "$@89", "opt_record", "unstring_statement",
  "$@90", "unstring_delimited", "unstring_delimited_list",
  "unstring_delimited_item", "unstring_into", "unstring_into_item",
  "unstring_into_delimiter", "unstring_into_count", "unstring_tallying",
  "end_unstring", "use_statement", "use_exception", "use_global",
  "use_exception_target", "_after", "_standard", "exception_or_error",
  "exception_or_overflow", "not_exception_or_overflow", "_procedure",
  "use_debugging", "use_debugging_target", "use_reporting",
  "write_statement", "$@91", "write_from", "write_option",
  "before_or_after", "write_handler", "end_write", "on_accp_exception",
  "on_disp_exception", "opt_on_exception", "$@92", "opt_not_on_exception",
  "$@93", "on_size_error", "opt_on_size_error", "$@94",
  "opt_not_on_size_error", "$@95", "on_overflow", "opt_on_overflow",
  "$@96", "opt_not_on_overflow", "$@97", "at_end", "at_end_sentence",
  "$@98", "not_at_end_sentence", "$@99", "at_eop", "at_eop_sentence",
  "$@100", "not_at_eop_sentence", "$@101", "opt_invalid_key",
  "invalid_key", "invalid_key_sentence", "$@102",
  "not_invalid_key_sentence", "$@103", "_opt_scroll_lines", "condition",
  "expr", "partial_expr", "$@104", "expr_tokens", "expr_token", "eq", "gt",
  "lt", "ge", "le", "exp_list", "e_sep", "exp", "linage_counter",
  "arithmetic_x_list", "arithmetic_x", "record_name", "table_name",
  "file_name_list", "file_name", "mnemonic_name_list", "mnemonic_name",
  "procedure_name_list", "procedure_name", "label", "integer_label",
  "reference_list", "reference", "opt_reference", "reference_or_literal",
  "undefined_word", "target_x_list", "target_x", "x_list", "x", "arith_x",
  "prog_or_entry", "alnum_or_id", "simple_value", "simple_all_value",
  "id_or_lit", "id_or_lit_or_func", "num_id_or_lit", "identifier",
  "identifier_1", "qualified_word", "subref", "refmod", "integer",
  "literal", "basic_literal", "basic_value", "function", "func_refmod",
  "func_args", "list_func_args", "trim_args", "numvalc_args",
  "locale_dt_args", "not_const_word", "flag_all", "flag_duplicates",
  "flag_initialized", "flag_next", "flag_not", "flag_optional",
  "flag_rounded", "flag_separate", "in_of", "records", "with_dups",
  "coll_sequence", "_advancing", "_are", "_area", "_as", "_at", "_binary",
  "_by", "_character", "_characters", "_contains", "_data", "_file",
  "_for", "_from", "_in", "_is", "_is_are", "_key", "_line_or_lines",
  "_lines", "_mode", "_number", "_of", "_on", "_in_order", "_other",
  "_program", "_record", "_right", "_set", "_sign", "_sign_is", "_size",
  "_status", "_tape", "_than", "_then", "_times", "_to", "_when", "_with", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-1922)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1518)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
   -1922,   285,   446, -1922,   196,   229,   446, -1922, -1922, -1922,
     559,   559,   397,   397, -1922,   577, -1922, -1922, -1922, -1922,
     687,   687,   281,   836,   836,   560,   518, -1922,   921,   928,
   -1922, -1922, -1922, -1922,   -54,   686,   882,   605,   768,   768,
   -1922,   641,    53,   671,   678,   778,   692, -1922,    13,  1016,
     845,  1025, -1922,   -28, -1922, -1922,   861, -1922, -1922, -1922,
     724, -1922, -1922, -1922,   839,   769, -1922,    43, -1922,   473,
     559,   397, -1922, -1922, -1922, -1922,   704, -1922,  1049,   427,
     736,   870,  1004,   821, -1922, -1922,   911,   397, -1922, -1922,
   -1922,   817,   819,   820,   824,   825, -1922, -1922, -1922, -1922,
   -1922,   920,   828,  1065,   880,   -48, -1922,   402, -1922, -1922,
   -1922, -1922,   834,   932,  1055, -1922,   418,   850, -1922,    86,
      86,   853,   842,   847,   836, -1922,   569,  1118,   169,   747,
    1021, -1922, -1922,   852, -1922, -1922,   913, -1922, -1922, -1922,
    1274, -1922, -1922, -1922, -1922,   859,   957,   985, -1922,   821,
   -1922, -1922, -1922, -1922, -1922,   495, -1922,   -34,   -90,   515,
   -1922, -1922, -1922, -1922,   943,  1103, -1922,   468, -1922,   547,
   -1922, -1922, -1922, -1922,    67,   168, -1922,   -38, -1922, -1922,
   -1922,   879,   673,  1212,   891,   891,   951,   976,  1103,  1103,
    1103,   891,  1103,  1284,  1103, -1922,   112, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     891,   920,   427, -1922,  1261, -1922,  1175,   418,   850, -1922,
     902,  1012,  1009,   850,   650,   935,  1054, -1922,  1103,  1000,
    1095, -1922, -1922,  1268,   768,  1103,  1146, -1922,   634, -1922,
   -1922,  1022, -1922,  1103,  1170, -1922,   775, -1922, -1922, -1922,
   -1922,   936,  1137, -1922, -1922,  1103,  1103, -1922,  1103,   953,
    1315,   953,  1103,   953, -1922,   891,    16, -1922, -1922, -1922,
   -1922, -1922,   821, -1922,   821, -1922, -1922,   850, -1922,   938,
    1039, -1922, -1922, -1922,   935, -1922,   945,   -19, -1922,  1261,
    1103,   -15,   -15,  1103,     8,  1149,  1103,  1368,  1125, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     499,   200,  1103, -1922,   963,   952, -1922,   845,  1146, -1922,
   -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922, -1922,  1103,
     701,   953,  1176,   456, -1922, -1922, -1922, -1922,   953, -1922,
   -1922,    58, -1922, -1922, -1922, -1922,   821, -1922,  1114,   821,
   -1922, -1922,   850, -1922,   964,   965, -1922, -1922,  1329, -1922,
    1331,  1146,   986,  1103,  1368,   953,    -7,   -37,  1146,   988,
   -1922,  1103,   990, -1922,   990,    -8, -1922, -1922, -1922, -1922,
   -1922,  1146, -1922, -1922, -1922,   510,   126, -1922,  1077, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,   701, -1922,  1038, -1922,
   -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922,  1146, -1922,
     796, -1922,  1146, -1922, -1922, -1922,  1107, -1922, -1922, -1922,
     765,  1032, -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922,
   -1922, -1922,  1206,    62,  1242,  1003, -1922, -1922, -1922,  1103,
    1103, -1922, -1922,  2643,   397, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     931, -1922,    68, -1922,   701, -1922,  1146, -1922,   806,  1149,
    1127,  1051, -1922,  1092,  1149,  1103,  1397,   262,     2,  1146,
    1027, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
    1080, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
    1103,  1421, -1922,   990, -1922,  1107, -1922, -1922,  4620,  1440,
    1286,  1146,    85, -1922, -1922, -1922,  1146, -1922, -1922,  1109,
   -1922,   -27,   -27,  2851,  1031,  1033, -1922, -1922, -1922, -1922,
   -1922,  1131,  3560,  3795,  1036, -1922, -1922,   931, -1922, -1922,
   -1922, -1922,  1106,  1103,  1270, -1922,   165, -1922,  1103,   713,
   -1922,  1103,  1103, -1922,  1103,  1103,  1274,   162,  1103,  1053,
   -1922,  1132, -1922, -1922,   935,  1269, -1922, -1922,   282,   522,
     533,   552,   639,  1066, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922,  1159, -1922,  1146, -1922, -1922, -1922, -1922,
     953,   953,  1289, -1922, -1922, -1922,   526, -1922, -1922, -1922,
    1103,   195, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   918,   442,
   -1922,   376, -1922, -1922, -1922, -1922, -1922,   150,  1284, -1922,
     536, -1922, -1922, -1922, -1922,  1398, -1922, -1922,  1273, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1051, -1922,  2239,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,    14, -1922,
   -1922,  1208, -1922, -1922, -1922, -1922,   154, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922,   981, -1922, -1922,  1103,    74,  1103, -1922,
   -1922,   555,   620, -1922, -1922, -1922,   -37,  1135,   953,   953,
   -1922,  1230,  1230,  1238, -1922,   953, -1922, -1922,    25,   -19,
   -1922, -1922,   935, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,  1075, -1922, -1922,  1119,
   -1922,  1071,  1128, -1922, -1922, -1922, -1922,  3077,   343,  1491,
   -1922,  1173,  1173,   701,  1259,  1259, -1922, -1922,  1081, -1922,
   -1922, -1922, -1922, -1922, -1922,    57,  1359, -1922, -1922,  1032,
    1146,  1089, -1922,  1091,   953,  3638,  1108,   -26,   982, -1922,
   -1922,  4203,   821,  4332,  4203,  1312,   372,   841,   102,   953,
   -1922, -1922,  1411, -1922,   102,   953,  4216,   953,  3821,  4203,
   -1922,  1594,   821,   953,   821,   953,    41,    66,   953,   821,
   -1922, -1922,  2984,  3875, -1922, -1922,   953,   953,   821,   953,
   -1922,   295,  1443,   953, -1922, -1922, -1922, -1922, -1922, -1922,
    1530, -1922,   891, -1922, -1922, -1922, -1922,   953,   122, -1922,
     159,  1121, -1922,  1121, -1922, -1922, -1922, -1922,   527, -1922,
   -1922, -1922, -1922, -1922,   953,  1103,  1386,  1386,   195, -1922,
   -1922, -1922, -1922,  1374, -1922, -1922, -1922,  1146,  1177,  4973,
    1120, -1922,   953, -1922,   343, -1922,  1178,  1340, -1922,  1397,
   -1922, -1922, -1922, -1922,   953,   953,   701,   -37,   -37,  1542,
    1284, -1922, -1922, -1922,  1453,   717, -1922,  1259,  1130,   953,
    1133,  1140,  1259,   456,  1142,  1143,  1145,  1147,  1154,  1155,
    1162,  1168,  1133,  1455, -1922,  3887, -1922, -1922, -1922, -1922,
    1403, -1922,  1556, -1922,  3328, -1922,  1221, -1922,   456, -1922,
   -1922,  1192, -1922, -1922,   155,   821,  1492,  1241, -1922,  1279,
    1311,  1024,  1495,  2087,  1104,  1165,  1496,   173,  1192, -1922,
   -1922,    37, -1922, -1922, -1922,  1527, -1922, -1922, -1922,  1259,
     102, -1922, -1922, -1922, -1922, -1922,  1235, -1922,    93,   953,
   -1922,   108, -1922, -1922, -1922, -1922, -1922,  4203, -1922,  1233,
    1497,  1581,   810, -1922,  1239, -1922,  1630,  1500,   683,  1243,
    1244,  -103,  1247,   648,  1466, -1922,  1311,  1466,   953,  1504,
    1217, -1922,   876, -1922, -1922, -1922, -1922, -1922,  1405, -1922,
     102, -1922,   408, -1922,    52, -1922, -1922,   494,  1597,  2357,
   -1922, -1922,   953,  1506,  4056,   953,  1474,   869,  1543, -1922,
    1325,  1280,  1382,  1466,   981, -1922,     9, -1922, -1922, -1922,
   -1922,    -5, -1922, -1922,  1103,   953, -1922, -1922,   155, -1922,
   -1922,   953, -1922,  1146,   935, -1922, -1922, -1922, -1922,  1545,
    1259,  4973,  4973,  4973,    17,   878, -1922, -1922, -1922,  1081,
   -1922,  4973, -1922, -1922,  1066, -1922,   343, -1922, -1922, -1922,
   -1922, -1922, -1922,  1206,   -37,  1548, -1922, -1922,   876,   857,
    1228,   135,   -23,  4973,  1265,  4973, -1922,  4973, -1922,  4529,
    1229,  4973,  4973,  4973,  4973,  4973,  4973,  4973,  4973, -1922,
   -1922, -1922,  4203,  1480, -1922, -1922,  1332,  1403, -1922, -1922,
   -1922, -1922,  1051, -1922, -1922,  1276, -1922,  1276, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,  3091, -1922, -1922, -1922, -1922,
   -1922,  1363,  1438, -1922,   548, -1922, -1922, -1922,   812, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,    54, -1922, -1922,
    1251,  1510,  1510,  1510,  1510, -1922, -1922,  4203,  4203, -1922,
     372,   219,  1540,  1246, -1922,  1252, -1922,   953, -1922,   111,
   -1922, -1922,  1240,  1505, -1922,   876,    84, -1922,   108, -1922,
   -1922, -1922, -1922,    50,  1281,   102, -1922, -1922,  4203, -1922,
   -1922, -1922, -1922,  1324, -1922, -1922, -1922, -1922,   953,   -26,
   -1922,   999, -1922, -1922,  1311,   155, -1922,  1475,   377,   244,
   -1922, -1922,   953,   244,  1288, -1922,  1081, -1922, -1922,    59,
     806, -1922, -1922,  1910, -1922,  1635,  1477,  4203,  4203, -1922,
    4137,   953, -1922,  1516, -1922, -1922,  4203,   876, -1922, -1922,
   -1922,  1597,  1488,   953, -1922,   998, -1922,    42,   377, -1922,
   -1922,  1577, -1922, -1922,  1424, -1922,   953,   953, -1922,   953,
    1509,   833,   -16, -1922,  4743,  1382, -1922,  4529,  1254,  1254,
     984, -1922, -1922, -1922,  4973,  4973,  4973,  4973,  4973,  4973,
    4781,   878,  1342, -1922, -1922,  1206,  1382, -1922, -1922, -1922,
    1510, -1922, -1922,  1263,  1271, -1922,   876,  1510,  1493, -1922,
   -1922, -1922, -1922,  1402,  1510,  1442,  1442,  1442,   107,  1479,
   -1922, -1922,   369, -1922,    69,   915,   953,   898,    87,  1266,
   -1922,  1081, -1922, -1922,   511,  1267,  1023,   575,  1272,  1052,
      91,    94,   694,  1275,  1124,  4149,   476,  4203,   102, -1922,
    1376, -1922, -1922, -1922, -1922, -1922, -1922,  1318,   -26, -1922,
     138,   953,   953,   454, -1922, -1922, -1922,   105,    56,  1351,
   -1922, -1922,  1590, -1922,  1460, -1922,     4,   360, -1922, -1922,
    1462, -1922, -1922, -1922,  1546,  4149,   530, -1922, -1922, -1922,
   -1922,  1703, -1922,  1335, -1922, -1922,   174, -1922, -1922,   219,
   -1922, -1922,  1382, -1922, -1922, -1922,  1051, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922,  1401,  1051, -1922,  1338, -1922,  1680,
   -1922, -1922, -1922,   407, -1922,   876,   789, -1922,    67,   478,
     232,   102,   102,  4149,   539,  1027,   821,  1600, -1922, -1922,
    1725, -1922,  1561, -1922, -1922, -1922, -1922,  1475, -1922,   953,
     501,    54,   469,  1309,  1617, -1922,  1313,   876,   770, -1922,
     369, -1922, -1922, -1922,  4203,  1103,    54, -1922, -1922, -1922,
   -1922,   -79,   953,  4149,   545,  1345,  1730,   953,  -105, -1922,
   -1922, -1922,  1444,  1446, -1922, -1922,   999, -1922,    10,   953,
    1103,  1580, -1922, -1922,  1146, -1922, -1922, -1922,  1103, -1922,
   -1922, -1922, -1922,  1442,  1088,  1103,   982, -1922, -1922,  1442,
   -1922,  1146, -1922, -1922, -1922, -1922, -1922,   953, -1922,   953,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   953,
    1553,   232, -1922,  1081, -1922, -1922,   915,   465,   465,  1254,
    1254,  1254, -1922,  1156, -1922,  1051, -1922,   953, -1922,  1462,
   -1922, -1922,  1510, -1922, -1922, -1922,  1103, -1922, -1922,  1103,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,    18, -1922, -1922,
   -1922,  1402, -1922, -1922, -1922,   155,   155,   155, -1922, -1922,
   -1922, -1922, -1922,  1133,  1279,  4893, -1922,   953,  1133,  1133,
    4973, -1922,  1133,  1133,  1133,   452,  1133,  1133, -1922, -1922,
    1498,  4149, -1922,   102, -1922, -1922,  1322, -1922,   -47,   120,
   -1922, -1922, -1922, -1922,   983, -1922,  1435, -1922,  1423, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1139,
    1510,  1501, -1922, -1922, -1922,  4203, -1922,  4203,   219, -1922,
   -1922, -1922,  1703, -1922,   953,  1640,  1337,   900,  1658,  1343,
     286,   876, -1922, -1922,  1716, -1922, -1922, -1922, -1922,   789,
   -1922,  1599, -1922,  1103,  1494, -1922, -1922, -1922, -1922,  1270,
     102, -1922,  4203,   162,   406, -1922, -1922, -1922,   953,  4203,
     675, -1922, -1922, -1922,  1637,  1517, -1922,  1638, -1922,  1544,
   -1922, -1922, -1922, -1922,  1313, -1922, -1922, -1922,  1521,  1639,
    1499,  1486,  1279, -1922,  4203,   286, -1922,  1507, -1922,   876,
   -1922,  1672,  1396, -1922, -1922,  1382, -1922,   970,  1775,   934,
   -1922, -1922, -1922,  1146,  1673,  1571,  1721,  5019,   -53,  1103,
   -1922, -1922,   -53, -1922,  1103,  1177, -1922, -1922, -1922,  1597,
   -1922,  1270, -1922,  1392, -1922, -1922, -1922,   -53,   -53,   124,
     124, -1922, -1922, -1922, -1922, -1922,  1351, -1922,  1166, -1922,
   -1922, -1922,   915, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,  4203, -1922, -1922,
   -1922, -1922, -1922,  1665, -1922, -1922, -1922, -1922, -1922, -1922,
    1103, -1922, -1922, -1922, -1922,  1110,  1103, -1922, -1922, -1922,
   -1922,    27, -1922,  1139, -1922, -1922, -1922, -1922, -1922,  4149,
    1472,  4149,  1473, -1922, -1922, -1922, -1922, -1922,  1663, -1922,
     900, -1922,  1698, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     286,   999, -1922, -1922,   999,    -6,   953, -1922, -1922,  4149,
   -1922, -1922,   643,  3795, -1922,  1747,  1565,  1586,   414, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,  4203,   749, -1922, -1922, -1922,  1660,  1551,   953,
    1351,  4149, -1922,  1730, -1922,  1242,  1715,  1242,  1499,   401,
   -1922, -1922,  1667, -1922,  1557, -1922, -1922, -1922,   393, -1922,
   -1922,  1103,  1723,  1601, -1922,   912, -1922,  1618,   960,  1368,
    1628,  1390,  1103,  1259,  1103,   953, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1445, -1922,
   -1922, -1922, -1922,    65, -1922, -1922, -1922, -1922, -1922, -1922,
     450, -1922,   543, -1922,  1388,  1103,  1103, -1922, -1922, -1922,
   -1922,   -53, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,   -53, -1922, -1922,   -53,   124,   124, -1922, -1922,
   -1922,  4203, -1922,  4203, -1922, -1922, -1922, -1922, -1922, -1922,
    1772,   999,   999, -1922,  1426,  1531,   821,    70, -1922,   953,
   -1922, -1922,  1490,  4203, -1922,  1103,   950,  1596, -1922,  1602,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1276, -1922,
    1276, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,   953,  1242, -1922,   953,  1689,
   -1922, -1922, -1922, -1922, -1922,   821, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922,  1029,  1146,  1103,  1103,  1669, -1922,  1103,
   -1922, -1922, -1922, -1922,   195, -1922,  1103, -1922,   953,   953,
    1113,  1662, -1922,  1558,  1146,    65, -1922, -1922, -1922, -1922,
   -1922, -1922,   -53, -1922, -1922, -1922, -1922,   -53, -1922,  1388,
   -1922,   953,   343,  1029, -1922, -1922, -1922, -1922, -1922, -1922,
    1351,  1351, -1922,  4203,   999, -1922,  4203,  1103,   821,   821,
    1554, -1922, -1922, -1922,  1427,   953,  1706, -1922, -1922, -1922,
   -1922, -1922, -1922,  1576,  1578, -1922, -1922, -1922,   953, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1146,  1146,
    1103, -1922,  1146, -1922,  1146, -1922,  1279, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,  4203, -1922, -1922,
   -1922, -1922, -1922, -1922,   953, -1922, -1922, -1922, -1922, -1922,
   -1922,   -26,   821,  1103, -1922, -1922, -1922, -1922,  1704,  1705,
   -1922, -1922, -1922, -1922,  1146, -1922, -1922, -1922,  1805, -1922,
     -26, -1922,  1051,  1051, -1922,  4203, -1922, -1922, -1922, -1922
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int16 yydefact[] =
{
       2,     0,     0,     1,     0,     0,     3,     4,     6,     7,
      38,    38,     0,     0,     5,     0,     8,    14,    28,    27,
      29,    29,     0,   242,   242,     0,     0,    24,    40,     0,
       9,    15,    30,    26,  1463,     0,   147,     0,   575,   575,
    1464,     0,     0,     0,     0,     0,     0,    39,   244,     0,
      17,     0,    25,    33,    37,    36,  1488,    35,    42,   149,
       0,   151,   254,   255,     0,   305,   247,   579,    18,    20,
      38,     0,    16,    34,  1489,    32,    41,   155,   153,   225,
       0,     0,   423,     0,   582,   580,   597,     0,    19,    10,
      11,     0,     0,     0,     0,     0,    43,    44,    45,    47,
      46,   150,     0,   223,  1455,   232,   152,     0,   227,   229,
     230,   245,     0,     0,   426,  1302,   248,   308,   256,   587,
     587,     0,     0,     0,   242,    23,    56,    71,    49,    80,
    1419,   156,   155,     0,   148,  1456,  1505,   233,   234,   235,
    1437,   226,   228,   249,   306,     0,     0,   429,   253,     0,
     252,   309,  1407,   258,  1446,   587,   584,   590,     0,   587,
     598,   576,    21,    12,     0,  1463,    54,  1488,    55,  1488,
      60,    62,    63,    64,     0,     0,    70,     0,    73,  1518,
      48,     0,  1517,     0,     0,     0,     0,  1496,  1463,  1463,
    1463,     0,  1463,  1449,  1463,    79,     0,    82,    84,    85,
      86,    88,    87,    89,    90,    91,    92,    93,    94,  1420,
       0,   154,   225,  1506,  1451,  1438,  1457,   246,   308,   424,
       0,     0,   521,   308,   311,     0,  1463,   585,  1463,     0,
     595,   588,   589,   599,   575,  1463,     0,    57,  1488,    59,
      61,     0,  1432,  1463,     0,    77,     0,    72,    74,    52,
      50,     0,     0,  1320,   102,  1463,  1463,  1497,  1463,     0,
       0,     0,  1463,     0,  1450,     0,     0,    81,    83,   157,
     224,  1452,     0,  1458,     0,   250,   307,   308,   427,     0,
       0,   243,   251,   314,     0,   318,     0,   319,   315,  1451,
    1463,     0,     0,  1463,  1451,  1475,  1463,  1435,     0,   257,
     259,   262,   263,   264,   265,   266,   267,   268,   269,   270,
       0,     0,  1463,   596,     0,     0,   577,    17,     0,  1369,
      69,    58,  1431,     0,    76,    75,    78,    51,    53,  1463,
       0,     0,     0,  1364,   143,  1315,   142,   146,     0,   145,
     129,  1465,   131,    95,    96,   159,   236,   237,   240,   231,
    1300,   425,   308,   430,     0,     0,   312,   320,   321,   316,
       0,     0,     0,  1463,  1435,     0,     0,     0,     0,     0,
    1476,  1463,     0,  1436,     0,     0,   260,   261,   591,   592,
     594,     0,   586,   600,   602,     0,     0,    68,     0,  1378,
    1374,  1379,  1377,  1375,  1380,  1376,   135,   136,   138,   144,
     141,  1425,  1426,     0,   140,  1467,  1466,   132,     0,    98,
    1490,   238,     0,   239,  1301,   428,   432,   522,   313,   329,
     323,   282,   302,  1427,  1428,   291,  1313,   286,   285,   284,
    1319,  1318,  1473,  1449,  1461,     0,   520,   303,   304,  1463,
    1463,   593,   602,     0,     0,    13,    66,    67,    65,   107,
     121,   117,   122,   104,   120,   118,   105,   106,   119,   103,
     108,   109,   111,   137,     0,  1365,   130,   133,    97,  1475,
       0,  1513,   207,     0,  1475,  1463,  1447,  1468,   209,     0,
    1517,   194,   193,   158,   160,   161,   162,   163,   164,   165,
       0,   166,   167,   206,   168,   169,   170,   171,   172,   173,
    1463,  1443,   241,     0,   431,   433,   434,   523,  1463,  1439,
       0,     0,   272,  1314,  1474,   293,     0,   275,  1462,  1501,
     301,     0,     0,     0,     0,   613,   609,   603,   604,   605,
     606,   612,     0,     0,     0,   110,   113,     0,   139,   134,
     101,   100,  1503,  1463,  1468,  1514,   179,   210,  1463,  1490,
    1448,  1463,  1463,  1469,  1463,  1463,  1437,     0,  1463,     0,
    1444,     0,   437,   435,   525,     0,   411,   353,   386,   374,
     383,   380,   377,  1515,   354,   355,   356,   357,   358,   359,
     360,   361,   362,  1492,   387,     0,   363,   350,   364,   365,
       0,     0,  1499,   367,   368,   366,   407,   370,   371,   369,
    1463,  1465,   330,   331,   332,   333,   334,   335,   351,   336,
     337,   338,   339,   340,   341,   342,   343,   344,     0,     0,
    1440,     0,   324,   283,   274,   273,   271,   292,  1449,  1502,
     280,   289,   288,   290,   287,     0,   608,   611,   614,   671,
     722,   731,   738,   742,   766,   770,   788,   781,   789,   790,
     794,   828,   837,   839,   866,   874,   876,  1513,   882,     0,
     893,   914,   916,   952,   954,   958,   670,   964,   977,   997,
    1014,  1016,  1020,  1027,  1028,  1044,  1064,  1082,     0,  1100,
    1111,  1119,  1121,  1123,  1125,  1130,  1152,  1175,   607,   621,
     622,   623,   624,   625,   626,   627,   628,   630,   629,   631,
     632,   633,   634,   635,   636,   637,   638,   639,   640,   641,
     642,   643,   644,   645,   646,   647,   648,   649,   650,   651,
     652,   653,   654,   655,   656,   657,   658,   659,   660,   661,
     662,   663,   664,   665,   666,   667,   668,  1148,  1149,  1150,
     669,   620,    22,     0,   112,  1504,  1463,     0,  1463,   181,
     180,   176,     0,  1491,   209,   205,     0,     0,     0,     0,
     218,  1486,  1486,     0,   219,     0,   190,   208,  1463,   319,
     529,   524,   526,   527,   422,   384,   385,   372,   373,   381,
     382,   378,   379,   375,   376,  1516,     0,  1493,   405,   391,
     345,  1360,   420,  1500,   408,   409,   406,     0,     0,   347,
     349,  1423,  1423,     0,  1479,  1479,   328,   325,  1370,  1372,
    1442,   294,   295,   296,   297,     0,     0,   276,  1460,   282,
       0,     0,   615,     0,     0,     0,  1239,   737,     0,   768,
     772,     0,     0,     0,     0,     0,  1239,   868,     0,     0,
     878,   883,     0,  1239,     0,     0,     0,     0,     0,     0,
     966,   987,     0,     0,     0,     0,     0,     0,     0,     0,
    1096,  1094,     0,     0,  1120,  1118,     0,     0,     0,     0,
    1153,  1159,     0,     0,   127,   123,   128,   126,   124,   125,
     114,   115,     0,   187,   188,   186,   185,     0,   175,   178,
       0,   199,   198,   199,   195,   211,   212,   213,   214,   217,
    1487,   220,   221,   222,  1316,  1463,   446,   446,  1465,   466,
     438,   441,   442,     0,   530,   528,   410,     0,  1511,     0,
    1361,  1362,     0,   352,   412,   414,   416,     0,   346,  1447,
     388,   389,  1371,  1480,     0,     0,     0,     0,     0,  1441,
    1449,   281,   601,   610,   720,   690,  1359,  1479,     0,     0,
    1393,  1396,  1479,  1293,     0,     0,     0,     0,     0,     0,
       0,     0,  1393,   729,  1335,   727,  1325,  1327,  1333,  1334,
    1412,   732,     0,  1238,     0,  1312,     0,  1308,  1310,  1309,
    1354,   744,  1353,  1355,   767,   771,   784,     0,  1295,  1421,
    1490,  1374,   826,   690,     0,  1327,   835,     0,   744,   845,
     844,     0,   841,   843,   873,   870,   869,   872,   867,  1479,
     875,  1321,  1323,   877,  1306,   887,  1509,  1237,   895,   915,
     448,     0,   918,   919,   920,   953,  1068,     0,   955,     0,
     962,     0,   965,   988,  1312,   978,   987,   980,     0,   985,
       0,  1309,     0,  1414,  1177,  1298,  1490,  1177,     0,  1042,
    1033,  1299,     0,  1305,  1045,  1046,  1047,  1048,  1049,  1057,
    1050,  1060,     0,  1303,     0,  1065,  1083,  1097,  1445,     0,
    1102,  1104,     0,  1116,     0,  1122,     0,  1127,  1132,  1160,
       0,  1161,  1481,  1177,     0,    99,  1410,   183,   182,   174,
     184,     0,   197,   196,  1463,     0,  1317,   191,     0,   447,
     443,     0,   444,     0,   436,   439,   532,   392,  1512,   393,
    1479,     0,     0,     0,  1281,  1279,  1342,  1284,  1336,  1340,
    1341,     0,  1363,   421,  1515,   415,     0,   348,  1424,   327,
     326,  1373,   300,  1473,     0,   278,   721,   672,  1442,     0,
     699,     0,     0,     0,     0,     0,  1381,  1398,  1392,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1382,
     730,   723,     0,     0,  1326,  1413,   735,  1412,  1263,  1264,
    1265,  1259,  1513,  1270,  1255,  1507,  1256,  1507,  1257,  1267,
    1258,  1262,  1261,  1260,  1266,  1247,  1248,  1249,  1250,  1251,
    1268,  1245,  1246,  1271,  1273,  1240,  1241,  1252,  1253,  1254,
    1244,   740,     0,   745,   755,  1352,   769,  1351,   774,   785,
     782,   787,   786,  1239,  1296,  1422,  1297,  1226,   827,   795,
     801,  1192,  1192,  1192,  1192,   836,   829,     0,     0,   838,
    1239,  1239,   864,   851,   847,   849,   871,     0,  1322,   880,
    1510,   885,   897,     0,   449,     0,   941,   926,   917,   921,
     923,   924,   925,  1072,     0,     0,   963,   959,     0,   971,
     968,   970,   969,   972,   979,   982,   616,  1239,     0,     0,
     989,     0,  1415,  1416,  1490,     0,  1015,   999,  1022,  1035,
    1043,  1029,     0,  1035,     0,  1347,  1348,  1058,  1061,     0,
       0,  1304,  1056,     0,  1055,     0,  1085,     0,     0,  1095,
       0,     0,  1103,     0,  1117,  1112,     0,     0,  1128,  1129,
    1126,  1445,     0,     0,  1162,     0,  1482,     0,  1022,   116,
    1430,     0,   189,  1411,     0,   202,     0,   215,   440,   445,
     451,   461,   319,   467,  1498,  1481,   396,     0,  1289,  1290,
       0,  1282,  1283,  1366,     0,     0,     0,     0,     0,     0,
       0,     0,  1494,   417,   299,  1473,  1481,   277,   695,   686,
    1192,   676,   683,   677,   679,   681,     0,  1192,     0,   675,
     682,   689,   688,     0,  1192,  1477,  1477,  1477,   693,   694,
    1344,  1343,     0,  1332,  1281,  1279,     0,     0,  1281,     0,
    1328,  1329,  1330,  1294,  1281,     0,     0,  1281,     0,     0,
    1281,  1281,  1281,     0,     0,  1199,  1421,     0,     0,   733,
       0,  1269,  1508,  1272,  1274,  1242,  1243,     0,     0,  1311,
     751,     0,     0,   758,   779,   780,   773,   775,     0,  1199,
    1231,  1233,   792,  1227,  1228,  1229,     0,   806,  1193,   798,
    1195,   799,   796,   797,     0,  1199,  1421,   842,   859,   861,
     860,   854,   856,   862,   865,   840,  1239,   848,   846,  1239,
     616,  1324,  1481,   879,  1307,   616,  1513,   905,   906,   908,
     910,   911,   907,   909,   900,  1513,   896,     0,   942,     0,
     944,   943,   945,   936,   937,     0,     0,   922,  1074,  1483,
       0,     0,   956,  1199,  1421,  1517,     0,   983,   617,   990,
     991,   994,     0,   986,  1184,  1183,   993,   999,  1178,     0,
       0,  1226,     0,     0,     0,  1034,     0,     0,     0,  1059,
       0,  1063,  1062,  1053,     0,  1463,  1226,  1099,  1098,  1105,
    1106,  1107,     0,  1199,  1421,     0,  1408,     0,  1107,  1174,
    1164,  1163,  1169,     0,  1171,  1172,  1179,  1429,     0,   216,
    1463,   453,   464,   465,   463,   321,   469,   545,  1463,   536,
     534,   535,   537,  1477,     0,  1463,     0,   548,   540,  1477,
     541,     0,   544,   549,   547,   542,   546,     0,   543,     0,
     531,   559,   554,   557,   556,   555,   558,   533,   560,     0,
     400,   395,  1337,  1338,  1339,  1292,  1280,  1285,  1286,  1287,
    1288,  1291,  1367,     0,  1495,  1513,   298,     0,   687,  1195,
     678,   680,  1192,   684,   674,   714,  1463,   703,   704,  1463,
     715,   705,   706,   709,   719,   716,   707,     0,   717,   708,
     718,   700,   701,   673,  1478,     0,     0,     0,   691,   692,
    1346,  1331,  1345,  1393,  1421,     0,  1397,     0,  1393,  1393,
       0,  1390,  1393,  1393,  1393,     0,  1393,  1393,  1200,   724,
    1202,  1199,   736,     0,   741,   739,   746,   747,   590,     0,
     757,   756,  1165,  1166,   761,   759,     0,   778,     0,   783,
     616,   616,   793,   791,  1230,   805,   804,   803,   802,  1518,
    1192,     0,   616,  1196,  1191,     0,   830,     0,  1239,  1239,
     858,   852,   855,   850,     0,   888,     0,     0,   912,     0,
       0,     0,   938,   940,     0,   932,   948,   933,   934,   927,
     928,   948,  1066,  1463,     0,  1484,  1073,   398,   399,  1468,
     957,   960,     0,     0,   974,   984,   981,   619,     0,     0,
    1001,  1000,  1215,  1217,  1018,  1212,  1213,  1025,  1023,     0,
    1239,  1036,  1239,  1030,  1038,  1051,  1052,  1054,  1417,  1092,
    1206,     0,  1421,  1113,     0,     0,  1409,  1133,  1134,     0,
    1137,  1140,  1144,  1138,  1170,  1481,  1173,  1185,  1433,     0,
     203,   204,   200,     0,     0,   455,     0,  1498,     0,  1463,
     538,   539,     0,   562,  1463,  1511,   563,   561,   394,  1445,
     390,  1468,  1368,   418,   279,  1190,   685,     0,     0,  1235,
    1235,   702,   697,   696,   698,  1386,  1199,  1394,     0,  1406,
    1391,  1384,  1404,  1385,  1387,  1388,  1401,  1402,  1389,  1383,
     616,  1203,  1198,   725,   734,   748,   749,     0,   753,   752,
     754,  1167,  1168,   764,   762,   616,   776,   777,  1232,  1234,
    1463,   811,   824,   825,   812,     0,  1463,   815,   816,   819,
     817,     0,   818,   808,   809,   800,   807,  1194,   616,  1199,
    1295,  1199,  1295,   857,   863,   616,   881,   889,   891,   898,
     901,   902,  1453,   913,   894,   899,   948,  1349,  1350,   948,
       0,   931,   929,   930,   935,  1076,     0,  1485,  1070,  1199,
     973,   967,     0,   618,   995,     0,     0,  1007,     0,   616,
     616,  1019,  1017,  1214,  1026,  1021,  1024,  1031,   616,  1040,
    1039,  1418,     0,     0,  1093,  1084,  1207,  1109,  1209,     0,
    1199,  1199,  1124,  1408,  1136,  1461,  1142,  1461,  1206,     0,
    1222,  1224,  1188,  1186,  1219,  1220,  1187,  1434,     0,   201,
     452,  1463,     0,   457,   462,  1477,   498,   518,   513,  1435,
       0,     0,  1463,  1479,  1463,     0,   468,   474,   475,   476,
     485,   477,   479,   482,   470,   471,   472,   478,   481,   499,
     483,   486,   473,     0,   480,   484,  1358,   553,  1356,  1357,
     569,   552,   564,   574,     0,  1463,  1463,   413,   711,   710,
     713,     0,   712,   726,  1395,  1201,   616,   750,   765,   743,
     616,   760,     0,   813,   814,     0,  1235,  1235,   810,  1197,
     832,     0,   831,     0,   853,   616,   892,   886,   903,  1454,
       0,   947,   939,   948,   950,     0,     0,  1079,  1075,  1069,
     961,   976,     0,     0,  1002,  1463,  1009,     0,  1003,     0,
    1006,  1216,  1218,   616,  1037,   616,  1086,  1275,  1507,  1277,
    1507,  1087,  1088,  1089,  1090,  1091,   616,  1110,  1101,  1210,
    1205,  1108,  1115,  1114,  1135,     0,  1461,  1139,     0,  1146,
    1158,  1155,  1157,  1156,  1151,  1154,   616,   616,  1189,  1176,
    1221,  1182,  1181,  1470,     0,  1463,  1463,   459,   497,  1463,
     519,   517,   514,   515,  1465,   507,  1463,  1239,     0,     0,
       0,     0,   500,     0,     0,   505,   508,   511,   572,   570,
     571,   573,     0,   567,   565,   566,   568,     0,   404,   401,
     402,     0,     0,  1470,  1204,   763,   821,   820,   823,   822,
    1199,  1199,   890,     0,   946,   951,     0,  1463,  1077,     0,
       0,  1067,  1071,   975,     0,     0,  1012,  1010,  1011,  1005,
    1004,  1032,  1041,  1272,  1274,  1208,   616,  1141,     0,  1145,
    1147,  1131,  1223,  1225,  1471,  1472,  1180,   454,     0,     0,
    1463,   450,     0,   506,     0,   503,  1421,   501,   502,   492,
     490,   491,   493,   489,   494,   488,   487,     0,   512,   510,
     509,   551,   550,   403,   397,   419,  1236,   834,   833,   904,
     949,     0,  1080,  1463,  1239,  1008,  1013,   998,     0,     0,
    1211,  1143,   456,   458,     0,   496,   495,   516,     0,  1078,
       0,   996,  1513,  1513,   460,     0,  1081,  1276,  1278,   504
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
   -1922, -1922, -1922, -1922,  1850, -1922, -1922, -1922,    72, -1922,
   -1922, -1922, -1922, -1922,  1549, -1922, -1922, -1922,  1186, -1922,
   -1922,    34,  1839, -1922, -1922,  1808,   874, -1922, -1922, -1922,
   -1922, -1922,  1681,  1737, -1922, -1922,  1700,   109, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,  1692, -1922, -1922, -1922, -1922,
    1674, -1922, -1922, -1922,   581, -1922, -1922, -1922, -1922,  1412,
   -1922, -1922,  1336,   790, -1922, -1922, -1922, -1922, -1922, -1922,
    1481, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,  1743, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   987,
      97, -1922,  1330, -1922, -1922, -1922,   991, -1922, -1922, -1922,
     149, -1922,  1671, -1922,  1779, -1922, -1922, -1922, -1922,  1541,
   -1922,   248, -1922, -1922, -1922, -1922,  1675, -1922,  1840,  1742,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  1074, -1922,
   -1922, -1922,  1373, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922,   930, -1922, -1922, -1922,  1612,
   -1922,  -518,  -735, -1922, -1922, -1922,  -402, -1922, -1922, -1922,
   -1922, -1922, -1922, -1278, -1275,  1100, -1273,   113, -1922, -1922,
   -1922, -1922,   307, -1922, -1922,  -228, -1260, -1922, -1922, -1259,
   -1922, -1258, -1922, -1922,   975, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,  1399, -1922, -1922, -1922,
     995, -1922,  -702, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
     -75, -1922, -1922, -1922, -1922, -1922, -1922,  -210, -1922, -1922,
   -1922, -1922,  -158, -1922, -1922, -1922, -1922, -1922,  1134, -1922,
   -1922, -1922, -1922, -1922, -1922,   209, -1922, -1922, -1922, -1922,
   -1922,  1787,  1035, -1922,   240, -1922, -1922, -1922, -1922,  1467,
   -1922, -1922, -1922, -1922, -1922, -1922,  -944, -1922, -1922,   175,
   -1922,  1377, -1922, -1922, -1922,   922,   534,   540, -1922, -1922,
     283, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,   919, -1922, -1922,   254,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922,    60, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922,   695, -1922, -1922,   688, -1922, -1922, -1922, -1922,
     463,   226, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,    47,   696,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,   680, -1922, -1922,
   -1922,   210, -1922, -1922,   447, -1922, -1922, -1922, -1468, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1921,   897, -1922, -1922,   199, -1922, -1922,   432, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,   616,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922,   657, -1922,   187,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922,   885, -1922,   884, -1922, -1922,  1087, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,   881,   409, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922,    20, -1922,   413, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1922, -1922, -1922, -1922,  -163, -1922,
   -1136, -1922, -1922, -1037, -1155, -1129, -1922,   346, -1922, -1269,
   -1922, -1922, -1922, -1922,    19, -1922, -1922, -1922, -1922,   -88,
   -1922, -1922,   211, -1922, -1922, -1922, -1922,    21, -1922,  -502,
   -1634, -1922, -1922,   535, -1922, -1196, -1254,  -807, -1168, -1922,
   -1922,   766,    44,    45,    51, -1922, -1922,   145,  -184,  -294,
    -117, -1114,  -819,    63,   916, -1463,   -83, -1922, -1039, -1922,
    -792, -1922,   758, -1084,  -241, -1922,  -563,  -153,  -813,  -958,
    -181,  -747, -1922, -1922,   455, -1010, -1532,  -929,  -801,  -669,
     691,  -573,  -220, -1922,  1050,  -230,  -618,  -652,  -277,  -361,
    -922, -1922, -1922, -1922, -1922, -1922,  1752, -1922, -1922,   811,
   -1922, -1922, -1922, -1599,  1180,  -263,  1685,   726,  -401, -1922,
    -362,  1429, -1922,  -606, -1922, -1054,  1057,  -384,   684, -1922,
   -1922,  -670, -1922, -1698,  -164,  -596,  -471,  -146,  -925,   646,
   -1340,  -797, -1183, -1922,  1227,  1934,  -707, -1922, -1922, -1922,
   -1922, -1922, -1922, -1922, -1162, -1922,   198,  -653,   871,  -470
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
       0,     1,     2,     6,     7,     8,    23,    38,    68,   124,
     234,     9,    24,    39,    69,    89,   445,    72,    70,    34,
      11,    20,    26,    41,    56,    57,    16,    36,    76,    96,
      97,   180,   181,   167,    98,   168,   169,   170,   171,   448,
     172,   173,    99,   176,   177,   178,   246,   100,   195,   196,
     197,   198,   409,   468,   542,   199,   329,   459,   460,   461,
     743,   880,   462,   881,   200,   340,   341,   466,   201,   396,
     397,   202,   203,   204,   205,   206,   207,   208,    47,    77,
      79,   103,   101,   131,   345,   410,   484,   485,   890,   751,
    1089,   486,   886,   487,   488,   489,   490,   491,   894,  1092,
    1782,   492,   493,   494,   495,   496,   897,   497,   498,   499,
     764,   134,   106,   107,   108,   109,   140,   110,   346,   347,
     413,    30,    65,   143,    83,   217,   148,   116,   149,   117,
     153,   226,   300,   301,   626,   302,  1357,   819,   512,   303,
     429,   304,   632,   305,   306,   627,   811,   812,   813,   814,
     307,   308,   309,    82,   218,   150,   151,   152,   224,   286,
     419,   287,   359,   360,   509,   806,   288,   508,   602,   603,
     604,   928,   605,   606,   607,   608,   609,   610,   918,  1336,
    1590,  1591,  1729,  1800,  2129,  2130,   611,   612,   796,   613,
     614,   615,  1124,   924,   925,  1997,   616,   617,   114,   277,
     147,   352,   222,   416,   504,   505,   506,   768,   910,   911,
    1100,  1101,  1019,   912,  1551,  1785,  1953,  2097,  2181,  1330,
    1554,  1104,  1333,  1787,  1974,  1975,  2196,  1976,  1977,  1978,
    1979,  2187,  1980,  1981,  1982,  1983,  2115,  2116,  2104,  1984,
    1985,  2101,   437,   281,   507,   564,   771,   772,   773,  1106,
    1334,  1587,  2127,  2122,  1588,    50,   233,   384,    86,   120,
     119,   155,   156,   157,   230,   314,   122,   316,   442,   443,
     527,   528,   529,   530,   531,   823,  1497,  1498,  1737,   532,
     533,   689,   690,   824,   944,  1140,  1378,  1379,  1374,  1631,
    1632,  1137,   691,   825,   963,  1163,  1161,   692,   826,   971,
    1409,   693,   827,  1418,   694,   828,  1204,  1420,  1666,  1667,
    1668,  1423,  1674,  1845,  1843,  2010,  2009,   695,   829,   984,
     696,   830,   985,  1426,  1427,   697,   831,   986,  1210,  1213,
     698,   699,   700,   832,  1683,   701,   833,   992,  1437,  1690,
    1863,  1864,  1219,   702,   834,   996,  1226,   703,   835,   704,
     836,  1001,  1002,  1232,  1233,  1234,  1460,  1458,  1875,  1235,
    1451,  1452,  1700,  1455,   705,   837,  1008,   706,   838,   707,
     839,   708,  1014,  1463,   709,   841,   710,   843,  1465,  1878,
    2025,  2027,   711,   844,  1242,  1474,  1708,  1880,  1881,  1882,
    1884,   712,   845,   713,   846,  1021,  1248,  1249,  1250,  1486,
    1719,  1720,  1251,  1483,  1484,  1485,  1713,  1252,  1891,  2146,
     714,   847,   715,   848,  1028,   716,   849,  1030,  1257,   717,
     850,  1032,  1263,  1496,  1901,   718,   851,  1035,  1266,  1736,
    1036,  1037,  1038,  1500,  1501,   719,   852,  1510,  1907,  2046,
    2156,  2217,   720,   853,   721,   854,  1912,   722,   855,  1511,
    1915,   723,   724,   856,  1049,  2053,  1283,  1513,  1918,  1753,
    1754,  2055,  1281,   725,   857,  1054,  1055,  1056,  1057,  1295,
    1058,  1059,  1060,  1061,   726,   858,  1025,  1895,  1253,  2039,
    1488,  1722,  2037,  2151,   727,   859,  1296,  1526,  1922,  1925,
     728,  1067,  1299,   729,   862,  1069,  1070,  1760,  2068,   730,
     863,  1073,  1305,   731,   865,   732,   866,   733,   867,   734,
     868,  1310,   735,   869,  1312,  1767,  1768,  1538,  1770,  1936,
    2077,  1938,  2171,   736,   737,   871,  2084,  1081,  1315,  1542,
    1675,  1844,  1775,   738,  1544,   739,   740,   873,  1276,  1777,
    2034,  1942,  2089,  1608,  1439,  1440,  1692,  1694,  1868,  1659,
    1660,  1830,  1832,  2006,  1927,  1928,  2066,  2070,  2166,  1744,
    1745,  1909,  1746,  1910,  1943,  1944,  2086,  1945,  2087,  1432,
    1433,  1434,  1680,  1435,  1681,  2000,  1016,  1017,   973,   974,
    1195,  1196,  1197,  1198,  1199,  2064,  2065,  1114,  1344,  1385,
     964,   987,  1214,  1044,  1050,   349,   350,  1062,  1063,  1239,
    1039,   977,   978,   425,   431,  1097,   432,   254,  1010,  1011,
     965,   989,  1117,  1382,  1641,  1721,  1886,   994,  1040,  1987,
     967,   946,   791,   920,   921,  1989,   968,   808,   809,   969,
    1146,  1148,  1389,  1403,  1398,  1395,   225,  1769,  1322,  1166,
    1274,  1923,   210,  1216,   930,   403,   365,  1323,   243,  1948,
     374,   216,   621,  1141,   561,   158,   551,   265,   272,  2030,
     136,   274,   820,   519,    42,   408,   554,  2176,   515,   371,
    1635,   934,  1317,  1726,   901,   174,   501,   788,  1605,   258,
     619,   630,   746,   214,  1413,  1241,  1109,   546,   786,   183
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     118,   236,   424,   807,   840,   798,   320,   555,   935,   500,
     557,  1327,   988,  1499,  1300,  1414,   872,   790,   334,   972,
     337,   815,   339,  1291,   259,   260,   261,   981,   263,  1003,
     266,  1018,   255,  1734,   914,   976,  1636,  1637,   262,   335,
    1159,   335,  1284,   335,  1064,  1816,   769,    21,  1405,   517,
    1048,  1543,  1238,   398,  1230,  1206,  1581,   269,  1009,  1582,
    1238,  1583,   310,  1453,   311,  1009,   118,  1441,  1442,  1443,
    1490,   318,  1009,   748,  1584,  1585,  1586, -1481,   966,   323,
     405,   380,   387,   905,  1341,   536,   966,   997,   386,   271,
     399,   330,   331,  1478,   332,  1685,    84,   404,   338,  1009,
    1372,  1029,  1031,   335,   937,    91,  1238,   343,  1009,   906,
     907,   335,   342,   344,  1445,  1071,   966,   264,   335,   398,
    1380,   123,    53,   184,   426,  1320,   362,   241,  1358,   367,
     369,   421,   372,  1809,   154,  1506,  1341,   175,   433,  1479,
     624,    88,  2016,  1946,  1493,   335,   357,   335,   381,   357,
    1142,   441,  1589,    40,  1341,  1149,   439,   816,  1341, -1481,
    1679,  1341,   770,  1930,  1075,   388,  1320,  1292,   185,  1328,
    1375,   761,   154,  1607,   319,    62,  1696,   244,   467,   810,
     926,   446,   502,   465,   513, -1517,   154,   538,   407,   348,
     430,   883,  1533,   895,  2035,  1448,  1245, -1441,  1375,   423,
     631,   975,  1838,   186,   187,   335,   188,   435,  1354, -1468,
    1052, -1517,  1237,   553,   189,    40,   438,   405,  1164,  1462,
   -1445,  1227,  1836,  1789,  1731,   231,  1324,  1200,  1023,  1794,
     378,  1609,    40,  1932,  -177,  1477,   539,  2075,  1609,  2078,
    1448,   860,  1549,  1053,   817,  1609,  1164,  1289,    51,   556,
    2149,  1480,  1779,  1894,   769, -1457,   510,  1536, -1517,  1727,
    1430,   137,   427,   348,  1763,   406,   414,  1119,   190,   975,
   -1517,  1087,    31,   810,   273,   521,   522,  1381,   240,  1704,
    1254,   623,   749,  1217,    54,     3,   628,  1677,  1453, -1360,
    2229,  1453,   319,  1661,   363,   803,   364,  1535, -1491,  1686,
    1481,   633,   633,  1079,   379,  1053,   926,  1678,   908,  2236,
    1431,   549,  1103,  1337,  2113,   228,   138,   139, -1517,  1780,
    1316,  1781,  1071,   273,   179,   333,   750,  1164,   228,  1080,
    1613,  1238,  1325,  1134,   232,   870,   559,  1633,   975,  1277,
     191,  1728,   919,   988,   618,   562,  1508,   240,  2150,  -177,
     179, -1445,   803,   861,  2114,   789,  1612,    63,  2033,  1376,
     229,  1129,  1130,   428, -1441,    54,  1669,  1342,    55,   552,
     770,   792,   163,   229,  1132,  1133,  1228,   333,  2168,   747,
     884,  1042,  1205,  1986,   752,   803,  1088,   756,   757,   -31,
     758,   759,  1833,   333,   765,   245,   625,  1688,  1377,  1329,
    1286, -1445,   406,   333,   333,   247,  1429,   333,    64,   988,
    1778,   358,  2158,   762,  1555,  1406,  1478,  2036,  2031,  1342,
     242,  2032,   440,  1003, -1457,   804,  1377,   319,   885,  1246,
    1606,  1810, -1468, -1463,  1687,  1839,   797,  1342,  1321,   988,
    2017,  1342,  1492,   317,  1342,  1293,   253,  1464,  1200,    55,
    1662,  1701,  1518, -1445,   192,   516,   938,    88,   537,  1119,
    1119,  1119,  1479,  1343,  1231,  1294,    85,   983,   909,  1119,
     763,   333,   333,   553,   389,  1714,  2085,  1503,   534,  1321,
    1444,  1446,   333,  1609,  1482,  1024,  1286,   988,   253,   333,
     983,  1119,  1247,  1119,   193,  1119,   333,  1391,  1919,  1119,
    1119,  1119,  1119,  1119,  1119,  1119,  1119,  1755,  1353,  1967,
   -1445,  1494,  1968,   390,  1969,  1643,  1703,   898,   899,  1411,
     391,  1705,   179,   333,   904,  1545,   932,  1971,  1972,  1973,
    1453,   389,   333, -1399,  1238,  1865,   335,  1653,   335,   335,
    1654,   333,   194,   154,  1840,   335,  1523,  2003,  1243, -1441,
    1527,  1528,  -177,  1530, -1445,   267,  1135,   447,  1120,  1534,
   -1445,  2080, -1445,   154,   389,  2144,  1042,  1507,  1449,  1383,
     390,  1355,  1450,  2148,  1480,  1806,  1390,   391,  1341,   179,
      62,  1869,   882,  1871,   887,   333,  1332,  2227,   988,   333,
     941,   392,  1939,  1286,   805,  -941,  1640,  1556,   179,   166,
    2020,  2081,  2022,   390,   913,  2047,    87,   979, -1517,  2082,
     391,  1672,  1669,  1449,  2002,  2099, -1491,  1450,  1899, -1517,
     319,  1742,     4,  1481,    18,  1115,  1665,  1026, -1517, -1488,
    2040,  1041,  1053,  1045,  -941,  1045,  1051, -1517,  1026,    12,
     775,  -941,  1341,   444,   104,  2048,   898,  1053,   392,   401,
    1931,   891,   993,  1045,   393,  1286,  -728, -1517,   801,  1131,
     376,  2072,  2073,  1096,  1461,  2049,   888,   335,  1826,   104,
    1090,  1724,    13,  1514,  1297,   983,  2091,  1514,  1730,  2083,
     377,   392,  1074,   394,   335,  1593,  2212,  1107,  2118,   776,
    1150,    22,  1119,  1119,  1119,  1119,  1119,  1119,  1119,    19,
    1748,  1889,  1123,    15,   164,  1834,  1812,  1813,  1814,   818,
    1697,   393,  -941,    25,  1286,  1202,   333,   335,   335,  1732,
    1749,  1815,   395,   402,    28,  1764,  1820,  1821,  1421,  1085,
    1823,  1824,  1825,  1673,  1828,  1829,  1848,  1849,  1428,  2119,
     394,  1098,   105,   794,   393,  1994,  1138,     5,  1867,   990,
    1120,  1120,  1120,  1725,  1743,  2001,  2001,  1676,   184,  1934,
    1120,  1341,    63, -1459,  1592,  1793,   999,   105,    74,  1043,
    1000,  1046,  1238,   394,     5,  -941,  1066,  1757,   892,   395,
   -1441,  2123,  1120,   164,  1120,  1077,  1120,    32,  1392,  1689,
    1120,  1120,  1120,  1120,  1120,  1120,  1120,  1120,  1715,   333,
     469,  1290,  1116,   185,  -941,   164,   179,  1482,  1512,  1642,
   -1445,     5,   395,  1706,  1215,   470,   165,  1338,  1339,  1340,
    2138,  2139,  1709,   333,   471,  1298,  -583,  1351,  1051,  1986,
   -1445,   115,  2124,  1286,  1286,   179,   115,  -941,   186,   187,
    2050,   188,   802,  -941,  1716,   141,  -581,    74,  1512,   189,
     889,  1387,  1827,  2185,   426,   893,   241,  1394,  1396,  1397,
    1399,  1342,   795,  1402,  1404,  1286, -1517,  1906,  1215,    74,
     164,  2207,  2208,  1331,  2041,   335,  1870,  1215,  1872,  1422,
     777,  1359,  1360,  1215,  1278,    17,  2005,  2120,  2121,   389,
    1139,   779,  1874,  1094,  2042,   165,  2163,  1272,  2164,  1172,
    1173,  2011,  1208,   190,  1347,  1348, -1517,  1349,   472,  2092,
     781,   237,  1467,   988,   335,  1468,  1469,   165,  1047, -1445,
    1318,  1361, -1488,  1362,  2019,  1342, -1517,  2057,   390,   778,
    1326,  2024,    29,  2058,    74,   391,  1083,   473,  -583, -1445,
     780, -1441,  1273,  1917,    90,   988, -1463,  1642,  1345,  1346,
    1347,  1348,  1803,  1349,  1363,  1364,  1365, -1405,  -581,   782,
    2231,    33,  2001,  2001,  2059,  2051,  2052,  1691,  2060,    92,
    1259,  1095,    40,   361,  2054,   191,  1594,   389,   368,   325,
    2125,  2126,   165,  1120,  1120,  1120,  1120,  1120,  1120,  1120,
     239,   472,  1905,  1119,  1116,  1116,  1116,   783,  1119,   166,
      35,  1366,   326,  1367,  1116,  1717,   392,  1504, -1441,  1747,
    1260,  1368,  1345,  1346,  1347,  1348,   390,  1349,  1261,   979,
     473, -1403,   753,   391,  1759,  1733,  1116,   474,  1116,   754,
    1116,    93,    43,  1505,  1116,  1116,  1116,  1116,  1116,  1116,
    1116,  1116,    37, -1517,  1342,    44,   784,  2204,    48,   979,
    1596,  1597,  1598,  1599,  1600,  1601,  1603,  1552,  1553,  1286,
     948,  1761,  2134, -1517,   389,    49,  2135,  1286,  1761,   393,
    1742,    94,   475,    95,   540,   950,   541,   321,   476,   799,
   -1407,  2142,  1369,    45,    52,   426,   513,  1723,  1262,   192,
    2007,    46,  1888,   283,   392,  1267,  1053,   979,   394,   800,
     289, -1517,   179,   390,   179,   477,   335,   335,  1268,  2161,
     391,  2162,   478,   290,    58,   543,   250,  1286,  1940,   450,
     548,    59,  2165,  1991,    60,   479,  1424,  1004,  1005,   193,
      67,  1345,  1346,  1347,  1348,    61,  1349,   395,  1998,  1999,
   -1400,  1006,  2172,  2173,  1470,  1471,     5,  1888,   276,   242,
     291,  1540,   480,   282,    71,  1541,  1430,   393,   451,   951,
     481,    74,  1472,  1473,  1521,   452,  2109,    78,  1522,   874,
    -192,  1850,  1634,  2098,  1851,  2056,  1430,   194,  1308,   111,
    1309,   392,  1852,  1853,  1854,    80,   394,  1007,    10,  1718,
     227,   482,    10,  1190,   227,   449,  1193,  1194,   979,  2189,
    2190,    81,  2140,  1743,  2141,   983,  1431,   351,   875,   980,
    1647,   954,   102,  1650,   955,   876,   112,  1425,  1655,   333,
    2102,  2103,  2220,  2191,  1941,   395,  1431,  1116,  1116,  1116,
    1116,  1116,  1116,  1116,   113,  1790,   454,  1791,  1841,   483,
    1842,   179,   121,  1780,   393,  1781,   956,   947,  1370,  1466,
     803,   115,  1467,  2174,  2175,  1468,  1469,  2013,  1898,  2014,
     125,    40,   126,   127,  1902,   450,   292,   128,   129,   130,
    1908,   132,  1888,   394,   133,   135,   293,   144,   145,  2093,
    -310,   146,   415,   160,  1120,   161,   877,  1371,  1384,  1120,
     162,  1855,  1388,   175,   209,   212,  2154,   215,   213,   455,
    1400,  1401,   219,   220,   451,   235,   333,   221,   513,  1856,
      40,   452,   395,   252,   957,  1345,  1346,  1347,  1348,   948,
    1349,   253,   249,   453,  1786,   256,  1857,  1350,  -751,   335,
    1995,  -751,  2133,   257,   950,  1345,  1346,  1347,  1348,   264,
    1349,  1795,   271,  2136,   273,   278,  2137,  1645,  1798,   878,
     280,  1818,  1345,  1346,  1347,  1348,  1822,  1349,   279,   958,
     959,  1758,   312,   294,   295,   285,  1804,   458,   313,   335,
     154,   315,  1858,   319,   324,   322,   296,   328,   297,   327,
     336,   353,   454,   333,   960,   354,  1783,   335,   356,   370,
     373,  1211,   375,   382,  1788,   383,  2209,  2192,  2193,  2210,
    -751,  1792,   961,   400, -1445,   412,  1819,   417,   418,  -322,
     962,   420,   333,   434,   503,  -751,   422,   879,   951,  1859,
     436,  1345,  1346,  1347,  1348,   511,  1349,   335,   464,   389,
    1595,   514,  1615,   520,  1616,   518,   544,  1617,  2194,  2195,
   -1352, -1352, -1352, -1352,   545,   455,   547,  1618,   456,   457,
    2228,   550,  1807,  2201,   558,  1808,   179,   560,  2202,   952,
    1345,  1346,  1347,  1348,   953,  1349,   620,   622,   390,  1649,
     954,   629,  1860,   955,   636,   391,   637,   638,   298,   742,
     745,   553,  1861,   766,  1470,  1471,   767,   774,  2239,  1345,
    1346,  1347,  1348,   785,  1349,   787,   793,   299,  1652,  -751,
     822,   821,  1472,  1473,   864,   956,   896,   900,  2183,   903,
    -751,   916,   917,   458,  2205,   945,   919,   927,   922,   982,
    1221,  1222,  1223,  1224,   995,   929,   933,   939,  1116,  1012,
    1013,   936,   942,  1116,   943,  1012,  1020,  1022,   970,   998,
    -751,  1015,   982,  1862,  1082,  -751,   392,  1084,  1012,  -751,
    1091,  -751,  1099,  1950,  -751,  1105,  -751,  1020,  1076,  1896,
    1078,  1345,  1346,  1347,  1348,  1121,  1349,  1127,  1126,  1108,
    1657,   810,  1619,   957,  1136,  1143,  1620,  1160,  1145,  2237,
    2238, -1351, -1351, -1351, -1351,  1147,  -751,  1151,  1152,  1621,
    1153,  -751,  1154,  1345,  1346,  1347,  1348,  2105,  1349,  1155,
    1156,  1165,  1802,  1345,  1346,  1347,  1348,  1157,  1349,   393,
    1118,  1167,  2004,  1158,  1201,  1203,  1209,  1215,   958,   959,
     753,  1218,  1236,  1225,  1240,  1990,  1255,  -751,  1256,  1258,
    1992, -1354,  1265,  1269,  1271,  1622,  1270, -1445,   394,  1275,
    1144,  1280,  1282,   960,  1053,   154,  1304,  1307,  1313,  1311,
    1314,   414,  1316,  1335,  -751,  2038,  1356,  1373,  1386,  1393,
    1407,   961,  1417,  1408,  1412,   975,  1436,  1438,  1454,   962,
    1476,   333,   948,  1456,  1491,  1207,   335,   395,  1509,  1459,
    1495,  1517,  1623,  1524,  -751,  1212,  2012,   950,  1525,  1532,
    -751,  1537,  2015,  1547,  1548,  1550,  1349,  1604,  1610,  -751,
    -751,  1012,  1634,  1376,  1614,  1611,  1624,  1663,   948,  1012,
    1244,  1664,  1646,  1648,  1658,  1682,  1431,  1693,  1651,  -751,
    1698,  1656,  1707,   950,  -751,  1699,  1695,   982,  1711,  -751,
    1625,  1710,  1735,  1738,  1739,  1626,  1750,  1751,  1765,  1766,
    1752,  1774,  -751,  1285,  1776,  1627, -1445,  1784,  1799,  1628,
    -751,  1012,  -751,  2117,  1846,  1012,  1831,  1847,  -751,  1877,
    1866,  1879,  1883,  1303,  1890,  1033,  1244,  1885,  1893,  1897,
    1743,   951,  1911,  1921,  1914,  1916,  1929,  1924,  1926,  1935,
    1937,  1933,  1947,  1951,  1952,  1954,  1996,  2094,  2008,  1207,
    2021,  2023,  1020,  2026,  2029,  2043,  2044,  2045,  2108,  2067,
    2110,  1033,  1118,  1118,  1118,  2076,  1629,   951,  2069,  2088,
    2095,  1941,  1118,  2106,  2100,  2096,  1630,  2107,  2128,  2152,
    2143,  1034,  2145,   954,  2153,  1963,   955,  2159,  2147,  1285,
    2170,  2131,  2132,  2160,  1118,  2197,  1118,  2180,  1118,  2214,
    2216,  2198,  1118,  1118,  1118,  1118,  1118,  1118,  1118,  1118,
    2218,  2213,  2219,  2235,  2232,  2233,    14,   980,   956,   954,
      27,    73,   955,   251,  2177,   182,   385,   238,  2188,   248,
     268,  1519,   535,   744,  1319,   211,  1949,   463,  1086,   755,
    1093,  2155,  1900,   270,  2199,  2117,   142,   411,    66,   335,
     426,   223,   275,   940,   956,   634,   355,   923,  1801,  1125,
    1970,  2203,  1102,  2112,   563,  2200,   915,   159,  1837,   523,
     741,   335,  1903,  1639,  1811,  1220,   947,  1229,  1638,   803,
    1835,  1457,  1702,  2018,  1873,  1447,   957,  2028,  1487,  1892,
    1712,  2178,  2179,  1264,  1546,  2182,  1285,  1904,  1475,  1740,
    1516,  1920,  2184,  1287,  1288,  1065,  1012,  1772,  2222,  2223,
    1302,  1773,  2225,  2074,  2226,  1805,  1913,  2079,  2157,  1502,
    1419,  1416,   957,   513,  1279,  2090,  1207,  2061,  2062,  1684,
    1122,   958,   959,  1515,  2063,  1756,   284,   366,  1410,  1489,
    1012, -1517,   931,  2211,   335,   760,  1128,  2206,   948,   902,
      75,   979,  1531,  1993,  2234,  1352,   960,     0,  1285,     0,
       0,     0,   414,   950,  1539,     0,  -992,   958,   959,     0,
     979,     0,     0,     0,   961,     0,  2224, -1517,     0,  -992,
    1244,     0,   962,   179,   333,     0,     0,     0,     0,     0,
       0,     0,   960,     0,     0,  1118,  1118,  1118,  1118,  1118,
    1118,  1118,  -992,     0,     0,     0,     0,     0,     0,  2230,
     961,     0,     0,  1520,     0,  -992,     0,  1285,   962,   179,
     333,     0,     0,     0,     0,   414,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1644,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   951,     0,     0,
       0,     0,     0,   947,     0,     0,   803,     0,   389,  1012,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1670,  1671,     0,     0,  1138,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   952,   414,
       0,     0,     0,   953,     0,     0,     0,   390,     0,   954,
       0,     0,   955,     0,   391,     0,     0,     0,     0,     0,
   -1441,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   948,     0,     0,     0,     0,
       0,     0,     0,     0,   956,     0,  1285,  1285,     0,     0,
     950,     0,  1012,  1012,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1741,     0,     0,     0,     0,     0,     0,     0,  1285,     0,
       0,     0,     0,     0,     0,   392,     0,     0,     0,     0,
       0,     0,     0,  1762,     0,     0,     0,     0,  1771,  1771,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     842,     0,   957,     0,     0,  -884,     0,     0,  -884,     0,
       0,  -884,  -884,  -884,     0,     0,     0,   982,     0,  -884,
       0,     0,     0,     0,   951,     0,     0,     0,  1796,     0,
    1797,     0,     0,     0,     0,   389,     0,     0,   393,     0,
       0,     0,     0,     0,     0,     0,     0,   958,   959,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  1521,   952,     0,   394,  1522,     0,
     953, -1441,   960,     0,   390,     0,   954,  -884,     0,   955,
       0,   391,     0,     0,     0,     0,  1207,  1207,  1207,     0,
     961,     0,  -884,     0,     0,     0,  1118,     0,   962,     0,
     333,  1118,     0,     0,     0,     0,   395,     0,     0,     0,
       0,   956,     0,     0,  1012,     0,     0,     0,     0,     0,
       0,     0,     0,   947,     0,     0,   803,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0, -1441,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  -884,
    -884,     0,   392,     0,     0,  1876,     0,     0,     0,     0,
       0,  1887,  1285,     0,     0,     0,     0,     0,     0,     0,
    1285,     0,     0,     0,     0,     0,  -884,  -884,     0,   957,
       0,  1012,     0,  -884,     0,     0,     0,  -884,     0,  1502,
       0,     0,     0,     0,     0,   948,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     950,     0,     0,     0,  -884,   393,  1887,  -884,  -884,     0,
    1285,     0,  -884,  1068,   958,   959,  -884,     0,  -884,     0,
       0,  -884,     0,  -884,     0,     0,     0,     0,     0,  1988,
       0,     0,     0,  1988,   394,     0,  -884,  -884,     0,   960,
       0,  -884,     0,     0,     0,     0,     0,     0,  1988,  1988,
       0,  -884,     0,  -884,     0,     0,     0,   961,  -884,     0,
       0,     0,     0,  -884,     0,   962,     0,   333,     0,     0,
       0,     0,     0,   395,     0,     0,     0,     0,     0,     0,
       0,  -884,     0,     0,   951,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -884,   389,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1301,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  -884,     0,     0,     0,   952,     0,     0,     0,     0,
     953,  1887,     0,     0,   390,     0,   954,     0,     0,   955,
       0,   391,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  -884,     0,     0,
       0,     0,     0,     0,     0,     0,  -884,  -884,     0,     0,
    2071,   956,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  -884,     0,     0,  1988,
       0,  -884,     0,  -578,   524,     0,  -619,     0,  -619,     0,
       0,     0,     0,  -619,     0,     0,  2111,     0,     0,  -884,
       0,  -619,   392,     0,     0,     0,     0,  -884,     0,  -884,
       0,     0,     0,     0,     0,  -884,  -884,  -884,  -884,  -884,
       0,  -884,     0,  -884,  -884,  -884,  -884,  -884,     0,   957,
       0,     0,  1988,  -619,  -619,     0,     0,     0,     0,     0,
    -619,     0,     0,  1988,     0,     0,  1988,     0,     0,     0,
       0,  -619,     0,     0,  -619,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   393,  -619,     0,     0,     0,
       0,     0,     0,     0,   958,   959,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,   394,  -619,  -619,     0,     0,   960,
       0,     0,     0,     0,     0,     0,  2167,     0,     0,  2169,
       0,     0,  -578,     0,     0,     0,  -578,   961,     0,     0,
       0,     0,     0,     0,     0,   962,  -619,   333,     0,     0,
       0,     0,     0,   395,     0,     0,     0,     0,  -619,  2186,
       0,     0,  -619,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1988,     0,  -619,     0,     0,  1988,  -578,
       0,     0,  -619,     0,     0,  -619,  -619,     0,     0,     0,
       0,     0,     0,  -619,     0,     0,     0,     0,     0,     0,
    -619,     0,  -619,     0,     0,  -619,  2215,     0,     0,     0,
       0,     0,   524,     0,  -619,     0,  -619,     0,     0,  2221,
       0,  -619,     0,     0,     0,     0,     0,     0,     0,  -619,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    -619,     0,     0,     0,  -619,     0,  -619,     0,     0,     0,
       0,     0,     0,  -619,     0,     0,     0,     0,     0,     0,
       0,  -619,  -619,     0,     0,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,     0,  -619,     0,     0,     0,  -619,
       0,     0,  -619,     0,     0,     0,     0,     0,     0,     0,
    -619,     0,     0,     0,  -619,     0,     0,     0,     0,     0,
       0,     0,     0,     0,  -578,     0,     0,     0,     0,     0,
       0,  -619,     0,     0,     0,     0,  -619,     0,     0,     0,
    -619,     0,     0,  -619,  -619,     0,     0,     0,     0,     0,
       0,   635,     0,  -619,     0,     0,     0,     0,  -619,     0,
    -619,     0,     0,     0,     0,     0,     0,     0,  -619,     0,
     947,     0,     0,   803,  -619,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,     0,     0,  -619,  -619,     0,     0,
    -619,     0,     0,     0,     0,     0,  -619,     0,  -619,  -619,
       0,     0,  -619,  -619,  -619,     0,     0,     0,     0,  -619,
    -619,     0,     0,  -619,  -619,     0,     0,     0,     0,     0,
       0,  -619,     0,     0,  -619,     0,     0,     0,  -619,  -619,
    -619,     0,     0,  -619,  -619,     0,     0,     0,     0,     0,
       0,     0,   948,     0,     0,  -619,     0,     0,     0,     0,
       0,     0,     0,   525,     0,     0,  -619,   950,     0,     0,
       0,     0,     0,     0,     0,     0,   526,     0,  -619,     0,
    1068,     0,  -619,     0,  -619,     0,     0,   947,     0,     0,
     803,  -619,     0,  1168,  1169,  1170,     0,     0,     0,     0,
       0,  1171,     0,   567,   568,   569,   570,   571,   572,     0,
       0,     0,     0,  -619,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  -619,     0,
       0,     0,     0,     0,     0,     0,     0,   574,     0,   575,
     576,   577,   578,   579,   580,     0,     0,     0,     0,  -619,
       0,   951,     0,     0,     0,     0,     0,     0,  -619,   948,
       0,     0,   389,     0,     0,     0,     0,     0,     0,     0,
       0,  -619,     0,     0,   950,     0,  -619,     0,  -619,   581,
       0,     0,     0,     0,     0,     0,  -619,     0,     0,     0,
       0,     0,   952,     0,     0,     0,  -619,   953,     0,     0,
       0,   390,     0,   954,     0,  -619,   955,     0,   391,     0,
       0,     0,     0,     0,  -619,     0,  -619,  -619,     0,     0,
    -619,     0,  -619,     0,     0,     0,     0,  -619,     0,     0,
       0,  1172,  1173,     0,     0,     0,     0,     0,   956,     0,
       0,     0,  -619,     0,     0,     0,     0,  -619,     0,     0,
       0,     0,  -619,     0,     0,     0,     0,     0,   951,  1174,
       0,   582,     0,  -619,     0,  1175,     0,     0,     0,   389,
       0,   525,     0,     0,  -619,     0,     0,     0,     0,   392,
       0,     0,     0,     0,   526,     0,     0,     0,  1415,     0,
       0,     0,     0,     0,     0,     0,  1176,     0,     0,   952,
    1177,     0,     0,     0,   953,     0,   957,     0,   390,     0,
     954,   584,     0,   955,     0,   391,     0,     0,     0,     0,
       0,     0,     0,     0,   947,     0,     0,   803,  1178,  1179,
    1168,  1169,  1170,  1180,     0,     0,     0,     0,  1171,     0,
       0,     0,   393,  1181,     0,   956,     0,     0,   586,     0,
    1182,   958,   959,     0,     0,  1183,     0,   588,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     589,   394,     0,  1184,     0,     0,   960,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   392,     0,     0,     0,
       0,     0,     0,     0,   961,     0,   948,     0,     0,     0,
       0,     0,   962,     0,   333,     0,     0,     0,     0,     0,
     395,   950,     0,   957,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   593,   594,   595,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   393,
       0,     0,     0,     0,     0,     0,     0,     0,   958,   959,
       0,     0,     0,     0,     0,     0,     0,     0,  1172,  1173,
       0,     0,     0,     0,     0,   597,   598,   599,   394,     0,
       0,     0,     0,   960,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   951,  1174,     0,     0,     0,
       0,   961,  1175,     0,     0,     0,   389,     0,     0,   962,
       0,   333,     0,     0,     0,     0,     0,   395,  1185,  1186,
    1187,  1188,     0,  1189,     0,  1190,  1191,  1192,  1193,  1194,
       0,     0,     0,  1176,     0,     0,   952,  1177,     0,     0,
       0,   953,     0,     0,     0,   390,     0,   954,     0,     0,
     955,     0,   391,   639,     0,   640,     0,     0,     0,     0,
     641,     0,     0,     0,     0,  1178,  1179,     0,   642,     0,
    1180,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1181,     0,   956,     0,     0,     0,     0,  1182,     0,     0,
       0,     0,  1183,     0,     0,     0,     0,     0,     0,     0,
     643,   644,     0,     0,     0,     0,     0,   645,     0,     0,
    1184,     0,     0,     0,     0,     0,     0,     0,   646,     0,
       0,   647,     0,   392,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   648,   947,     0,     0,   803,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     957,     0,     0,     0,     0,   649,     0,     0,     0,     0,
       0,     0,   650,   651,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   393,     0,     0,     0,
       0,     0,     0,   652,     0,   958,   959,     0,     0,     0,
       0,     0,     0,     0,     0,   653,   948,     0,     0,   654,
       0,     0,     0,     0,     0,   394,     0,   949,     0,     0,
     960,   950,   655,     0,     0,     0,     0,     0,     0,   656,
       0,     0,   657,   658,     0,     0,     0,     0,   961,     0,
     659,     0,     0,     0,     0,     0,   962,   660,   333,   661,
       0,     0,   662,     0,   395,  1185,  1186,  1187,  1188,     0,
    1189,     0,  1190,  1191,  1192,  1193,  1194,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   663,   639,     0,
     640,   664,     0,   665,     0,   641,     0,     0,     0,     0,
     666,     0,     0,   642,     0,   951,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   389,   947,     0,     0,
     803,     0,   667,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   643,   644,   668,     0,     0,
       0,     0,   645,     0,     0,     0,   952,     0,     0,     0,
       0,   953,     0,   646,     0,   390,   647,   954,   669,     0,
     955,     0,   391,     0,     0,     0,     0,   670,   648,     0,
       0,   947,     0,     0,   803,     0,     0,     0,     0,     0,
     671,     0,     0,   947,     0,   672,   803,   673,     0,   948,
     649,     0,   956,     0,     0,   674,     0,   650,   651,     0,
    1027,     0,     0,     0,   950,   675,     0,     0,     0,     0,
       0,     0,     0,     0,   676,     0,     0,     0,     0,     0,
       0,     0,     0,   677,     0,   678,   679,     0,   652,   680,
       0,   681,     0,   392,     0,     0,   682,     0,     0,     0,
     653,     0,     0,   948,   654,     0,     0,     0,     0,     0,
       0,   683,     0,     0,  1072,   948,   684,   655,   950,     0,
     957,   685,     0,     0,   656,     0,     0,   657,   658,     0,
     950,     0,   686,     0,     0,   659,     0,     0,     0,     0,
       0,     0,   660,   687,   661,     0,     0,   662,   951,     0,
       0,     0,     0,   688,     0,     0,   393,     0,     0,   389,
       0,     0,     0,     0,     0,   958,   959,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   663,     0,     0,   394,   664,     0,   665,   952,
     960,     0,     0,     0,   953,   666,     0,     0,   390,     0,
     954,     0,   951,   955,     0,   391,     0,     0,   961,     0,
       0,     0,   947,   389,   951,   803,   962,   667,   333,     0,
       0,     0,     0,     0,   395,   389,     0,     0,     0,     0,
       0,     0,   668,     0,     0,   956,     0,     0,     0,     0,
       0,     0,     0,   952,     0,     0,     0,     0,   953,     0,
       0,     0,   390,   669,   954,   952,     0,   955,     0,   391,
     953,     0,   670,     0,   390,     0,   954,     0,     0,   955,
       0,   391,     0,     0,     0,   671,   392,     0,     0,     0,
     672,     0,   673,     0,   948,     0,     0,     0,     0,   956,
     674,     0,     0,   947,     0,     0,   803,     0,     0,   950,
     675,   956,     0,   957,     0,   947,     0,     0,   803,   676,
       0,     0,     0,     0,     0,     0,     0,     0,   677,     0,
     678,   679,     0,     0,   680,     0,   681,     0,     0,     0,
     392,   682,     0,     0,     0,     0,     0,     0,     0,   393,
       0,     0,   392,     0,     0,     0,   683,     0,   958,   959,
       0,   684,     0,     0,     0,     0,   685,   957,     0,   947,
       0,     0,   803,     0,     0,   948,     0,   686,   394,   957,
       0,     0,     0,   960,     0,   803,     0,   948,   687,  1306,
     950,     0,     0,   951,     0,     0,     0,     0,     0,     0,
       0,   961,   950,   393,   389,     0,     0,     0,     0,   962,
       0,   333,   958,   959,     0,   393,     0,   395,     0,     0,
       0,     0,     0,     0,   958,   959,     0,     0,     0,     0,
       0,     0,   394,     0,   952,     0,     0,   960,     0,   953,
    1162,   948,     0,   390,   394,   954,     0,     0,   955,   960,
     391,     0,     0,     0,   948,   961,   950,     0,     0,     0,
       0,     0,     0,   962,     0,   333,     0,   961,     0,   950,
       0,   395,     0,     0,   951,   962,     0,   333,     0,     0,
     956,     0,     0,   395,     0,   389,   951,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   389,   947,     0,
       0,   803,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   952,     0,     0,     0,     0,
     953,   392,     0,     0,   390,     0,   954,   952,     0,   955,
       0,   391,   953,     0,     0,     0,   390,     0,   954,     0,
     951,   955,     0,   391,     0,     0,     0,     0,   957,     0,
       0,   389,     0,   951,     0,     0,     0,     0,     0,     0,
       0,   956,     0,     0,   389,     0,     0,     0,     0,     0,
     948,     0,     0,   956,     0,     0,     0,     0,     0,     0,
       0,   952,     0,     0,   393,   950,   953,     0,     0,     0,
     390,     0,   954,   958,   959,   955,     0,   391,     0,     0,
       0,     0,   392,   390,     0,   954,     0,     0,   955,     0,
     391,     0,     0,   394,   392,     0,     0,     0,   960,     0,
       0,     0,     0,     0,     0,     0,     0,   956,     0,   957,
       0,     0,     0,     0,     0,     0,   961,     0,     0,     0,
     956,   957,     0,     0,   962,     0,   333,     0,     0,     0,
       0,     0,   395,     0,     0,     0,     0,     0,     0,  1529,
       0,     0,     0,     0,     0,   393,     0,     0,   392,   951,
       0,     0,  1658,     0,   958,   959,     0,   393,     0,     0,
     389,   392,     0,     0,     0,     0,   958,   959,     0,     0,
       0,     0,     0,     0,   394,   957,     0,     0,     0,   960,
       0,     0,     0,     0,     0,     0,   394,     0,   957,     0,
     952,   960,     0,     0,     0,   953,     0,   961,     0,   991,
       0,   954,     0,     0,   955,   962,   391,   333,     0,   961,
       0,   393,     0,   395,     0,     0,     0,   962,     0,   333,
     958,   959,     0,     0,   393,   395,     0,     0,     0,     0,
       0,     0,     0,   958,   959,     0,   956,     0,     0,     0,
     394,     0,     0,     0,     0,   960,     0,   948,     0,     0,
       0,     0,     0,   394,     0,     0,     0,     0,   960,     0,
       0,     0,   950,   961,     0,     0,     0,     0,     0,     0,
       0,   962,     0,   333,     0,     0,   961,   392,     0,   395,
       0,   565,     0,     0,   962,     0,   333,     0,     0,     0,
       0,     0,   395,   566,     0,     0,   567,   568,   569,   570,
     571,   572,   573,     0,   957,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     574,     0,   575,   576,   577,   578,   579,   580,     0,     0,
     393,     0,     0,     0,     0,     0,   951,     0,     0,   958,
     959,     0,     0,     0,     0,     0,     0,   389,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   394,
       0,     0,   581,     0,   960,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   961,     0,     0,     0,   390,     0,   954,     0,
     962,   955,   333,   391,     0,     0,     0,     0,   395,     0,
       0,     0,     0,  1557,     0,  1558,     0,     0,  1559,   567,
     568,   569,   570,   571,   572,   573,  1560,  1561,  1562,     0,
       0,     0,     0,   956,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1563,     0,     0,     0,
       0,     0,     0,   574,   582,   575,   576,   577,   578,   579,
     580,     0,     0,     0,     0,     0,     0,    40,     0,     0,
     583,     0,     0,     0,   392,     0, -1498,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   581,     0,     0,     0,   948,
       0,   957,     0,     0,   584,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   950,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   585,     0,     0,     0,
       0,     0,     0,     0,     0,  1564,     0,   393,     0,     0,
       0,   586,     0,     0,     0,     0,   958,   959,   587,     0,
     588,     0,     0,  1565,     0,     0,  1566,  1567,     0,     0,
       0,     0,     0,   589,     0,     0,   394,     0,     0,     0,
    1568,   960,     0,   590,     0,     0,     0,   582,     0,     0,
     591,     0,     0,     0,     0,     0,     0,     0,     0,   961,
       0,     0,     0,   583,     0,     0,     0,   962,   951,   333,
       0,     0,     0,     0,     0,   395,     0,  1569,     0,   389,
       0,   948,     0,     0,     0,     0,  1570,   592,     0,   593,
     594,   595,     0,     0,     0,     0,   950,   584,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1110,
       0,     0,     0,   596,   953,     0,     0,     0,   390,  1571,
     954,     0,     0,   955,     0,   391,     0,     0,     0,     0,
   -1498,     0,     0,  1572,   586,     0,     0,     0,   597,   598,
     599,   587,     0,   588,     0,     0,     0,     0,     0,     0,
       0,   600,     0,     0,   601,   956,   589,  1573,     0,     0,
       0,   948,     0,     0,     0,   567,   568,   569,   570,   571,
     572,   573,     0,  -317,     0,     0,   950,     0,     0,     0,
     951,  1574,     0,     0,     0,     0,  1575,     0,     0,     0,
       0,   389,  1955,  1956,     0,     0,   392,     0,     0,   574,
    1576,   575,   576,   577,   578,   579,   580,     0,     0,     0,
     592,     0,   593,   594,   595,     0,     0,     0,     0,     0,
       0,  1110,     0,   957,     0,     0,   953,     0,     0,     0,
     390,     0,   954,     0,     0,   955,     0,   391,     0,     0,
       0,   581,     0,     0,     0,     0,  1577,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,  1578,     0,   393,
     951,   597,   598,   599,     0,     0,     0,   956,   958,   959,
       0,   389,     0,     0,   600,     0,  1579,   601,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   394,     0,
       0,     0,     0,   960,     0,     0,  1580,     0,     0,     0,
       0,  1110,     0,     0,     0,     0,   953,     0,   392,     0,
     390,   961,   954,     0,  1957,   955,     0,   391,     0,   962,
       0,   333,     0,   582,     0,     0,     0,   395,  1111,  1112,
       0,     0,     0,     0,     0,   957,  1113,  1602,     0,   583,
       0,     0,     0,     0,     0,     0,     0,   956,     0,     0,
       0,     0,     0,  1958,  1959,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   393,     0,   584,     0,     0,     0,     0,  1960,     0,
     958,   959,     0,     0,     0,     0,     0,     0,   392,     0,
       0,     0,     0,     0,     0,   585,     0,     0,     0,     0,
     394,     0,     0,     0,     0,   960,     0,     0,     0,     0,
     586,     0,     0,     0,     0,   957,     0,   587,     0,   588,
       0,     0,  1961,   961,     0,     0,     0,     0,     0,     0,
       0,   962,   589,   333,     0,     0,     0,     0,     0,   395,
    1111,  1112,     0,     0,     0,     0,     0,     0,  1113,  1817,
       0,   393,     0,     0,     0,     0,     0,     0,     0,     0,
     958,   959,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     394,     0,     0,     0,     0,   960,   592,     0,   593,   594,
     595,     0,     0,     0,     0,  1962,     0,     0,     0,     0,
       0,     0,     0,   961,     0,     0,     0,     0,     0,  1963,
       0,   962,     0,   333,     0,     0,     0,     0,     0,   395,
    1111,  1112,     0,     0,     0,     0,     0,     0,  1113,     0,
       0,     0,  1964,     0,     0,     0,     0,   597,   598,   599,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     600,     0,     0,   601,  1965,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,  1966
};

static const yytype_int16 yycheck[] =
{
      83,   165,   364,   621,   657,   601,   236,   478,   805,   410,
     480,  1095,   831,  1267,  1068,  1177,   686,   590,   259,   826,
     261,   627,   263,  1062,   188,   189,   190,   828,   192,   836,
     194,   844,   185,  1496,   769,   827,  1376,  1377,   191,   259,
     962,   261,  1052,   263,   857,  1644,   564,    13,  1162,   433,
       9,     9,  1010,   330,    17,   984,  1334,   210,     6,  1334,
    1018,  1334,   226,  1231,   228,     6,   149,  1222,  1223,  1224,
    1253,   235,     6,   544,  1334,  1334,  1334,    27,   825,   243,
      22,   311,   323,    58,    67,    17,   833,   834,   318,    81,
     331,   255,   256,     9,   258,    91,    53,   338,   262,     6,
    1139,   848,   849,   323,    47,    71,  1064,    91,     6,    84,
      85,   331,   265,   266,  1228,   862,   863,    55,   338,   396,
     143,    87,    69,    11,   365,   116,   290,    60,  1138,   293,
     294,   361,   296,   115,    48,  1271,    67,   175,   368,    55,
      55,    69,   115,  1777,  1258,   365,   165,   367,   312,   165,
     947,   381,  1335,   207,    67,   952,   164,   627,    67,   109,
    1429,    67,   564,  1762,   866,   329,   116,   115,    56,  1098,
      63,     9,    48,  1356,   227,   162,  1445,     9,   408,    29,
     798,    55,   412,   403,   425,   290,    48,   464,   341,   272,
     227,   117,  1306,   756,   200,    21,    88,    47,    63,   363,
     227,   227,    82,    91,    92,   425,    94,   371,  1133,   207,
     144,   290,  1009,   211,   102,   207,   374,    22,   965,   108,
      82,    48,   269,  1563,  1493,   315,   231,   974,   846,  1569,
      30,  1360,   207,  1765,   112,  1245,   466,  1935,  1367,  1937,
      21,   227,  1326,   239,   628,  1374,   993,  1060,    39,   479,
     180,   167,   242,  1721,   772,   101,   420,  1311,   165,    27,
     206,   309,   269,   346,  1533,   207,   349,   919,   156,   227,
     101,   112,    24,    29,   169,   439,   440,   300,   169,  1462,
    1027,   511,   117,   990,   312,     0,   516,   231,  1456,   392,
    2211,  1459,   227,  1407,   309,     9,   311,  1307,    36,   295,
     216,   521,   522,     8,   104,   239,   924,   251,   283,  2230,
     256,   475,   908,  1110,   249,   362,   364,   365,   168,   309,
     270,   311,  1069,   169,   429,   430,   161,  1074,   362,    34,
    1367,  1289,   337,   939,   424,   181,   500,  1374,   227,  1046,
     228,   109,   445,  1162,   508,   503,  1275,   238,   278,   227,
     429,   227,     9,   339,   289,   585,  1366,   344,  1890,   224,
     407,   934,   935,   370,   120,   312,  1420,   350,   396,   107,
     772,   591,   124,   407,   937,   938,   203,   430,  2076,   543,
     306,   851,   227,   436,   548,     9,   227,   551,   552,   443,
     554,   555,  1661,   430,   558,   227,   311,  1436,   291,  1101,
    1052,   315,   207,   430,   430,   443,  1213,   430,   395,  1228,
    1546,   430,  2046,   251,   430,  1162,     9,   423,  1886,   350,
     353,  1889,   430,  1230,   319,    49,   291,   227,   354,   321,
    1355,   413,   430,   425,   430,   315,   600,   350,   429,  1258,
     413,   350,  1255,   234,   350,   393,   430,  1239,  1195,   396,
    1408,   277,   393,   315,   342,   393,   399,   385,   390,  1111,
    1112,  1113,    55,   446,   427,   413,   423,   828,   443,  1121,
     308,   430,   430,   211,   188,  1485,  1939,  1269,   444,   429,
    1227,  1228,   430,  1612,   400,   846,  1138,  1306,   430,   430,
     851,  1143,   384,  1145,   382,  1147,   430,  1149,  1752,  1151,
    1152,  1153,  1154,  1155,  1156,  1157,  1158,  1517,  1126,  1787,
     424,  1258,  1787,   227,  1787,   446,  1460,   758,   759,  1172,
     234,  1465,   429,   430,   765,  1317,   803,  1787,  1787,  1787,
    1698,   188,   430,   446,  1492,  1690,   756,   446,   758,   759,
     446,   430,   430,    48,   424,   765,  1293,  1816,  1018,   399,
    1297,  1298,   430,  1300,   430,   443,   940,   431,   919,  1306,
     436,   160,   424,    48,   188,  2033,  1036,  1274,   394,  1142,
     227,  1134,   398,  2036,   167,  1612,  1149,   234,    67,   429,
     162,  1695,   746,  1697,   748,   430,  1104,  2186,  1407,   430,
     820,   305,  1775,  1245,   218,   188,   227,  1332,   429,   430,
    1869,   200,  1871,   227,   768,   191,   133,   827,   231,   208,
     234,   157,  1666,   394,  1810,  1955,   354,   398,  1732,   259,
     227,   120,   176,   216,   227,   919,  1418,   847,   251,    60,
    1899,   851,   239,   853,   227,   855,   856,   231,   858,   443,
     358,   234,    67,   133,   242,   231,   887,   239,   305,   193,
    1764,    31,   833,   873,   368,  1307,   180,   251,   216,   936,
     161,  1930,  1931,   904,  1237,   251,   111,   887,   216,   242,
     890,   193,   443,  1279,   180,  1036,   283,  1283,  1491,   278,
     181,   305,   863,   397,   904,  1337,  2149,   917,   238,   407,
     953,   114,  1344,  1345,  1346,  1347,  1348,  1349,  1350,   302,
     231,  1711,   922,   144,   236,  1663,  1635,  1636,  1637,   173,
     180,   368,   305,    26,  1366,   978,   430,   937,   938,   180,
     251,  1643,   436,   267,   443,   180,  1648,  1649,   180,   882,
    1652,  1653,  1654,   279,  1656,  1657,  1680,  1681,  1208,   289,
     397,   905,   340,   217,   368,  1799,    29,   301,  1692,   832,
    1111,  1112,  1113,   275,   253,  1809,  1810,  1427,    11,  1769,
    1121,    67,   344,   227,  1337,  1566,   394,   340,   300,   852,
     398,   854,  1730,   397,   301,   368,   859,  1524,   158,   436,
      63,   238,  1143,   236,  1145,   868,  1147,   227,  1149,   429,
    1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,     9,   430,
       4,   393,   919,    56,   397,   236,   429,   400,  1278,  1382,
     315,   301,   436,  1466,   338,    19,   348,  1111,  1112,  1113,
    2016,  2017,  1475,   430,    28,   331,   331,  1121,  1048,   436,
     315,   430,   289,  1485,  1486,   429,   430,   430,    91,    92,
     426,    94,   400,   436,    55,   443,   331,   300,  1318,   102,
     295,  1145,   400,  2107,  1095,   235,    60,  1151,  1152,  1153,
    1154,   350,   336,  1157,  1158,  1517,   191,   192,   338,   300,
     236,  2140,  2141,  1103,   231,  1095,  1695,   338,  1697,   331,
     358,    24,    25,   338,  1047,    11,  1830,   437,   438,   188,
     173,   358,  1699,   366,   251,   348,  2058,   249,  2060,   150,
     151,  1845,   985,   156,   439,   440,   231,   442,   195,  1948,
     358,   443,    12,  1732,  1134,    15,    16,   348,   855,   424,
    1083,    64,   353,    66,  1868,   350,   251,   178,   227,   407,
    1094,  1875,    96,   184,   300,   234,   873,   224,   443,   424,
     407,   224,   294,  1750,    70,  1764,   181,  1520,   437,   438,
     439,   440,  1605,   442,    97,    98,    99,   446,   443,   407,
    2214,   443,  2016,  2017,   215,  1909,  1910,  1437,   219,   265,
     160,   444,   207,   289,  1918,   228,  1337,   188,   294,   204,
     437,   438,   348,  1344,  1345,  1346,  1347,  1348,  1349,  1350,
     443,   195,  1739,  1645,  1111,  1112,  1113,   358,  1650,   430,
      79,   144,   227,   146,  1121,   216,   305,     8,   291,  1511,
     200,   154,   437,   438,   439,   440,   227,   442,   208,  1239,
     224,   446,   309,   234,  1526,  1495,  1143,   231,  1145,   316,
    1147,   327,   346,    34,  1151,  1152,  1153,  1154,  1155,  1156,
    1157,  1158,   114,   231,   350,   163,   407,  2131,   443,  1269,
    1344,  1345,  1346,  1347,  1348,  1349,  1350,   224,   225,  1711,
      78,  1531,  2006,   251,   188,   297,  2010,  1719,  1538,   368,
     120,   367,   276,   369,   268,    93,   270,   443,   282,   161,
     430,  2025,   225,   201,   443,  1326,  1327,  1488,   278,   342,
    1837,   209,  1710,   443,   305,   412,   239,  1317,   397,   181,
      46,   426,   429,   227,   429,   309,  1326,  1327,   425,  2053,
     234,  2055,   316,    59,   443,   469,   443,  1769,   148,   188,
     474,   443,  2066,  1792,   346,   329,   314,   286,   287,   382,
     114,   437,   438,   439,   440,   443,   442,   436,  1807,  1808,
     446,   300,  2086,  2087,   244,   245,   301,  1765,   218,   353,
      96,   153,   356,   223,   129,   157,   206,   368,   227,   177,
     364,   300,   262,   263,   394,   234,  1963,   443,   398,   188,
     374,    32,   260,   261,    35,  1922,   206,   430,   309,   443,
     311,   305,    43,    44,    45,   346,   397,   346,     2,   400,
     155,   395,     6,   444,   159,   118,   447,   448,  1418,    86,
      87,   432,  2021,   253,  2023,  1566,   256,   277,   227,   227,
    1394,   229,   163,  1397,   232,   234,   346,   405,  1402,   430,
     260,   261,  2166,   110,   254,   436,   256,  1344,  1345,  1346,
    1347,  1348,  1349,  1350,   230,   147,   305,   149,   255,   443,
     257,   429,   331,   309,   368,   311,   264,     6,   391,     9,
       9,   430,    12,   224,   225,    15,    16,   147,  1729,   149,
     443,   207,   443,   443,  1734,   188,   212,   443,   443,   349,
    1740,   443,  1890,   397,   209,   395,   222,   443,   346,  1948,
     430,   226,   352,   430,  1645,   443,   305,   430,  1143,  1650,
     443,   152,  1147,   175,   273,   443,  2043,    23,   385,   368,
    1155,  1156,   443,   346,   227,   362,   430,   322,  1549,   170,
     207,   234,   436,   101,   332,   437,   438,   439,   440,    78,
     442,   430,   443,   246,  1554,   374,   187,   449,     6,  1549,
    1801,     9,  2001,   357,    93,   437,   438,   439,   440,    55,
     442,  1571,    81,  2012,   169,   443,  2015,   449,  1589,   368,
     341,  1645,   437,   438,   439,   440,  1650,   442,   346,   377,
     378,  1525,   362,   309,   310,   430,  1607,   436,   273,  1589,
      48,   103,   233,   227,   204,   353,   322,   240,   324,   443,
      65,   443,   305,   430,   402,   346,  1550,  1607,   443,   240,
      22,   150,   267,   430,  1558,   443,  2143,   284,   285,  2146,
      78,  1565,   420,   227,    82,   291,  1647,   443,   443,    80,
     428,    80,   430,   425,   307,    93,   430,   436,   177,   280,
     430,   437,   438,   439,   440,   393,   442,  1647,   390,   188,
     446,   225,    30,   430,    32,   193,   309,    35,   325,   326,
     416,   417,   418,   419,   393,   368,   354,    45,   371,   372,
    2197,    54,  1616,  2122,   374,  1619,   429,    36,  2127,   218,
     437,   438,   439,   440,   223,   442,    26,   181,   227,   446,
     229,   362,   333,   232,   443,   234,   443,   346,   424,   443,
     374,   211,   343,   430,   244,   245,   354,   218,  2235,   437,
     438,   439,   440,   427,   442,   336,   207,   443,   446,   177,
     227,   103,   262,   263,   296,   264,   371,   277,  2104,   271,
     188,   436,   393,   436,  2132,   824,   445,    26,   390,   828,
     416,   417,   418,   419,   833,   352,   267,   168,  1645,   838,
     839,   450,   443,  1650,   443,   844,   845,   846,   430,   227,
     218,   130,   851,   404,   101,   223,   305,    17,   857,   227,
     429,   229,   166,  1783,   232,   181,   234,   866,   867,  1723,
     869,   437,   438,   439,   440,   445,   442,   227,   390,   392,
     446,    29,   170,   332,   121,   445,   174,   122,   445,  2232,
    2233,   416,   417,   418,   419,   445,   264,   445,   445,   187,
     445,   269,   445,   437,   438,   439,   440,  1959,   442,   445,
     445,   198,   446,   437,   438,   439,   440,   445,   442,   368,
     919,    55,   446,   445,   393,   423,   124,   338,   377,   378,
     309,   126,    95,   127,   389,  1789,   393,   305,   131,    48,
    1794,   392,   132,   390,   387,   233,   392,   315,   397,   173,
     949,   137,   425,   402,   239,    48,   140,   173,   323,   106,
     370,  1734,   270,   108,   332,  1896,   108,   429,   393,   430,
     180,   420,   299,   331,   388,   227,   415,   157,   128,   428,
     165,   430,    78,   427,   393,   984,  1896,   436,   203,   427,
     356,   393,   280,    48,   362,   444,  1850,    93,   211,   173,
     368,   203,  1856,   116,   270,   186,   442,   355,   435,   377,
     378,  1010,   260,   224,   211,   434,   304,   331,    78,  1018,
    1019,   393,   446,   446,   363,   125,   256,   255,   446,   397,
      17,   446,   321,    93,   402,   390,   180,  1036,    48,   407,
     328,   393,   132,     8,   173,   333,   427,   120,   393,     9,
     427,   297,   420,  1052,   298,   343,   424,   167,   195,   347,
     428,  1060,   430,  1983,   319,  1064,   258,   334,   436,   119,
     259,   424,   104,  1072,    48,   171,  1075,   424,   169,   275,
     253,   177,   135,   252,   136,   231,   290,   138,   279,   107,
     384,   274,     7,   110,   213,    64,   394,  1951,   123,  1098,
     318,   318,  1101,   130,    96,    48,   231,   211,  1962,   139,
    1964,   171,  1111,  1112,  1113,    90,   404,   177,   257,   142,
      87,   254,  1121,   185,   196,   214,   414,   427,   430,  2039,
      48,   227,   396,   229,   334,   380,   232,   231,   297,  1138,
     141,  1995,  1996,   231,  1143,   173,  1145,   168,  1147,   412,
     134,   283,  1151,  1152,  1153,  1154,  1155,  1156,  1157,  1158,
     274,   297,   274,    48,   150,   150,     6,   227,   264,   229,
      21,    53,   232,   182,  2094,   128,   317,   167,  2109,   177,
     196,  1290,   460,   537,  1084,   132,  1779,   396,   887,   549,
     893,  2045,  1733,   212,  2114,  2115,   107,   346,    48,  2109,
    2131,   149,   217,   819,   264,   522,   284,   797,  1591,   924,
    1787,  2129,   907,  1978,   505,  2115,   772,   120,  1668,   442,
     533,  2131,  1737,  1379,  1631,   993,     6,   998,  1378,     9,
    1666,  1233,  1459,  1863,  1698,  1230,   332,  1880,  1248,  1719,
    1483,  2095,  2096,  1036,  1318,  2099,  1245,  1738,  1242,  1507,
    1283,  1754,  2106,  1058,  1060,   858,  1255,  1538,  2178,  2179,
    1069,  1538,  2182,  1933,  2184,  1609,  1745,  1938,  2046,  1268,
    1202,  1195,   332,  2204,  1048,  1944,  1275,  1923,  1923,  1434,
     920,   377,   378,  1282,  1923,  1520,   224,   292,  1167,  1253,
    1289,   387,   802,  2147,  2204,   556,   929,  2133,    78,   762,
      56,  2211,  1301,  1795,  2224,  1124,   402,    -1,  1307,    -1,
      -1,    -1,  2085,    93,  1313,    -1,   412,   377,   378,    -1,
    2230,    -1,    -1,    -1,   420,    -1,  2180,   387,    -1,   425,
    1329,    -1,   428,   429,   430,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   402,    -1,    -1,  1344,  1345,  1346,  1347,  1348,
    1349,  1350,   412,    -1,    -1,    -1,    -1,    -1,    -1,  2213,
     420,    -1,    -1,   143,    -1,   425,    -1,  1366,   428,   429,
     430,    -1,    -1,    -1,    -1,  2148,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1386,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,     9,    -1,   188,  1408,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1421,  1422,    -1,    -1,    29,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,  2212,
      -1,    -1,    -1,   223,    -1,    -1,    -1,   227,    -1,   229,
      -1,    -1,   232,    -1,   234,    -1,    -1,    -1,    -1,    -1,
      63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   264,    -1,  1485,  1486,    -1,    -1,
      93,    -1,  1491,  1492,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1509,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1517,    -1,
      -1,    -1,    -1,    -1,    -1,   305,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1532,    -1,    -1,    -1,    -1,  1537,  1538,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,   332,    -1,    -1,     6,    -1,    -1,     9,    -1,
      -1,    12,    13,    14,    -1,    -1,    -1,  1566,    -1,    20,
      -1,    -1,    -1,    -1,   177,    -1,    -1,    -1,  1577,    -1,
    1579,    -1,    -1,    -1,    -1,   188,    -1,    -1,   368,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   377,   378,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   394,   218,    -1,   397,   398,    -1,
     223,   224,   402,    -1,   227,    -1,   229,    78,    -1,   232,
      -1,   234,    -1,    -1,    -1,    -1,  1635,  1636,  1637,    -1,
     420,    -1,    93,    -1,    -1,    -1,  1645,    -1,   428,    -1,
     430,  1650,    -1,    -1,    -1,    -1,   436,    -1,    -1,    -1,
      -1,   264,    -1,    -1,  1663,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   291,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,
     151,    -1,   305,    -1,    -1,  1704,    -1,    -1,    -1,    -1,
      -1,  1710,  1711,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1719,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,   332,
      -1,  1730,    -1,   184,    -1,    -1,    -1,   188,    -1,  1738,
      -1,    -1,    -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      93,    -1,    -1,    -1,   215,   368,  1765,   218,   219,    -1,
    1769,    -1,   223,   106,   377,   378,   227,    -1,   229,    -1,
      -1,   232,    -1,   234,    -1,    -1,    -1,    -1,    -1,  1788,
      -1,    -1,    -1,  1792,   397,    -1,   247,   248,    -1,   402,
      -1,   252,    -1,    -1,    -1,    -1,    -1,    -1,  1807,  1808,
      -1,   262,    -1,   264,    -1,    -1,    -1,   420,   269,    -1,
      -1,    -1,    -1,   274,    -1,   428,    -1,   430,    -1,    -1,
      -1,    -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   292,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   305,   188,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   332,    -1,    -1,    -1,   218,    -1,    -1,    -1,    -1,
     223,  1890,    -1,    -1,   227,    -1,   229,    -1,    -1,   232,
      -1,   234,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   377,   378,    -1,    -1,
    1929,   264,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,    -1,  1948,
      -1,   402,    -1,     0,     1,    -1,     3,    -1,     5,    -1,
      -1,    -1,    -1,    10,    -1,    -1,  1965,    -1,    -1,   420,
      -1,    18,   305,    -1,    -1,    -1,    -1,   428,    -1,   430,
      -1,    -1,    -1,    -1,    -1,   436,   437,   438,   439,   440,
      -1,   442,    -1,   444,   445,   446,   447,   448,    -1,   332,
      -1,    -1,  2001,    50,    51,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    -1,  2012,    -1,    -1,  2015,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   368,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   377,   378,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   105,    -1,
      -1,    -1,    -1,    -1,   397,   112,   113,    -1,    -1,   402,
      -1,    -1,    -1,    -1,    -1,    -1,  2075,    -1,    -1,  2078,
      -1,    -1,   129,    -1,    -1,    -1,   133,   420,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   428,   143,   430,    -1,    -1,
      -1,    -1,    -1,   436,    -1,    -1,    -1,    -1,   155,  2108,
      -1,    -1,   159,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  2122,    -1,   172,    -1,    -1,  2127,   176,
      -1,    -1,   179,    -1,    -1,   182,   183,    -1,    -1,    -1,
      -1,    -1,    -1,   190,    -1,    -1,    -1,    -1,    -1,    -1,
     197,    -1,   199,    -1,    -1,   202,  2155,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,    -1,     5,    -1,    -1,  2168,
      -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     237,    -1,    -1,    -1,   241,    -1,   243,    -1,    -1,    -1,
      -1,    -1,    -1,   250,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,   272,    -1,    -1,    -1,    68,
      -1,    -1,    71,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     287,    -1,    -1,    -1,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   301,    -1,    -1,    -1,    -1,    -1,
      -1,   308,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,
     317,    -1,    -1,   112,   113,    -1,    -1,    -1,    -1,    -1,
      -1,   120,    -1,   330,    -1,    -1,    -1,    -1,   335,    -1,
     337,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,
       6,    -1,    -1,     9,   143,    -1,    -1,    -1,   355,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   155,   364,    -1,    -1,
     159,    -1,    -1,    -1,    -1,    -1,   373,    -1,   375,   376,
      -1,    -1,   379,   172,   381,    -1,    -1,    -1,    -1,   386,
     179,    -1,    -1,   182,   183,    -1,    -1,    -1,    -1,    -1,
      -1,   190,    -1,    -1,   401,    -1,    -1,    -1,   197,   406,
     199,    -1,    -1,   202,   411,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    78,    -1,    -1,   422,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   430,    -1,    -1,   433,    93,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   443,    -1,   237,    -1,
     106,    -1,   241,    -1,   243,    -1,    -1,     6,    -1,    -1,
       9,   250,    -1,    12,    13,    14,    -1,    -1,    -1,    -1,
      -1,    20,    -1,    36,    37,    38,    39,    40,    41,    -1,
      -1,    -1,    -1,   272,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   287,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,
      73,    74,    75,    76,    77,    -1,    -1,    -1,    -1,   308,
      -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,   317,    78,
      -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   330,    -1,    -1,    93,    -1,   335,    -1,   337,   112,
      -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,    -1,    -1,
      -1,    -1,   218,    -1,    -1,    -1,   355,   223,    -1,    -1,
      -1,   227,    -1,   229,    -1,   364,   232,    -1,   234,    -1,
      -1,    -1,    -1,    -1,   373,    -1,   375,   376,    -1,    -1,
     379,    -1,   381,    -1,    -1,    -1,    -1,   386,    -1,    -1,
      -1,   150,   151,    -1,    -1,    -1,    -1,    -1,   264,    -1,
      -1,    -1,   401,    -1,    -1,    -1,    -1,   406,    -1,    -1,
      -1,    -1,   411,    -1,    -1,    -1,    -1,    -1,   177,   178,
      -1,   194,    -1,   422,    -1,   184,    -1,    -1,    -1,   188,
      -1,   430,    -1,    -1,   433,    -1,    -1,    -1,    -1,   305,
      -1,    -1,    -1,    -1,   443,    -1,    -1,    -1,   207,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   215,    -1,    -1,   218,
     219,    -1,    -1,    -1,   223,    -1,   332,    -1,   227,    -1,
     229,   244,    -1,   232,    -1,   234,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     6,    -1,    -1,     9,   247,   248,
      12,    13,    14,   252,    -1,    -1,    -1,    -1,    20,    -1,
      -1,    -1,   368,   262,    -1,   264,    -1,    -1,   281,    -1,
     269,   377,   378,    -1,    -1,   274,    -1,   290,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     303,   397,    -1,   292,    -1,    -1,   402,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   305,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   420,    -1,    78,    -1,    -1,    -1,
      -1,    -1,   428,    -1,   430,    -1,    -1,    -1,    -1,    -1,
     436,    93,    -1,   332,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   359,   360,   361,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   377,   378,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   150,   151,
      -1,    -1,    -1,    -1,    -1,   408,   409,   410,   397,    -1,
      -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,    -1,
      -1,   420,   184,    -1,    -1,    -1,   188,    -1,    -1,   428,
      -1,   430,    -1,    -1,    -1,    -1,    -1,   436,   437,   438,
     439,   440,    -1,   442,    -1,   444,   445,   446,   447,   448,
      -1,    -1,    -1,   215,    -1,    -1,   218,   219,    -1,    -1,
      -1,   223,    -1,    -1,    -1,   227,    -1,   229,    -1,    -1,
     232,    -1,   234,     3,    -1,     5,    -1,    -1,    -1,    -1,
      10,    -1,    -1,    -1,    -1,   247,   248,    -1,    18,    -1,
     252,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     262,    -1,   264,    -1,    -1,    -1,    -1,   269,    -1,    -1,
      -1,    -1,   274,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
     292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    71,    -1,   305,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    83,     6,    -1,    -1,     9,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     332,    -1,    -1,    -1,    -1,   105,    -1,    -1,    -1,    -1,
      -1,    -1,   112,   113,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,    -1,
      -1,    -1,    -1,   143,    -1,   377,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   155,    78,    -1,    -1,   159,
      -1,    -1,    -1,    -1,    -1,   397,    -1,    89,    -1,    -1,
     402,    93,   172,    -1,    -1,    -1,    -1,    -1,    -1,   179,
      -1,    -1,   182,   183,    -1,    -1,    -1,    -1,   420,    -1,
     190,    -1,    -1,    -1,    -1,    -1,   428,   197,   430,   199,
      -1,    -1,   202,    -1,   436,   437,   438,   439,   440,    -1,
     442,    -1,   444,   445,   446,   447,   448,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   237,     3,    -1,
       5,   241,    -1,   243,    -1,    10,    -1,    -1,    -1,    -1,
     250,    -1,    -1,    18,    -1,   177,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   188,     6,    -1,    -1,
       9,    -1,   272,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,   287,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,   218,    -1,    -1,    -1,
      -1,   223,    -1,    68,    -1,   227,    71,   229,   308,    -1,
     232,    -1,   234,    -1,    -1,    -1,    -1,   317,    83,    -1,
      -1,     6,    -1,    -1,     9,    -1,    -1,    -1,    -1,    -1,
     330,    -1,    -1,     6,    -1,   335,     9,   337,    -1,    78,
     105,    -1,   264,    -1,    -1,   345,    -1,   112,   113,    -1,
      89,    -1,    -1,    -1,    93,   355,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   364,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   373,    -1,   375,   376,    -1,   143,   379,
      -1,   381,    -1,   305,    -1,    -1,   386,    -1,    -1,    -1,
     155,    -1,    -1,    78,   159,    -1,    -1,    -1,    -1,    -1,
      -1,   401,    -1,    -1,    89,    78,   406,   172,    93,    -1,
     332,   411,    -1,    -1,   179,    -1,    -1,   182,   183,    -1,
      93,    -1,   422,    -1,    -1,   190,    -1,    -1,    -1,    -1,
      -1,    -1,   197,   433,   199,    -1,    -1,   202,   177,    -1,
      -1,    -1,    -1,   443,    -1,    -1,   368,    -1,    -1,   188,
      -1,    -1,    -1,    -1,    -1,   377,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   237,    -1,    -1,   397,   241,    -1,   243,   218,
     402,    -1,    -1,    -1,   223,   250,    -1,    -1,   227,    -1,
     229,    -1,   177,   232,    -1,   234,    -1,    -1,   420,    -1,
      -1,    -1,     6,   188,   177,     9,   428,   272,   430,    -1,
      -1,    -1,    -1,    -1,   436,   188,    -1,    -1,    -1,    -1,
      -1,    -1,   287,    -1,    -1,   264,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   218,    -1,    -1,    -1,    -1,   223,    -1,
      -1,    -1,   227,   308,   229,   218,    -1,   232,    -1,   234,
     223,    -1,   317,    -1,   227,    -1,   229,    -1,    -1,   232,
      -1,   234,    -1,    -1,    -1,   330,   305,    -1,    -1,    -1,
     335,    -1,   337,    -1,    78,    -1,    -1,    -1,    -1,   264,
     345,    -1,    -1,     6,    -1,    -1,     9,    -1,    -1,    93,
     355,   264,    -1,   332,    -1,     6,    -1,    -1,     9,   364,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   373,    -1,
     375,   376,    -1,    -1,   379,    -1,   381,    -1,    -1,    -1,
     305,   386,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,
      -1,    -1,   305,    -1,    -1,    -1,   401,    -1,   377,   378,
      -1,   406,    -1,    -1,    -1,    -1,   411,   332,    -1,     6,
      -1,    -1,     9,    -1,    -1,    78,    -1,   422,   397,   332,
      -1,    -1,    -1,   402,    -1,     9,    -1,    78,   433,   173,
      93,    -1,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   420,    93,   368,   188,    -1,    -1,    -1,    -1,   428,
      -1,   430,   377,   378,    -1,   368,    -1,   436,    -1,    -1,
      -1,    -1,    -1,    -1,   377,   378,    -1,    -1,    -1,    -1,
      -1,    -1,   397,    -1,   218,    -1,    -1,   402,    -1,   223,
     393,    78,    -1,   227,   397,   229,    -1,    -1,   232,   402,
     234,    -1,    -1,    -1,    78,   420,    93,    -1,    -1,    -1,
      -1,    -1,    -1,   428,    -1,   430,    -1,   420,    -1,    93,
      -1,   436,    -1,    -1,   177,   428,    -1,   430,    -1,    -1,
     264,    -1,    -1,   436,    -1,   188,   177,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   188,     6,    -1,
      -1,     9,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   218,    -1,    -1,    -1,    -1,
     223,   305,    -1,    -1,   227,    -1,   229,   218,    -1,   232,
      -1,   234,   223,    -1,    -1,    -1,   227,    -1,   229,    -1,
     177,   232,    -1,   234,    -1,    -1,    -1,    -1,   332,    -1,
      -1,   188,    -1,   177,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   264,    -1,    -1,   188,    -1,    -1,    -1,    -1,    -1,
      78,    -1,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,    -1,   368,    93,   223,    -1,    -1,    -1,
     227,    -1,   229,   377,   378,   232,    -1,   234,    -1,    -1,
      -1,    -1,   305,   227,    -1,   229,    -1,    -1,   232,    -1,
     234,    -1,    -1,   397,   305,    -1,    -1,    -1,   402,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   264,    -1,   332,
      -1,    -1,    -1,    -1,    -1,    -1,   420,    -1,    -1,    -1,
     264,   332,    -1,    -1,   428,    -1,   430,    -1,    -1,    -1,
      -1,    -1,   436,    -1,    -1,    -1,    -1,    -1,    -1,   362,
      -1,    -1,    -1,    -1,    -1,   368,    -1,    -1,   305,   177,
      -1,    -1,   363,    -1,   377,   378,    -1,   368,    -1,    -1,
     188,   305,    -1,    -1,    -1,    -1,   377,   378,    -1,    -1,
      -1,    -1,    -1,    -1,   397,   332,    -1,    -1,    -1,   402,
      -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,   332,    -1,
     218,   402,    -1,    -1,    -1,   223,    -1,   420,    -1,   227,
      -1,   229,    -1,    -1,   232,   428,   234,   430,    -1,   420,
      -1,   368,    -1,   436,    -1,    -1,    -1,   428,    -1,   430,
     377,   378,    -1,    -1,   368,   436,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   377,   378,    -1,   264,    -1,    -1,    -1,
     397,    -1,    -1,    -1,    -1,   402,    -1,    78,    -1,    -1,
      -1,    -1,    -1,   397,    -1,    -1,    -1,    -1,   402,    -1,
      -1,    -1,    93,   420,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   428,    -1,   430,    -1,    -1,   420,   305,    -1,   436,
      -1,    21,    -1,    -1,   428,    -1,   430,    -1,    -1,    -1,
      -1,    -1,   436,    33,    -1,    -1,    36,    37,    38,    39,
      40,    41,    42,    -1,   332,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    -1,    72,    73,    74,    75,    76,    77,    -1,    -1,
     368,    -1,    -1,    -1,    -1,    -1,   177,    -1,    -1,   377,
     378,    -1,    -1,    -1,    -1,    -1,    -1,   188,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   397,
      -1,    -1,   112,    -1,   402,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   420,    -1,    -1,    -1,   227,    -1,   229,    -1,
     428,   232,   430,   234,    -1,    -1,    -1,    -1,   436,    -1,
      -1,    -1,    -1,    30,    -1,    32,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    -1,
      -1,    -1,    -1,   264,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    70,   194,    72,    73,    74,    75,    76,
      77,    -1,    -1,    -1,    -1,    -1,    -1,   207,    -1,    -1,
     210,    -1,    -1,    -1,   305,    -1,   216,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   112,    -1,    -1,    -1,    78,
      -1,   332,    -1,    -1,   244,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    93,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   266,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   152,    -1,   368,    -1,    -1,
      -1,   281,    -1,    -1,    -1,    -1,   377,   378,   288,    -1,
     290,    -1,    -1,   170,    -1,    -1,   173,   174,    -1,    -1,
      -1,    -1,    -1,   303,    -1,    -1,   397,    -1,    -1,    -1,
     187,   402,    -1,   313,    -1,    -1,    -1,   194,    -1,    -1,
     320,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   420,
      -1,    -1,    -1,   210,    -1,    -1,    -1,   428,   177,   430,
      -1,    -1,    -1,    -1,    -1,   436,    -1,   224,    -1,   188,
      -1,    78,    -1,    -1,    -1,    -1,   233,   357,    -1,   359,
     360,   361,    -1,    -1,    -1,    -1,    93,   244,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   218,
      -1,    -1,    -1,   383,   223,    -1,    -1,    -1,   227,   266,
     229,    -1,    -1,   232,    -1,   234,    -1,    -1,    -1,    -1,
     400,    -1,    -1,   280,   281,    -1,    -1,    -1,   408,   409,
     410,   288,    -1,   290,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   421,    -1,    -1,   424,   264,   303,   304,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    36,    37,    38,    39,    40,
      41,    42,    -1,   443,    -1,    -1,    93,    -1,    -1,    -1,
     177,   328,    -1,    -1,    -1,    -1,   333,    -1,    -1,    -1,
      -1,   188,    63,    64,    -1,    -1,   305,    -1,    -1,    70,
     347,    72,    73,    74,    75,    76,    77,    -1,    -1,    -1,
     357,    -1,   359,   360,   361,    -1,    -1,    -1,    -1,    -1,
      -1,   218,    -1,   332,    -1,    -1,   223,    -1,    -1,    -1,
     227,    -1,   229,    -1,    -1,   232,    -1,   234,    -1,    -1,
      -1,   112,    -1,    -1,    -1,    -1,   393,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   404,    -1,   368,
     177,   408,   409,   410,    -1,    -1,    -1,   264,   377,   378,
      -1,   188,    -1,    -1,   421,    -1,   423,   424,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   397,    -1,
      -1,    -1,    -1,   402,    -1,    -1,   443,    -1,    -1,    -1,
      -1,   218,    -1,    -1,    -1,    -1,   223,    -1,   305,    -1,
     227,   420,   229,    -1,   185,   232,    -1,   234,    -1,   428,
      -1,   430,    -1,   194,    -1,    -1,    -1,   436,   437,   438,
      -1,    -1,    -1,    -1,    -1,   332,   445,   446,    -1,   210,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   264,    -1,    -1,
      -1,    -1,    -1,   224,   225,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   368,    -1,   244,    -1,    -1,    -1,    -1,   249,    -1,
     377,   378,    -1,    -1,    -1,    -1,    -1,    -1,   305,    -1,
      -1,    -1,    -1,    -1,    -1,   266,    -1,    -1,    -1,    -1,
     397,    -1,    -1,    -1,    -1,   402,    -1,    -1,    -1,    -1,
     281,    -1,    -1,    -1,    -1,   332,    -1,   288,    -1,   290,
      -1,    -1,   293,   420,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   428,   303,   430,    -1,    -1,    -1,    -1,    -1,   436,
     437,   438,    -1,    -1,    -1,    -1,    -1,    -1,   445,   446,
      -1,   368,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     377,   378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     397,    -1,    -1,    -1,    -1,   402,   357,    -1,   359,   360,
     361,    -1,    -1,    -1,    -1,   366,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   420,    -1,    -1,    -1,    -1,    -1,   380,
      -1,   428,    -1,   430,    -1,    -1,    -1,    -1,    -1,   436,
     437,   438,    -1,    -1,    -1,    -1,    -1,    -1,   445,    -1,
      -1,    -1,   403,    -1,    -1,    -1,    -1,   408,   409,   410,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     421,    -1,    -1,   424,   425,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   443
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int16 yystos[] =
{
       0,   452,   453,     0,   176,   301,   454,   455,   456,   462,
     469,   471,   443,   443,   455,   144,   477,   477,   227,   302,
     472,   472,   114,   457,   463,    26,   473,   473,   443,    96,
     572,   572,   227,   443,   470,    79,   478,   114,   458,   464,
     207,   474,  1115,   346,   163,   201,   209,   529,   443,   297,
     706,   706,   443,    69,   312,   396,   475,   476,   443,   443,
     346,   443,   162,   344,   395,   573,   579,   114,   459,   465,
     469,   129,   468,   476,   300,  1126,   479,   530,   443,   531,
     346,   432,   604,   575,    53,   423,   709,   133,   459,   466,
     477,   472,   265,   327,   367,   369,   480,   481,   485,   493,
     498,   533,   163,   532,   242,   340,   563,   564,   565,   566,
     568,   443,   346,   230,   649,   430,   578,   580,  1047,   711,
     710,   331,   717,   472,   460,   443,   443,   443,   443,   443,
     349,   534,   443,   209,   562,   395,  1111,   309,   364,   365,
     567,   443,   565,   574,   443,   346,   226,   651,   577,   579,
     606,   607,   608,   581,    48,   712,   713,   714,  1106,   712,
     430,   443,   443,   572,   236,   348,   430,   484,   486,   487,
     488,   489,   491,   492,  1126,   175,   494,   495,   496,   429,
     482,   483,   484,  1140,    11,    56,    91,    92,    94,   102,
     156,   228,   342,   382,   430,   499,   500,   501,   502,   506,
     515,   519,   522,   523,   524,   525,   526,   527,   528,   273,
    1093,   533,   443,   385,  1134,    23,  1102,   576,   605,   443,
     346,   322,   653,   580,   609,  1087,   582,   713,   362,   407,
     715,   315,   424,   707,   461,   362,  1115,   443,   487,   443,
     488,    60,   353,  1099,     9,   227,   497,   443,   496,   443,
     443,   483,   101,   430,  1058,  1058,   374,   357,  1130,  1115,
    1115,  1115,  1058,  1115,    55,  1108,  1115,   443,   501,  1058,
     563,    81,  1109,   169,  1112,   577,   606,   650,   443,   346,
     341,   694,   606,   443,  1087,   430,   610,   612,   617,    46,
      59,    96,   212,   222,   309,   310,   322,   324,   424,   443,
     583,   584,   586,   590,   592,   594,   595,   601,   602,   603,
    1115,  1115,   362,   273,   716,   103,   718,   706,  1115,   227,
    1076,   443,   353,  1115,   204,   204,   227,   443,   240,   507,
    1115,  1115,  1115,   430,  1055,  1073,    65,  1055,  1115,  1055,
     516,   517,  1058,    91,  1058,   535,   569,   570,  1047,  1046,
    1047,   606,   652,   443,   346,   610,   443,   165,   430,   613,
     614,  1109,  1115,   309,   311,  1097,  1097,  1115,  1109,  1115,
     240,  1120,  1115,    22,  1101,   267,   161,   181,    30,   104,
    1076,  1115,   430,   443,   708,   465,  1076,  1055,  1115,   188,
     227,   234,   305,   368,   397,   436,   520,   521,  1079,  1055,
     227,   193,   267,  1096,  1055,    22,   207,  1058,  1116,   503,
     536,   570,   291,   571,  1047,   606,   654,   443,   443,   611,
      80,  1076,   430,  1115,  1101,  1054,  1055,   269,   370,   591,
     227,  1055,  1057,  1076,   425,  1115,   430,   693,   693,   164,
     430,  1076,   719,   720,   133,   467,    55,   431,   490,   118,
     188,   227,   234,   246,   305,   368,   371,   372,   436,   508,
     509,   510,   513,   521,   390,  1073,   518,  1076,   504,     4,
      19,    28,   195,   224,   231,   276,   282,   309,   316,   329,
     356,   364,   395,   443,   537,   538,   542,   544,   545,   546,
     547,   548,   552,   553,   554,   555,   556,   558,   559,   560,
    1099,  1127,  1076,   307,   655,   656,   657,   695,   618,   615,
    1115,   393,   589,  1055,   225,  1119,   393,  1108,   193,  1114,
     430,  1115,  1115,   720,     1,   430,   443,   721,   722,   723,
     724,   725,   730,   731,   472,   510,    17,   390,  1079,  1076,
     268,   270,   505,  1120,   309,   393,  1138,   354,  1120,  1115,
      54,  1107,   107,   211,  1117,  1117,  1076,  1140,   374,  1115,
      36,  1105,   693,   657,   696,    21,    33,    36,    37,    38,
      39,    40,    41,    42,    70,    72,    73,    74,    75,    76,
      77,   112,   194,   210,   244,   266,   281,   288,   290,   303,
     313,   320,   357,   359,   360,   361,   383,   408,   409,   410,
     421,   424,   619,   620,   621,   623,   624,   625,   626,   627,
     628,   637,   638,   640,   641,   642,   647,   648,  1115,  1131,
      26,  1103,   181,  1076,    55,   311,   585,   596,  1076,   362,
    1132,   227,   593,  1073,   593,   120,   443,   443,   346,     3,
       5,    10,    18,    50,    51,    57,    68,    71,    83,   105,
     112,   113,   143,   155,   159,   172,   179,   182,   183,   190,
     197,   199,   202,   237,   241,   243,   250,   272,   287,   308,
     317,   330,   335,   337,   345,   355,   364,   373,   375,   376,
     379,   381,   386,   401,   406,   411,   422,   433,   443,   732,
     733,   743,   748,   752,   755,   768,   771,   776,   781,   782,
     783,   786,   794,   798,   800,   815,   818,   820,   822,   825,
     827,   833,   842,   844,   861,   863,   866,   870,   876,   886,
     893,   895,   898,   902,   903,   914,   925,   935,   941,   944,
     950,   954,   956,   958,   960,   963,   974,   975,   984,   986,
     987,   732,   443,   511,   513,   374,  1133,  1115,  1117,   117,
     161,   540,  1115,   309,   316,   553,  1115,  1115,  1115,  1115,
    1102,     9,   251,   308,   561,  1115,   430,   354,   658,   612,
     617,   697,   698,   699,   218,   358,   407,   358,   407,   358,
     407,   358,   407,   358,   407,   427,  1139,   336,  1128,  1076,
    1072,  1073,  1073,   207,   217,   336,   639,  1115,  1116,   161,
     181,   216,   400,     9,    49,   218,   616,  1077,  1078,  1079,
      29,   597,   598,   599,   600,  1104,  1140,  1108,   173,   588,
    1113,   103,   227,   726,   734,   744,   749,   753,   756,   769,
     772,   777,   784,   787,   795,   799,   801,   816,   819,   821,
    1138,   826,     1,   828,   834,   843,   845,   862,   864,   867,
     871,   877,   887,   894,   896,   899,   904,   915,   926,   936,
     227,   339,   945,   951,   296,   955,   957,   959,   961,   964,
     181,   976,  1112,   988,   188,   227,   234,   305,   368,   436,
     512,   514,  1115,   117,   306,   354,   543,  1115,   111,   295,
     539,    31,   158,   235,   549,  1057,   371,   557,  1055,  1055,
     277,  1125,  1125,   271,  1055,    58,    84,    85,   283,   443,
     659,   660,   664,  1115,   613,   699,   436,   393,   629,   445,
    1074,  1075,   390,   626,   644,   645,  1077,    26,   622,   352,
    1095,  1095,  1079,   267,  1122,  1122,   450,    47,   399,   168,
     589,  1076,   443,   443,   735,  1071,  1072,     6,    78,    89,
      93,   177,   218,   223,   229,   232,   264,   332,   377,   378,
     402,   420,   428,   745,  1041,  1061,  1062,  1071,  1077,  1080,
     430,   750,  1028,  1029,  1030,   227,  1051,  1052,  1053,  1073,
     227,  1069,  1071,  1080,   770,   773,   778,  1042,  1043,  1062,
    1047,   227,   788,  1061,  1068,  1071,   796,  1062,   227,   394,
     398,   802,   803,  1028,   286,   287,   300,   346,   817,     6,
    1059,  1060,  1071,  1071,   823,   130,  1027,  1028,  1059,   663,
    1071,   846,  1071,  1077,  1080,   927,  1073,    89,   865,  1062,
     868,  1062,   872,   171,   227,   878,   881,   882,   883,  1051,
    1069,  1073,  1140,  1047,  1044,  1073,  1047,  1044,     9,   905,
    1045,  1073,   144,   239,   916,   917,   918,   919,   921,   922,
     923,   924,  1048,  1049,  1059,   927,  1047,   942,   106,   946,
     947,  1062,    89,   952,  1061,   663,  1071,  1047,  1071,     8,
      34,   978,   101,  1044,    17,  1058,   557,   112,   227,   541,
    1073,   429,   550,   550,   366,   444,  1055,  1056,  1115,   166,
     661,   662,   661,  1116,   672,   181,   700,  1076,   392,  1137,
     218,   437,   438,   445,  1038,  1040,  1041,  1063,  1071,  1078,
    1080,   445,  1075,  1073,   643,   645,   390,   227,  1107,  1072,
    1072,  1079,  1057,  1057,  1104,  1108,   121,   742,    29,   173,
     736,  1104,  1122,   445,  1071,   445,  1081,   445,  1082,  1122,
    1096,   445,   445,   445,   445,   445,   445,   445,   445,  1081,
     122,   747,   393,   746,  1062,   198,  1090,    55,    12,    13,
      14,    20,   150,   151,   178,   184,   215,   219,   247,   248,
     252,   262,   269,   274,   292,   437,   438,   439,   440,   442,
     444,   445,   446,   447,   448,  1031,  1032,  1033,  1034,  1035,
    1062,   393,  1096,   423,   757,   227,  1068,  1071,  1047,   124,
     779,   150,   444,   780,  1043,   338,  1094,  1127,   126,   793,
     736,   416,   417,   418,   419,   127,   797,    48,   203,   757,
      17,   427,   804,   805,   806,   810,    95,  1122,  1060,  1050,
     389,  1136,   835,  1140,  1071,    88,   321,   384,   847,   848,
     849,   853,   858,   929,  1062,   393,   131,   869,    48,   160,
     200,   208,   278,   873,   882,   132,   879,   412,   425,   390,
     392,   387,   249,   294,  1091,   173,   989,  1127,   989,  1045,
     137,   913,   425,   907,  1066,  1071,  1078,   922,   924,  1059,
     393,  1049,   115,   393,   413,   920,   937,   180,   331,   943,
    1106,   203,   947,  1071,   140,   953,   173,   173,   309,   311,
     962,   106,   965,   323,   370,   979,   270,  1123,   989,   514,
     116,   429,  1089,  1098,   231,   337,  1115,  1054,  1068,   663,
     670,  1076,   612,   673,   701,   108,   630,  1122,  1040,  1040,
    1040,    67,   350,   446,  1039,   437,   438,   439,   440,   442,
     449,  1040,  1139,  1077,  1119,  1057,   108,   587,  1066,    24,
      25,    64,    66,    97,    98,    99,   144,   146,   154,   225,
     391,   430,  1049,   429,   739,    63,   224,   291,   737,   738,
     143,   300,  1064,  1072,  1038,  1040,   393,  1040,  1038,  1083,
    1072,  1078,  1080,   430,  1040,  1086,  1040,  1040,  1085,  1040,
    1038,  1038,  1040,  1084,  1040,  1042,  1062,   180,   331,   751,
    1090,  1138,   388,  1135,  1135,   207,  1032,   299,   754,  1053,
     758,   180,   331,   762,   314,   405,   774,   775,  1140,  1028,
     206,   256,  1020,  1021,  1022,  1024,   415,   789,   157,   995,
     996,   995,   995,   995,  1062,  1042,  1062,   803,    21,   394,
     398,   811,   812,  1029,   128,   814,   427,   806,   808,   427,
     807,  1072,   108,   824,  1051,   829,     9,    12,    15,    16,
     244,   245,   262,   263,   836,   840,   165,  1066,     9,    55,
     167,   216,   400,   854,   855,   856,   850,   848,   931,  1098,
    1123,   393,  1059,  1042,  1062,   356,   874,   727,   728,  1027,
     884,   885,  1071,  1051,     8,    34,   991,  1127,  1068,   203,
     888,   900,  1140,   908,  1104,  1071,   908,   393,   393,   505,
     143,   394,   398,  1062,    48,   211,   938,  1062,  1062,   362,
    1062,  1071,   173,  1042,  1062,  1066,  1106,   203,   968,  1071,
     153,   157,   980,     9,   985,  1051,   900,   116,   270,  1054,
     186,   665,   224,   225,   671,   430,   613,    30,    32,    35,
      43,    44,    45,    63,   152,   170,   173,   174,   187,   224,
     233,   266,   280,   304,   328,   333,   347,   393,   404,   423,
     443,   624,   625,   627,   637,   640,   642,   702,   705,  1123,
     631,   632,  1072,  1078,  1080,   446,  1040,  1040,  1040,  1040,
    1040,  1040,   446,  1040,   355,  1129,  1119,  1123,   994,   996,
     435,   434,  1066,   994,   211,    30,    32,    35,    45,   170,
     174,   187,   233,   280,   304,   328,   333,   343,   347,   404,
     414,   740,   741,   994,   260,  1121,  1121,  1121,   738,   737,
     227,  1065,  1072,   446,  1071,   449,   446,  1039,   446,   446,
    1039,   446,   446,   446,   446,  1039,   446,   446,   363,  1000,
    1001,  1042,  1060,   331,   393,  1051,   759,   760,   761,  1106,
    1071,  1071,   157,   279,   763,   981,  1112,   231,   251,  1000,
    1023,  1025,   125,   785,  1024,    91,   295,   430,  1049,   429,
     790,  1140,   997,   255,   998,   180,  1000,   180,    17,   390,
     813,   277,   811,   727,  1123,   727,  1138,   321,   837,  1138,
     393,    48,   855,   857,  1066,     9,    55,   216,   400,   851,
     852,  1066,   932,  1099,   193,   275,  1124,    27,   109,   633,
    1059,  1000,   180,  1140,  1046,   132,   880,   729,     8,   173,
     888,  1071,   120,   253,  1010,  1011,  1013,  1020,   231,   251,
     427,   120,   427,   910,   911,  1066,  1065,  1062,  1115,  1020,
     948,  1140,  1071,  1000,   180,   393,     9,   966,   967,  1088,
     969,  1071,   948,   969,   297,   983,   298,   990,   991,   242,
     309,   311,   551,  1115,   167,   666,  1076,   674,  1115,  1121,
     147,   149,  1115,  1069,  1121,  1076,  1071,  1071,  1055,   195,
     634,   633,   446,  1138,  1055,   998,   994,  1115,  1115,   115,
     413,   741,  1068,  1068,  1068,  1081,  1094,   446,  1040,  1055,
    1081,  1081,  1040,  1081,  1081,  1081,   216,   400,  1081,  1081,
    1002,   258,  1003,  1000,  1060,   760,   269,   715,    82,   315,
     424,   255,   257,   765,   982,   764,   319,   334,   727,   727,
      32,    35,    43,    44,    45,   152,   170,   187,   233,   280,
     333,   343,   404,   791,   792,   995,   259,   727,   999,  1042,
    1043,  1042,  1043,   812,  1028,   809,  1071,   119,   830,   424,
     838,   839,   840,   104,   841,   424,  1067,  1071,  1077,  1066,
      48,   859,   852,   169,   859,   928,  1115,   275,  1117,  1042,
     561,   875,  1140,   730,   885,  1062,   192,   889,  1140,  1012,
    1014,   135,   897,  1013,   136,   901,   231,  1028,   909,  1027,
     910,   252,   939,  1092,   138,   940,   279,  1005,  1006,   290,
    1094,  1042,  1067,   274,  1066,   107,   970,   384,   972,  1123,
     148,   254,   992,  1015,  1016,  1018,  1021,     7,  1100,   551,
    1076,   110,   213,   667,    64,    63,    64,   185,   224,   225,
     249,   293,   366,   380,   403,   425,   443,   624,   625,   627,
     628,   637,   640,   642,   675,   676,   678,   679,   680,   681,
     683,   684,   685,   686,   690,   691,   436,  1070,  1071,  1076,
    1115,  1070,  1115,  1137,  1106,  1117,   394,   646,  1070,  1070,
    1026,  1106,  1026,  1000,   446,   727,  1004,  1062,   123,   767,
     766,   727,  1115,   147,   149,  1115,   115,   413,   792,   727,
    1000,   318,  1000,   318,   727,   831,   130,   832,   839,    96,
    1110,   859,   859,  1067,   991,   200,   423,   933,  1055,   930,
    1000,   231,   251,    48,   231,   211,   890,   191,   231,   251,
     426,   727,   727,   906,   727,   912,  1062,   178,   184,   215,
     219,  1033,  1034,  1035,  1036,  1037,  1007,   139,   949,   257,
    1008,  1071,  1000,  1000,   967,  1114,    90,   971,  1114,  1005,
     160,   200,   208,   278,   977,  1046,  1017,  1019,   142,   993,
    1018,   283,  1049,  1070,  1115,    87,   214,   668,   261,  1121,
     196,   692,   260,   261,   689,  1101,   185,   427,  1115,  1122,
    1115,  1071,   681,   249,   289,   687,   688,  1076,   238,   289,
     437,   438,   704,   238,   289,   437,   438,   703,   430,   635,
     636,  1115,  1115,  1070,   727,   727,  1070,  1070,  1026,  1026,
    1043,  1043,   727,    48,   859,   396,   860,   297,  1046,   180,
     278,   934,  1073,   334,  1062,  1115,   891,  1010,  1021,   231,
     231,   727,   727,  1135,  1135,   727,  1009,  1071,  1114,  1071,
     141,   973,   727,   727,   224,   225,  1118,  1076,  1115,  1115,
     168,   669,  1115,  1116,  1115,  1027,  1071,   682,  1055,    86,
      87,   110,   284,   285,   325,   326,   677,   173,   283,  1076,
     688,  1070,  1070,   636,  1054,  1077,  1118,  1000,  1000,  1062,
    1062,  1115,  1046,   297,   412,  1071,   134,   892,   274,   274,
     727,  1071,  1076,  1076,  1115,  1076,  1076,  1094,  1062,   881,
    1115,  1027,   150,   150,  1076,    48,   881,  1138,  1138,  1062
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int16 yyr1[] =
{
       0,   451,   453,   452,   454,   454,   455,   455,   457,   458,
     456,   460,   461,   459,   463,   464,   462,   465,   465,   465,
     466,   466,   467,   468,   470,   469,   471,   472,   472,   473,
     473,   474,   474,   475,   475,   475,   476,   476,   477,   477,
     478,   478,   479,   479,   480,   480,   480,   480,   481,   482,
     482,   482,   482,   483,   484,   485,   486,   486,   486,   486,
     487,   487,   488,   488,   488,   489,   490,   490,   491,   492,
     493,   494,   494,   495,   495,   496,   496,   497,   497,   498,
     499,   499,   500,   500,   501,   501,   501,   501,   501,   501,
     501,   501,   501,   501,   501,   502,   503,   502,   504,   504,
     505,   505,   507,   506,   508,   508,   508,   508,   508,   509,
     509,   510,   510,   511,   510,   512,   512,   513,   513,   513,
     513,   513,   513,   514,   514,   514,   514,   514,   514,   515,
     516,   517,   517,   518,   518,   519,   520,   520,   521,   521,
     522,   523,   524,   525,   526,   527,   528,   529,   529,   530,
     529,   531,   529,   532,   532,   533,   533,   535,   534,   536,
     536,   537,   537,   537,   537,   537,   537,   537,   537,   537,
     537,   537,   537,   537,   538,   538,   539,   539,   539,   540,
     540,   540,   541,   541,   541,   542,   543,   543,   543,   544,
     545,   546,   547,   547,   547,   548,   549,   549,   549,   550,
     550,   550,   550,   551,   551,   552,   552,   553,   553,   553,
     553,   554,   555,   556,   557,   557,   557,   558,   559,   560,
     561,   561,   561,   562,   562,   563,   563,   564,   564,   565,
     565,   566,   567,   567,   567,   567,   568,   569,   569,   570,
     571,   571,   572,   572,   573,   574,   573,   575,   573,   576,
     576,   577,   578,   578,   579,   579,   581,   580,   582,   582,
     583,   583,   583,   583,   583,   583,   583,   583,   583,   583,
     583,   584,   585,   585,   585,   586,   586,   586,   587,   587,
     588,   588,   589,   589,   590,   591,   591,   592,   592,   593,
     593,   594,   595,   596,   596,   597,   597,   597,   598,   599,
     600,   601,   602,   603,   603,   604,   605,   604,   606,   606,
     608,   607,   609,   609,   609,   610,   611,   610,   612,   613,
     613,   613,   614,   615,   615,   616,   616,   616,   617,   618,
     618,   619,   619,   619,   619,   619,   619,   619,   619,   619,
     619,   619,   619,   619,   619,   620,   621,   622,   622,   623,
     624,   625,   625,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   626,   626,
     626,   626,   626,   626,   626,   626,   626,   626,   627,   627,
     628,   629,   629,   630,   630,   631,   632,   632,   633,   633,
     634,   634,   635,   635,   636,   637,   638,   639,   639,   639,
     640,   641,   643,   642,   644,   644,   645,   645,   646,   646,
     647,   647,   648,   649,   650,   649,   651,   652,   651,   653,
     654,   653,   655,   655,   656,   656,   657,   658,   658,   659,
     659,   659,   659,   660,   660,   661,   662,   662,   663,   663,
     664,   665,   665,   666,   666,   667,   667,   668,   668,   669,
     669,   670,   670,   670,   671,   671,   672,   672,   673,   674,
     674,   675,   675,   675,   675,   675,   675,   675,   675,   675,
     675,   675,   675,   675,   675,   675,   675,   676,   677,   677,
     677,   677,   677,   677,   677,   678,   679,   679,   679,   680,
     680,   681,   682,   683,   684,   685,   686,   686,   687,   687,
     688,   688,   688,   689,   689,   689,   690,   691,   692,   692,
     693,   694,   695,   696,   694,   697,   697,   698,   698,   699,
     700,   699,   701,   701,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   702,   702,   702,   702,   702,   702,
     702,   702,   702,   702,   703,   703,   703,   703,   703,   704,
     704,   704,   704,   704,   705,   706,   707,   708,   706,   709,
     710,   709,   711,   709,   712,   712,   713,   714,   714,   714,
     715,   715,   715,   715,   715,   716,   716,   717,   717,   718,
     719,   718,   720,   720,   721,   721,   721,   721,   721,   721,
     722,   723,   724,   725,   726,   726,   728,   729,   727,   731,
     730,   730,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   732,   732,   732,   732,   732,   732,   732,   732,   732,
     732,   734,   733,   735,   735,   735,   735,   735,   735,   735,
     735,   735,   735,   735,   735,   735,   735,   735,   735,   735,
     736,   736,   736,   736,   736,   736,   737,   738,   738,   739,
     739,   740,   740,   741,   741,   741,   741,   741,   741,   741,
     741,   741,   741,   741,   741,   741,   741,   741,   741,   741,
     742,   742,   744,   743,   745,   745,   745,   746,   746,   747,
     747,   749,   748,   750,   750,   751,   751,   752,   753,   753,
     754,   754,   756,   755,   757,   758,   757,   759,   759,   760,
     760,   761,   761,   761,   761,   762,   762,   762,   763,   764,
     763,   765,   766,   765,   767,   767,   769,   768,   770,   770,
     772,   771,   773,   773,   774,   774,   774,   774,   774,   775,
     775,   777,   776,   778,   779,   779,   780,   780,   781,   782,
     784,   783,   785,   785,   787,   786,   788,   788,   788,   788,
     788,   789,   789,   789,   789,   789,   790,   790,   790,   791,
     791,   792,   792,   792,   792,   792,   792,   792,   792,   792,
     792,   792,   792,   792,   792,   792,   793,   793,   795,   794,
     796,   796,   796,   796,   796,   797,   797,   799,   798,   801,
     800,   802,   802,   803,   803,   803,   804,   805,   805,   807,
     806,   808,   809,   808,   810,   810,   811,   811,   812,   812,
     812,   812,   813,   813,   814,   814,   816,   815,   817,   817,
     817,   817,   817,   817,   819,   818,   821,   820,   823,   822,
     824,   824,   826,   825,   828,   829,   827,   827,   830,   831,
     830,   832,   832,   834,   833,   835,   835,   836,   836,   836,
     837,   837,   838,   838,   839,   840,   840,   840,   840,   840,
     840,   840,   841,   841,   843,   842,   845,   844,   846,   846,
     846,   847,   847,   848,   848,   848,   850,   849,   851,   851,
     852,   852,   852,   852,   852,   852,   853,   854,   854,   855,
     855,   856,   856,   856,   856,   856,   857,   858,   859,   859,
     860,   860,   862,   861,   864,   863,   865,   865,   867,   866,
     868,   868,   869,   869,   871,   870,   872,   872,   873,   873,
     873,   873,   874,   874,   875,   875,   875,   877,   876,   878,
     879,   878,   878,   880,   880,   881,   881,   882,   882,   882,
     882,   882,   883,   883,   884,   884,   885,   887,   886,   888,
     888,   889,   889,   889,   889,   889,   889,   890,   890,   891,
     891,   891,   892,   892,   894,   893,   896,   895,   897,   897,
     899,   898,   900,   900,   900,   901,   901,   902,   904,   903,
     905,   906,   905,   907,   907,   908,   909,   908,   910,   910,
     912,   911,   913,   913,   915,   914,   916,   916,   916,   916,
     916,   917,   918,   918,   919,   920,   920,   921,   921,   922,
     923,   923,   924,   924,   926,   925,   928,   927,   929,   929,
     930,   930,   931,   931,   932,   932,   933,   933,   933,   934,
     934,   934,   936,   937,   935,   938,   938,   939,   939,   939,
     939,   939,   940,   940,   942,   941,   941,   943,   943,   943,
     945,   944,   946,   946,   947,   947,   947,   948,   948,   949,
     949,   951,   950,   952,   952,   952,   953,   953,   954,   955,
     955,   957,   956,   959,   958,   961,   960,   962,   962,   962,
     964,   963,   965,   965,   966,   966,   967,   968,   968,   969,
     970,   970,   971,   971,   972,   972,   973,   973,   974,   974,
     974,   975,   976,   976,   977,   977,   977,   977,   977,   978,
     978,   979,   979,   980,   980,   981,   981,   982,   982,   983,
     983,   984,   985,   985,   986,   988,   987,   989,   989,   990,
     990,   990,   990,   991,   991,   992,   992,   992,   993,   993,
     994,   995,   996,   997,   996,   998,   999,   998,  1000,  1001,
    1002,  1001,  1003,  1004,  1003,  1005,  1006,  1007,  1006,  1008,
    1009,  1008,  1010,  1010,  1010,  1012,  1011,  1014,  1013,  1015,
    1015,  1015,  1017,  1016,  1019,  1018,  1020,  1020,  1021,  1021,
    1021,  1023,  1022,  1025,  1024,  1026,  1026,  1027,  1028,  1030,
    1029,  1031,  1031,  1031,  1032,  1032,  1032,  1032,  1032,  1032,
    1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,
    1032,  1032,  1032,  1032,  1032,  1032,  1032,  1032,  1033,  1033,
    1033,  1034,  1034,  1035,  1035,  1036,  1036,  1037,  1037,  1038,
    1038,  1039,  1039,  1039,  1040,  1040,  1040,  1040,  1040,  1040,
    1040,  1040,  1040,  1041,  1041,  1042,  1042,  1043,  1044,  1045,
    1046,  1046,  1047,  1048,  1048,  1049,  1050,  1050,  1051,  1052,
    1052,  1052,  1053,  1054,  1054,  1055,  1056,  1056,  1057,  1057,
    1058,  1059,  1059,  1060,  1060,  1061,  1061,  1062,  1062,  1062,
    1062,  1062,  1062,  1062,  1062,  1062,  1063,  1063,  1063,  1063,
    1063,  1063,  1063,  1064,  1064,  1065,  1065,  1066,  1066,  1067,
    1067,  1068,  1068,  1069,  1069,  1069,  1070,  1070,  1070,  1071,
    1072,  1072,  1072,  1072,  1073,  1073,  1074,  1075,  1075,  1076,
    1077,  1077,  1078,  1078,  1079,  1079,  1079,  1079,  1079,  1079,
    1079,  1080,  1080,  1080,  1080,  1080,  1080,  1080,  1080,  1080,
    1080,  1080,  1080,  1081,  1081,  1081,  1082,  1082,  1083,  1083,
    1084,  1084,  1084,  1085,  1085,  1086,  1086,  1087,  1088,  1088,
    1089,  1089,  1090,  1090,  1091,  1091,  1091,  1092,  1092,  1093,
    1093,  1094,  1094,  1095,  1095,  1096,  1096,  1097,  1097,  1098,
    1098,  1099,  1099,  1100,  1100,  1101,  1101,  1102,  1102,  1103,
    1103,  1104,  1104,  1105,  1105,  1106,  1106,  1107,  1107,  1108,
    1108,  1109,  1109,  1110,  1110,  1111,  1111,  1112,  1112,  1113,
    1113,  1114,  1114,  1115,  1115,  1116,  1116,  1116,  1117,  1117,
    1118,  1118,  1118,  1119,  1119,  1120,  1120,  1121,  1121,  1122,
    1122,  1123,  1123,  1124,  1124,  1124,  1125,  1125,  1126,  1126,
    1127,  1127,  1128,  1128,  1129,  1129,  1130,  1130,  1131,  1131,
    1131,  1132,  1132,  1133,  1133,  1134,  1134,  1135,  1135,  1136,
    1136,  1137,  1137,  1138,  1138,  1139,  1139,  1140,  1140
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     2,     1,     1,     0,     0,
       8,     0,     0,     8,     0,     0,     7,     0,     1,     2,
       0,     3,     3,     3,     0,     7,     5,     1,     1,     0,
       2,     0,     3,     1,     2,     1,     1,     1,     0,     5,
       0,     4,     0,     2,     1,     1,     1,     1,     3,     0,
       2,     3,     2,     3,     1,     3,     0,     2,     3,     2,
       1,     2,     1,     1,     1,     5,     1,     1,     4,     3,
       3,     0,     2,     1,     2,     3,     3,     1,     2,     3,
       0,     2,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     5,     0,     5,
       1,     1,     0,     5,     1,     1,     1,     1,     1,     1,
       2,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     1,     2,     1,     2,     4,     1,     2,     1,     3,
       4,     4,     3,     3,     4,     3,     3,     0,     5,     0,
       4,     0,     4,     0,     3,     0,     2,     0,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     4,     0,     1,     1,     0,
       1,     1,     1,     1,     1,     4,     1,     1,     1,     6,
       3,     5,     0,     1,     1,     4,     2,     2,     1,     0,
       4,     5,     2,     1,     1,     3,     1,     1,     3,     1,
       2,     4,     4,     4,     1,     3,     4,     4,     3,     3,
       2,     2,     2,     0,     3,     0,     2,     1,     2,     1,
       1,     5,     0,     1,     1,     1,     5,     1,     2,     2,
       0,     2,     0,     9,     0,     0,     5,     0,     3,     0,
       2,     3,     2,     2,     1,     1,     0,     4,     0,     2,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     0,     1,     1,     4,     6,     9,     0,     3,
       0,     2,     0,     2,     3,     1,     1,     5,     5,     1,
       1,     3,     5,     0,     2,     1,     1,     1,     5,     4,
       3,     4,     3,     3,     3,     0,     0,     5,     0,     1,
       0,     2,     3,     4,     2,     1,     0,     4,     1,     0,
       1,     1,     1,     0,     2,     1,     3,     3,     6,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     0,     2,     2,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       1,     2,     2,     1,     2,     2,     1,     1,     3,     3,
       7,     0,     2,     0,     3,     1,     0,     5,     1,     1,
       0,     3,     1,     2,     1,     2,     2,     0,     1,     1,
       3,     1,     0,     8,     1,     2,     1,     3,     0,     3,
       2,     4,     2,     0,     0,     5,     0,     0,     5,     0,
       0,     5,     0,     1,     1,     2,     5,     0,     2,     2,
       3,     1,     1,     2,     2,     2,     0,     1,     1,     2,
       8,     0,     3,     0,     4,     0,     4,     0,     3,     0,
       3,     1,     4,     2,     1,     1,     0,     2,     4,     0,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     4,     4,     2,     1,     1,
       2,     3,     1,     3,     6,     2,     3,     2,     1,     2,
       2,     1,     2,     0,     1,     1,     4,     2,     0,     1,
       1,     0,     0,     0,     6,     0,     1,     1,     2,     1,
       0,     5,     0,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     0,     1,     1,     1,     1,     0,
       1,     1,     1,     1,     3,     0,     0,     0,     9,     0,
       0,     3,     0,     3,     1,     2,     4,     0,     2,     2,
       0,     3,     3,     4,     3,     0,     1,     0,     2,     0,
       0,     7,     0,     2,     1,     1,     1,     2,     2,     1,
       4,     2,     1,     1,     0,     1,     0,     0,     3,     0,
       2,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     4,     4,     3,     3,     3,     4,     3,
       4,     3,     3,     3,     4,     5,     3,     4,     3,     3,
       0,     3,     3,     2,     2,     2,     3,     3,     3,     0,
       2,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     1,     1,     1,     1,
       0,     1,     0,     4,     4,     5,     6,     0,     2,     0,
       1,     0,     3,     3,     5,     0,     2,     2,     0,     5,
       0,     2,     0,     8,     0,     0,     3,     1,     2,     2,
       3,     0,     2,     2,     2,     0,     2,     2,     0,     0,
       3,     0,     0,     3,     0,     1,     0,     3,     0,     2,
       0,     3,     0,     3,     0,     1,     3,     3,     2,     1,
       1,     0,     4,     4,     0,     1,     1,     1,     1,     1,
       0,     6,     0,     1,     0,     4,     3,     3,     3,     3,
       5,     0,     2,     2,     2,     2,     0,     2,     2,     1,
       2,     1,     1,     2,     2,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     1,     0,     1,     0,     4,
       4,     6,     6,     8,     8,     0,     1,     0,     4,     0,
       5,     1,     3,     1,     1,     1,     2,     1,     2,     0,
       3,     0,     0,     4,     2,     3,     1,     3,     2,     1,
       1,     1,     0,     2,     0,     1,     0,     3,     0,     1,
       1,     2,     1,     1,     0,     3,     0,     3,     0,     5,
       0,     3,     0,     2,     0,     0,     8,     3,     0,     0,
       3,     0,     1,     0,     7,     0,     2,     0,     3,     3,
       0,     2,     1,     2,     4,     1,     1,     1,     1,     1,
       1,     1,     0,     1,     0,     3,     0,     4,     1,     1,
       1,     1,     2,     1,     1,     1,     0,     3,     1,     2,
       2,     2,     1,     1,     1,     2,     2,     1,     2,     4,
       2,     0,     1,     1,     1,     1,     4,     5,     0,     4,
       0,     1,     0,     3,     0,     3,     3,     4,     0,     4,
       4,     6,     0,     1,     0,     3,     0,     5,     1,     1,
       1,     1,     0,     3,     0,     3,     2,     0,     3,     2,
       0,     4,     2,     0,     1,     1,     3,     0,     1,     2,
       3,     3,     0,     3,     1,     3,     7,     0,    10,     0,
       2,     0,     2,     2,     3,     3,     2,     0,     3,     0,
       1,     1,     0,     1,     0,     4,     0,     7,     0,     1,
       0,     7,     0,     2,     3,     0,     1,     1,     0,     4,
       4,     0,     7,     0,     2,     0,     0,     4,     1,     2,
       0,     4,     0,     1,     0,     3,     1,     1,     1,     1,
       1,     4,     4,     3,     4,     1,     1,     1,     2,     3,
       1,     2,     3,     3,     0,     3,     0,     7,     0,     5,
       0,     2,     0,     2,     0,     3,     0,     2,     4,     0,
       2,     4,     0,     0,     7,     0,     4,     2,     2,     2,
       2,     2,     0,     1,     0,     4,     2,     0,     2,     2,
       0,     8,     1,     2,     1,     3,     3,     0,     3,     0,
       1,     0,     4,     4,     6,     6,     0,     1,     2,     0,
       1,     0,     3,     0,     7,     0,     4,     0,     1,     1,
       0,     9,     0,     3,     1,     3,     2,     2,     2,     3,
       0,     3,     0,     3,     0,     3,     0,     1,     1,     1,
       1,     8,     0,     1,     1,     1,     1,     1,     1,     0,
       1,     0,     1,     1,     1,     1,     1,     1,     1,     0,
       1,     5,     1,     2,     5,     0,     8,     0,     2,     0,
       4,     3,     3,     1,     1,     0,     1,     1,     0,     1,
       2,     2,     0,     0,     3,     0,     0,     3,     2,     0,
       0,     3,     0,     0,     3,     2,     0,     0,     3,     0,
       0,     3,     1,     1,     2,     0,     3,     0,     3,     1,
       1,     2,     0,     3,     0,     3,     0,     1,     1,     1,
       2,     0,     3,     0,     3,     0,     3,     1,     1,     0,
       2,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     2,     1,     2,     1,     5,     1,     5,     1,
       3,     0,     1,     1,     1,     3,     3,     3,     3,     2,
       2,     3,     3,     1,     3,     1,     2,     2,     1,     1,
       1,     2,     1,     1,     2,     1,     0,     2,     1,     1,
       1,     3,     1,     1,     2,     1,     0,     1,     1,     1,
       1,     1,     2,     1,     3,     1,     2,     1,     3,     3,
       3,     4,     3,     1,     1,     1,     1,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     1,     3,     3,     4,     5,     1,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     5,     5,     5,     5,     5,     5,     5,
       4,     5,     2,     0,     4,     5,     0,     3,     0,     1,
       1,     3,     3,     1,     3,     1,     3,     0,     0,     1,
       0,     1,     0,     1,     0,     1,     1,     0,     1,     0,
       1,     0,     1,     0,     2,     1,     1,     2,     2,     2,
       1,     2,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     1,     0,     1,
       0,     1,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     2,     0,     1,     0,     1,
       0,     1,     0,     1,     0,     1,     0,     1,     0,     1,
       2,     0,     1,     0,     1,     0,     1,     0,     1,     0,
       1,     0,     1,     0,     1,     0,     1,     0,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= TOKEN_EOF)
    {
      yychar = TOKEN_EOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* $@1: %empty  */
#line 757 "parser.y"
  {
	perform_stack = NULL;
	current_statement = NULL;
	next_label_id = 0;
	current_linage = 0;
	current_storage = 0;
	eval_level = 0;
	eval_inc = 0;
	eval_inc2 = 0;
	prog_end = 0;
	depth = 0;
	inspect_keyword = 0;
	check_unreached = 0;
	samearea = 1;
	memset ((char *)eval_check, 0, sizeof(eval_check));
	memset ((char *)term_array, 0, sizeof(term_array));
	linage_file = NULL;
	next_label_list = NULL;
	current_program = cb_build_program (NULL, 0);
	cb_build_registers ();
	current_program->flag_main = cb_flag_main;
  }
#line 5139 "parser.c"
    break;

  case 3: /* start: $@1 nested_list  */
#line 781 "parser.y"
  {
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
	if (depth > 1) {
		cb_error (_("Multiple PROGRAM-ID's without matching END PROGRAM"));
	}
	if (errorcount > 0) {
		YYABORT;
	}
	if (!current_program->entry_list) {
		emit_entry (current_program->program_id, 0, NULL);
	}
  }
#line 5159 "parser.c"
    break;

  case 8: /* $@2: %empty  */
#line 810 "parser.y"
                        { cb_validate_program_environment (current_program); }
#line 5165 "parser.c"
    break;

  case 9: /* $@3: %empty  */
#line 811 "parser.y"
                        { cb_validate_program_data (current_program); }
#line 5171 "parser.c"
    break;

  case 11: /* $@4: %empty  */
#line 819 "parser.y"
                        { cb_validate_program_environment (current_program); }
#line 5177 "parser.c"
    break;

  case 12: /* $@5: %empty  */
#line 820 "parser.y"
                        { cb_validate_program_data (current_program); }
#line 5183 "parser.c"
    break;

  case 14: /* $@6: %empty  */
#line 828 "parser.y"
                        { cb_validate_program_environment (current_program); }
#line 5189 "parser.c"
    break;

  case 15: /* $@7: %empty  */
#line 829 "parser.y"
                        { cb_validate_program_data (current_program); }
#line 5195 "parser.c"
    break;

  case 21: /* end_program: "END PROGRAM" program_name '.'  */
#line 841 "parser.y"
  {
	char			*s;

	if (CB_LITERAL_P (yyvsp[-1])) {
		s = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		s = (char *)(CB_NAME (yyvsp[-1]));
	}
	if (depth) {
		depth--;
	}
	if (strcmp (stack_progid[depth], s)) {
		cb_error (_("END PROGRAM '%s' is different to PROGRAM-ID '%s'"),
			s, stack_progid[depth]);
	}
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
  }
#line 5220 "parser.c"
    break;

  case 22: /* end_mandatory: "END PROGRAM" program_name '.'  */
#line 865 "parser.y"
  {
	char			*s;

	if (CB_LITERAL_P (yyvsp[-1])) {
		s = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		s = (char *)(CB_NAME (yyvsp[-1]));
	}
	if (depth) {
		depth--;
	}
	if (strcmp (stack_progid[depth], s)) {
		cb_error (_("END PROGRAM '%s' is different to PROGRAM-ID '%s'"),
			s, stack_progid[depth]);
	}
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
  }
#line 5245 "parser.c"
    break;

  case 23: /* end_function: "END FUNCTION" program_name '.'  */
#line 889 "parser.y"
  {
	char			*s;

	if (CB_LITERAL_P (yyvsp[-1])) {
		s = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		s = (char *)(CB_NAME (yyvsp[-1]));
	}
	if (depth) {
		depth--;
	}
	if (strcmp (stack_progid[depth], s)) {
		cb_error (_("END FUNCTION '%s' is different to FUNCTION-ID '%s'"),
			s, stack_progid[depth]);
	}
	if (!current_program->flag_validated) {
		current_program->flag_validated = 1;
		cb_validate_program_body (current_program);
	}
  }
#line 5270 "parser.c"
    break;

  case 24: /* $@8: %empty  */
#line 918 "parser.y"
  {
	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P (yyvsp[-1])) {
		stack_progid[depth] = (char *)(CB_LITERAL (yyvsp[-1])->data);
	} else {
		stack_progid[depth] = (char *)(CB_NAME (yyvsp[-1]));
	}
	if (prog_end) {
		if (!current_program->flag_validated) {
			current_program->flag_validated = 1;
			cb_validate_program_body (current_program);
		}
		perform_stack = NULL;
		current_statement = NULL;
		next_label_id = 0;
		current_linage = 0;
		current_storage = 0;
		eval_level = 0;
		inspect_keyword = 0;
		check_unreached = 0;
		eval_inc = 0;
		eval_inc2 = 0;
		samearea = 1;
		memset ((char *)eval_check, 0, sizeof(eval_check));
		memset ((char *)term_array, 0, sizeof(term_array));
		linage_file = NULL;
		next_label_list = NULL;
		current_program = cb_build_program (current_program, depth);
		cb_build_registers ();
	} else {
		prog_end = 1;
	}
	depth++;
	current_program->program_id = cb_build_program_id (yyvsp[-1], yyvsp[0]);
  }
#line 5311 "parser.c"
    break;

  case 26: /* function_division: "FUNCTION-ID" '.' program_name as_literal '.'  */
#line 959 "parser.y"
  {
	cb_error (_("FUNCTION-ID is not yet implemented"));
	current_section = NULL;
	current_paragraph = NULL;
	if (CB_LITERAL_P (yyvsp[-2])) {
		stack_progid[depth] = (char *)(CB_LITERAL (yyvsp[-2])->data);
	} else {
		stack_progid[depth] = (char *)(CB_NAME (yyvsp[-2]));
	}
	if (prog_end) {
		if (!current_program->flag_validated) {
			current_program->flag_validated = 1;
			cb_validate_program_body (current_program);
		}
		perform_stack = NULL;
		current_statement = NULL;
		next_label_id = 0;
		current_linage = 0;
		current_storage = 0;
		eval_level = 0;
		inspect_keyword = 0;
		check_unreached = 0;
		eval_inc = 0;
		eval_inc2 = 0;
		samearea = 1;
		memset ((char *)eval_check, 0, sizeof(eval_check));
		memset ((char *)term_array, 0, sizeof(term_array));
		linage_file = NULL;
		next_label_list = NULL;
		current_program = cb_build_program (current_program, depth);
		cb_build_registers ();
	} else {
		prog_end = 1;
	}
	depth++;
	current_program->program_id = cb_build_program_id (yyvsp[-2], yyvsp[-1]);
	current_program->prog_type = CB_FUNCTION_TYPE;
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  }
#line 5356 "parser.c"
    break;

  case 29: /* as_literal: %empty  */
#line 1007 "parser.y"
                                { yyval = NULL; }
#line 5362 "parser.c"
    break;

  case 30: /* as_literal: AS "Literal"  */
#line 1008 "parser.y"
                                { yyval = yyvsp[0]; }
#line 5368 "parser.c"
    break;

  case 33: /* program_type_clause: COMMON  */
#line 1017 "parser.y"
  {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  }
#line 5379 "parser.c"
    break;

  case 34: /* program_type_clause: COMMON _init_or_recurs  */
#line 1024 "parser.y"
  {
	if (!current_program->nested_level) {
		cb_error (_("COMMON may only be used in a nested program"));
	}
	current_program->flag_common = 1;
  }
#line 5390 "parser.c"
    break;

  case 36: /* _init_or_recurs: "INITIAL"  */
#line 1035 "parser.y"
  {
	current_program->flag_initial = 1;
  }
#line 5398 "parser.c"
    break;

  case 37: /* _init_or_recurs: RECURSIVE  */
#line 1039 "parser.y"
  {
	current_program->flag_recursive = 1;
	current_program->flag_initial = 1;
  }
#line 5407 "parser.c"
    break;

  case 41: /* configuration_section: CONFIGURATION SECTION '.' configuration_list  */
#line 1064 "parser.y"
  {
	if (current_program->nested_level) {
		cb_error (_("CONFIGURATION SECTION not allowed in nested programs"));
	}
  }
#line 5417 "parser.c"
    break;

  case 53: /* with_debugging_mode: _with DEBUGGING MODE  */
#line 1099 "parser.y"
  {
	cb_verify (cb_debugging_line, "DEBUGGING MODE");
  }
#line 5425 "parser.c"
    break;

  case 54: /* computer_name: "Identifier"  */
#line 1105 "parser.y"
       { }
#line 5431 "parser.c"
    break;

  case 65: /* object_computer_memory: MEMORY SIZE _is integer object_char_or_word  */
#line 1136 "parser.y"
  {
	cb_verify (cb_memory_size_clause, "MEMORY SIZE");
  }
#line 5439 "parser.c"
    break;

  case 68: /* object_computer_sequence: _program coll_sequence _is reference  */
#line 1148 "parser.y"
  {
	current_program->collating_sequence = yyvsp[0];
  }
#line 5447 "parser.c"
    break;

  case 69: /* object_computer_segment: "SEGMENT-LIMIT" _is integer  */
#line 1155 "parser.y"
  {
	/* Ignore */
  }
#line 5455 "parser.c"
    break;

  case 75: /* repository_name: FUNCTION repository_literal_list INTRINSIC  */
#line 1180 "parser.y"
  {
	current_program->function_spec_list = yyvsp[-1];
  }
#line 5463 "parser.c"
    break;

  case 76: /* repository_name: FUNCTION ALL INTRINSIC  */
#line 1184 "parser.y"
  {
	functions_are_all = 1;
  }
#line 5471 "parser.c"
    break;

  case 77: /* repository_literal_list: "Literal"  */
#line 1190 "parser.y"
                        { yyval = cb_list_init (yyvsp[0]); }
#line 5477 "parser.c"
    break;

  case 78: /* repository_literal_list: repository_literal_list "Literal"  */
#line 1192 "parser.y"
                        { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 5483 "parser.c"
    break;

  case 95: /* mnemonic_name_clause: "Identifier" _is CRT  */
#line 1232 "parser.y"
  {
	save_tree_1 = lookup_system_name (CB_NAME (yyvsp[-2]));
	if (save_tree_1 == cb_error_node) {
		cb_error_x (yyvsp[-2], _("Unknown system-name '%s'"), CB_NAME (yyvsp[-2]));
	} else if (CB_SYSTEM_NAME(save_tree_1)->token != CB_DEVICE_CONSOLE) {
		cb_error_x (save_tree_1, _("Invalid CRT clause"));
	}
	/* current_program->flag_screen = 1; */
  }
#line 5497 "parser.c"
    break;

  case 96: /* $@9: %empty  */
#line 1242 "parser.y"
  {
	save_tree_1 = lookup_system_name (CB_NAME (yyvsp[-2]));
	if (save_tree_1 == cb_error_node) {
		cb_error_x (yyvsp[-2], _("Unknown system-name '%s'"), CB_NAME (yyvsp[-2]));
	} else {
		cb_define (yyvsp[0], save_tree_1);
	}
	save_tree_2 = yyvsp[0];
  }
#line 5511 "parser.c"
    break;

  case 99: /* special_name_mnemonic_on_off: special_name_mnemonic_on_off on_or_off _status _is undefined_word  */
#line 1257 "parser.y"
  {
	cb_define_switch_name (yyvsp[0], save_tree_1, yyvsp[-3], save_tree_2);
  }
#line 5519 "parser.c"
    break;

  case 100: /* on_or_off: ON  */
#line 1263 "parser.y"
                                { yyval = cb_int1; }
#line 5525 "parser.c"
    break;

  case 101: /* on_or_off: OFF  */
#line 1264 "parser.y"
                                { yyval = cb_int0; }
#line 5531 "parser.c"
    break;

  case 102: /* $@10: %empty  */
#line 1272 "parser.y"
  {
	save_tree_1 = yyvsp[0];
  }
#line 5539 "parser.c"
    break;

  case 103: /* alphabet_name_clause: ALPHABET undefined_word $@10 _is alphabet_definition  */
#line 1276 "parser.y"
  {
	current_program->alphabet_name_list =
		cb_list_add (current_program->alphabet_name_list, yyvsp[0]);
  }
#line 5548 "parser.c"
    break;

  case 104: /* alphabet_definition: NATIVE  */
#line 1283 "parser.y"
                { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_NATIVE); }
#line 5554 "parser.c"
    break;

  case 105: /* alphabet_definition: "STANDARD-1"  */
#line 1284 "parser.y"
                { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_1); }
#line 5560 "parser.c"
    break;

  case 106: /* alphabet_definition: "STANDARD-2"  */
#line 1285 "parser.y"
                { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_STANDARD_2); }
#line 5566 "parser.c"
    break;

  case 107: /* alphabet_definition: EBCDIC  */
#line 1286 "parser.y"
                { yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_EBCDIC); }
#line 5572 "parser.c"
    break;

  case 108: /* alphabet_definition: alphabet_literal_list  */
#line 1288 "parser.y"
  {
	yyval = cb_build_alphabet_name (save_tree_1, CB_ALPHABET_CUSTOM);
	CB_ALPHABET_NAME (yyval)->custom_list = yyvsp[0];
  }
#line 5581 "parser.c"
    break;

  case 109: /* alphabet_literal_list: alphabet_literal  */
#line 1295 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 5587 "parser.c"
    break;

  case 110: /* alphabet_literal_list: alphabet_literal_list alphabet_literal  */
#line 1297 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 5593 "parser.c"
    break;

  case 111: /* alphabet_literal: alphabet_lits  */
#line 1301 "parser.y"
                                        { yyval = yyvsp[0]; }
#line 5599 "parser.c"
    break;

  case 112: /* alphabet_literal: alphabet_lits THRU alphabet_lits  */
#line 1302 "parser.y"
                                        { yyval = cb_build_pair (yyvsp[-2], yyvsp[0]); }
#line 5605 "parser.c"
    break;

  case 113: /* @11: %empty  */
#line 1304 "parser.y"
  {
	yyval = cb_list_init (yyvsp[-1]);
	save_tree_2 = yyval;
  }
#line 5614 "parser.c"
    break;

  case 114: /* alphabet_literal: alphabet_lits ALSO @11 alphabet_also_sequence  */
#line 1309 "parser.y"
  {
	yyval = yyvsp[-1];
  }
#line 5622 "parser.c"
    break;

  case 117: /* alphabet_lits: "Literal"  */
#line 1320 "parser.y"
                                { yyval = yyvsp[0]; }
#line 5628 "parser.c"
    break;

  case 118: /* alphabet_lits: SPACE  */
#line 1321 "parser.y"
                                { yyval = cb_space; }
#line 5634 "parser.c"
    break;

  case 119: /* alphabet_lits: ZERO  */
#line 1322 "parser.y"
                                { yyval = cb_zero; }
#line 5640 "parser.c"
    break;

  case 120: /* alphabet_lits: QUOTE  */
#line 1323 "parser.y"
                                { yyval = cb_quote; }
#line 5646 "parser.c"
    break;

  case 121: /* alphabet_lits: "HIGH-VALUE"  */
#line 1324 "parser.y"
                                { yyval = cb_norm_high; }
#line 5652 "parser.c"
    break;

  case 122: /* alphabet_lits: "LOW-VALUE"  */
#line 1325 "parser.y"
                                { yyval = cb_norm_low; }
#line 5658 "parser.c"
    break;

  case 123: /* alphabet_also_literal: "Literal"  */
#line 1329 "parser.y"
                                { cb_list_add (save_tree_2, yyvsp[0]); }
#line 5664 "parser.c"
    break;

  case 124: /* alphabet_also_literal: SPACE  */
#line 1330 "parser.y"
                                { cb_list_add (save_tree_2, cb_space); }
#line 5670 "parser.c"
    break;

  case 125: /* alphabet_also_literal: ZERO  */
#line 1331 "parser.y"
                                { cb_list_add (save_tree_2, cb_zero); }
#line 5676 "parser.c"
    break;

  case 126: /* alphabet_also_literal: QUOTE  */
#line 1332 "parser.y"
                                { cb_list_add (save_tree_2, cb_quote); }
#line 5682 "parser.c"
    break;

  case 127: /* alphabet_also_literal: "HIGH-VALUE"  */
#line 1333 "parser.y"
                                { cb_list_add (save_tree_2, cb_norm_high); }
#line 5688 "parser.c"
    break;

  case 128: /* alphabet_also_literal: "LOW-VALUE"  */
#line 1334 "parser.y"
                                { cb_list_add (save_tree_2, cb_norm_low); }
#line 5694 "parser.c"
    break;

  case 129: /* symbolic_characters_clause: SYMBOLIC _characters symbolic_characters_list  */
#line 1342 "parser.y"
  {
	if (yyvsp[0]) {
		current_program->symbolic_list =
			cb_list_add (current_program->symbolic_list, yyvsp[0]);
	}
	PENDING ("SYMBOLIC CHARACTERS");
  }
#line 5706 "parser.c"
    break;

  case 130: /* symbolic_characters_list: char_list _is_are integer_list  */
#line 1353 "parser.y"
  {
	if (cb_list_length (yyvsp[-2]) != cb_list_length (yyvsp[0])) {
		cb_error (_("Invalid SYMBOLIC clause"));
		yyval = NULL;
	} else {
		yyval = NULL;
	}
  }
#line 5719 "parser.c"
    break;

  case 131: /* char_list: undefined_word  */
#line 1364 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 5725 "parser.c"
    break;

  case 132: /* char_list: char_list undefined_word  */
#line 1365 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 5731 "parser.c"
    break;

  case 133: /* integer_list: integer  */
#line 1369 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 5737 "parser.c"
    break;

  case 134: /* integer_list: integer_list integer  */
#line 1370 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 5743 "parser.c"
    break;

  case 135: /* class_name_clause: CLASS undefined_word _is class_item_list  */
#line 1378 "parser.y"
  {
	current_program->class_name_list =
			cb_list_add (current_program->class_name_list,
			cb_build_class_name (yyvsp[-2], yyvsp[0]));
  }
#line 5753 "parser.c"
    break;

  case 136: /* class_item_list: class_item  */
#line 1386 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 5759 "parser.c"
    break;

  case 137: /* class_item_list: class_item_list class_item  */
#line 1387 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 5765 "parser.c"
    break;

  case 138: /* class_item: basic_value  */
#line 1391 "parser.y"
                                { yyval = yyvsp[0]; }
#line 5771 "parser.c"
    break;

  case 139: /* class_item: basic_value THRU basic_value  */
#line 1393 "parser.y"
  {
	/* if (CB_LITERAL ($1)->data[0] < CB_LITERAL ($3)->data[0]) */
	if (literal_value (yyvsp[-2]) < literal_value (yyvsp[0])) {
		yyval = cb_build_pair (yyvsp[-2], yyvsp[0]);
	} else {
		yyval = cb_build_pair (yyvsp[0], yyvsp[-2]);
	}
  }
#line 5784 "parser.c"
    break;

  case 140: /* locale_clause: LOCALE undefined_word _is reference  */
#line 1407 "parser.y"
  {
	cb_tree	l;

	l = cb_build_locale_name (yyvsp[-2], yyvsp[0]);
	if (l != cb_error_node) {
		current_program->locale_list =
			cb_list_add (current_program->locale_list, l);
	}
  }
#line 5798 "parser.c"
    break;

  case 141: /* currency_sign_clause: CURRENCY _sign _is "Literal"  */
#line 1422 "parser.y"
  {
	unsigned char *s = CB_LITERAL (yyvsp[0])->data;

	if (CB_LITERAL (yyvsp[0])->size != 1) {
		cb_error_x (yyvsp[0], _("Invalid currency sign '%s'"), s);
	}
	switch (*s) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	case 'a':
	case 'A':
	case 'b':
	case 'B':
	case 'c':
	case 'C':
	case 'd':
	case 'D':
	case 'e':
	case 'E':
	case 'n':
	case 'N':
	case 'p':
	case 'P':
	case 'r':
	case 'R':
	case 's':
	case 'S':
	case 'v':
	case 'V':
	case 'x':
	case 'X':
	case 'z':
	case 'Z':
	case '+':
	case '-':
	case ',':
	case '.':
	case '*':
	case '/':
	case ';':
	case '(':
	case ')':
	case '=':
	case '"':
	case ' ':
		cb_error_x (yyvsp[0], _("Invalid currency sign '%s'"), s);
		break;
	default:
		break;
	}
	current_program->currency_symbol = s[0];
  }
#line 5863 "parser.c"
    break;

  case 142: /* decimal_point_clause: "DECIMAL-POINT" _is COMMA  */
#line 1489 "parser.y"
  {
	current_program->decimal_point = ',';
	current_program->numeric_separator = '.';
  }
#line 5872 "parser.c"
    break;

  case 143: /* cursor_clause: CURSOR _is reference  */
#line 1499 "parser.y"
                                { current_program->cursor_pos = yyvsp[0]; }
#line 5878 "parser.c"
    break;

  case 144: /* crt_status_clause: CRT STATUS _is reference  */
#line 1506 "parser.y"
                                { current_program->crt_status = yyvsp[0]; }
#line 5884 "parser.c"
    break;

  case 145: /* screen_control: "SCREEN-CONTROL" _is reference  */
#line 1513 "parser.y"
                                {  PENDING ("SCREEN CONTROL"); }
#line 5890 "parser.c"
    break;

  case 146: /* event_status: "EVENT-STATUS" _is reference  */
#line 1519 "parser.y"
                                {  PENDING ("EVENT STATUS"); }
#line 5896 "parser.c"
    break;

  case 149: /* $@12: %empty  */
#line 1531 "parser.y"
  {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  }
#line 5909 "parser.c"
    break;

  case 151: /* $@13: %empty  */
#line 1540 "parser.y"
  {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("INPUT-OUTPUT SECTION header missing - assumed"));
	} else {
		cb_error (_("INPUT-OUTPUT SECTION header missing"));
	}
  }
#line 5922 "parser.c"
    break;

  case 157: /* $@14: %empty  */
#line 1565 "parser.y"
  {
	organized_seen = 0;
	if (yyvsp[0] == cb_error_node) {
		YYERROR;
	}

	/* build new file */
	current_file = build_file (yyvsp[0]);
	current_file->optional = CB_INTEGER (yyvsp[-1])->val;

	/* register the file */
	current_program->file_list =
		cb_cons (CB_TREE (current_file), current_program->file_list);
  }
#line 5941 "parser.c"
    break;

  case 158: /* file_control_entry: SELECT flag_optional undefined_word $@14 select_clause_sequence '.'  */
#line 1580 "parser.y"
  {
	validate_file (current_file, yyvsp[-3]);
  }
#line 5949 "parser.c"
    break;

  case 174: /* assign_clause: ASSIGN _to _ext_clause _device assignment_name  */
#line 1610 "parser.y"
  {
	current_file->assign = cb_build_assignment_name (current_file, yyvsp[0]);
  }
#line 5957 "parser.c"
    break;

  case 175: /* assign_clause: ASSIGN _to _ext_clause DISK  */
#line 1614 "parser.y"
  {
	current_file->fileid_assign = 1;
  }
#line 5965 "parser.c"
    break;

  case 178: /* _device: PRINTER  */
#line 1621 "parser.y"
                { current_file->organization = COB_ORG_LINE_SEQUENTIAL; }
#line 5971 "parser.c"
    break;

  case 180: /* _ext_clause: EXTERNAL  */
#line 1626 "parser.y"
  {
	current_file->external_assign = 1;
  }
#line 5979 "parser.c"
    break;

  case 183: /* assignment_name: DISPLAY  */
#line 1635 "parser.y"
  {
	const char	*s;

	s = "$#@DUMMY@#$";
	yyval = cb_build_alphanumeric_literal ((unsigned char *)s, strlen (s));
  }
#line 5990 "parser.c"
    break;

  case 186: /* access_mode: SEQUENTIAL  */
#line 1652 "parser.y"
                        { current_file->access_mode = COB_ACCESS_SEQUENTIAL; }
#line 5996 "parser.c"
    break;

  case 187: /* access_mode: DYNAMIC  */
#line 1653 "parser.y"
                        { current_file->access_mode = COB_ACCESS_DYNAMIC; }
#line 6002 "parser.c"
    break;

  case 188: /* access_mode: RANDOM  */
#line 1654 "parser.y"
                        { current_file->access_mode = COB_ACCESS_RANDOM; }
#line 6008 "parser.c"
    break;

  case 189: /* alternative_record_key_clause: ALTERNATE RECORD _key _is opt_splitk flag_duplicates  */
#line 1662 "parser.y"
  {
	struct cb_alt_key *p;
	struct cb_alt_key *l;

	p = cobc_malloc (sizeof (struct cb_alt_key));
	p->key = yyvsp[-1];
	p->duplicates = CB_INTEGER (yyvsp[0])->val;
	p->next = NULL;

	/* add to the end of list */
	if (current_file->alt_key_list == NULL) {
		current_file->alt_key_list = p;
	} else {
		l = current_file->alt_key_list;
		for (; l->next; l = l->next);
		l->next = p;
	}
  }
#line 6031 "parser.c"
    break;

  case 190: /* collating_sequence_clause: coll_sequence _is "Identifier"  */
#line 1687 "parser.y"
  {
	PENDING ("COLLATING SEQUENCE");
  }
#line 6039 "parser.c"
    break;

  case 191: /* file_status_clause: file_or_sort STATUS _is reference opt_reference  */
#line 1697 "parser.y"
  {
	current_file->file_status = yyvsp[-1];
	if (yyvsp[0]) {
		PENDING ("2nd FILE STATUS");
	}
  }
#line 6050 "parser.c"
    break;

  case 196: /* lock_mode: MANUAL lock_with  */
#line 1718 "parser.y"
                        { current_file->lock_mode = COB_LOCK_MANUAL; }
#line 6056 "parser.c"
    break;

  case 197: /* lock_mode: AUTOMATIC lock_with  */
#line 1719 "parser.y"
                        { current_file->lock_mode = COB_LOCK_AUTOMATIC; }
#line 6062 "parser.c"
    break;

  case 198: /* lock_mode: EXCLUSIVE  */
#line 1720 "parser.y"
                        { current_file->lock_mode = COB_LOCK_EXCLUSIVE; }
#line 6068 "parser.c"
    break;

  case 201: /* lock_with: WITH LOCK ON MULTIPLE lock_records  */
#line 1726 "parser.y"
  {
	current_file->lock_mode |= COB_LOCK_MULTIPLE;
  }
#line 6076 "parser.c"
    break;

  case 202: /* lock_with: WITH ROLLBACK  */
#line 1729 "parser.y"
                                { PENDING ("WITH ROLLBACK"); }
#line 6082 "parser.c"
    break;

  case 207: /* organization: INDEXED  */
#line 1746 "parser.y"
  {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_INDEXED;
		organized_seen = 1;
	}
  }
#line 6095 "parser.c"
    break;

  case 208: /* organization: _record _binary SEQUENTIAL  */
#line 1755 "parser.y"
  {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_SEQUENTIAL;
		organized_seen = 1;
	}
  }
#line 6108 "parser.c"
    break;

  case 209: /* organization: RELATIVE  */
#line 1764 "parser.y"
  {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_RELATIVE;
		organized_seen = 1;
	}
  }
#line 6121 "parser.c"
    break;

  case 210: /* organization: LINE SEQUENTIAL  */
#line 1773 "parser.y"
  {
	if (organized_seen) {
		cb_error (_("Invalid or duplicate ORGANIZED clause"));
	} else {
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		organized_seen = 1;
	}
  }
#line 6134 "parser.c"
    break;

  case 211: /* padding_character_clause: PADDING _character _is reference_or_literal  */
#line 1788 "parser.y"
  {
	cb_verify (cb_padding_character_clause, "PADDING CHARACTER");
  }
#line 6142 "parser.c"
    break;

  case 212: /* record_delimiter_clause: RECORD DELIMITER _is "STANDARD-1"  */
#line 1797 "parser.y"
                                        { /* ignored */ }
#line 6148 "parser.c"
    break;

  case 213: /* record_key_clause: RECORD _key _is opt_splitk  */
#line 1805 "parser.y"
  {
	current_file->key = yyvsp[0];
  }
#line 6156 "parser.c"
    break;

  case 214: /* opt_splitk: reference  */
#line 1811 "parser.y"
                                        { yyval = yyvsp[0]; }
#line 6162 "parser.c"
    break;

  case 215: /* opt_splitk: reference '=' reference_list  */
#line 1812 "parser.y"
                                        { PENDING ("SPLIT KEYS"); }
#line 6168 "parser.c"
    break;

  case 216: /* opt_splitk: reference SOURCE _is reference_list  */
#line 1813 "parser.y"
                                        { PENDING ("SPLIT KEYS"); }
#line 6174 "parser.c"
    break;

  case 217: /* relative_key_clause: RELATIVE _key _is reference  */
#line 1819 "parser.y"
                                { current_file->key = yyvsp[0]; }
#line 6180 "parser.c"
    break;

  case 218: /* reserve_clause: RESERVE integer _area  */
#line 1826 "parser.y"
                                { /* ignored */ }
#line 6186 "parser.c"
    break;

  case 219: /* sharing_clause: SHARING _with sharing_option  */
#line 1833 "parser.y"
                                { current_file->sharing = yyvsp[0]; }
#line 6192 "parser.c"
    break;

  case 220: /* sharing_option: ALL _other  */
#line 1837 "parser.y"
                                { yyval = NULL; PENDING ("SHARING ALL OTHER"); }
#line 6198 "parser.c"
    break;

  case 221: /* sharing_option: NO _other  */
#line 1838 "parser.y"
                                { yyval = cb_int1; }
#line 6204 "parser.c"
    break;

  case 222: /* sharing_option: READ ONLY  */
#line 1839 "parser.y"
                                { yyval = cb_int0; }
#line 6210 "parser.c"
    break;

  case 231: /* same_clause: SAME same_option _area _for file_name_list  */
#line 1869 "parser.y"
  {
	cb_tree l;

	switch (CB_INTEGER (yyvsp[-3])->val) {
	case 0:
		/* SAME AREA */
		break;
	case 1:
		/* SAME RECORD */
		for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
			if (CB_VALUE (l) != cb_error_node) {
				CB_FILE (cb_ref (CB_VALUE (l)))->same_clause = samearea;
			}
		}
		samearea++;
		break;
	case 2:
		/* SAME SORT-MERGE */
		break;
	}
  }
#line 6236 "parser.c"
    break;

  case 232: /* same_option: %empty  */
#line 1893 "parser.y"
                                { yyval = cb_int0; }
#line 6242 "parser.c"
    break;

  case 233: /* same_option: RECORD  */
#line 1894 "parser.y"
                                { yyval = cb_int1; }
#line 6248 "parser.c"
    break;

  case 234: /* same_option: SORT  */
#line 1895 "parser.y"
                                { yyval = cb_int2; }
#line 6254 "parser.c"
    break;

  case 235: /* same_option: "SORT-MERGE"  */
#line 1896 "parser.y"
                                { yyval = cb_int2; }
#line 6260 "parser.c"
    break;

  case 236: /* multiple_file_tape_clause: MULTIPLE _file _tape _contains multiple_file_list  */
#line 1903 "parser.y"
  {
	cb_verify (cb_multiple_file_tape_clause, "MULTIPLE FILE TAPE");
  }
#line 6268 "parser.c"
    break;

  case 239: /* multiple_file: file_name multiple_file_position  */
#line 1914 "parser.y"
                                   { }
#line 6274 "parser.c"
    break;

  case 245: /* $@15: %empty  */
#line 1942 "parser.y"
                                { current_storage = CB_STORAGE_FILE; }
#line 6280 "parser.c"
    break;

  case 247: /* $@16: %empty  */
#line 1945 "parser.y"
  {
	/* hack for MF compatibility */
	if (cb_relaxed_syntax_check) {
		cb_warning (_("FILE SECTION header missing - assumed"));
	} else {
		cb_error (_("FILE SECTION header missing"));
	}
	current_storage = CB_STORAGE_FILE;
  }
#line 6294 "parser.c"
    break;

  case 251: /* file_description: file_type file_description_entry record_description_list  */
#line 1964 "parser.y"
  {
	if (yyvsp[0] && yyvsp[0] != cb_error_node) {
		finalize_file (current_file, CB_FIELD (yyvsp[0]));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  }
#line 6306 "parser.c"
    break;

  case 252: /* file_description_sequence_without_type: file_description_entry record_description_list  */
#line 1976 "parser.y"
  {
	if (yyvsp[0] && yyvsp[0] != cb_error_node) {
		finalize_file (current_file, CB_FIELD (yyvsp[0]));
	} else {
		cb_error (_("RECORD description missing or invalid"));
	}
  }
#line 6318 "parser.c"
    break;

  case 254: /* file_type: FD  */
#line 1987 "parser.y"
                               { yyval = cb_int0; }
#line 6324 "parser.c"
    break;

  case 255: /* file_type: SD  */
#line 1988 "parser.y"
                               { yyval = cb_int1; }
#line 6330 "parser.c"
    break;

  case 256: /* @17: %empty  */
#line 1998 "parser.y"
  {
	if (yyvsp[0] == cb_error_node) {
		YYERROR;
	}

	current_file = CB_FILE (cb_ref (yyvsp[0]));
	if (yyvsp[-1] == cb_int1) {
		current_file->organization = COB_ORG_SORT;
	}
  }
#line 6345 "parser.c"
    break;

  case 257: /* file_description_entry: file_name @17 file_description_clause_sequence '.'  */
#line 2009 "parser.y"
  {
	/* Shut up bison */
	dummy_tree = yyvsp[-2];
  }
#line 6354 "parser.c"
    break;

  case 260: /* file_description_clause: _is EXTERNAL  */
#line 2021 "parser.y"
  {
	if (current_file->global) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->external = 1;
  }
#line 6365 "parser.c"
    break;

  case 261: /* file_description_clause: _is GLOBAL  */
#line 2028 "parser.y"
  {
	if (current_file->external) {
		cb_error (_("File cannot have both EXTERNAL and GLOBAL clauses"));
	}
	current_file->global = 1;
  }
#line 6376 "parser.c"
    break;

  case 271: /* block_contains_clause: BLOCK _contains integer opt_to_integer _records_or_characters  */
#line 2050 "parser.y"
  { /* ignored */ }
#line 6382 "parser.c"
    break;

  case 275: /* record_clause: RECORD _contains integer _characters  */
#line 2060 "parser.y"
  {
	if (current_file->organization == COB_ORG_LINE_SEQUENTIAL) {
		cb_warning (_("RECORD clause ignored for LINE SEQUENTIAL"));
	} else {
		current_file->record_max = cb_get_int (yyvsp[-1]);
		if (current_file->record_max < 1)  {
			current_file->record_max = 1;
			cb_error (_("RECORD clause invalid"));
		}
	}
  }
#line 6398 "parser.c"
    break;

  case 276: /* record_clause: RECORD _contains integer TO integer _characters  */
#line 2072 "parser.y"
  {
	int	error_ind = 0;

	if (current_file->organization == COB_ORG_LINE_SEQUENTIAL) {
		cb_warning (_("RECORD clause ignored for LINE SEQUENTIAL"));
	} else {
		current_file->record_min = cb_get_int (yyvsp[-3]);
		current_file->record_max = cb_get_int (yyvsp[-1]);
		if (current_file->record_min < 0)  {
			current_file->record_min = 0;
			error_ind = 1;
		}
		if (current_file->record_max < 1)  {
			current_file->record_max = 1;
			error_ind = 1;
		}
		if (current_file->record_max <= current_file->record_min)  {
			error_ind = 1;
		}
		if (error_ind) {
			cb_error (_("RECORD clause invalid"));
		}
	}
  }
#line 6427 "parser.c"
    break;

  case 277: /* record_clause: RECORD _is VARYING _in _size opt_from_integer opt_to_integer _characters record_depending  */
#line 2098 "parser.y"
  {
	int	error_ind = 0;

	current_file->record_min = yyvsp[-3] ? cb_get_int (yyvsp[-3]) : 0;
	current_file->record_max = yyvsp[-2] ? cb_get_int (yyvsp[-2]) : 0;
	if (yyvsp[-3] && current_file->record_min < 0)  {
		current_file->record_min = 0;
		error_ind = 1;
	}
	if (yyvsp[-2] && current_file->record_max < 1)  {
		current_file->record_max = 1;
		error_ind = 1;
	}
	if ((yyvsp[-3] || yyvsp[-2]) && current_file->record_max <= current_file->record_min)  {
		error_ind = 1;
	}
	if (error_ind) {
		cb_error (_("RECORD clause invalid"));
	}
  }
#line 6452 "parser.c"
    break;

  case 279: /* record_depending: DEPENDING _on reference  */
#line 2122 "parser.y"
  {
	current_file->record_depending = yyvsp[0];
  }
#line 6460 "parser.c"
    break;

  case 280: /* opt_from_integer: %empty  */
#line 2128 "parser.y"
                                { yyval = NULL; }
#line 6466 "parser.c"
    break;

  case 281: /* opt_from_integer: _from integer  */
#line 2129 "parser.y"
                                { yyval = yyvsp[0]; }
#line 6472 "parser.c"
    break;

  case 282: /* opt_to_integer: %empty  */
#line 2133 "parser.y"
                                { yyval = NULL; }
#line 6478 "parser.c"
    break;

  case 283: /* opt_to_integer: TO integer  */
#line 2134 "parser.y"
                                { yyval = yyvsp[0]; }
#line 6484 "parser.c"
    break;

  case 284: /* label_records_clause: LABEL records label_option  */
#line 2142 "parser.y"
  {
	cb_verify (cb_label_records_clause, "LABEL RECORDS");
  }
#line 6492 "parser.c"
    break;

  case 287: /* value_of_clause: VALUE OF "Identifier" _is valueof_name  */
#line 2157 "parser.y"
  {
	cb_verify (cb_value_of_clause, "VALUE OF");
  }
#line 6500 "parser.c"
    break;

  case 288: /* value_of_clause: VALUE OF "FILE-ID" _is valueof_name  */
#line 2161 "parser.y"
  {
	if (!current_file->assign) {
		current_file->assign = cb_build_assignment_name (current_file, yyvsp[0]);
	}
  }
#line 6510 "parser.c"
    break;

  case 291: /* data_records_clause: DATA records reference_list  */
#line 2177 "parser.y"
  {
	cb_verify (cb_data_records_clause, "DATA RECORDS");
  }
#line 6518 "parser.c"
    break;

  case 292: /* linage_clause: LINAGE _is reference_or_literal _lines linage_sequence  */
#line 2188 "parser.y"
  {
	if (current_file->organization != COB_ORG_LINE_SEQUENTIAL
	    && current_file->organization != COB_ORG_SEQUENTIAL) {
		cb_error (_("LINAGE clause with wrong file type"));
		yyval = cb_error_node;
	} else {
		current_file->linage = yyvsp[-2];
		current_file->organization = COB_ORG_LINE_SEQUENTIAL;
		if (current_linage == 0) {
			linage_file = current_file;
		}
		current_linage++;
	}
  }
#line 6537 "parser.c"
    break;

  case 298: /* linage_footing: _with FOOTING _at reference_or_literal _lines  */
#line 2216 "parser.y"
  {
	current_file->latfoot = yyvsp[-1];
  }
#line 6545 "parser.c"
    break;

  case 299: /* linage_top: _at TOP reference_or_literal _lines  */
#line 2223 "parser.y"
  {
	current_file->lattop = yyvsp[-1];
  }
#line 6553 "parser.c"
    break;

  case 300: /* linage_bottom: _at BOTTOM reference_or_literal  */
#line 2230 "parser.y"
  {
	current_file->latbot = yyvsp[0];
  }
#line 6561 "parser.c"
    break;

  case 301: /* recording_mode_clause: RECORDING _mode _is "Identifier"  */
#line 2239 "parser.y"
                                { /* ignore */ }
#line 6567 "parser.c"
    break;

  case 302: /* code_set_clause: "CODE-SET" _is "Identifier"  */
#line 2247 "parser.y"
  {
	if (yyvsp[0] != cb_error_node) {
		cb_tree x;

		x = cb_ref (yyvsp[0]);
		if (!CB_ALPHABET_NAME_P (x)) {
			cb_error_x (yyvsp[0], _("Alphabet-name is expected '%s'"), cb_name (yyvsp[0]));
		} else if (CB_ALPHABET_NAME (x)->custom_list) {
			PENDING ("CODE-SET");
		}
	}
  }
#line 6584 "parser.c"
    break;

  case 303: /* report_clause: REPORT _is report_name  */
#line 2265 "parser.y"
  {
	cb_warning (_("file descriptor REPORT IS"));
  }
#line 6592 "parser.c"
    break;

  case 304: /* report_clause: REPORTS _are report_name  */
#line 2269 "parser.y"
  {
	cb_warning (_("file descriptor REPORTS ARE"));
  }
#line 6600 "parser.c"
    break;

  case 306: /* $@18: %empty  */
#line 2280 "parser.y"
                                { current_storage = CB_STORAGE_WORKING; }
#line 6606 "parser.c"
    break;

  case 307: /* working_storage_section: "WORKING-STORAGE" SECTION '.' $@18 record_description_list  */
#line 2282 "parser.y"
  {
	if (yyvsp[0]) {
		current_program->working_storage =
			cb_field_add (current_program->working_storage, CB_FIELD (yyvsp[0]));
	}
  }
#line 6617 "parser.c"
    break;

  case 308: /* record_description_list: %empty  */
#line 2291 "parser.y"
                                { yyval = NULL; }
#line 6623 "parser.c"
    break;

  case 309: /* record_description_list: record_description_list_1  */
#line 2292 "parser.y"
                                { yyval = yyvsp[0]; }
#line 6629 "parser.c"
    break;

  case 310: /* $@19: %empty  */
#line 2296 "parser.y"
  {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  }
#line 6639 "parser.c"
    break;

  case 311: /* record_description_list_1: $@19 record_description_list_2  */
#line 2302 "parser.y"
  {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	yyval = CB_TREE (description_field);
  }
#line 6652 "parser.c"
    break;

  case 316: /* $@20: %empty  */
#line 2322 "parser.y"
  {
	cb_tree x;

	x = cb_build_field_tree (yyvsp[-1], yyvsp[0], current_field, current_storage, current_file);
	if (x == cb_error_node) {
		YYERROR;
	} else {
		current_field = CB_FIELD (x);
	}
  }
#line 6667 "parser.c"
    break;

  case 317: /* data_description: level_number entry_name $@20 data_description_clause_sequence  */
#line 2333 "parser.y"
  {
	if (!qualifier && (current_field->level == 88 ||
	    current_field->level == 77 || current_field->level == 66 ||
	    current_field->flag_item_78)) {
		cb_error (_("Item requires a data name"));
	}
	if (current_field->level == 88) {
		cb_validate_88_item (current_field);
	}
	if (current_field->flag_item_78) {
		/* Reset to last non-78 item */
		current_field = cb_validate_78_item (current_field);
	}
	if (!description_field) {
		description_field = current_field;
	}
  }
#line 6689 "parser.c"
    break;

  case 319: /* entry_name: %empty  */
#line 2358 "parser.y"
  {
	yyval = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  }
#line 6699 "parser.c"
    break;

  case 320: /* entry_name: FILLER  */
#line 2364 "parser.y"
  {
	yyval = cb_build_filler ();
	qualifier = NULL;
	non_const_word = 0;
  }
#line 6709 "parser.c"
    break;

  case 321: /* entry_name: "Identifier"  */
#line 2370 "parser.y"
  {
	yyval = yyvsp[0];
	qualifier = yyvsp[0];
	non_const_word = 0;
  }
#line 6719 "parser.c"
    break;

  case 322: /* const_name: "Identifier"  */
#line 2379 "parser.y"
  {
	yyval = yyvsp[0];
	qualifier = yyvsp[0];
	non_const_word = 0;
  }
#line 6729 "parser.c"
    break;

  case 324: /* const_global: _is GLOBAL  */
#line 2388 "parser.y"
  {
	current_field->flag_is_global = 1;
	cb_error (_("CONSTANT with GLOBAL clause is not yet supported"));
  }
#line 6738 "parser.c"
    break;

  case 325: /* lit_or_length: literal  */
#line 2395 "parser.y"
                                { yyval = yyvsp[0]; }
#line 6744 "parser.c"
    break;

  case 326: /* lit_or_length: LENGTH _of identifier_1  */
#line 2396 "parser.y"
                                { yyval = cb_build_const_length (yyvsp[0]); }
#line 6750 "parser.c"
    break;

  case 327: /* lit_or_length: "BYTE-LENGTH" _of identifier_1  */
#line 2397 "parser.y"
                                { yyval = cb_build_const_length (yyvsp[0]); }
#line 6756 "parser.c"
    break;

  case 328: /* constant_entry: level_number const_name CONSTANT const_global _as lit_or_length  */
#line 2402 "parser.y"
  {
	cb_tree x;
	int	level;

	level = cb_get_level (yyvsp[-5]);
	if (level && level != 1) {
		cb_error (_("CONSTANT item not at 01 level"));
	}
	x = cb_build_constant (yyvsp[-4], yyvsp[0]);
	CB_FIELD (x)->flag_item_78 = 1;
	CB_FIELD (x)->level = 1;
	cb_needs_01 = 1;
	/* Ignore return value */
	cb_validate_78_item (CB_FIELD (x));
  }
#line 6776 "parser.c"
    break;

  case 329: /* data_description_clause_sequence: %empty  */
#line 2421 "parser.y"
  {
	/* required to check redefines */
	yyval = NULL;
  }
#line 6785 "parser.c"
    break;

  case 330: /* data_description_clause_sequence: data_description_clause_sequence data_description_clause  */
#line 2427 "parser.y"
  {
	/* required to check redefines */
	yyval = cb_true;
  }
#line 6794 "parser.c"
    break;

  case 345: /* redefines_clause: REDEFINES identifier_1  */
#line 2455 "parser.y"
  {
	if (yyvsp[-2] != NULL) {
		/* hack for MF compatibility */
		if (cb_relaxed_syntax_check) {
			cb_warning_x (yyvsp[0], _("REDEFINES clause should follow entry-name"));
		} else {
			cb_error_x (yyvsp[0], _("REDEFINES clause must follow entry-name"));
		}
	}

	current_field->redefines = cb_resolve_redefines (current_field, yyvsp[0]);
	if (current_field->redefines == NULL) {
		YYERROR;
	}
  }
#line 6814 "parser.c"
    break;

  case 346: /* external_clause: _is EXTERNAL as_extname  */
#line 2477 "parser.y"
  {
	if (current_storage != CB_STORAGE_WORKING) {
		cb_error (_("EXTERNAL not allowed here"));
	} else if (current_field->level != 1 && current_field->level != 77) {
		cb_error (_("EXTERNAL only allowed at 01/77 level"));
	} else if (!qualifier) {
		cb_error (_("EXTERNAL requires a data name"));
	} else if (current_field->flag_is_global) {
		cb_error (_("GLOBAL and EXTERNAL are mutually exclusive"));
	} else if (current_field->flag_item_based) {
		cb_error (_("BASED and EXTERNAL are mutually exclusive"));
	} else if (current_field->redefines) {
		cb_error (_("EXTERNAL and REDEFINES are mutually exclusive"));
	} else {
		current_field->flag_external = 1;
		has_external = 1;
	}
  }
#line 6837 "parser.c"
    break;

  case 347: /* as_extname: %empty  */
#line 2498 "parser.y"
                                { current_field->ename = NULL; }
#line 6843 "parser.c"
    break;

  case 348: /* as_extname: AS "Literal"  */
#line 2500 "parser.y"
 {
	struct cb_field *x;

	x = CB_FIELD(cb_build_field (cb_build_reference ((char *)(CB_LITERAL (yyvsp[0])->data))));
	current_field->ename = x->name;
 }
#line 6854 "parser.c"
    break;

  case 349: /* global_clause: _is GLOBAL  */
#line 2512 "parser.y"
  {
	if (current_field->level != 1 && current_field->level != 77) {
		cb_error (_("GLOBAL only allowed at 01/77 level"));
	} else if (!qualifier) {
		cb_error (_("GLOBAL requires a data name"));
	} else if (current_field->flag_external) {
		cb_error (_("GLOBAL and EXTERNAL are mutually exclusive"));
	} else if (current_storage == CB_STORAGE_LOCAL) {
		cb_error (_("GLOBAL not allowed here"));
	} else {
		current_field->flag_is_global = 1;
	}
  }
#line 6872 "parser.c"
    break;

  case 350: /* picture_clause: PICTURE  */
#line 2531 "parser.y"
                                { current_field->pic = CB_PICTURE (yyvsp[0]); }
#line 6878 "parser.c"
    break;

  case 353: /* usage: BINARY  */
#line 2543 "parser.y"
                                { current_field->usage = CB_USAGE_BINARY; }
#line 6884 "parser.c"
    break;

  case 354: /* usage: COMP  */
#line 2544 "parser.y"
                                { current_field->usage = CB_USAGE_BINARY; }
#line 6890 "parser.c"
    break;

  case 355: /* usage: "COMP-1"  */
#line 2545 "parser.y"
                                { current_field->usage = CB_USAGE_FLOAT; }
#line 6896 "parser.c"
    break;

  case 356: /* usage: "COMP-2"  */
#line 2546 "parser.y"
                                { current_field->usage = CB_USAGE_DOUBLE; }
#line 6902 "parser.c"
    break;

  case 357: /* usage: "COMP-3"  */
#line 2547 "parser.y"
                                { current_field->usage = CB_USAGE_PACKED; }
#line 6908 "parser.c"
    break;

  case 358: /* usage: "COMP-4"  */
#line 2548 "parser.y"
                                { current_field->usage = CB_USAGE_BINARY; }
#line 6914 "parser.c"
    break;

  case 359: /* usage: "COMP-5"  */
#line 2549 "parser.y"
                                { current_field->usage = CB_USAGE_COMP_5; }
#line 6920 "parser.c"
    break;

  case 360: /* usage: "COMP-X"  */
#line 2550 "parser.y"
                                { current_field->usage = CB_USAGE_COMP_X; }
#line 6926 "parser.c"
    break;

  case 361: /* usage: DISPLAY  */
#line 2551 "parser.y"
                                { current_field->usage = CB_USAGE_DISPLAY; }
#line 6932 "parser.c"
    break;

  case 362: /* usage: INDEX  */
#line 2552 "parser.y"
                                { current_field->usage = CB_USAGE_INDEX; }
#line 6938 "parser.c"
    break;

  case 363: /* usage: "PACKED-DECIMAL"  */
#line 2553 "parser.y"
                                { current_field->usage = CB_USAGE_PACKED; }
#line 6944 "parser.c"
    break;

  case 364: /* usage: POINTER  */
#line 2555 "parser.y"
  {
	current_field->usage = CB_USAGE_POINTER;
	current_field->flag_is_pointer = 1;
  }
#line 6953 "parser.c"
    break;

  case 365: /* usage: "PROGRAM-POINTER"  */
#line 2560 "parser.y"
  {
	current_field->usage = CB_USAGE_PROGRAM_POINTER;
	current_field->flag_is_pointer = 1;
  }
#line 6962 "parser.c"
    break;

  case 366: /* usage: "SIGNED-SHORT"  */
#line 2564 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_SHORT; }
#line 6968 "parser.c"
    break;

  case 367: /* usage: "SIGNED-INT"  */
#line 2565 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_INT; }
#line 6974 "parser.c"
    break;

  case 368: /* usage: "SIGNED-LONG"  */
#line 2566 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_LONG; }
#line 6980 "parser.c"
    break;

  case 369: /* usage: "UNSIGNED-SHORT"  */
#line 2567 "parser.y"
                                { current_field->usage = CB_USAGE_UNSIGNED_SHORT; }
#line 6986 "parser.c"
    break;

  case 370: /* usage: "UNSIGNED-INT"  */
#line 2568 "parser.y"
                                { current_field->usage = CB_USAGE_UNSIGNED_INT; }
#line 6992 "parser.c"
    break;

  case 371: /* usage: "UNSIGNED-LONG"  */
#line 2569 "parser.y"
                                { current_field->usage = CB_USAGE_UNSIGNED_LONG; }
#line 6998 "parser.c"
    break;

  case 372: /* usage: "BINARY-CHAR" SIGNED  */
#line 2570 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_CHAR; }
#line 7004 "parser.c"
    break;

  case 373: /* usage: "BINARY-CHAR" UNSIGNED  */
#line 2571 "parser.y"
                                { current_field->usage = CB_USAGE_UNSIGNED_CHAR; }
#line 7010 "parser.c"
    break;

  case 374: /* usage: "BINARY-CHAR"  */
#line 2572 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_CHAR; }
#line 7016 "parser.c"
    break;

  case 375: /* usage: "BINARY-SHORT" SIGNED  */
#line 2573 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_SHORT; }
#line 7022 "parser.c"
    break;

  case 376: /* usage: "BINARY-SHORT" UNSIGNED  */
#line 2574 "parser.y"
                                { current_field->usage = CB_USAGE_UNSIGNED_SHORT; }
#line 7028 "parser.c"
    break;

  case 377: /* usage: "BINARY-SHORT"  */
#line 2575 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_SHORT; }
#line 7034 "parser.c"
    break;

  case 378: /* usage: "BINARY-LONG" SIGNED  */
#line 2576 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_INT; }
#line 7040 "parser.c"
    break;

  case 379: /* usage: "BINARY-LONG" UNSIGNED  */
#line 2577 "parser.y"
                                { current_field->usage = CB_USAGE_UNSIGNED_INT; }
#line 7046 "parser.c"
    break;

  case 380: /* usage: "BINARY-LONG"  */
#line 2578 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_INT; }
#line 7052 "parser.c"
    break;

  case 381: /* usage: "BINARY-DOUBLE" SIGNED  */
#line 2579 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_LONG; }
#line 7058 "parser.c"
    break;

  case 382: /* usage: "BINARY-DOUBLE" UNSIGNED  */
#line 2580 "parser.y"
                                { current_field->usage = CB_USAGE_UNSIGNED_LONG; }
#line 7064 "parser.c"
    break;

  case 383: /* usage: "BINARY-DOUBLE"  */
#line 2581 "parser.y"
                                { current_field->usage = CB_USAGE_SIGNED_LONG; }
#line 7070 "parser.c"
    break;

  case 384: /* usage: "BINARY-C-LONG" SIGNED  */
#line 2583 "parser.y"
  {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  }
#line 7082 "parser.c"
    break;

  case 385: /* usage: "BINARY-C-LONG" UNSIGNED  */
#line 2591 "parser.y"
  {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_UNSIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_UNSIGNED_LONG;
	}
  }
#line 7094 "parser.c"
    break;

  case 386: /* usage: "BINARY-C-LONG"  */
#line 2599 "parser.y"
  {
	if (sizeof(long) == 4) {
		current_field->usage = CB_USAGE_SIGNED_INT;
	} else {
		current_field->usage = CB_USAGE_SIGNED_LONG;
	}
  }
#line 7106 "parser.c"
    break;

  case 387: /* usage: NATIONAL  */
#line 2606 "parser.y"
                                { PENDING ("USAGE NATIONAL");}
#line 7112 "parser.c"
    break;

  case 388: /* sign_clause: _sign_is LEADING flag_separate  */
#line 2614 "parser.y"
  {
	current_field->flag_sign_separate = CB_INTEGER (yyvsp[0])->val;
	current_field->flag_sign_leading  = 1;
  }
#line 7121 "parser.c"
    break;

  case 389: /* sign_clause: _sign_is TRAILING flag_separate  */
#line 2619 "parser.y"
  {
	current_field->flag_sign_separate = CB_INTEGER (yyvsp[0])->val;
	current_field->flag_sign_leading  = 0;
  }
#line 7130 "parser.c"
    break;

  case 390: /* occurs_clause: OCCURS integer occurs_to_integer _times occurs_depending occurs_keys occurs_indexed  */
#line 2631 "parser.y"
  {
	if (current_field->occurs_depending && !(yyvsp[-4])) {
		cb_verify (cb_odo_without_to, "ODO without TO clause");
	}
	current_field->occurs_min = yyvsp[-4] ? cb_get_int (yyvsp[-5]) : 1;
	current_field->occurs_max = yyvsp[-4] ? cb_get_int (yyvsp[-4]) : cb_get_int (yyvsp[-5]);
	current_field->indexes++;
	if (current_field->indexes > COB_MAX_SUBSCRIPTS) {
		cb_error (_("Maximum OCCURS depth exceeded"));
	}
	current_field->flag_occurs = 1;
  }
#line 7147 "parser.c"
    break;

  case 391: /* occurs_to_integer: %empty  */
#line 2646 "parser.y"
                                { yyval = NULL; }
#line 7153 "parser.c"
    break;

  case 392: /* occurs_to_integer: TO integer  */
#line 2647 "parser.y"
                                { yyval = yyvsp[0]; }
#line 7159 "parser.c"
    break;

  case 394: /* occurs_depending: DEPENDING _on reference  */
#line 2652 "parser.y"
  {
	current_field->occurs_depending = yyvsp[0];
  }
#line 7167 "parser.c"
    break;

  case 395: /* occurs_keys: occurs_key_list  */
#line 2659 "parser.y"
  {
	if (yyvsp[0]) {
		cb_tree		l;
		struct cb_key	*keys;
		int		i;
		int		nkeys;

		l = yyvsp[0];
		nkeys = cb_list_length (yyvsp[0]);
		keys = cobc_malloc (sizeof (struct cb_key) * nkeys);

		for (i = 0; i < nkeys; i++) {
			keys[i].dir = CB_PURPOSE_INT (l);
			keys[i].key = CB_VALUE (l);
			l = CB_CHAIN (l);
		}
		current_field->keys = keys;
		current_field->nkeys = nkeys;
	}
  }
#line 7192 "parser.c"
    break;

  case 396: /* occurs_key_list: %empty  */
#line 2682 "parser.y"
                                { yyval = NULL; }
#line 7198 "parser.c"
    break;

  case 397: /* occurs_key_list: occurs_key_list ascending_or_descending _key _is reference_list  */
#line 2685 "parser.y"
  {
	cb_tree l;

	for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = yyvsp[-3];
		if (qualifier && !CB_REFERENCE(CB_VALUE(l))->chain &&
		    strcasecmp (CB_NAME(CB_VALUE(l)), CB_NAME(qualifier))) {
			CB_REFERENCE(CB_VALUE(l))->chain = qualifier;
		}
	}
	yyval = cb_list_append (yyvsp[-4], yyvsp[0]);
  }
#line 7215 "parser.c"
    break;

  case 398: /* ascending_or_descending: ASCENDING  */
#line 2700 "parser.y"
                                { yyval = cb_int (COB_ASCENDING); }
#line 7221 "parser.c"
    break;

  case 399: /* ascending_or_descending: DESCENDING  */
#line 2701 "parser.y"
                                { yyval = cb_int (COB_DESCENDING); }
#line 7227 "parser.c"
    break;

  case 401: /* occurs_indexed: INDEXED _by occurs_index_list  */
#line 2706 "parser.y"
  {
	current_field->index_list = yyvsp[0];
  }
#line 7235 "parser.c"
    break;

  case 402: /* occurs_index_list: occurs_index  */
#line 2712 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 7241 "parser.c"
    break;

  case 403: /* occurs_index_list: occurs_index_list occurs_index  */
#line 2714 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 7247 "parser.c"
    break;

  case 404: /* occurs_index: "Identifier"  */
#line 2719 "parser.y"
  {
	yyval = cb_build_index (yyvsp[0], cb_int1, 1, current_field);
  }
#line 7255 "parser.c"
    break;

  case 405: /* justified_clause: JUSTIFIED _right  */
#line 2728 "parser.y"
                                { current_field->flag_justified = 1; }
#line 7261 "parser.c"
    break;

  case 406: /* synchronized_clause: SYNCHRONIZED left_or_right  */
#line 2735 "parser.y"
                                { current_field->flag_synchronized = 1; }
#line 7267 "parser.c"
    break;

  case 410: /* blank_clause: BLANK _when ZERO  */
#line 2747 "parser.y"
                                { current_field->flag_blank_zero = 1; }
#line 7273 "parser.c"
    break;

  case 411: /* based_clause: BASED  */
#line 2755 "parser.y"
  {
	if (current_storage != CB_STORAGE_WORKING &&
	    current_storage != CB_STORAGE_LINKAGE &&
	    current_storage != CB_STORAGE_LOCAL) {
		cb_error (_("BASED not allowed here"));
	} else if (current_field->level != 1 && current_field->level != 77) {
		cb_error (_("BASED only allowed at 01/77 level"));
	} else if (!qualifier) {
		cb_error (_("BASED requires a data name"));
	} else if (current_field->flag_external) {
		cb_error (_("BASED and EXTERNAL are mutually exclusive"));
	} else if (current_field->redefines) {
		cb_error (_("BASED and REDEFINES are mutually exclusive"));
	} else if (current_field->flag_any_length) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_item_based = 1;
	}
  }
#line 7297 "parser.c"
    break;

  case 412: /* $@21: %empty  */
#line 2779 "parser.y"
                                { current_field->values = yyvsp[0]; }
#line 7303 "parser.c"
    break;

  case 414: /* value_item_list: value_item  */
#line 2784 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 7309 "parser.c"
    break;

  case 415: /* value_item_list: value_item_list value_item  */
#line 2785 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 7315 "parser.c"
    break;

  case 416: /* value_item: literal  */
#line 2789 "parser.y"
                                { yyval = yyvsp[0]; }
#line 7321 "parser.c"
    break;

  case 417: /* value_item: literal THRU literal  */
#line 2790 "parser.y"
                                { yyval = cb_build_pair (yyvsp[-2], yyvsp[0]); }
#line 7327 "parser.c"
    break;

  case 419: /* false_is: "FALSE" _is literal  */
#line 2795 "parser.y"
  {
	if (current_field->level != 88) {
		cb_error (_("FALSE clause only allowed for 88 level"));
	}
	current_field->false_88 = cb_list_init (yyvsp[0]);
  }
#line 7338 "parser.c"
    break;

  case 420: /* renames_clause: RENAMES qualified_word  */
#line 2808 "parser.y"
  {
	if (cb_ref (yyvsp[0]) != cb_error_node) {
		if (CB_FIELD (cb_ref (yyvsp[0]))->level == 01 ||
		    CB_FIELD (cb_ref (yyvsp[0]))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else {
			current_field->redefines = CB_FIELD (cb_ref (yyvsp[0]));
			current_field->pic = current_field->redefines->pic;
		}
	}
  }
#line 7354 "parser.c"
    break;

  case 421: /* renames_clause: RENAMES qualified_word THRU qualified_word  */
#line 2820 "parser.y"
  {
	if (cb_ref (yyvsp[-2]) != cb_error_node && cb_ref (yyvsp[0]) != cb_error_node) {
		if (CB_FIELD (cb_ref (yyvsp[-2]))->level == 01 ||
		    CB_FIELD (cb_ref (yyvsp[-2]))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else if (CB_FIELD (cb_ref (yyvsp[0]))->level == 01 ||
		    CB_FIELD (cb_ref (yyvsp[0]))->level > 50) {
			cb_error (_("RENAMES may not reference a level 01 or > 50"));
		} else {
			current_field->redefines = CB_FIELD (cb_ref (yyvsp[-2]));
			current_field->rename_thru = CB_FIELD (cb_ref (yyvsp[0]));
		}
	}
  }
#line 7373 "parser.c"
    break;

  case 422: /* any_length_clause: ANY LENGTH  */
#line 2840 "parser.y"
  {
	if (current_field->flag_item_based) {
		cb_error (_("BASED and ANY LENGTH are mutually exclusive"));
	} else {
		current_field->flag_any_length = 1;
	}
  }
#line 7385 "parser.c"
    break;

  case 424: /* $@22: %empty  */
#line 2855 "parser.y"
  {
	current_storage = CB_STORAGE_LOCAL;
	if (current_program->nested_level) {
		cb_error (_("LOCAL-STORAGE not allowed in nested programs"));
	}
  }
#line 7396 "parser.c"
    break;

  case 425: /* local_storage_section: "LOCAL-STORAGE" SECTION '.' $@22 record_description_list  */
#line 2862 "parser.y"
  {
	if (yyvsp[0]) {
		current_program->local_storage = CB_FIELD (yyvsp[0]);
	}
  }
#line 7406 "parser.c"
    break;

  case 427: /* $@23: %empty  */
#line 2875 "parser.y"
                                { current_storage = CB_STORAGE_LINKAGE; }
#line 7412 "parser.c"
    break;

  case 428: /* linkage_section: LINKAGE SECTION '.' $@23 record_description_list  */
#line 2877 "parser.y"
  {
	if (yyvsp[0]) {
		current_program->linkage_storage = CB_FIELD (yyvsp[0]);
	}
  }
#line 7422 "parser.c"
    break;

  case 430: /* $@24: %empty  */
#line 2890 "parser.y"
  {
	cb_error (_("REPORT SECTION not supported"));
	current_storage = CB_STORAGE_REPORT;
  }
#line 7431 "parser.c"
    break;

  case 437: /* report_description_options: %empty  */
#line 2923 "parser.y"
  {
	cb_warning (_("Report description using defaults"));
  }
#line 7439 "parser.c"
    break;

  case 439: /* report_description_option: _is GLOBAL  */
#line 2931 "parser.y"
  {
	cb_error (_("GLOBAL is not allowed with RD"));
  }
#line 7447 "parser.c"
    break;

  case 471: /* report_group_option: type_clause  */
#line 3011 "parser.y"
              { cb_warning (_("looking for Report line TYPE")); }
#line 7453 "parser.c"
    break;

  case 522: /* $@25: %empty  */
#line 3116 "parser.y"
                                { current_storage = CB_STORAGE_SCREEN; }
#line 7459 "parser.c"
    break;

  case 523: /* $@26: %empty  */
#line 3117 "parser.y"
  {
	current_field = NULL;
	description_field = NULL;
	cb_clear_real_field ();
  }
#line 7469 "parser.c"
    break;

  case 524: /* screen_section: SCREEN SECTION '.' $@25 $@26 opt_screen_description_list  */
#line 3123 "parser.y"
  {
	struct cb_field *p;

	for (p = description_field; p; p = p->sister) {
		cb_validate_field (p);
	}
	current_program->screen_storage = description_field;
	current_program->flag_screen = 1;
  }
#line 7483 "parser.c"
    break;

  case 530: /* $@27: %empty  */
#line 3147 "parser.y"
  {
	cb_tree x;

	x = cb_build_field_tree (yyvsp[-1], yyvsp[0], current_field, current_storage, current_file);
	if (x == cb_error_node) {
		YYERROR;
	}

	current_field = CB_FIELD (x);
	if (current_field->parent) {
		current_field->screen_flag |= current_field->parent->screen_flag;
		current_field->screen_foreg = current_field->parent->screen_foreg;
		current_field->screen_backg = current_field->parent->screen_backg;
	}
  }
#line 7503 "parser.c"
    break;

  case 531: /* screen_description: level_number entry_name $@27 screen_options '.'  */
#line 3163 "parser.y"
  {
	if (!qualifier && (current_field->level == 88 ||
	    current_field->level == 77 || current_field->level == 66 ||
	    current_field->flag_item_78)) {
		cb_error (_("Item requires a data name"));
	}
	if (current_field->level == 88) {
		cb_validate_88_item (current_field);
	}
	if (current_field->flag_item_78) {
		/* Reset to last non-78 item */
		current_field = cb_validate_78_item (current_field);
	}
	if (!description_field) {
		description_field = current_field;
	}
  }
#line 7525 "parser.c"
    break;

  case 534: /* screen_option: "BLANK-LINE"  */
#line 3187 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_BLANK_LINE; }
#line 7531 "parser.c"
    break;

  case 535: /* screen_option: "BLANK-SCREEN"  */
#line 3188 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_BLANK_SCREEN; }
#line 7537 "parser.c"
    break;

  case 536: /* screen_option: BELL  */
#line 3189 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_BELL; }
#line 7543 "parser.c"
    break;

  case 537: /* screen_option: BLINK  */
#line 3190 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_BLINK; }
#line 7549 "parser.c"
    break;

  case 538: /* screen_option: ERASE EOL  */
#line 3191 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_ERASE_EOL; }
#line 7555 "parser.c"
    break;

  case 539: /* screen_option: ERASE EOS  */
#line 3192 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_ERASE_EOS; }
#line 7561 "parser.c"
    break;

  case 540: /* screen_option: HIGHLIGHT  */
#line 3193 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_HIGHLIGHT; }
#line 7567 "parser.c"
    break;

  case 541: /* screen_option: LOWLIGHT  */
#line 3194 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_LOWLIGHT; }
#line 7573 "parser.c"
    break;

  case 542: /* screen_option: "REVERSE-VIDEO"  */
#line 3195 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_REVERSE; }
#line 7579 "parser.c"
    break;

  case 543: /* screen_option: UNDERLINE  */
#line 3196 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_UNDERLINE; }
#line 7585 "parser.c"
    break;

  case 544: /* screen_option: OVERLINE  */
#line 3197 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_OVERLINE; }
#line 7591 "parser.c"
    break;

  case 545: /* screen_option: AUTO  */
#line 3198 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_AUTO; }
#line 7597 "parser.c"
    break;

  case 546: /* screen_option: SECURE  */
#line 3199 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_SECURE; }
#line 7603 "parser.c"
    break;

  case 547: /* screen_option: REQUIRED  */
#line 3200 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_REQUIRED; }
#line 7609 "parser.c"
    break;

  case 548: /* screen_option: FULL  */
#line 3201 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_FULL; }
#line 7615 "parser.c"
    break;

  case 549: /* screen_option: PROMPT  */
#line 3202 "parser.y"
                { current_field->screen_flag |= COB_SCREEN_PROMPT; }
#line 7621 "parser.c"
    break;

  case 550: /* screen_option: LINE _number _is screen_line_plus_minus num_id_or_lit  */
#line 3204 "parser.y"
  {
	current_field->screen_line = yyvsp[0];
  }
#line 7629 "parser.c"
    break;

  case 551: /* screen_option: COLUMN _number _is screen_col_plus_minus num_id_or_lit  */
#line 3208 "parser.y"
  {
	current_field->screen_column = yyvsp[0];
  }
#line 7637 "parser.c"
    break;

  case 552: /* screen_option: "FOREGROUND-COLOR" _is num_id_or_lit  */
#line 3212 "parser.y"
  {
	current_field->screen_foreg = yyvsp[0];
  }
#line 7645 "parser.c"
    break;

  case 553: /* screen_option: "BACKGROUND-COLOR" _is num_id_or_lit  */
#line 3216 "parser.y"
  {
	current_field->screen_backg = yyvsp[0];
  }
#line 7653 "parser.c"
    break;

  case 561: /* screen_option: USING identifier  */
#line 3227 "parser.y"
  {
	current_field->screen_from = yyvsp[0];
	current_field->screen_to = yyvsp[0];
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  }
#line 7664 "parser.c"
    break;

  case 562: /* screen_option: FROM id_or_lit_or_func  */
#line 3234 "parser.y"
  {
	current_field->screen_from = yyvsp[0];
  }
#line 7672 "parser.c"
    break;

  case 563: /* screen_option: TO identifier  */
#line 3238 "parser.y"
  {
	current_field->screen_to = yyvsp[0];
	current_field->screen_flag |= COB_SCREEN_PROMPT;
	current_field->screen_flag |= COB_SCREEN_INPUT;
  }
#line 7682 "parser.c"
    break;

  case 564: /* screen_line_plus_minus: %empty  */
#line 3247 "parser.y"
  {
	/* Nothing */
  }
#line 7690 "parser.c"
    break;

  case 565: /* screen_line_plus_minus: PLUS  */
#line 3251 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  }
#line 7698 "parser.c"
    break;

  case 566: /* screen_line_plus_minus: '+'  */
#line 3255 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_LINE_PLUS;
  }
#line 7706 "parser.c"
    break;

  case 567: /* screen_line_plus_minus: MINUS  */
#line 3259 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  }
#line 7714 "parser.c"
    break;

  case 568: /* screen_line_plus_minus: '-'  */
#line 3263 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_LINE_MINUS;
  }
#line 7722 "parser.c"
    break;

  case 569: /* screen_col_plus_minus: %empty  */
#line 3270 "parser.y"
  {
	/* Nothing */
  }
#line 7730 "parser.c"
    break;

  case 570: /* screen_col_plus_minus: PLUS  */
#line 3274 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  }
#line 7738 "parser.c"
    break;

  case 571: /* screen_col_plus_minus: '+'  */
#line 3278 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_COLUMN_PLUS;
  }
#line 7746 "parser.c"
    break;

  case 572: /* screen_col_plus_minus: MINUS  */
#line 3282 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  }
#line 7754 "parser.c"
    break;

  case 573: /* screen_col_plus_minus: '-'  */
#line 3286 "parser.y"
  {
	current_field->screen_flag |= COB_SCREEN_COLUMN_MINUS;
  }
#line 7762 "parser.c"
    break;

  case 574: /* screen_occurs_clause: OCCURS integer _times  */
#line 3294 "parser.y"
  {
	current_field->occurs_max = cb_get_int (yyvsp[-1]);
	current_field->occurs_min = current_field->occurs_max;
	current_field->indexes++;
	current_field->flag_occurs = 1;
  }
#line 7773 "parser.c"
    break;

  case 576: /* $@28: %empty  */
#line 3308 "parser.y"
  {
	current_section = NULL;
	current_paragraph = NULL;
	cb_define_system_name ("CONSOLE");
	cb_define_system_name ("SYSIN");
	cb_define_system_name ("SYSOUT");
	cb_define_system_name ("SYSERR");
	cb_set_in_procedure ();
  }
#line 7787 "parser.c"
    break;

  case 577: /* $@29: %empty  */
#line 3318 "parser.y"
  {
	if (current_program->flag_main && !current_program->flag_chained && yyvsp[-4]) {
		cb_error (_("Executable program requested but PROCEDURE/ENTRY has USING clause"));
	}
	emit_entry (current_program->program_id, 0, yyvsp[-4]); /* main entry point */
	if (current_program->source_name) {
		emit_entry (current_program->source_name, 1, yyvsp[-4]);
	}
  }
#line 7801 "parser.c"
    break;

  case 578: /* procedure_division: PROCEDURE DIVISION procedure_using_chaining procedure_returning '.' $@28 procedure_declaratives $@29 procedure_list  */
#line 3328 "parser.y"
  {
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
	}
	if (current_section) {
		if (current_section->exit_label) {
			emit_statement (current_section->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_section));
	}
  }
#line 7820 "parser.c"
    break;

  case 579: /* procedure_using_chaining: %empty  */
#line 3345 "parser.y"
                                { yyval = NULL; }
#line 7826 "parser.c"
    break;

  case 580: /* $@30: %empty  */
#line 3347 "parser.y"
  {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  }
#line 7835 "parser.c"
    break;

  case 581: /* procedure_using_chaining: USING $@30 procedure_param_list  */
#line 3351 "parser.y"
                                { yyval = yyvsp[0]; }
#line 7841 "parser.c"
    break;

  case 582: /* $@31: %empty  */
#line 3353 "parser.y"
  {
	call_mode = CB_CALL_BY_REFERENCE;
	current_program->flag_chained = 1;
  }
#line 7850 "parser.c"
    break;

  case 583: /* procedure_using_chaining: CHAINING $@31 procedure_param_list  */
#line 3357 "parser.y"
                                { yyval = yyvsp[0]; }
#line 7856 "parser.c"
    break;

  case 584: /* procedure_param_list: procedure_param  */
#line 3361 "parser.y"
                                { yyval = yyvsp[0]; }
#line 7862 "parser.c"
    break;

  case 585: /* procedure_param_list: procedure_param_list procedure_param  */
#line 3363 "parser.y"
                                { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); }
#line 7868 "parser.c"
    break;

  case 586: /* procedure_param: procedure_type size_optional procedure_optional "Identifier"  */
#line 3368 "parser.y"
  {
	yyval = cb_build_pair (cb_int (call_mode), cb_build_identifier (yyvsp[0]));
	CB_SIZES (yyval) = size_mode;
  }
#line 7877 "parser.c"
    break;

  case 588: /* procedure_type: _by REFERENCE  */
#line 3377 "parser.y"
  {
	call_mode = CB_CALL_BY_REFERENCE;
  }
#line 7885 "parser.c"
    break;

  case 589: /* procedure_type: _by VALUE  */
#line 3381 "parser.y"
  {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  }
#line 7897 "parser.c"
    break;

  case 591: /* size_optional: SIZE _is AUTO  */
#line 3393 "parser.y"
  {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_AUTO;
	}
  }
#line 7909 "parser.c"
    break;

  case 592: /* size_optional: SIZE _is DEFAULT  */
#line 3401 "parser.y"
  {
	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else {
		size_mode = CB_SIZE_4;
	}
  }
#line 7921 "parser.c"
    break;

  case 593: /* size_optional: UNSIGNED SIZE _is integer  */
#line 3409 "parser.y"
  {
	unsigned char *s = CB_LITERAL (yyvsp[0])->data;

	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else if (CB_LITERAL (yyvsp[0])->size != 1) {
		cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
	} else {
		size_mode = CB_SIZE_UNSIGNED;
		switch (*s) {
		case '1':
			size_mode |= CB_SIZE_1;
			break;
		case '2':
			size_mode |= CB_SIZE_2;
			break;
		case '4':
			size_mode |= CB_SIZE_4;
			break;
		case '8':
			size_mode |= CB_SIZE_8;
			break;
		default:
			cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
			break;
		}
	}
  }
#line 7954 "parser.c"
    break;

  case 594: /* size_optional: SIZE _is integer  */
#line 3438 "parser.y"
  {
	unsigned char *s = CB_LITERAL (yyvsp[0])->data;

	if (call_mode != CB_CALL_BY_VALUE) {
		cb_error (_("SIZE only allowed for BY VALUE items"));
	} else if (CB_LITERAL (yyvsp[0])->size != 1) {
		cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
	} else {
		size_mode = 0;
		switch (*s) {
		case '1':
			size_mode = CB_SIZE_1;
			break;
		case '2':
			size_mode = CB_SIZE_2;
			break;
		case '4':
			size_mode = CB_SIZE_4;
			break;
		case '8':
			size_mode = CB_SIZE_8;
			break;
		default:
			cb_error_x (yyvsp[0], _("Invalid value for SIZE"));
			break;
		}
	}
  }
#line 7987 "parser.c"
    break;

  case 596: /* procedure_optional: OPTIONAL  */
#line 3471 "parser.y"
  {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OPTIONAL only allowed for BY REFERENCE items"));
	}
  }
#line 7997 "parser.c"
    break;

  case 597: /* procedure_returning: %empty  */
#line 3480 "parser.y"
  {
	if (current_program->prog_type == CB_FUNCTION_TYPE) {
		cb_error (_("RETURNING clause is required for a FUNCTION"));
	}
  }
#line 8007 "parser.c"
    break;

  case 598: /* procedure_returning: RETURNING "Identifier"  */
#line 3486 "parser.y"
  {
	if (cb_ref (yyvsp[0]) != cb_error_node) {
		current_program->returning = yyvsp[0];
		if (cb_field (yyvsp[0])->storage != CB_STORAGE_LINKAGE) {
			cb_error (_("RETURNING item is not defined in LINKAGE SECTION"));
		}
	}
  }
#line 8020 "parser.c"
    break;

  case 600: /* $@32: %empty  */
#line 3497 "parser.y"
                        { in_declaratives = 1; }
#line 8026 "parser.c"
    break;

  case 601: /* procedure_declaratives: DECLARATIVES '.' $@32 procedure_list END DECLARATIVES '.'  */
#line 3500 "parser.y"
  {
	in_declaratives = 0;
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
		current_paragraph = NULL;
	}
	if (current_section) {
		if (current_section->exit_label) {
			emit_statement (current_section->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_section));
		current_section = NULL;
	}
  }
#line 8048 "parser.c"
    break;

  case 607: /* procedure: statements '.'  */
#line 3533 "parser.y"
  {
	if (next_label_list) {
		cb_tree label;
		char name[16];

		sprintf (name, "L$%d", next_label_id);
		label = cb_build_reference (name);
		emit_statement (cb_build_label (label, NULL));
		current_program->label_list =
			cb_list_append (current_program->label_list, next_label_list);
		next_label_list = NULL;
		next_label_id++;
	}
	/* check_unreached = 0; */
  }
#line 8068 "parser.c"
    break;

  case 608: /* procedure: error '.'  */
#line 3549 "parser.y"
  {
	check_unreached = 0;
  }
#line 8076 "parser.c"
    break;

  case 609: /* procedure: '.'  */
#line 3553 "parser.y"
  {
	/* check_unreached = 0; */
  }
#line 8084 "parser.c"
    break;

  case 610: /* section_header: section_name SECTION opt_segment '.'  */
#line 3565 "parser.y"
  {
	non_const_word = 0;
	check_unreached = 0;
	if (yyvsp[-3] == cb_error_node) {
		YYERROR;
	}

	/* Exit the last section */
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
	}
	if (current_section) {
		if (current_section->exit_label) {
			emit_statement (current_section->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_section));
	}

	/* Begin a new section */
	current_section = CB_LABEL (cb_build_label (yyvsp[-3], NULL));
	current_section->is_section = 1;
	current_paragraph = NULL;
	emit_statement (CB_TREE (current_section));
  }
#line 8116 "parser.c"
    break;

  case 611: /* paragraph_header: "Identifier" '.'  */
#line 3596 "parser.y"
  {
	cb_tree label;

	non_const_word = 0;
	check_unreached = 0;
	yyval = cb_build_section_name (yyvsp[-1], 1);
	/* if ($1 == cb_error_node) */
	if (yyval == cb_error_node) {
		YYERROR;
	}

	/* Exit the last paragraph */
	if (current_paragraph) {
		if (current_paragraph->exit_label) {
			emit_statement (current_paragraph->exit_label);
		}
		emit_statement (cb_build_perform_exit (current_paragraph));
	}

	/* Begin a new paragraph */
	if (!current_section) {
		label = cb_build_reference ("MAIN SECTION");
		current_section = CB_LABEL (cb_build_label (label, NULL));
		current_section->is_section = 1;
		emit_statement (CB_TREE (current_section));
	}
	current_paragraph = CB_LABEL (cb_build_label (yyval, current_section));
	if (current_section) {
		current_section->children =
			cb_cons (CB_TREE (current_paragraph), current_section->children);
	}
	emit_statement (CB_TREE (current_paragraph));
  }
#line 8154 "parser.c"
    break;

  case 612: /* invalid_statement: section_name  */
#line 3633 "parser.y"
  {
	non_const_word = 0;
	check_unreached = 0;
	if (yyvsp[0] != cb_error_node) {
		cb_error_x (yyvsp[0], _("Unknown statement '%s'"), CB_NAME (yyvsp[0]));
	}
	YYERROR;
  }
#line 8167 "parser.c"
    break;

  case 613: /* section_name: "Identifier"  */
#line 3644 "parser.y"
                                { yyval = cb_build_section_name (yyvsp[0], 0); }
#line 8173 "parser.c"
    break;

  case 615: /* opt_segment: "Literal"  */
#line 3648 "parser.y"
                                { /* ignore */ }
#line 8179 "parser.c"
    break;

  case 616: /* @33: %empty  */
#line 3657 "parser.y"
  {
	yyval = current_program->exec_list;
	current_program->exec_list = NULL;
  }
#line 8188 "parser.c"
    break;

  case 617: /* @34: %empty  */
#line 3661 "parser.y"
  {
	yyval = CB_TREE (current_statement);
	current_statement = NULL;
  }
#line 8197 "parser.c"
    break;

  case 618: /* statement_list: @33 @34 statements  */
#line 3666 "parser.y"
  {
	yyval = cb_list_reverse (current_program->exec_list);
	current_program->exec_list = yyvsp[-2];
	current_statement = CB_STATEMENT (yyvsp[-1]);
  }
#line 8207 "parser.c"
    break;

  case 619: /* $@35: %empty  */
#line 3674 "parser.y"
  {
	cb_tree label;

	if (!current_section) {
		label = cb_build_reference ("MAIN SECTION");
		current_section = CB_LABEL (cb_build_label (label, NULL));
		current_section->is_section = 1;
		emit_statement (CB_TREE (current_section));
	}
	if (!current_paragraph) {
		label = cb_build_reference ("MAIN PARAGRAPH");
		current_paragraph = CB_LABEL (cb_build_label (label, NULL));
		emit_statement (CB_TREE (current_paragraph));
		current_section->children =
			cb_cons (CB_TREE (current_paragraph), current_section->children);
	}
  }
#line 8229 "parser.c"
    break;

  case 670: /* statement: "NEXT SENTENCE"  */
#line 3745 "parser.y"
  {
	if (cb_verify (cb_next_sentence_phrase, "NEXT SENTENCE")) {
		cb_tree label;
		char	name[16];

		BEGIN_STATEMENT ("NEXT SENTENCE", 0);
		sprintf (name, "L$%d", next_label_id);
		label = cb_build_reference (name);
		next_label_list = cb_list_add (next_label_list, label);
		emit_statement (cb_build_goto (label, NULL));
	}
	check_unreached = 0;
  }
#line 8247 "parser.c"
    break;

  case 671: /* $@36: %empty  */
#line 3767 "parser.y"
  {
	BEGIN_STATEMENT ("ACCEPT", TERM_ACCEPT);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  }
#line 8259 "parser.c"
    break;

  case 673: /* accept_body: identifier opt_at_line_column opt_accp_attr on_accp_exception  */
#line 3780 "parser.y"
  {
	cb_emit_accept (yyvsp[-3], yyvsp[-2], fgc, bgc, scroll, dispattrs);
  }
#line 8267 "parser.c"
    break;

  case 674: /* accept_body: identifier FROM ESCAPE KEY  */
#line 3784 "parser.y"
  {
	PENDING ("ACCEPT .. FROM ESCAPE KEY");
  }
#line 8275 "parser.c"
    break;

  case 675: /* accept_body: identifier FROM LINES  */
#line 3788 "parser.y"
  {
	cb_emit_accept_line_or_col (yyvsp[-2], 0);
  }
#line 8283 "parser.c"
    break;

  case 676: /* accept_body: identifier FROM COLUMNS  */
#line 3792 "parser.y"
  {
	cb_emit_accept_line_or_col (yyvsp[-2], 1);
  }
#line 8291 "parser.c"
    break;

  case 677: /* accept_body: identifier FROM DATE  */
#line 3796 "parser.y"
  {
	cb_emit_accept_date (yyvsp[-2]);
  }
#line 8299 "parser.c"
    break;

  case 678: /* accept_body: identifier FROM DATE YYYYMMDD  */
#line 3800 "parser.y"
  {
	cb_emit_accept_date_yyyymmdd (yyvsp[-3]);
  }
#line 8307 "parser.c"
    break;

  case 679: /* accept_body: identifier FROM DAY  */
#line 3804 "parser.y"
  {
	cb_emit_accept_day (yyvsp[-2]);
  }
#line 8315 "parser.c"
    break;

  case 680: /* accept_body: identifier FROM DAY YYYYDDD  */
#line 3808 "parser.y"
  {
	cb_emit_accept_day_yyyyddd (yyvsp[-3]);
  }
#line 8323 "parser.c"
    break;

  case 681: /* accept_body: identifier FROM "DAY-OF-WEEK"  */
#line 3812 "parser.y"
  {
	cb_emit_accept_day_of_week (yyvsp[-2]);
  }
#line 8331 "parser.c"
    break;

  case 682: /* accept_body: identifier FROM TIME  */
#line 3816 "parser.y"
  {
	cb_emit_accept_time (yyvsp[-2]);
  }
#line 8339 "parser.c"
    break;

  case 683: /* accept_body: identifier FROM "COMMAND-LINE"  */
#line 3820 "parser.y"
  {
	cb_emit_accept_command_line (yyvsp[-2]);
  }
#line 8347 "parser.c"
    break;

  case 684: /* accept_body: identifier FROM "ENVIRONMENT-VALUE" on_accp_exception  */
#line 3824 "parser.y"
  {
	cb_emit_accept_environment (yyvsp[-3]);
  }
#line 8355 "parser.c"
    break;

  case 685: /* accept_body: identifier FROM ENVIRONMENT simple_value on_accp_exception  */
#line 3828 "parser.y"
  { 
	cb_emit_get_environment (yyvsp[-1], yyvsp[-4]);
  }
#line 8363 "parser.c"
    break;

  case 686: /* accept_body: identifier FROM "ARGUMENT-NUMBER"  */
#line 3832 "parser.y"
  {
	cb_emit_accept_arg_number (yyvsp[-2]);
  }
#line 8371 "parser.c"
    break;

  case 687: /* accept_body: identifier FROM "ARGUMENT-VALUE" on_accp_exception  */
#line 3836 "parser.y"
  {
	cb_emit_accept_arg_value (yyvsp[-3]);
  }
#line 8379 "parser.c"
    break;

  case 688: /* accept_body: identifier FROM mnemonic_name  */
#line 3840 "parser.y"
  {
	cb_emit_accept_mnemonic (yyvsp[-2], yyvsp[0]);
  }
#line 8387 "parser.c"
    break;

  case 689: /* accept_body: identifier FROM "Identifier"  */
#line 3844 "parser.y"
  {
	cb_emit_accept_name (yyvsp[-2], yyvsp[0]);
  }
#line 8395 "parser.c"
    break;

  case 690: /* opt_at_line_column: %empty  */
#line 3850 "parser.y"
                                { yyval = NULL; }
#line 8401 "parser.c"
    break;

  case 691: /* opt_at_line_column: _at line_number column_number  */
#line 3851 "parser.y"
                                { yyval = cb_build_pair (yyvsp[-1], yyvsp[0]); }
#line 8407 "parser.c"
    break;

  case 692: /* opt_at_line_column: _at column_number line_number  */
#line 3852 "parser.y"
                                { yyval = cb_build_pair (yyvsp[0], yyvsp[-1]); }
#line 8413 "parser.c"
    break;

  case 693: /* opt_at_line_column: _at line_number  */
#line 3853 "parser.y"
                                { yyval = cb_build_pair (yyvsp[0], NULL); }
#line 8419 "parser.c"
    break;

  case 694: /* opt_at_line_column: _at column_number  */
#line 3854 "parser.y"
                                { yyval = cb_build_pair (NULL, yyvsp[0]); }
#line 8425 "parser.c"
    break;

  case 695: /* opt_at_line_column: AT simple_value  */
#line 3855 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8431 "parser.c"
    break;

  case 696: /* line_number: LINE _number id_or_lit  */
#line 3859 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8437 "parser.c"
    break;

  case 697: /* column_number: COLUMN _number id_or_lit  */
#line 3863 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8443 "parser.c"
    break;

  case 698: /* column_number: POSITION _number id_or_lit  */
#line 3864 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8449 "parser.c"
    break;

  case 703: /* accp_attr: BELL  */
#line 3877 "parser.y"
                { dispattrs |= COB_SCREEN_BELL; }
#line 8455 "parser.c"
    break;

  case 704: /* accp_attr: BLINK  */
#line 3878 "parser.y"
                { dispattrs |= COB_SCREEN_BLINK; }
#line 8461 "parser.c"
    break;

  case 705: /* accp_attr: HIGHLIGHT  */
#line 3879 "parser.y"
                { dispattrs |= COB_SCREEN_HIGHLIGHT; }
#line 8467 "parser.c"
    break;

  case 706: /* accp_attr: LOWLIGHT  */
#line 3880 "parser.y"
                { dispattrs |= COB_SCREEN_LOWLIGHT; }
#line 8473 "parser.c"
    break;

  case 707: /* accp_attr: "REVERSE-VIDEO"  */
#line 3881 "parser.y"
                { dispattrs |= COB_SCREEN_REVERSE; }
#line 8479 "parser.c"
    break;

  case 708: /* accp_attr: UNDERLINE  */
#line 3882 "parser.y"
                { dispattrs |= COB_SCREEN_UNDERLINE; }
#line 8485 "parser.c"
    break;

  case 709: /* accp_attr: OVERLINE  */
#line 3883 "parser.y"
                { dispattrs |= COB_SCREEN_OVERLINE; }
#line 8491 "parser.c"
    break;

  case 710: /* accp_attr: "FOREGROUND-COLOR" _is num_id_or_lit  */
#line 3885 "parser.y"
  {
	fgc = yyvsp[0];
  }
#line 8499 "parser.c"
    break;

  case 711: /* accp_attr: "BACKGROUND-COLOR" _is num_id_or_lit  */
#line 3889 "parser.y"
  {
	bgc = yyvsp[0];
  }
#line 8507 "parser.c"
    break;

  case 712: /* accp_attr: SCROLL UP _opt_scroll_lines  */
#line 3893 "parser.y"
  {
	scroll = yyvsp[0];
  }
#line 8515 "parser.c"
    break;

  case 713: /* accp_attr: SCROLL DOWN _opt_scroll_lines  */
#line 3897 "parser.y"
  {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = yyvsp[0];
  }
#line 8524 "parser.c"
    break;

  case 714: /* accp_attr: AUTO  */
#line 3901 "parser.y"
                { dispattrs |= COB_SCREEN_AUTO; }
#line 8530 "parser.c"
    break;

  case 715: /* accp_attr: FULL  */
#line 3902 "parser.y"
                { dispattrs |= COB_SCREEN_FULL; }
#line 8536 "parser.c"
    break;

  case 716: /* accp_attr: REQUIRED  */
#line 3903 "parser.y"
                { dispattrs |= COB_SCREEN_REQUIRED; }
#line 8542 "parser.c"
    break;

  case 717: /* accp_attr: SECURE  */
#line 3904 "parser.y"
                { dispattrs |= COB_SCREEN_SECURE; }
#line 8548 "parser.c"
    break;

  case 718: /* accp_attr: UPDATE  */
#line 3905 "parser.y"
                { dispattrs |= COB_SCREEN_UPDATE; }
#line 8554 "parser.c"
    break;

  case 719: /* accp_attr: PROMPT  */
#line 3906 "parser.y"
                { dispattrs |= COB_SCREEN_PROMPT; }
#line 8560 "parser.c"
    break;

  case 720: /* end_accept: %empty  */
#line 3910 "parser.y"
                                { terminator_warning (TERM_ACCEPT); }
#line 8566 "parser.c"
    break;

  case 721: /* end_accept: "END-ACCEPT"  */
#line 3911 "parser.y"
                                { terminator_clear (TERM_ACCEPT); }
#line 8572 "parser.c"
    break;

  case 722: /* $@37: %empty  */
#line 3920 "parser.y"
                                { BEGIN_STATEMENT ("ADD", TERM_ADD); }
#line 8578 "parser.c"
    break;

  case 724: /* add_body: x_list TO arithmetic_x_list on_size_error  */
#line 3927 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], '+', cb_build_binary_list (yyvsp[-3], '+'));
  }
#line 8586 "parser.c"
    break;

  case 725: /* add_body: x_list add_to GIVING arithmetic_x_list on_size_error  */
#line 3931 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_list (yyvsp[-4], '+'));
  }
#line 8594 "parser.c"
    break;

  case 726: /* add_body: CORRESPONDING identifier TO identifier flag_rounded on_size_error  */
#line 3935 "parser.y"
  {
	cb_emit_corresponding (cb_build_add, yyvsp[-2], yyvsp[-4], yyvsp[-1]);
  }
#line 8602 "parser.c"
    break;

  case 728: /* add_to: TO x  */
#line 3941 "parser.y"
                                { cb_list_add (yyvsp[-2], yyvsp[0]); }
#line 8608 "parser.c"
    break;

  case 729: /* end_add: %empty  */
#line 3945 "parser.y"
                                { terminator_warning (TERM_ADD); }
#line 8614 "parser.c"
    break;

  case 730: /* end_add: "END-ADD"  */
#line 3946 "parser.y"
                                { terminator_clear (TERM_ADD); }
#line 8620 "parser.c"
    break;

  case 731: /* $@38: %empty  */
#line 3955 "parser.y"
                                { BEGIN_STATEMENT ("ALLOCATE", 0); }
#line 8626 "parser.c"
    break;

  case 733: /* allocate_body: "Identifier" flag_initialized allocate_returning  */
#line 3961 "parser.y"
  {
	cb_emit_allocate (yyvsp[-2], yyvsp[0], NULL, yyvsp[-1]);
  }
#line 8634 "parser.c"
    break;

  case 734: /* allocate_body: expr CHARACTERS flag_initialized RETURNING target_x  */
#line 3965 "parser.y"
  {
	cb_emit_allocate (NULL, yyvsp[0], yyvsp[-4], yyvsp[-2]);
  }
#line 8642 "parser.c"
    break;

  case 735: /* allocate_returning: %empty  */
#line 3971 "parser.y"
                                { yyval = NULL; }
#line 8648 "parser.c"
    break;

  case 736: /* allocate_returning: RETURNING target_x  */
#line 3972 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8654 "parser.c"
    break;

  case 737: /* alter_statement: ALTER alter_options  */
#line 3982 "parser.y"
  {
	cb_error (_("ALTER statement is obsolete and unsupported"));
  }
#line 8662 "parser.c"
    break;

  case 742: /* $@39: %empty  */
#line 4000 "parser.y"
                                { BEGIN_STATEMENT ("CALL", TERM_CALL); }
#line 8668 "parser.c"
    break;

  case 743: /* call_statement: CALL $@39 id_or_lit_or_func call_using call_returning call_on_exception call_not_on_exception end_call  */
#line 4004 "parser.y"
  {
	cb_emit_call (yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1]);
  }
#line 8676 "parser.c"
    break;

  case 744: /* call_using: %empty  */
#line 4010 "parser.y"
                                { yyval = NULL; }
#line 8682 "parser.c"
    break;

  case 745: /* $@40: %empty  */
#line 4012 "parser.y"
  {
	call_mode = CB_CALL_BY_REFERENCE;
	size_mode = CB_SIZE_4;
  }
#line 8691 "parser.c"
    break;

  case 746: /* call_using: USING $@40 call_param_list  */
#line 4016 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8697 "parser.c"
    break;

  case 747: /* call_param_list: call_param  */
#line 4020 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8703 "parser.c"
    break;

  case 748: /* call_param_list: call_param_list call_param  */
#line 4022 "parser.y"
                                { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); }
#line 8709 "parser.c"
    break;

  case 749: /* call_param: call_type OMITTED  */
#line 4027 "parser.y"
  {
	if (call_mode != CB_CALL_BY_REFERENCE) {
		cb_error (_("OMITTED only allowed with BY REFERENCE"));
	}
	yyval = cb_build_pair (cb_int (call_mode), cb_null);
  }
#line 8720 "parser.c"
    break;

  case 750: /* call_param: call_type size_optional x  */
#line 4034 "parser.y"
  {
	yyval = cb_build_pair (cb_int (call_mode), yyvsp[0]);
	CB_SIZES (yyval) = size_mode;
  }
#line 8729 "parser.c"
    break;

  case 752: /* call_type: _by REFERENCE  */
#line 4043 "parser.y"
  {
	call_mode = CB_CALL_BY_REFERENCE;
  }
#line 8737 "parser.c"
    break;

  case 753: /* call_type: _by CONTENT  */
#line 4047 "parser.y"
  {
	if (current_program->flag_chained) {
		cb_error (_("BY CONTENT not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_CONTENT;
	}
  }
#line 8749 "parser.c"
    break;

  case 754: /* call_type: _by VALUE  */
#line 4055 "parser.y"
  {
	if (current_program->flag_chained) {
		cb_error (_("BY VALUE not allowed in CHAINED program"));
	} else {
		call_mode = CB_CALL_BY_VALUE;
	}
  }
#line 8761 "parser.c"
    break;

  case 755: /* call_returning: %empty  */
#line 4065 "parser.y"
                                { yyval = NULL; }
#line 8767 "parser.c"
    break;

  case 756: /* call_returning: RETURNING identifier  */
#line 4066 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8773 "parser.c"
    break;

  case 757: /* call_returning: GIVING identifier  */
#line 4067 "parser.y"
                                { yyval = yyvsp[0]; }
#line 8779 "parser.c"
    break;

  case 758: /* call_on_exception: %empty  */
#line 4072 "parser.y"
  {
	yyval = NULL;
  }
#line 8787 "parser.c"
    break;

  case 759: /* $@41: %empty  */
#line 4076 "parser.y"
  {
	check_unreached = 0;
  }
#line 8795 "parser.c"
    break;

  case 760: /* call_on_exception: exception_or_overflow $@41 statement_list  */
#line 4080 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 8803 "parser.c"
    break;

  case 761: /* call_not_on_exception: %empty  */
#line 4087 "parser.y"
  {
	yyval = NULL;
  }
#line 8811 "parser.c"
    break;

  case 762: /* $@42: %empty  */
#line 4091 "parser.y"
  {
	check_unreached = 0;
  }
#line 8819 "parser.c"
    break;

  case 763: /* call_not_on_exception: not_exception_or_overflow $@42 statement_list  */
#line 4095 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 8827 "parser.c"
    break;

  case 764: /* end_call: %empty  */
#line 4101 "parser.y"
                                { terminator_warning (TERM_CALL); }
#line 8833 "parser.c"
    break;

  case 765: /* end_call: "END-CALL"  */
#line 4102 "parser.y"
                                { terminator_clear (TERM_CALL); }
#line 8839 "parser.c"
    break;

  case 766: /* $@43: %empty  */
#line 4111 "parser.y"
                                { BEGIN_STATEMENT ("CANCEL", 0); }
#line 8845 "parser.c"
    break;

  case 769: /* cancel_list: cancel_list id_or_lit  */
#line 4117 "parser.y"
  {
	cb_emit_cancel (yyvsp[0]);
  }
#line 8853 "parser.c"
    break;

  case 770: /* $@44: %empty  */
#line 4128 "parser.y"
                                { BEGIN_STATEMENT ("CLOSE", 0); }
#line 8859 "parser.c"
    break;

  case 773: /* close_list: close_list file_name close_option  */
#line 4135 "parser.y"
  {
	BEGIN_IMPLICIT_STATEMENT ();
	if (yyvsp[-1] != cb_error_node) {
		cb_emit_close (yyvsp[-1], yyvsp[0]);
	}
  }
#line 8870 "parser.c"
    break;

  case 774: /* close_option: %empty  */
#line 4144 "parser.y"
                                { yyval = cb_int (COB_CLOSE_NORMAL); }
#line 8876 "parser.c"
    break;

  case 775: /* close_option: reel_or_unit  */
#line 4145 "parser.y"
                                { yyval = cb_int (COB_CLOSE_UNIT); }
#line 8882 "parser.c"
    break;

  case 776: /* close_option: reel_or_unit _for REMOVAL  */
#line 4146 "parser.y"
                                { yyval = cb_int (COB_CLOSE_UNIT_REMOVAL); }
#line 8888 "parser.c"
    break;

  case 777: /* close_option: _with NO REWIND  */
#line 4147 "parser.y"
                                { yyval = cb_int (COB_CLOSE_NO_REWIND); }
#line 8894 "parser.c"
    break;

  case 778: /* close_option: _with LOCK  */
#line 4148 "parser.y"
                                { yyval = cb_int (COB_CLOSE_LOCK); }
#line 8900 "parser.c"
    break;

  case 781: /* $@45: %empty  */
#line 4159 "parser.y"
                                { BEGIN_STATEMENT ("COMPUTE", TERM_COMPUTE); }
#line 8906 "parser.c"
    break;

  case 783: /* compute_body: arithmetic_x_list comp_equal expr on_size_error  */
#line 4166 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-3], 0, yyvsp[-1]);
  }
#line 8914 "parser.c"
    break;

  case 784: /* end_compute: %empty  */
#line 4172 "parser.y"
                                { terminator_warning (TERM_COMPUTE); }
#line 8920 "parser.c"
    break;

  case 785: /* end_compute: "END-COMPUTE"  */
#line 4173 "parser.y"
                                { terminator_clear (TERM_COMPUTE); }
#line 8926 "parser.c"
    break;

  case 788: /* commit_statement: COMMIT  */
#line 4184 "parser.y"
  {
	BEGIN_STATEMENT ("COMMIT", 0);
	cb_emit_commit ();
  }
#line 8935 "parser.c"
    break;

  case 789: /* continue_statement: CONTINUE  */
#line 4197 "parser.y"
  {
	BEGIN_STATEMENT ("CONTINUE", 0);
	cb_emit_continue ();
  }
#line 8944 "parser.c"
    break;

  case 790: /* $@46: %empty  */
#line 4209 "parser.y"
                                { BEGIN_STATEMENT ("DELETE", TERM_DELETE); }
#line 8950 "parser.c"
    break;

  case 791: /* delete_statement: DELETE $@46 file_name _record opt_invalid_key end_delete  */
#line 4212 "parser.y"
  {
	if (yyvsp[-3] != cb_error_node) {
		cb_emit_delete (yyvsp[-3]);
	}
  }
#line 8960 "parser.c"
    break;

  case 792: /* end_delete: %empty  */
#line 4220 "parser.y"
                                { terminator_warning (TERM_DELETE); }
#line 8966 "parser.c"
    break;

  case 793: /* end_delete: "END-DELETE"  */
#line 4221 "parser.y"
                                { terminator_clear (TERM_DELETE); }
#line 8972 "parser.c"
    break;

  case 794: /* $@47: %empty  */
#line 4231 "parser.y"
  {
	BEGIN_STATEMENT ("DISPLAY", TERM_DISPLAY);
	dispattrs = 0;
	fgc = NULL;
	bgc = NULL;
	scroll = NULL;
  }
#line 8984 "parser.c"
    break;

  case 796: /* display_body: id_or_lit "UPON ENVIRONMENT-NAME" on_disp_exception  */
#line 4244 "parser.y"
  {
	cb_emit_env_name (yyvsp[-2]);
  }
#line 8992 "parser.c"
    break;

  case 797: /* display_body: id_or_lit "UPON ENVIRONMENT-VALUE" on_disp_exception  */
#line 4248 "parser.y"
  {
	cb_emit_env_value (yyvsp[-2]);
  }
#line 9000 "parser.c"
    break;

  case 798: /* display_body: id_or_lit "UPON ARGUMENT-NUMBER" on_disp_exception  */
#line 4252 "parser.y"
  {
	cb_emit_arg_number (yyvsp[-2]);
  }
#line 9008 "parser.c"
    break;

  case 799: /* display_body: id_or_lit "UPON COMMAND-LINE" on_disp_exception  */
#line 4256 "parser.y"
  {
	cb_emit_command_line (yyvsp[-2]);
  }
#line 9016 "parser.c"
    break;

  case 800: /* display_body: x_list opt_at_line_column display_upon with_clause on_disp_exception  */
#line 4260 "parser.y"
  {
	cb_emit_display (yyvsp[-4], yyvsp[-2], yyvsp[-1], yyvsp[-3], fgc, bgc, scroll, dispattrs);
  }
#line 9024 "parser.c"
    break;

  case 801: /* display_upon: %empty  */
#line 4266 "parser.y"
                                { yyval = cb_int0; }
#line 9030 "parser.c"
    break;

  case 802: /* display_upon: UPON mnemonic_name  */
#line 4267 "parser.y"
                                { yyval = cb_build_display_upon (yyvsp[0]); }
#line 9036 "parser.c"
    break;

  case 803: /* display_upon: UPON "Identifier"  */
#line 4268 "parser.y"
                                { yyval = cb_build_display_upon_direct (yyvsp[0]); }
#line 9042 "parser.c"
    break;

  case 804: /* display_upon: UPON PRINTER  */
#line 4269 "parser.y"
                                { yyval = cb_int0; }
#line 9048 "parser.c"
    break;

  case 805: /* display_upon: UPON CRT  */
#line 4270 "parser.y"
                                { yyval = cb_int0; }
#line 9054 "parser.c"
    break;

  case 806: /* with_clause: %empty  */
#line 4274 "parser.y"
                                { yyval = cb_int1; }
#line 9060 "parser.c"
    break;

  case 807: /* with_clause: _with "NO ADVANCING"  */
#line 4275 "parser.y"
                                { yyval = cb_int0; }
#line 9066 "parser.c"
    break;

  case 808: /* with_clause: WITH disp_attrs  */
#line 4276 "parser.y"
                                { yyval = cb_int1; }
#line 9072 "parser.c"
    break;

  case 811: /* disp_attr: BELL  */
#line 4286 "parser.y"
                { dispattrs |= COB_SCREEN_BELL; }
#line 9078 "parser.c"
    break;

  case 812: /* disp_attr: BLINK  */
#line 4287 "parser.y"
                { dispattrs |= COB_SCREEN_BLINK; }
#line 9084 "parser.c"
    break;

  case 813: /* disp_attr: ERASE EOL  */
#line 4288 "parser.y"
                { dispattrs |= COB_SCREEN_ERASE_EOL; }
#line 9090 "parser.c"
    break;

  case 814: /* disp_attr: ERASE EOS  */
#line 4289 "parser.y"
                { dispattrs |= COB_SCREEN_ERASE_EOS; }
#line 9096 "parser.c"
    break;

  case 815: /* disp_attr: HIGHLIGHT  */
#line 4290 "parser.y"
                { dispattrs |= COB_SCREEN_HIGHLIGHT; }
#line 9102 "parser.c"
    break;

  case 816: /* disp_attr: LOWLIGHT  */
#line 4291 "parser.y"
                { dispattrs |= COB_SCREEN_LOWLIGHT; }
#line 9108 "parser.c"
    break;

  case 817: /* disp_attr: "REVERSE-VIDEO"  */
#line 4292 "parser.y"
                { dispattrs |= COB_SCREEN_REVERSE; }
#line 9114 "parser.c"
    break;

  case 818: /* disp_attr: UNDERLINE  */
#line 4293 "parser.y"
                { dispattrs |= COB_SCREEN_UNDERLINE; }
#line 9120 "parser.c"
    break;

  case 819: /* disp_attr: OVERLINE  */
#line 4294 "parser.y"
                { dispattrs |= COB_SCREEN_OVERLINE; }
#line 9126 "parser.c"
    break;

  case 820: /* disp_attr: "FOREGROUND-COLOR" _is num_id_or_lit  */
#line 4296 "parser.y"
  {
	fgc = yyvsp[0];
  }
#line 9134 "parser.c"
    break;

  case 821: /* disp_attr: "BACKGROUND-COLOR" _is num_id_or_lit  */
#line 4300 "parser.y"
  {
	bgc = yyvsp[0];
  }
#line 9142 "parser.c"
    break;

  case 822: /* disp_attr: SCROLL UP _opt_scroll_lines  */
#line 4304 "parser.y"
  {
	scroll = yyvsp[0];
  }
#line 9150 "parser.c"
    break;

  case 823: /* disp_attr: SCROLL DOWN _opt_scroll_lines  */
#line 4308 "parser.y"
  {
	dispattrs |= COB_SCREEN_SCROLL_DOWN;
	scroll = yyvsp[0];
  }
#line 9159 "parser.c"
    break;

  case 824: /* disp_attr: "BLANK-LINE"  */
#line 4312 "parser.y"
                { dispattrs |= COB_SCREEN_BLANK_LINE; }
#line 9165 "parser.c"
    break;

  case 825: /* disp_attr: "BLANK-SCREEN"  */
#line 4313 "parser.y"
                { dispattrs |= COB_SCREEN_BLANK_SCREEN; }
#line 9171 "parser.c"
    break;

  case 826: /* end_display: %empty  */
#line 4317 "parser.y"
                                { terminator_warning (TERM_DISPLAY); }
#line 9177 "parser.c"
    break;

  case 827: /* end_display: "END-DISPLAY"  */
#line 4318 "parser.y"
                                { terminator_clear (TERM_DISPLAY); }
#line 9183 "parser.c"
    break;

  case 828: /* $@48: %empty  */
#line 4327 "parser.y"
                                { BEGIN_STATEMENT ("DIVIDE", TERM_DIVIDE); }
#line 9189 "parser.c"
    break;

  case 830: /* divide_body: x INTO arithmetic_x_list on_size_error  */
#line 4334 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], '/', yyvsp[-3]);
  }
#line 9197 "parser.c"
    break;

  case 831: /* divide_body: x INTO x GIVING arithmetic_x_list on_size_error  */
#line 4338 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_op (yyvsp[-3], '/', yyvsp[-5]));
  }
#line 9205 "parser.c"
    break;

  case 832: /* divide_body: x BY x GIVING arithmetic_x_list on_size_error  */
#line 4342 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_op (yyvsp[-5], '/', yyvsp[-3]));
  }
#line 9213 "parser.c"
    break;

  case 833: /* divide_body: x INTO x GIVING arithmetic_x REMAINDER arithmetic_x on_size_error  */
#line 4346 "parser.y"
  {
	cb_emit_divide (yyvsp[-5], yyvsp[-7], yyvsp[-3], yyvsp[-1]);
  }
#line 9221 "parser.c"
    break;

  case 834: /* divide_body: x BY x GIVING arithmetic_x REMAINDER arithmetic_x on_size_error  */
#line 4350 "parser.y"
  {
	cb_emit_divide (yyvsp[-7], yyvsp[-5], yyvsp[-3], yyvsp[-1]);
  }
#line 9229 "parser.c"
    break;

  case 835: /* end_divide: %empty  */
#line 4356 "parser.y"
                                { terminator_warning (TERM_DIVIDE); }
#line 9235 "parser.c"
    break;

  case 836: /* end_divide: "END-DIVIDE"  */
#line 4357 "parser.y"
                                { terminator_clear (TERM_DIVIDE); }
#line 9241 "parser.c"
    break;

  case 837: /* $@49: %empty  */
#line 4366 "parser.y"
                                { BEGIN_STATEMENT ("ENTRY", 0); }
#line 9247 "parser.c"
    break;

  case 838: /* entry_statement: ENTRY $@49 "Literal" call_using  */
#line 4368 "parser.y"
  {
	if (current_program->nested_level) {
		cb_error (_("ENTRY is invalid in nested program"));
	} else if (cb_verify (cb_entry_statement, "ENTRY")) {
		if (cobc_check_valid_name ((char *)(CB_LITERAL (yyvsp[-1])->data))) {
			cb_error (_("ENTRY '%s' invalid"), (char *)(CB_LITERAL (yyvsp[-1])->data));
		}
		emit_entry ((char *)(CB_LITERAL (yyvsp[-1])->data), 1, yyvsp[0]);
	}
	check_unreached = 0;
  }
#line 9263 "parser.c"
    break;

  case 839: /* $@50: %empty  */
#line 4388 "parser.y"
  {
	BEGIN_STATEMENT ("EVALUATE", TERM_EVALUATE);
	eval_level++;
	for (eval_inc = 0; eval_inc < 64; eval_inc++) {
		eval_check[eval_level][eval_inc] = 0;
	}
	eval_inc = 0;
	eval_inc2 = 0;
  }
#line 9277 "parser.c"
    break;

  case 840: /* evaluate_statement: EVALUATE $@50 evaluate_subject_list evaluate_condition_list end_evaluate  */
#line 4399 "parser.y"
  {
	cb_emit_evaluate (yyvsp[-2], yyvsp[-1]);
	eval_level--;
  }
#line 9286 "parser.c"
    break;

  case 841: /* evaluate_subject_list: evaluate_subject  */
#line 4406 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 9292 "parser.c"
    break;

  case 842: /* evaluate_subject_list: evaluate_subject_list ALSO evaluate_subject  */
#line 4408 "parser.y"
                                { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); }
#line 9298 "parser.c"
    break;

  case 843: /* evaluate_subject: expr  */
#line 4413 "parser.y"
  {
	yyval = yyvsp[0];
	if (CB_REFERENCE_P (yyvsp[0])) {
		eval_check[eval_level][eval_inc++] = 0;
	} else {
		eval_check[eval_level][eval_inc++] = 1;
	}
  }
#line 9311 "parser.c"
    break;

  case 844: /* evaluate_subject: "TRUE"  */
#line 4422 "parser.y"
  {
	yyval = cb_true;
	eval_check[eval_level][eval_inc++] = 2;
  }
#line 9320 "parser.c"
    break;

  case 845: /* evaluate_subject: "FALSE"  */
#line 4427 "parser.y"
  {
	yyval = cb_false;
	eval_check[eval_level][eval_inc++] = 3;
  }
#line 9329 "parser.c"
    break;

  case 846: /* evaluate_condition_list: evaluate_case_list evaluate_other  */
#line 4435 "parser.y"
  {
	yyval = yyvsp[-1];
	if (yyvsp[0]) {
		yyval = cb_list_add (yyval, yyvsp[0]);
	}
  }
#line 9340 "parser.c"
    break;

  case 847: /* evaluate_case_list: evaluate_case  */
#line 4444 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 9346 "parser.c"
    break;

  case 848: /* evaluate_case_list: evaluate_case_list evaluate_case  */
#line 4446 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 9352 "parser.c"
    break;

  case 849: /* $@51: %empty  */
#line 4451 "parser.y"
  {
	check_unreached = 0;
  }
#line 9360 "parser.c"
    break;

  case 850: /* evaluate_case: evaluate_when_list $@51 statement_list  */
#line 4455 "parser.y"
  {
	yyval = cb_cons (yyvsp[0], yyvsp[-2]);
	eval_inc2 = 0;
  }
#line 9369 "parser.c"
    break;

  case 851: /* evaluate_other: %empty  */
#line 4463 "parser.y"
  {
	yyval = NULL;
  }
#line 9377 "parser.c"
    break;

  case 852: /* $@52: %empty  */
#line 4467 "parser.y"
  {
	check_unreached = 0;
  }
#line 9385 "parser.c"
    break;

  case 853: /* evaluate_other: WHEN OTHER $@52 statement_list  */
#line 4471 "parser.y"
  {
	yyval = cb_cons (yyvsp[0], NULL);
	eval_inc2 = 0;
  }
#line 9394 "parser.c"
    break;

  case 854: /* evaluate_when_list: WHEN evaluate_object_list  */
#line 4478 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 9400 "parser.c"
    break;

  case 855: /* evaluate_when_list: evaluate_when_list WHEN evaluate_object_list  */
#line 4480 "parser.y"
                                { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); }
#line 9406 "parser.c"
    break;

  case 856: /* evaluate_object_list: evaluate_object  */
#line 4484 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 9412 "parser.c"
    break;

  case 857: /* evaluate_object_list: evaluate_object_list ALSO evaluate_object  */
#line 4486 "parser.y"
                                { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); }
#line 9418 "parser.c"
    break;

  case 858: /* evaluate_object: partial_expr opt_evaluate_thru_expr  */
#line 4491 "parser.y"
  {
	cb_tree not;
	cb_tree e1;
	cb_tree e2;

	not = cb_int0;
	e2 = yyvsp[0];
	/* in case the first token is NOT */
	if (CB_PURPOSE_INT (yyvsp[-1]) == '!') {
		if (eval_check[eval_level][eval_inc2] < 2) {
			not = cb_int1;
			yyvsp[-1] = CB_CHAIN (yyvsp[-1]);
		}
	}

	/* build expr now */
	e1 = cb_build_expr (yyvsp[-1]);

	if (e2 == NULL) {
		/* WHEN expr */
		eval_inc2++;
		yyval = cb_build_pair (not, cb_build_pair (e1, NULL));
	} else {
		/* WHEN expr THRU expr */
		yyval = cb_build_pair (not, cb_build_pair (e1, e2));
		eval_inc2++;
	}
  }
#line 9451 "parser.c"
    break;

  case 859: /* evaluate_object: ANY  */
#line 4519 "parser.y"
                                { yyval = cb_any; eval_inc2++; }
#line 9457 "parser.c"
    break;

  case 860: /* evaluate_object: "TRUE"  */
#line 4520 "parser.y"
                                { yyval = cb_true; eval_inc2++; }
#line 9463 "parser.c"
    break;

  case 861: /* evaluate_object: "FALSE"  */
#line 4521 "parser.y"
                                { yyval = cb_false; eval_inc2++; }
#line 9469 "parser.c"
    break;

  case 862: /* opt_evaluate_thru_expr: %empty  */
#line 4524 "parser.y"
                                { yyval = NULL; }
#line 9475 "parser.c"
    break;

  case 863: /* opt_evaluate_thru_expr: THRU expr  */
#line 4525 "parser.y"
                                { yyval = yyvsp[0]; }
#line 9481 "parser.c"
    break;

  case 864: /* end_evaluate: %empty  */
#line 4529 "parser.y"
                                { terminator_warning (TERM_EVALUATE); }
#line 9487 "parser.c"
    break;

  case 865: /* end_evaluate: "END-EVALUATE"  */
#line 4530 "parser.y"
                                { terminator_clear (TERM_EVALUATE); }
#line 9493 "parser.c"
    break;

  case 866: /* $@53: %empty  */
#line 4539 "parser.y"
                                { BEGIN_STATEMENT ("EXIT", 0); }
#line 9499 "parser.c"
    break;

  case 868: /* exit_body: %empty  */
#line 4544 "parser.y"
                                { /* nothing */ }
#line 9505 "parser.c"
    break;

  case 869: /* exit_body: PROGRAM  */
#line 4546 "parser.y"
  {
	if (in_declaratives && use_global_ind) {
		cb_error (_("EXIT PROGRAM is not allowed within a USE GLOBAL procedure"));
	}
	check_unreached = 1;
	cb_emit_exit (0);
  }
#line 9517 "parser.c"
    break;

  case 870: /* exit_body: PERFORM  */
#line 4554 "parser.y"
  {
	struct cb_perform	*p;
	char			name[64];

	if (!perform_stack) {
		cb_error (_("EXIT PERFORM is only valid with inline PERFORM"));
	} else {
		p = CB_PERFORM (CB_VALUE (perform_stack));
		if (!p->exit_label) {
			sprintf (name, "EXIT PERFORM %d", cb_id);
			p->exit_label = cb_build_reference (name);
			CB_LABEL (cb_build_label (p->exit_label, NULL))->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (p->exit_label), NULL);
	}
  }
#line 9538 "parser.c"
    break;

  case 871: /* exit_body: PERFORM CYCLE  */
#line 4571 "parser.y"
  {
	struct cb_perform	*p;
	char			name[64];

	if (!perform_stack) {
		cb_error (_("EXIT PERFORM is only valid with inline PERFORM"));
	} else {
		p = CB_PERFORM (CB_VALUE (perform_stack));
		if (!p->cycle_label) {
			sprintf (name, "EXIT PERFORM CYCLE %d", cb_id);
			p->cycle_label = cb_build_reference (name);
			CB_LABEL (cb_build_label (p->cycle_label, NULL))->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (p->cycle_label), NULL);
	}
  }
#line 9559 "parser.c"
    break;

  case 872: /* exit_body: SECTION  */
#line 4588 "parser.y"
  {
	cb_tree	plabel;
	char	name[64];

	if (!current_section) {
		cb_error (_("EXIT SECTION is only valid with an active SECTION"));
	} else {
		if (!current_section->exit_label) {
			sprintf (name, "EXIT SECTION %d", cb_id);
			plabel = cb_build_reference (name);
			current_section->exit_label = cb_build_label (plabel, NULL);
			current_section->exit_label_ref = plabel;
			CB_LABEL (current_section->exit_label)->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (current_section->exit_label_ref), NULL);
	}
  }
#line 9581 "parser.c"
    break;

  case 873: /* exit_body: PARAGRAPH  */
#line 4606 "parser.y"
  {
	cb_tree	plabel;
	char	name[64];

	if (!current_paragraph) {
		cb_error (_("EXIT PARAGRAPH is only valid with an active PARAGRAPH"));
	} else {
		if (!current_paragraph->exit_label) {
			sprintf (name, "EXIT PARAGRAPH %d", cb_id);
			plabel = cb_build_reference (name);
			current_paragraph->exit_label = cb_build_label (plabel, NULL);
			current_paragraph->exit_label_ref = plabel;
			CB_LABEL (current_paragraph->exit_label)->need_begin = 1;
		}
		cb_emit_goto (cb_list_init (current_paragraph->exit_label_ref), NULL);
	}
  }
#line 9603 "parser.c"
    break;

  case 874: /* $@54: %empty  */
#line 4630 "parser.y"
                                { BEGIN_STATEMENT ("FREE", 0); }
#line 9609 "parser.c"
    break;

  case 875: /* free_statement: FREE $@54 target_x_list  */
#line 4632 "parser.y"
  {
	cb_emit_free (yyvsp[0]);
  }
#line 9617 "parser.c"
    break;

  case 876: /* $@55: %empty  */
#line 4643 "parser.y"
                                { BEGIN_STATEMENT ("GENERATE", 0); }
#line 9623 "parser.c"
    break;

  case 877: /* generate_statement: GENERATE $@55 identifier  */
#line 4645 "parser.y"
  {
	PENDING("GENERATE");
  }
#line 9631 "parser.c"
    break;

  case 878: /* $@56: %empty  */
#line 4656 "parser.y"
                                { BEGIN_STATEMENT ("GO TO", 0); }
#line 9637 "parser.c"
    break;

  case 879: /* goto_statement: GO _to $@56 procedure_name_list goto_depending  */
#line 4658 "parser.y"
  {
	cb_emit_goto (yyvsp[-1], yyvsp[0]);
  }
#line 9645 "parser.c"
    break;

  case 880: /* goto_depending: %empty  */
#line 4665 "parser.y"
  {
	check_unreached = 1;
	yyval = NULL;
  }
#line 9654 "parser.c"
    break;

  case 881: /* goto_depending: DEPENDING _on identifier  */
#line 4670 "parser.y"
  {
	check_unreached = 0;
	yyval = yyvsp[0];
  }
#line 9663 "parser.c"
    break;

  case 882: /* $@57: %empty  */
#line 4682 "parser.y"
                                { BEGIN_STATEMENT ("GOBACK", 0); }
#line 9669 "parser.c"
    break;

  case 883: /* goback_statement: GOBACK $@57  */
#line 4683 "parser.y"
  {
	check_unreached = 1;
	cb_emit_exit (1);
  }
#line 9678 "parser.c"
    break;

  case 884: /* $@58: %empty  */
#line 4695 "parser.y"
                                { BEGIN_STATEMENT ("IF", TERM_IF); }
#line 9684 "parser.c"
    break;

  case 885: /* $@59: %empty  */
#line 4697 "parser.y"
  {
	check_unreached = 0;
  }
#line 9692 "parser.c"
    break;

  case 886: /* if_statement: IF $@58 condition _then $@59 statement_list if_else_sentence end_if  */
#line 4702 "parser.y"
  {
	cb_emit_if (yyvsp[-5], yyvsp[-2], yyvsp[-1]);
  }
#line 9700 "parser.c"
    break;

  case 888: /* if_else_sentence: %empty  */
#line 4710 "parser.y"
  {
	yyval = NULL;
  }
#line 9708 "parser.c"
    break;

  case 889: /* $@60: %empty  */
#line 4714 "parser.y"
  {
	check_unreached = 0;
  }
#line 9716 "parser.c"
    break;

  case 890: /* if_else_sentence: ELSE $@60 statement_list  */
#line 4718 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 9724 "parser.c"
    break;

  case 891: /* end_if: %empty  */
#line 4724 "parser.y"
                                { terminator_warning (TERM_IF); }
#line 9730 "parser.c"
    break;

  case 892: /* end_if: "END-IF"  */
#line 4725 "parser.y"
                                { terminator_clear (TERM_IF); }
#line 9736 "parser.c"
    break;

  case 893: /* $@61: %empty  */
#line 4734 "parser.y"
                                { BEGIN_STATEMENT ("INITIALIZE", 0); }
#line 9742 "parser.c"
    break;

  case 894: /* initialize_statement: INITIALIZE $@61 target_x_list initialize_filler initialize_value initialize_replacing initialize_default  */
#line 4736 "parser.y"
  {
	cb_emit_initialize (yyvsp[-4], yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
  }
#line 9750 "parser.c"
    break;

  case 895: /* initialize_filler: %empty  */
#line 4742 "parser.y"
                                { yyval = NULL; }
#line 9756 "parser.c"
    break;

  case 896: /* initialize_filler: _with FILLER  */
#line 4743 "parser.y"
                                { yyval = cb_true; }
#line 9762 "parser.c"
    break;

  case 897: /* initialize_value: %empty  */
#line 4747 "parser.y"
                                { yyval = NULL; }
#line 9768 "parser.c"
    break;

  case 898: /* initialize_value: ALL _to VALUE  */
#line 4748 "parser.y"
                                { yyval = cb_true; }
#line 9774 "parser.c"
    break;

  case 899: /* initialize_value: initialize_category _to VALUE  */
#line 4749 "parser.y"
                                { yyval = yyvsp[-2]; }
#line 9780 "parser.c"
    break;

  case 900: /* initialize_replacing: %empty  */
#line 4753 "parser.y"
                                { yyval = NULL; }
#line 9786 "parser.c"
    break;

  case 901: /* initialize_replacing: REPLACING initialize_replacing_list  */
#line 4755 "parser.y"
                                { yyval = yyvsp[0]; }
#line 9792 "parser.c"
    break;

  case 902: /* initialize_replacing_list: initialize_replacing_item  */
#line 4759 "parser.y"
                                { yyval = yyvsp[0]; }
#line 9798 "parser.c"
    break;

  case 903: /* initialize_replacing_list: initialize_replacing_list initialize_replacing_item  */
#line 4761 "parser.y"
                                { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); }
#line 9804 "parser.c"
    break;

  case 904: /* initialize_replacing_item: initialize_category _data BY x  */
#line 4765 "parser.y"
                                 { yyval = cb_build_pair (yyvsp[-3], yyvsp[0]); }
#line 9810 "parser.c"
    break;

  case 905: /* initialize_category: ALPHABETIC  */
#line 4769 "parser.y"
                        { yyval = cb_int (CB_CATEGORY_ALPHABETIC); }
#line 9816 "parser.c"
    break;

  case 906: /* initialize_category: ALPHANUMERIC  */
#line 4770 "parser.y"
                        { yyval = cb_int (CB_CATEGORY_ALPHANUMERIC); }
#line 9822 "parser.c"
    break;

  case 907: /* initialize_category: NUMERIC  */
#line 4771 "parser.y"
                        { yyval = cb_int (CB_CATEGORY_NUMERIC); }
#line 9828 "parser.c"
    break;

  case 908: /* initialize_category: "ALPHANUMERIC-EDITED"  */
#line 4772 "parser.y"
                        { yyval = cb_int (CB_CATEGORY_ALPHANUMERIC_EDITED); }
#line 9834 "parser.c"
    break;

  case 909: /* initialize_category: "NUMERIC-EDITED"  */
#line 4773 "parser.y"
                        { yyval = cb_int (CB_CATEGORY_NUMERIC_EDITED); }
#line 9840 "parser.c"
    break;

  case 910: /* initialize_category: NATIONAL  */
#line 4774 "parser.y"
                        { yyval = cb_int (CB_CATEGORY_NATIONAL); }
#line 9846 "parser.c"
    break;

  case 911: /* initialize_category: "NATIONAL-EDITED"  */
#line 4775 "parser.y"
                        { yyval = cb_int (CB_CATEGORY_NATIONAL_EDITED); }
#line 9852 "parser.c"
    break;

  case 912: /* initialize_default: %empty  */
#line 4779 "parser.y"
                                { yyval = NULL; }
#line 9858 "parser.c"
    break;

  case 913: /* initialize_default: DEFAULT  */
#line 4780 "parser.y"
                                { yyval = cb_true; }
#line 9864 "parser.c"
    break;

  case 914: /* $@62: %empty  */
#line 4789 "parser.y"
                                { BEGIN_STATEMENT ("INITIATE", 0); }
#line 9870 "parser.c"
    break;

  case 915: /* initiate_statement: INITIATE $@62 identifier_list  */
#line 4791 "parser.y"
  {
	PENDING("INITIATE");
  }
#line 9878 "parser.c"
    break;

  case 916: /* $@63: %empty  */
#line 4802 "parser.y"
  {
	BEGIN_STATEMENT ("INSPECT", 0);
	sending_id = 0;
	inspect_keyword = 0;
  }
#line 9888 "parser.c"
    break;

  case 918: /* send_identifier: identifier  */
#line 4811 "parser.y"
                                { save_tree_1 = yyvsp[0]; sending_id = 0; }
#line 9894 "parser.c"
    break;

  case 919: /* send_identifier: literal  */
#line 4812 "parser.y"
                                { save_tree_1 = yyvsp[0]; sending_id = 1; }
#line 9900 "parser.c"
    break;

  case 920: /* send_identifier: function  */
#line 4813 "parser.y"
                                { save_tree_1 = yyvsp[0]; sending_id = 1; }
#line 9906 "parser.c"
    break;

  case 923: /* inspect_item: inspect_tallying  */
#line 4822 "parser.y"
                                { cb_emit_inspect (save_tree_1, yyvsp[0], cb_int0, 0); }
#line 9912 "parser.c"
    break;

  case 924: /* inspect_item: inspect_replacing  */
#line 4823 "parser.y"
                                { cb_emit_inspect (save_tree_1, yyvsp[0], cb_int1, 1); }
#line 9918 "parser.c"
    break;

  case 925: /* inspect_item: inspect_converting  */
#line 4824 "parser.y"
                                { cb_emit_inspect (save_tree_1, yyvsp[0], cb_int0, 2); }
#line 9924 "parser.c"
    break;

  case 926: /* $@64: %empty  */
#line 4830 "parser.y"
                                { cb_init_tarrying (); }
#line 9930 "parser.c"
    break;

  case 927: /* inspect_tallying: TALLYING $@64 tallying_list  */
#line 4831 "parser.y"
                                { yyval = yyvsp[0]; }
#line 9936 "parser.c"
    break;

  case 928: /* tallying_list: tallying_item  */
#line 4835 "parser.y"
                                { yyval = yyvsp[0]; }
#line 9942 "parser.c"
    break;

  case 929: /* tallying_list: tallying_list tallying_item  */
#line 4836 "parser.y"
                                { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); }
#line 9948 "parser.c"
    break;

  case 930: /* tallying_item: simple_value FOR  */
#line 4840 "parser.y"
                                { yyval = cb_build_tarrying_data (yyvsp[-1]); }
#line 9954 "parser.c"
    break;

  case 931: /* tallying_item: CHARACTERS inspect_region  */
#line 4841 "parser.y"
                                { yyval = cb_build_tarrying_characters (yyvsp[0]); }
#line 9960 "parser.c"
    break;

  case 932: /* tallying_item: ALL  */
#line 4842 "parser.y"
                                { yyval = cb_build_tarrying_all (); }
#line 9966 "parser.c"
    break;

  case 933: /* tallying_item: LEADING  */
#line 4843 "parser.y"
                                { yyval = cb_build_tarrying_leading (); }
#line 9972 "parser.c"
    break;

  case 934: /* tallying_item: TRAILING  */
#line 4844 "parser.y"
                                { yyval = cb_build_tarrying_trailing (); }
#line 9978 "parser.c"
    break;

  case 935: /* tallying_item: simple_value inspect_region  */
#line 4845 "parser.y"
                                { yyval = cb_build_tarrying_value (yyvsp[-1], yyvsp[0]); }
#line 9984 "parser.c"
    break;

  case 936: /* inspect_replacing: REPLACING replacing_list  */
#line 4851 "parser.y"
                                { yyval = yyvsp[0]; inspect_keyword = 0; }
#line 9990 "parser.c"
    break;

  case 937: /* replacing_list: replacing_item  */
#line 4855 "parser.y"
                                { yyval = yyvsp[0]; }
#line 9996 "parser.c"
    break;

  case 938: /* replacing_list: replacing_list replacing_item  */
#line 4856 "parser.y"
                                { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); }
#line 10002 "parser.c"
    break;

  case 939: /* replacing_item: CHARACTERS BY simple_value inspect_region  */
#line 4861 "parser.y"
  {
	yyval = cb_build_replacing_characters (yyvsp[-1], yyvsp[0]);
	inspect_keyword = 0;
  }
#line 10011 "parser.c"
    break;

  case 940: /* replacing_item: rep_keyword replacing_region  */
#line 4865 "parser.y"
                                        { yyval = yyvsp[0]; }
#line 10017 "parser.c"
    break;

  case 941: /* rep_keyword: %empty  */
#line 4869 "parser.y"
                                { /* Nothing */ }
#line 10023 "parser.c"
    break;

  case 942: /* rep_keyword: ALL  */
#line 4870 "parser.y"
                                { inspect_keyword = 1; }
#line 10029 "parser.c"
    break;

  case 943: /* rep_keyword: LEADING  */
#line 4871 "parser.y"
                                { inspect_keyword = 2; }
#line 10035 "parser.c"
    break;

  case 944: /* rep_keyword: FIRST  */
#line 4872 "parser.y"
                                { inspect_keyword = 3; }
#line 10041 "parser.c"
    break;

  case 945: /* rep_keyword: TRAILING  */
#line 4873 "parser.y"
                                { inspect_keyword = 4; }
#line 10047 "parser.c"
    break;

  case 946: /* replacing_region: simple_value BY simple_all_value inspect_region  */
#line 4878 "parser.y"
  {
	switch (inspect_keyword) {
		case 1:
			yyval = cb_build_replacing_all (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		case 2:
			yyval = cb_build_replacing_leading (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		case 3:
			yyval = cb_build_replacing_first (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		case 4:
			yyval = cb_build_replacing_trailing (yyvsp[-3], yyvsp[-1], yyvsp[0]);
			break;
		default:
			cb_error (_("INSPECT missing a keyword"));
			yyval = cb_error_node;
			break;
	}
  }
#line 10072 "parser.c"
    break;

  case 947: /* inspect_converting: CONVERTING simple_value TO simple_all_value inspect_region  */
#line 4904 "parser.y"
  {
	yyval = cb_build_converting (yyvsp[-3], yyvsp[-1], yyvsp[0]);
  }
#line 10080 "parser.c"
    break;

  case 948: /* inspect_region: %empty  */
#line 4912 "parser.y"
                                { yyval = cb_build_inspect_region_start (); }
#line 10086 "parser.c"
    break;

  case 949: /* inspect_region: inspect_region before_or_after _initial x  */
#line 4914 "parser.y"
                                { yyval = cb_build_inspect_region (yyvsp[-3], yyvsp[-2], yyvsp[0]); }
#line 10092 "parser.c"
    break;

  case 952: /* $@65: %empty  */
#line 4925 "parser.y"
                                { BEGIN_STATEMENT ("MERGE", 0); }
#line 10098 "parser.c"
    break;

  case 954: /* $@66: %empty  */
#line 4935 "parser.y"
                                { BEGIN_STATEMENT ("MOVE", 0); }
#line 10104 "parser.c"
    break;

  case 956: /* move_body: x TO target_x_list  */
#line 4941 "parser.y"
  {
	cb_emit_move (yyvsp[-2], yyvsp[0]);
  }
#line 10112 "parser.c"
    break;

  case 957: /* move_body: CORRESPONDING x TO target_x_list  */
#line 4945 "parser.y"
  {
	cb_emit_move_corresponding (yyvsp[-2], yyvsp[0]);
  }
#line 10120 "parser.c"
    break;

  case 958: /* $@67: %empty  */
#line 4956 "parser.y"
                                { BEGIN_STATEMENT ("MULTIPLY", TERM_MULTIPLY); }
#line 10126 "parser.c"
    break;

  case 960: /* multiply_body: x BY arithmetic_x_list on_size_error  */
#line 4963 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], '*', yyvsp[-3]);
  }
#line 10134 "parser.c"
    break;

  case 961: /* multiply_body: x BY x GIVING arithmetic_x_list on_size_error  */
#line 4967 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_op (yyvsp[-5], '*', yyvsp[-3]));
  }
#line 10142 "parser.c"
    break;

  case 962: /* end_multiply: %empty  */
#line 4973 "parser.y"
                                { terminator_warning (TERM_MULTIPLY); }
#line 10148 "parser.c"
    break;

  case 963: /* end_multiply: "END-MULTIPLY"  */
#line 4974 "parser.y"
                                { terminator_clear (TERM_MULTIPLY); }
#line 10154 "parser.c"
    break;

  case 964: /* $@68: %empty  */
#line 4983 "parser.y"
                                { BEGIN_STATEMENT ("OPEN", 0); }
#line 10160 "parser.c"
    break;

  case 967: /* open_list: open_list open_mode open_sharing file_name_list open_option  */
#line 4990 "parser.y"
  {
	cb_tree l;
	for (l = yyvsp[-1]; l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			BEGIN_IMPLICIT_STATEMENT ();
			cb_emit_open (CB_VALUE (l), yyvsp[-3], yyvsp[-2]);
		}
	}
  }
#line 10174 "parser.c"
    break;

  case 968: /* open_mode: INPUT  */
#line 5002 "parser.y"
                                { yyval = cb_int (COB_OPEN_INPUT); }
#line 10180 "parser.c"
    break;

  case 969: /* open_mode: OUTPUT  */
#line 5003 "parser.y"
                                { yyval = cb_int (COB_OPEN_OUTPUT); }
#line 10186 "parser.c"
    break;

  case 970: /* open_mode: "I-O"  */
#line 5004 "parser.y"
                                { yyval = cb_int (COB_OPEN_I_O); }
#line 10192 "parser.c"
    break;

  case 971: /* open_mode: EXTEND  */
#line 5005 "parser.y"
                                { yyval = cb_int (COB_OPEN_EXTEND); }
#line 10198 "parser.c"
    break;

  case 972: /* open_sharing: %empty  */
#line 5009 "parser.y"
                                { yyval = NULL; }
#line 10204 "parser.c"
    break;

  case 973: /* open_sharing: SHARING _with sharing_option  */
#line 5010 "parser.y"
                                { yyval = yyvsp[0]; }
#line 10210 "parser.c"
    break;

  case 974: /* open_option: %empty  */
#line 5014 "parser.y"
                                { yyval = NULL; }
#line 10216 "parser.c"
    break;

  case 975: /* open_option: _with NO REWIND  */
#line 5015 "parser.y"
                                { yyval = NULL; }
#line 10222 "parser.c"
    break;

  case 976: /* open_option: _with LOCK  */
#line 5016 "parser.y"
                                { PENDING ("OPEN ... WITH LOCK"); }
#line 10228 "parser.c"
    break;

  case 977: /* $@69: %empty  */
#line 5028 "parser.y"
                                { BEGIN_STATEMENT ("PERFORM", TERM_PERFORM); }
#line 10234 "parser.c"
    break;

  case 979: /* perform_body: perform_procedure perform_option  */
#line 5034 "parser.y"
  {
	cb_emit_perform (yyvsp[0], yyvsp[-1]);
  }
#line 10242 "parser.c"
    break;

  case 980: /* $@70: %empty  */
#line 5038 "parser.y"
  {
	perform_stack = cb_cons (yyvsp[0], perform_stack);
	check_unreached = 0;
  }
#line 10251 "parser.c"
    break;

  case 981: /* perform_body: perform_option $@70 statement_list end_perform  */
#line 5043 "parser.y"
  {
	perform_stack = CB_CHAIN (perform_stack);
	cb_emit_perform (yyvsp[-3], yyvsp[-1]);
  }
#line 10260 "parser.c"
    break;

  case 982: /* perform_body: perform_option "END-PERFORM"  */
#line 5048 "parser.y"
  {
	cb_emit_perform (yyvsp[-1], NULL);
  }
#line 10268 "parser.c"
    break;

  case 983: /* end_perform: %empty  */
#line 5054 "parser.y"
                                { terminator_error (); }
#line 10274 "parser.c"
    break;

  case 984: /* end_perform: "END-PERFORM"  */
#line 5055 "parser.y"
                                { terminator_clear (TERM_PERFORM); }
#line 10280 "parser.c"
    break;

  case 985: /* perform_procedure: procedure_name  */
#line 5060 "parser.y"
  {
	CB_REFERENCE (yyvsp[0])->length = cb_true; /* return from $1 */
	yyval = cb_build_pair (yyvsp[0], yyvsp[0]);
  }
#line 10289 "parser.c"
    break;

  case 986: /* perform_procedure: procedure_name THRU procedure_name  */
#line 5065 "parser.y"
  {
	CB_REFERENCE (yyvsp[0])->length = cb_true; /* return from $3 */
	yyval = cb_build_pair (yyvsp[-2], yyvsp[0]);
  }
#line 10298 "parser.c"
    break;

  case 987: /* perform_option: %empty  */
#line 5073 "parser.y"
  {
	yyval = cb_build_perform_once (NULL);
  }
#line 10306 "parser.c"
    break;

  case 988: /* perform_option: FOREVER  */
#line 5077 "parser.y"
  {
	yyval = cb_build_perform_forever (NULL);
  }
#line 10314 "parser.c"
    break;

  case 989: /* perform_option: id_or_lit_or_func TIMES  */
#line 5081 "parser.y"
  {
	yyval = cb_build_perform_times (yyvsp[-1]);
	current_program->loop_counter++;
  }
#line 10323 "parser.c"
    break;

  case 990: /* perform_option: perform_test UNTIL condition  */
#line 5086 "parser.y"
  {
	cb_tree varying;

	varying = cb_list_init (cb_build_perform_varying (NULL, NULL, NULL, yyvsp[0]));
	yyval = cb_build_perform_until (yyvsp[-2], varying);
  }
#line 10334 "parser.c"
    break;

  case 991: /* perform_option: perform_test VARYING perform_varying_list  */
#line 5093 "parser.y"
  {
	yyval = cb_build_perform_until (yyvsp[-2], yyvsp[0]);
  }
#line 10342 "parser.c"
    break;

  case 992: /* perform_test: %empty  */
#line 5099 "parser.y"
                                { yyval = CB_BEFORE; }
#line 10348 "parser.c"
    break;

  case 993: /* perform_test: _with TEST before_or_after  */
#line 5100 "parser.y"
                                { yyval = yyvsp[0]; }
#line 10354 "parser.c"
    break;

  case 994: /* perform_varying_list: perform_varying  */
#line 5104 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 10360 "parser.c"
    break;

  case 995: /* perform_varying_list: perform_varying_list AFTER perform_varying  */
#line 5106 "parser.y"
                                { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); }
#line 10366 "parser.c"
    break;

  case 996: /* perform_varying: identifier FROM x BY x UNTIL condition  */
#line 5111 "parser.y"
  {
	yyval = cb_build_perform_varying (yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[0]);
  }
#line 10374 "parser.c"
    break;

  case 997: /* $@71: %empty  */
#line 5122 "parser.y"
                                { BEGIN_STATEMENT ("READ", TERM_READ); }
#line 10380 "parser.c"
    break;

  case 998: /* read_statement: READ $@71 file_name flag_next _record read_into with_lock read_key read_handler end_read  */
#line 5125 "parser.y"
  {
	if (yyvsp[-7] != cb_error_node) {
		if (yyvsp[-3] && (CB_FILE(cb_ref (yyvsp[-7]))->lock_mode & COB_LOCK_AUTOMATIC)) {
			cb_error (_("LOCK clause invalid with file LOCK AUTOMATIC"));
		} else if (yyvsp[-2] &&
		      (CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_RELATIVE &&
		       CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_INDEXED)) {
			cb_error (_("KEY clause invalid with this file type"));
		} else if (current_statement->handler_id == COB_EC_I_O_INVALID_KEY &&
		      (CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_RELATIVE &&
		       CB_FILE(cb_ref (yyvsp[-7]))->organization != COB_ORG_INDEXED)) {
			cb_error (_("INVALID KEY clause invalid with this file type"));
		} else {
			cb_emit_read (yyvsp[-7], yyvsp[-6], yyvsp[-4], yyvsp[-2], yyvsp[-3]);
		}
	}
  }
#line 10402 "parser.c"
    break;

  case 999: /* read_into: %empty  */
#line 5145 "parser.y"
                                { yyval = NULL; }
#line 10408 "parser.c"
    break;

  case 1000: /* read_into: INTO identifier  */
#line 5146 "parser.y"
                                { yyval = yyvsp[0]; }
#line 10414 "parser.c"
    break;

  case 1001: /* with_lock: %empty  */
#line 5150 "parser.y"
                                { yyval = NULL; }
#line 10420 "parser.c"
    break;

  case 1002: /* with_lock: IGNORING LOCK  */
#line 5152 "parser.y"
  {
	yyval = cb_int3;
  }
#line 10428 "parser.c"
    break;

  case 1003: /* with_lock: _with LOCK  */
#line 5156 "parser.y"
  {
	yyval = cb_int1;
  }
#line 10436 "parser.c"
    break;

  case 1004: /* with_lock: _with NO LOCK  */
#line 5160 "parser.y"
  {
	yyval = cb_int2;
  }
#line 10444 "parser.c"
    break;

  case 1005: /* with_lock: _with IGNORE LOCK  */
#line 5164 "parser.y"
  {
	yyval = cb_int3;
  }
#line 10452 "parser.c"
    break;

  case 1006: /* with_lock: _with WAIT  */
#line 5168 "parser.y"
  {
	yyval = cb_int4;
  }
#line 10460 "parser.c"
    break;

  case 1007: /* read_key: %empty  */
#line 5174 "parser.y"
                                { yyval = NULL; }
#line 10466 "parser.c"
    break;

  case 1008: /* read_key: KEY _is identifier  */
#line 5175 "parser.y"
                                { yyval = yyvsp[0]; }
#line 10472 "parser.c"
    break;

  case 1012: /* end_read: %empty  */
#line 5184 "parser.y"
                                { terminator_warning (TERM_READ); }
#line 10478 "parser.c"
    break;

  case 1013: /* end_read: "END-READ"  */
#line 5185 "parser.y"
                                { terminator_clear (TERM_READ); }
#line 10484 "parser.c"
    break;

  case 1014: /* $@72: %empty  */
#line 5194 "parser.y"
                                { BEGIN_STATEMENT ("RELEASE", 0); }
#line 10490 "parser.c"
    break;

  case 1015: /* release_statement: RELEASE $@72 record_name write_from  */
#line 5196 "parser.y"
  {
	if (yyvsp[-1] != cb_error_node) {
		cb_emit_release (yyvsp[-1], yyvsp[0]);
	}
  }
#line 10500 "parser.c"
    break;

  case 1016: /* $@73: %empty  */
#line 5209 "parser.y"
                                { BEGIN_STATEMENT ("RETURN", TERM_RETURN); }
#line 10506 "parser.c"
    break;

  case 1017: /* return_statement: RETURN $@73 file_name _record read_into at_end end_return  */
#line 5212 "parser.y"
  {
	if (yyvsp[-4] != cb_error_node) {
		cb_emit_return (yyvsp[-4], yyvsp[-2]);
	}
  }
#line 10516 "parser.c"
    break;

  case 1018: /* end_return: %empty  */
#line 5220 "parser.y"
                                { terminator_warning (TERM_RETURN); }
#line 10522 "parser.c"
    break;

  case 1019: /* end_return: "END-RETURN"  */
#line 5221 "parser.y"
                                { terminator_clear (TERM_RETURN); }
#line 10528 "parser.c"
    break;

  case 1020: /* $@74: %empty  */
#line 5230 "parser.y"
                                { BEGIN_STATEMENT ("REWRITE", TERM_REWRITE); }
#line 10534 "parser.c"
    break;

  case 1021: /* rewrite_statement: REWRITE $@74 record_name write_from write_lock opt_invalid_key end_rewrite  */
#line 5233 "parser.y"
  {
	if (yyvsp[-4] != cb_error_node) {
		cb_emit_rewrite (yyvsp[-4], yyvsp[-3], yyvsp[-2]);
	}
  }
#line 10544 "parser.c"
    break;

  case 1022: /* write_lock: %empty  */
#line 5241 "parser.y"
                                { yyval = NULL; }
#line 10550 "parser.c"
    break;

  case 1023: /* write_lock: _with LOCK  */
#line 5243 "parser.y"
  {
	yyval = cb_int1;
  }
#line 10558 "parser.c"
    break;

  case 1024: /* write_lock: _with NO LOCK  */
#line 5247 "parser.y"
  {
	yyval = cb_int2;
  }
#line 10566 "parser.c"
    break;

  case 1025: /* end_rewrite: %empty  */
#line 5253 "parser.y"
                                { terminator_warning (TERM_REWRITE); }
#line 10572 "parser.c"
    break;

  case 1026: /* end_rewrite: "END-REWRITE"  */
#line 5254 "parser.y"
                                { terminator_clear (TERM_REWRITE); }
#line 10578 "parser.c"
    break;

  case 1027: /* rollback_statement: ROLLBACK  */
#line 5264 "parser.y"
  {
	BEGIN_STATEMENT ("ROLLBACK", 0);
	cb_emit_rollback ();
  }
#line 10587 "parser.c"
    break;

  case 1028: /* $@75: %empty  */
#line 5276 "parser.y"
                                { BEGIN_STATEMENT ("SEARCH", TERM_SEARCH); }
#line 10593 "parser.c"
    break;

  case 1030: /* search_body: table_name search_varying search_at_end search_whens  */
#line 5283 "parser.y"
  {
	cb_emit_search (yyvsp[-3], yyvsp[-2], yyvsp[-1], yyvsp[0]);
  }
#line 10601 "parser.c"
    break;

  case 1031: /* $@76: %empty  */
#line 5287 "parser.y"
  {
	check_unreached = 0;
  }
#line 10609 "parser.c"
    break;

  case 1032: /* search_body: ALL table_name search_at_end WHEN expr $@76 statement_list  */
#line 5291 "parser.y"
  {
	cb_emit_search_all (yyvsp[-5], yyvsp[-4], yyvsp[-2], yyvsp[0]);
  }
#line 10617 "parser.c"
    break;

  case 1033: /* search_varying: %empty  */
#line 5297 "parser.y"
                                { yyval = NULL; }
#line 10623 "parser.c"
    break;

  case 1034: /* search_varying: VARYING identifier  */
#line 5298 "parser.y"
                                { yyval = yyvsp[0]; }
#line 10629 "parser.c"
    break;

  case 1035: /* search_at_end: %empty  */
#line 5302 "parser.y"
                                { yyval = NULL; }
#line 10635 "parser.c"
    break;

  case 1036: /* $@77: %empty  */
#line 5304 "parser.y"
  {
	check_unreached = 0;
  }
#line 10643 "parser.c"
    break;

  case 1037: /* search_at_end: _at END $@77 statement_list  */
#line 5308 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 10651 "parser.c"
    break;

  case 1038: /* search_whens: search_when  */
#line 5314 "parser.y"
                                { yyval = yyvsp[0]; }
#line 10657 "parser.c"
    break;

  case 1039: /* search_whens: search_when search_whens  */
#line 5315 "parser.y"
                                { yyval = yyvsp[-1]; CB_IF (yyvsp[-1])->stmt2 = yyvsp[0]; }
#line 10663 "parser.c"
    break;

  case 1040: /* $@78: %empty  */
#line 5320 "parser.y"
  {
	check_unreached = 0;
  }
#line 10671 "parser.c"
    break;

  case 1041: /* search_when: WHEN condition $@78 statement_list  */
#line 5324 "parser.y"
  {
	yyval = cb_build_if (yyvsp[-2], yyvsp[0], NULL);
  }
#line 10679 "parser.c"
    break;

  case 1042: /* end_search: %empty  */
#line 5330 "parser.y"
                                { terminator_warning (TERM_SEARCH); }
#line 10685 "parser.c"
    break;

  case 1043: /* end_search: "END-SEARCH"  */
#line 5331 "parser.y"
                                { terminator_clear (TERM_SEARCH); }
#line 10691 "parser.c"
    break;

  case 1044: /* $@79: %empty  */
#line 5340 "parser.y"
                                { BEGIN_STATEMENT ("SET", 0); }
#line 10697 "parser.c"
    break;

  case 1051: /* set_environment: ENVIRONMENT simple_value TO simple_value  */
#line 5356 "parser.y"
  {
	cb_emit_setenv (yyvsp[-2], yyvsp[0]);
  }
#line 10705 "parser.c"
    break;

  case 1052: /* set_to: target_x_list TO ENTRY alnum_or_id  */
#line 5365 "parser.y"
  {
	cb_emit_set_to (yyvsp[-3], cb_build_ppointer (yyvsp[0]));
  }
#line 10713 "parser.c"
    break;

  case 1053: /* set_to: target_x_list TO x  */
#line 5369 "parser.y"
  {
	cb_emit_set_to (yyvsp[-2], yyvsp[0]);
  }
#line 10721 "parser.c"
    break;

  case 1054: /* set_up_down: target_x_list up_or_down BY x  */
#line 5378 "parser.y"
  {
	cb_emit_set_up_down (yyvsp[-3], yyvsp[-2], yyvsp[0]);
  }
#line 10729 "parser.c"
    break;

  case 1055: /* up_or_down: UP  */
#line 5384 "parser.y"
                                { yyval = cb_int0; }
#line 10735 "parser.c"
    break;

  case 1056: /* up_or_down: DOWN  */
#line 5385 "parser.y"
                                { yyval = cb_int1; }
#line 10741 "parser.c"
    break;

  case 1059: /* set_to_on_off: mnemonic_name_list TO on_or_off  */
#line 5397 "parser.y"
  {
	cb_emit_set_on_off (yyvsp[-2], yyvsp[0]);
  }
#line 10749 "parser.c"
    break;

  case 1062: /* set_to_true_false: target_x_list TO "TRUE"  */
#line 5411 "parser.y"
  {
	cb_emit_set_true (yyvsp[-2]);
  }
#line 10757 "parser.c"
    break;

  case 1063: /* set_to_true_false: target_x_list TO "FALSE"  */
#line 5415 "parser.y"
  {
	cb_emit_set_false (yyvsp[-2]);
  }
#line 10765 "parser.c"
    break;

  case 1064: /* $@80: %empty  */
#line 5426 "parser.y"
                                { BEGIN_STATEMENT ("SORT", 0); }
#line 10771 "parser.c"
    break;

  case 1066: /* $@81: %empty  */
#line 5432 "parser.y"
  {
	cb_emit_sort_init (yyvsp[-3], yyvsp[-2], yyvsp[0]);
	if (CB_FILE_P (cb_ref (yyvsp[-3])) && yyvsp[-2] == NULL) {
		cb_error (_("File sort requires KEY phrase"));
	}
	/* used in sort_input/sort_output */
	save_tree_1 = yyvsp[-3];
  }
#line 10784 "parser.c"
    break;

  case 1067: /* sort_body: qualified_word sort_key_list sort_duplicates sort_collating $@81 sort_input sort_output  */
#line 5441 "parser.y"
  {
	cb_emit_sort_finish (yyvsp[-6]);
  }
#line 10792 "parser.c"
    break;

  case 1068: /* sort_key_list: %empty  */
#line 5448 "parser.y"
  {
	yyval = NULL;
  }
#line 10800 "parser.c"
    break;

  case 1069: /* sort_key_list: sort_key_list _on ascending_or_descending _key opt_key_list  */
#line 5453 "parser.y"
  {
	cb_tree l;

	if (yyvsp[0] == NULL) {
		yyvsp[0] = cb_list_init (NULL);
	}
	for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
		CB_PURPOSE (l) = yyvsp[-2];
	}
	yyval = cb_list_append (yyvsp[-4], yyvsp[0]);
  }
#line 10816 "parser.c"
    break;

  case 1070: /* opt_key_list: %empty  */
#line 5467 "parser.y"
                                { yyval = NULL; }
#line 10822 "parser.c"
    break;

  case 1071: /* opt_key_list: opt_key_list qualified_word  */
#line 5468 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 10828 "parser.c"
    break;

  case 1073: /* sort_duplicates: with_dups _in_order  */
#line 5472 "parser.y"
                                { /* nothing */ }
#line 10834 "parser.c"
    break;

  case 1074: /* sort_collating: %empty  */
#line 5476 "parser.y"
                                        { yyval = cb_null; }
#line 10840 "parser.c"
    break;

  case 1075: /* sort_collating: coll_sequence _is reference  */
#line 5477 "parser.y"
                                        { yyval = cb_ref (yyvsp[0]); }
#line 10846 "parser.c"
    break;

  case 1076: /* sort_input: %empty  */
#line 5482 "parser.y"
  {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires USING or INPUT PROCEDURE"));
	}
  }
#line 10856 "parser.c"
    break;

  case 1077: /* sort_input: USING file_name_list  */
#line 5488 "parser.y"
  {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("USING invalid with table SORT"));
	} else {
		cb_emit_sort_using (save_tree_1, yyvsp[0]);
	}
  }
#line 10868 "parser.c"
    break;

  case 1078: /* sort_input: INPUT PROCEDURE _is perform_procedure  */
#line 5496 "parser.y"
  {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("INPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_input (yyvsp[0]);
	}
  }
#line 10880 "parser.c"
    break;

  case 1079: /* sort_output: %empty  */
#line 5507 "parser.y"
  {
	if (CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("File sort requires GIVING or OUTPUT PROCEDURE"));
	}
  }
#line 10890 "parser.c"
    break;

  case 1080: /* sort_output: GIVING file_name_list  */
#line 5513 "parser.y"
  {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("GIVING invalid with table SORT"));
	} else {
		cb_emit_sort_giving (save_tree_1, yyvsp[0]);
	}
  }
#line 10902 "parser.c"
    break;

  case 1081: /* sort_output: OUTPUT PROCEDURE _is perform_procedure  */
#line 5521 "parser.y"
  {
	if (!CB_FILE_P (cb_ref (save_tree_1))) {
		cb_error (_("OUTPUT PROCEDURE invalid with table SORT"));
	} else {
		cb_emit_sort_output (yyvsp[0]);
	}
  }
#line 10914 "parser.c"
    break;

  case 1082: /* $@82: %empty  */
#line 5536 "parser.y"
                                { BEGIN_STATEMENT ("START", TERM_START); }
#line 10920 "parser.c"
    break;

  case 1083: /* @83: %empty  */
#line 5537 "parser.y"
                                { yyval = cb_int (COB_EQ); }
#line 10926 "parser.c"
    break;

  case 1084: /* start_statement: START $@82 file_name @83 start_key opt_invalid_key end_start  */
#line 5540 "parser.y"
  {
	if (CB_FILE_P (cb_ref (yyvsp[-4]))) {
		if (CB_FILE (cb_ref (yyvsp[-4]))->organization != COB_ORG_INDEXED &&
		     CB_FILE (cb_ref (yyvsp[-4]))->organization != COB_ORG_RELATIVE) {
			cb_error (_("START not allowed on SEQUENTIAL files"));
			yyval = cb_error_node;
		} else {
			cb_emit_start (yyvsp[-4], yyvsp[-3], yyvsp[-2]);
		}
	} else {
		cb_error_x (yyvsp[-4], _("'%s' is not a file name"), CB_NAME (yyvsp[-4]));
		yyval = cb_error_node;
	}
  }
#line 10945 "parser.c"
    break;

  case 1085: /* start_key: %empty  */
#line 5557 "parser.y"
                                { yyval = NULL; }
#line 10951 "parser.c"
    break;

  case 1086: /* start_key: KEY _is start_op x  */
#line 5558 "parser.y"
                                { yyvsp[-4] = yyvsp[-1]; yyval = yyvsp[0]; }
#line 10957 "parser.c"
    break;

  case 1087: /* start_op: flag_not eq  */
#line 5562 "parser.y"
                        { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_NE : COB_EQ); }
#line 10963 "parser.c"
    break;

  case 1088: /* start_op: flag_not gt  */
#line 5563 "parser.y"
                        { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_LE : COB_GT); }
#line 10969 "parser.c"
    break;

  case 1089: /* start_op: flag_not lt  */
#line 5564 "parser.y"
                        { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_GE : COB_LT); }
#line 10975 "parser.c"
    break;

  case 1090: /* start_op: flag_not ge  */
#line 5565 "parser.y"
                        { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_LT : COB_GE); }
#line 10981 "parser.c"
    break;

  case 1091: /* start_op: flag_not le  */
#line 5566 "parser.y"
                        { yyval = cb_int ((yyvsp[-1] == cb_int1) ? COB_GT : COB_LE); }
#line 10987 "parser.c"
    break;

  case 1092: /* end_start: %empty  */
#line 5570 "parser.y"
                                { terminator_warning (TERM_START); }
#line 10993 "parser.c"
    break;

  case 1093: /* end_start: "END-START"  */
#line 5571 "parser.y"
                                { terminator_clear (TERM_START); }
#line 10999 "parser.c"
    break;

  case 1094: /* $@84: %empty  */
#line 5580 "parser.y"
                                { BEGIN_STATEMENT ("STOP", 0); }
#line 11005 "parser.c"
    break;

  case 1095: /* stop_statement: STOP RUN $@84 stop_returning  */
#line 5582 "parser.y"
  {
	cb_emit_stop_run (yyvsp[0]);
  }
#line 11013 "parser.c"
    break;

  case 1096: /* stop_statement: STOP "Literal"  */
#line 5586 "parser.y"
  {
	cb_verify (cb_stop_literal_statement, "STOP literal");
  }
#line 11021 "parser.c"
    break;

  case 1097: /* stop_returning: %empty  */
#line 5592 "parser.y"
                        { yyval = current_program->cb_return_code; }
#line 11027 "parser.c"
    break;

  case 1098: /* stop_returning: RETURNING x  */
#line 5593 "parser.y"
                        { yyval = yyvsp[0]; }
#line 11033 "parser.c"
    break;

  case 1099: /* stop_returning: GIVING x  */
#line 5594 "parser.y"
                        { yyval = yyvsp[0]; }
#line 11039 "parser.c"
    break;

  case 1100: /* $@85: %empty  */
#line 5603 "parser.y"
                                { BEGIN_STATEMENT ("STRING", TERM_STRING); }
#line 11045 "parser.c"
    break;

  case 1101: /* string_statement: STRING $@85 string_item_list INTO identifier opt_with_pointer on_overflow end_string  */
#line 5606 "parser.y"
  {
	cb_emit_string (yyvsp[-5], yyvsp[-3], yyvsp[-2]);
  }
#line 11053 "parser.c"
    break;

  case 1102: /* string_item_list: string_item  */
#line 5612 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 11059 "parser.c"
    break;

  case 1103: /* string_item_list: string_item_list string_item  */
#line 5613 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 11065 "parser.c"
    break;

  case 1104: /* string_item: x  */
#line 5617 "parser.y"
                                { yyval = yyvsp[0]; }
#line 11071 "parser.c"
    break;

  case 1105: /* string_item: DELIMITED _by SIZE  */
#line 5618 "parser.y"
                                { yyval = cb_build_pair (cb_int0, NULL); }
#line 11077 "parser.c"
    break;

  case 1106: /* string_item: DELIMITED _by x  */
#line 5619 "parser.y"
                                { yyval = cb_build_pair (yyvsp[0], NULL); }
#line 11083 "parser.c"
    break;

  case 1107: /* opt_with_pointer: %empty  */
#line 5623 "parser.y"
                                { yyval = cb_int0; }
#line 11089 "parser.c"
    break;

  case 1108: /* opt_with_pointer: _with POINTER identifier  */
#line 5624 "parser.y"
                                { yyval = yyvsp[0]; }
#line 11095 "parser.c"
    break;

  case 1109: /* end_string: %empty  */
#line 5628 "parser.y"
                                { terminator_warning (TERM_STRING); }
#line 11101 "parser.c"
    break;

  case 1110: /* end_string: "END-STRING"  */
#line 5629 "parser.y"
                                { terminator_clear (TERM_STRING); }
#line 11107 "parser.c"
    break;

  case 1111: /* $@86: %empty  */
#line 5638 "parser.y"
                                { BEGIN_STATEMENT ("SUBTRACT", TERM_SUBTRACT); }
#line 11113 "parser.c"
    break;

  case 1113: /* subtract_body: x_list FROM arithmetic_x_list on_size_error  */
#line 5645 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], '-', cb_build_binary_list (yyvsp[-3], '+'));
  }
#line 11121 "parser.c"
    break;

  case 1114: /* subtract_body: x_list FROM x GIVING arithmetic_x_list on_size_error  */
#line 5649 "parser.y"
  {
	cb_emit_arithmetic (yyvsp[-1], 0, cb_build_binary_list (cb_cons (yyvsp[-3], yyvsp[-5]), '-'));
  }
#line 11129 "parser.c"
    break;

  case 1115: /* subtract_body: CORRESPONDING identifier FROM identifier flag_rounded on_size_error  */
#line 5653 "parser.y"
  {
	cb_emit_corresponding (cb_build_sub, yyvsp[-2], yyvsp[-4], yyvsp[-1]);
  }
#line 11137 "parser.c"
    break;

  case 1116: /* end_subtract: %empty  */
#line 5659 "parser.y"
                                { terminator_warning (TERM_SUBTRACT); }
#line 11143 "parser.c"
    break;

  case 1117: /* end_subtract: "END-SUBTRACT"  */
#line 5660 "parser.y"
                                { terminator_clear (TERM_SUBTRACT); }
#line 11149 "parser.c"
    break;

  case 1118: /* suppress_statement: SUPPRESS _printing  */
#line 5670 "parser.y"
  {
	BEGIN_STATEMENT ("SUPPRESS", 0);
	PENDING("SUPPRESS");
  }
#line 11158 "parser.c"
    break;

  case 1121: /* $@87: %empty  */
#line 5685 "parser.y"
                                { BEGIN_STATEMENT ("TERMINATE", 0); }
#line 11164 "parser.c"
    break;

  case 1122: /* terminate_statement: TERMINATE $@87 identifier_list  */
#line 5687 "parser.y"
  {
	PENDING("TERMINATE");
  }
#line 11172 "parser.c"
    break;

  case 1123: /* $@88: %empty  */
#line 5698 "parser.y"
                                { BEGIN_STATEMENT ("TRANSFORM", 0); }
#line 11178 "parser.c"
    break;

  case 1124: /* transform_statement: TRANSFORM $@88 identifier FROM simple_value TO simple_all_value  */
#line 5700 "parser.y"
  {
	cb_tree		x;

	x = cb_build_converting (yyvsp[-2], yyvsp[0], cb_build_inspect_region_start ());
	cb_emit_inspect (yyvsp[-4], x, cb_int0, 2);
  }
#line 11189 "parser.c"
    break;

  case 1125: /* $@89: %empty  */
#line 5714 "parser.y"
                                { BEGIN_STATEMENT ("UNLOCK", 0); }
#line 11195 "parser.c"
    break;

  case 1126: /* unlock_statement: UNLOCK $@89 file_name opt_record  */
#line 5716 "parser.y"
  {
	if (yyvsp[-1] != cb_error_node) {
		cb_emit_unlock (yyvsp[-1]);
	}
  }
#line 11205 "parser.c"
    break;

  case 1130: /* $@90: %empty  */
#line 5735 "parser.y"
                                { BEGIN_STATEMENT ("UNSTRING", TERM_UNSTRING); }
#line 11211 "parser.c"
    break;

  case 1131: /* unstring_statement: UNSTRING $@90 identifier unstring_delimited unstring_into opt_with_pointer unstring_tallying on_overflow end_unstring  */
#line 5739 "parser.y"
  {
	cb_emit_unstring (yyvsp[-6], yyvsp[-5], yyvsp[-4], yyvsp[-3], yyvsp[-2]);
  }
#line 11219 "parser.c"
    break;

  case 1132: /* unstring_delimited: %empty  */
#line 5745 "parser.y"
                                { yyval = NULL; }
#line 11225 "parser.c"
    break;

  case 1133: /* unstring_delimited: DELIMITED _by unstring_delimited_list  */
#line 5747 "parser.y"
                                { yyval = yyvsp[0]; }
#line 11231 "parser.c"
    break;

  case 1134: /* unstring_delimited_list: unstring_delimited_item  */
#line 5751 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 11237 "parser.c"
    break;

  case 1135: /* unstring_delimited_list: unstring_delimited_list OR unstring_delimited_item  */
#line 5753 "parser.y"
                                { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); }
#line 11243 "parser.c"
    break;

  case 1136: /* unstring_delimited_item: flag_all simple_value  */
#line 5758 "parser.y"
  {
	yyval = cb_build_unstring_delimited (yyvsp[-1], yyvsp[0]);
  }
#line 11251 "parser.c"
    break;

  case 1137: /* unstring_into: INTO unstring_into_item  */
#line 5764 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 11257 "parser.c"
    break;

  case 1138: /* unstring_into: unstring_into unstring_into_item  */
#line 5766 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 11263 "parser.c"
    break;

  case 1139: /* unstring_into_item: identifier unstring_into_delimiter unstring_into_count  */
#line 5771 "parser.y"
  {
	yyval = cb_build_unstring_into (yyvsp[-2], yyvsp[-1], yyvsp[0]);
  }
#line 11271 "parser.c"
    break;

  case 1140: /* unstring_into_delimiter: %empty  */
#line 5777 "parser.y"
                                { yyval = NULL; }
#line 11277 "parser.c"
    break;

  case 1141: /* unstring_into_delimiter: DELIMITER _in identifier  */
#line 5778 "parser.y"
                                { yyval = yyvsp[0]; }
#line 11283 "parser.c"
    break;

  case 1142: /* unstring_into_count: %empty  */
#line 5782 "parser.y"
                                { yyval = NULL; }
#line 11289 "parser.c"
    break;

  case 1143: /* unstring_into_count: COUNT _in identifier  */
#line 5783 "parser.y"
                                { yyval = yyvsp[0]; }
#line 11295 "parser.c"
    break;

  case 1144: /* unstring_tallying: %empty  */
#line 5787 "parser.y"
                                { yyval = NULL; }
#line 11301 "parser.c"
    break;

  case 1145: /* unstring_tallying: TALLYING _in identifier  */
#line 5788 "parser.y"
                                { yyval = yyvsp[0]; }
#line 11307 "parser.c"
    break;

  case 1146: /* end_unstring: %empty  */
#line 5792 "parser.y"
                                { terminator_warning (TERM_UNSTRING); }
#line 11313 "parser.c"
    break;

  case 1147: /* end_unstring: "END-UNSTRING"  */
#line 5793 "parser.y"
                                { terminator_clear (TERM_UNSTRING); }
#line 11319 "parser.c"
    break;

  case 1151: /* use_exception: USE use_global _after _standard exception_or_error _procedure _on use_exception_target  */
#line 5811 "parser.y"
  {
	if (!in_declaratives) {
		cb_error (_("USE statement must be within DECLARATIVES"));
	} else if (!current_section) {
		cb_error (_("SECTION header missing before USE statement"));
	} else {
		current_section->need_begin = 1;
		current_section->need_return = 1;
		CB_EXCEPTION_ENABLE (COB_EC_I_O) = 1;
		if (use_global_ind) {
			current_section->is_global = 1;
			current_program->global_list =
				cb_list_add (current_program->global_list,
					     CB_TREE (current_section));
		}
	}
  }
#line 11341 "parser.c"
    break;

  case 1152: /* use_global: %empty  */
#line 5832 "parser.y"
  {
	use_global_ind = 0;
  }
#line 11349 "parser.c"
    break;

  case 1153: /* use_global: GLOBAL  */
#line 5836 "parser.y"
  {
	use_global_ind = 1;
	current_program->flag_global_use = 1;
  }
#line 11358 "parser.c"
    break;

  case 1154: /* use_exception_target: file_name_list  */
#line 5844 "parser.y"
  {
	cb_tree		l;

	for (l = yyvsp[0]; l; l = CB_CHAIN (l)) {
		if (CB_VALUE (l) != cb_error_node) {
			setup_use_file (CB_FILE (cb_ref (CB_VALUE (l))));
		}
	}
  }
#line 11372 "parser.c"
    break;

  case 1155: /* use_exception_target: INPUT  */
#line 5854 "parser.y"
  {
	current_program->global_handler[COB_OPEN_INPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_INPUT].handler_prog = current_program;
  }
#line 11381 "parser.c"
    break;

  case 1156: /* use_exception_target: OUTPUT  */
#line 5859 "parser.y"
  {
	current_program->global_handler[COB_OPEN_OUTPUT].handler_label = current_section;
	current_program->global_handler[COB_OPEN_OUTPUT].handler_prog = current_program;
  }
#line 11390 "parser.c"
    break;

  case 1157: /* use_exception_target: "I-O"  */
#line 5864 "parser.y"
  {
	current_program->global_handler[COB_OPEN_I_O].handler_label = current_section;
	current_program->global_handler[COB_OPEN_I_O].handler_prog = current_program;
  }
#line 11399 "parser.c"
    break;

  case 1158: /* use_exception_target: EXTEND  */
#line 5869 "parser.y"
  {
	current_program->global_handler[COB_OPEN_EXTEND].handler_label = current_section;
	current_program->global_handler[COB_OPEN_EXTEND].handler_prog = current_program;
  }
#line 11408 "parser.c"
    break;

  case 1171: /* use_debugging: USE _for DEBUGGING _on use_debugging_target  */
#line 5901 "parser.y"
  {
	PENDING ("USE FOR DEBUGGING");
  }
#line 11416 "parser.c"
    break;

  case 1174: /* use_reporting: USE use_global BEFORE REPORTING identifier  */
#line 5913 "parser.y"
  {
	PENDING ("USE BEFORE REPORTING");
  }
#line 11424 "parser.c"
    break;

  case 1175: /* $@91: %empty  */
#line 5924 "parser.y"
                                { BEGIN_STATEMENT ("WRITE", TERM_WRITE); }
#line 11430 "parser.c"
    break;

  case 1176: /* write_statement: WRITE $@91 record_name write_from write_lock write_option write_handler end_write  */
#line 5927 "parser.y"
  {
	if (yyvsp[-5] != cb_error_node) {
		cb_emit_write (yyvsp[-5], yyvsp[-4], yyvsp[-2], yyvsp[-3]);
	}
  }
#line 11440 "parser.c"
    break;

  case 1177: /* write_from: %empty  */
#line 5935 "parser.y"
                                { yyval = NULL; }
#line 11446 "parser.c"
    break;

  case 1178: /* write_from: FROM id_or_lit  */
#line 5936 "parser.y"
                                { yyval = yyvsp[0]; }
#line 11452 "parser.c"
    break;

  case 1179: /* write_option: %empty  */
#line 5941 "parser.y"
  {
	yyval = cb_int0;
  }
#line 11460 "parser.c"
    break;

  case 1180: /* write_option: before_or_after _advancing num_id_or_lit _line_or_lines  */
#line 5945 "parser.y"
  {
	yyval = cb_build_write_advancing_lines (yyvsp[-3], yyvsp[-1]);
  }
#line 11468 "parser.c"
    break;

  case 1181: /* write_option: before_or_after _advancing mnemonic_name  */
#line 5949 "parser.y"
  {
	yyval = cb_build_write_advancing_mnemonic (yyvsp[-2], yyvsp[0]);
  }
#line 11476 "parser.c"
    break;

  case 1182: /* write_option: before_or_after _advancing PAGE  */
#line 5953 "parser.y"
  {
	yyval = cb_build_write_advancing_page (yyvsp[-2]);
  }
#line 11484 "parser.c"
    break;

  case 1183: /* before_or_after: BEFORE  */
#line 5959 "parser.y"
                                { yyval = CB_BEFORE; }
#line 11490 "parser.c"
    break;

  case 1184: /* before_or_after: AFTER  */
#line 5960 "parser.y"
                                { yyval = CB_AFTER; }
#line 11496 "parser.c"
    break;

  case 1188: /* end_write: %empty  */
#line 5969 "parser.y"
                                { terminator_warning (TERM_WRITE); }
#line 11502 "parser.c"
    break;

  case 1189: /* end_write: "END-WRITE"  */
#line 5970 "parser.y"
                                { terminator_clear (TERM_WRITE); }
#line 11508 "parser.c"
    break;

  case 1190: /* on_accp_exception: opt_on_exception opt_not_on_exception  */
#line 5985 "parser.y"
  {
	current_statement->handler_id = COB_EC_IMP_ACCEPT;
  }
#line 11516 "parser.c"
    break;

  case 1191: /* on_disp_exception: opt_on_exception opt_not_on_exception  */
#line 5993 "parser.y"
  {
	current_statement->handler_id = COB_EC_IMP_DISPLAY;
  }
#line 11524 "parser.c"
    break;

  case 1193: /* $@92: %empty  */
#line 6000 "parser.y"
  {
	check_unreached = 0;
  }
#line 11532 "parser.c"
    break;

  case 1194: /* opt_on_exception: EXCEPTION $@92 statement_list  */
#line 6004 "parser.y"
  {
	current_statement->handler1 = yyvsp[0];
  }
#line 11540 "parser.c"
    break;

  case 1196: /* $@93: %empty  */
#line 6011 "parser.y"
  {
	check_unreached = 0;
  }
#line 11548 "parser.c"
    break;

  case 1197: /* opt_not_on_exception: "NOT EXCEPTION" $@93 statement_list  */
#line 6015 "parser.y"
  {
	current_statement->handler2 = yyvsp[0];
  }
#line 11556 "parser.c"
    break;

  case 1198: /* on_size_error: opt_on_size_error opt_not_on_size_error  */
#line 6027 "parser.y"
  {
	current_statement->handler_id = COB_EC_SIZE;
  }
#line 11564 "parser.c"
    break;

  case 1200: /* $@94: %empty  */
#line 6034 "parser.y"
  {
	check_unreached = 0;
  }
#line 11572 "parser.c"
    break;

  case 1201: /* opt_on_size_error: "SIZE ERROR" $@94 statement_list  */
#line 6038 "parser.y"
  {
	current_statement->handler1 = yyvsp[0];
  }
#line 11580 "parser.c"
    break;

  case 1203: /* $@95: %empty  */
#line 6045 "parser.y"
  {
	check_unreached = 0;
  }
#line 11588 "parser.c"
    break;

  case 1204: /* opt_not_on_size_error: "NOT SIZE ERROR" $@95 statement_list  */
#line 6049 "parser.y"
  {
	current_statement->handler2 = yyvsp[0];
  }
#line 11596 "parser.c"
    break;

  case 1205: /* on_overflow: opt_on_overflow opt_not_on_overflow  */
#line 6061 "parser.y"
  {
	current_statement->handler_id = COB_EC_OVERFLOW;
  }
#line 11604 "parser.c"
    break;

  case 1207: /* $@96: %empty  */
#line 6068 "parser.y"
  {
	check_unreached = 0;
  }
#line 11612 "parser.c"
    break;

  case 1208: /* opt_on_overflow: OVERFLOW $@96 statement_list  */
#line 6072 "parser.y"
  {
	current_statement->handler1 = yyvsp[0];
  }
#line 11620 "parser.c"
    break;

  case 1210: /* $@97: %empty  */
#line 6079 "parser.y"
  {
	check_unreached = 0;
  }
#line 11628 "parser.c"
    break;

  case 1211: /* opt_not_on_overflow: "NOT OVERFLOW" $@97 statement_list  */
#line 6083 "parser.y"
  {
	current_statement->handler2 = yyvsp[0];
  }
#line 11636 "parser.c"
    break;

  case 1212: /* at_end: at_end_sentence  */
#line 6095 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = yyvsp[0];
  }
#line 11645 "parser.c"
    break;

  case 1213: /* at_end: not_at_end_sentence  */
#line 6100 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler2 = yyvsp[0];
  }
#line 11654 "parser.c"
    break;

  case 1214: /* at_end: at_end_sentence not_at_end_sentence  */
#line 6105 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_AT_END;
	current_statement->handler1 = yyvsp[-1];
	current_statement->handler2 = yyvsp[0];
  }
#line 11664 "parser.c"
    break;

  case 1215: /* $@98: %empty  */
#line 6114 "parser.y"
  {
	check_unreached = 0;
  }
#line 11672 "parser.c"
    break;

  case 1216: /* at_end_sentence: END $@98 statement_list  */
#line 6118 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 11680 "parser.c"
    break;

  case 1217: /* $@99: %empty  */
#line 6125 "parser.y"
  {
	check_unreached = 0;
  }
#line 11688 "parser.c"
    break;

  case 1218: /* not_at_end_sentence: "NOT END" $@99 statement_list  */
#line 6129 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 11696 "parser.c"
    break;

  case 1219: /* at_eop: at_eop_sentence  */
#line 6141 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = yyvsp[0];
  }
#line 11705 "parser.c"
    break;

  case 1220: /* at_eop: not_at_eop_sentence  */
#line 6146 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler2 = yyvsp[0];
  }
#line 11714 "parser.c"
    break;

  case 1221: /* at_eop: at_eop_sentence not_at_eop_sentence  */
#line 6151 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_EOP;
	current_statement->handler1 = yyvsp[-1];
	current_statement->handler2 = yyvsp[0];
  }
#line 11724 "parser.c"
    break;

  case 1222: /* $@100: %empty  */
#line 6160 "parser.y"
  {
	check_unreached = 0;
  }
#line 11732 "parser.c"
    break;

  case 1223: /* at_eop_sentence: EOP $@100 statement_list  */
#line 6164 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 11740 "parser.c"
    break;

  case 1224: /* $@101: %empty  */
#line 6171 "parser.y"
  {
	check_unreached = 0;
  }
#line 11748 "parser.c"
    break;

  case 1225: /* not_at_eop_sentence: "NOT EOP" $@101 statement_list  */
#line 6175 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 11756 "parser.c"
    break;

  case 1228: /* invalid_key: invalid_key_sentence  */
#line 6191 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = yyvsp[0];
  }
#line 11765 "parser.c"
    break;

  case 1229: /* invalid_key: not_invalid_key_sentence  */
#line 6196 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler2 = yyvsp[0];
  }
#line 11774 "parser.c"
    break;

  case 1230: /* invalid_key: invalid_key_sentence not_invalid_key_sentence  */
#line 6201 "parser.y"
  {
	current_statement->handler_id = COB_EC_I_O_INVALID_KEY;
	current_statement->handler1 = yyvsp[-1];
	current_statement->handler2 = yyvsp[0];
  }
#line 11784 "parser.c"
    break;

  case 1231: /* $@102: %empty  */
#line 6210 "parser.y"
  {
	check_unreached = 0;
  }
#line 11792 "parser.c"
    break;

  case 1232: /* invalid_key_sentence: "INVALID KEY" $@102 statement_list  */
#line 6214 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 11800 "parser.c"
    break;

  case 1233: /* $@103: %empty  */
#line 6221 "parser.y"
  {
	check_unreached = 0;
  }
#line 11808 "parser.c"
    break;

  case 1234: /* not_invalid_key_sentence: "NOT INVALID KEY" $@103 statement_list  */
#line 6225 "parser.y"
  {
	yyval = yyvsp[0];
  }
#line 11816 "parser.c"
    break;

  case 1235: /* _opt_scroll_lines: %empty  */
#line 6237 "parser.y"
  {
	yyval = cb_one;
  }
#line 11824 "parser.c"
    break;

  case 1236: /* _opt_scroll_lines: _by num_id_or_lit _line_or_lines  */
#line 6241 "parser.y"
  {
	yyval = yyvsp[-1];
  }
#line 11832 "parser.c"
    break;

  case 1237: /* condition: expr  */
#line 6253 "parser.y"
  {
	yyval = cb_build_cond (yyvsp[0]);
  }
#line 11840 "parser.c"
    break;

  case 1238: /* expr: partial_expr  */
#line 6260 "parser.y"
  {
	yyval = cb_build_expr (yyvsp[0]);
  }
#line 11848 "parser.c"
    break;

  case 1239: /* $@104: %empty  */
#line 6266 "parser.y"
  {
	current_expr = NULL;
  }
#line 11856 "parser.c"
    break;

  case 1240: /* partial_expr: $@104 expr_tokens  */
#line 6270 "parser.y"
  {
	yyval = cb_list_reverse (current_expr);
  }
#line 11864 "parser.c"
    break;

  case 1244: /* expr_token: x  */
#line 6282 "parser.y"
                                { push_expr ('x', yyvsp[0]); }
#line 11870 "parser.c"
    break;

  case 1245: /* expr_token: '('  */
#line 6284 "parser.y"
                                { push_expr ('(', NULL); }
#line 11876 "parser.c"
    break;

  case 1246: /* expr_token: ')'  */
#line 6285 "parser.y"
                                { push_expr (')', NULL); }
#line 11882 "parser.c"
    break;

  case 1247: /* expr_token: '+'  */
#line 6287 "parser.y"
                                { push_expr ('+', NULL); }
#line 11888 "parser.c"
    break;

  case 1248: /* expr_token: '-'  */
#line 6288 "parser.y"
                                { push_expr ('-', NULL); }
#line 11894 "parser.c"
    break;

  case 1249: /* expr_token: '*'  */
#line 6289 "parser.y"
                                { push_expr ('*', NULL); }
#line 11900 "parser.c"
    break;

  case 1250: /* expr_token: '/'  */
#line 6290 "parser.y"
                                { push_expr ('/', NULL); }
#line 11906 "parser.c"
    break;

  case 1251: /* expr_token: '^'  */
#line 6291 "parser.y"
                                { push_expr ('^', NULL); }
#line 11912 "parser.c"
    break;

  case 1252: /* expr_token: eq  */
#line 6293 "parser.y"
                                { push_expr ('=', NULL); }
#line 11918 "parser.c"
    break;

  case 1253: /* expr_token: gt  */
#line 6294 "parser.y"
                                { push_expr ('>', NULL); }
#line 11924 "parser.c"
    break;

  case 1254: /* expr_token: lt  */
#line 6295 "parser.y"
                                { push_expr ('<', NULL); }
#line 11930 "parser.c"
    break;

  case 1255: /* expr_token: GE  */
#line 6296 "parser.y"
                                { push_expr (']', NULL); }
#line 11936 "parser.c"
    break;

  case 1256: /* expr_token: LE  */
#line 6297 "parser.y"
                                { push_expr ('[', NULL); }
#line 11942 "parser.c"
    break;

  case 1257: /* expr_token: NE  */
#line 6298 "parser.y"
                                { push_expr ('~', NULL); }
#line 11948 "parser.c"
    break;

  case 1258: /* expr_token: NOT  */
#line 6300 "parser.y"
                                { push_expr ('!', NULL); }
#line 11954 "parser.c"
    break;

  case 1259: /* expr_token: AND  */
#line 6301 "parser.y"
                                { push_expr ('&', NULL); }
#line 11960 "parser.c"
    break;

  case 1260: /* expr_token: OR  */
#line 6302 "parser.y"
                                { push_expr ('|', NULL); }
#line 11966 "parser.c"
    break;

  case 1261: /* expr_token: OMITTED  */
#line 6304 "parser.y"
                                { push_expr ('O', NULL); }
#line 11972 "parser.c"
    break;

  case 1262: /* expr_token: NUMERIC  */
#line 6305 "parser.y"
                                { push_expr ('9', NULL); }
#line 11978 "parser.c"
    break;

  case 1263: /* expr_token: ALPHABETIC  */
#line 6306 "parser.y"
                                { push_expr ('A', NULL); }
#line 11984 "parser.c"
    break;

  case 1264: /* expr_token: "ALPHABETIC-LOWER"  */
#line 6307 "parser.y"
                                { push_expr ('L', NULL); }
#line 11990 "parser.c"
    break;

  case 1265: /* expr_token: "ALPHABETIC-UPPER"  */
#line 6308 "parser.y"
                                { push_expr ('U', NULL); }
#line 11996 "parser.c"
    break;

  case 1266: /* expr_token: POSITIVE  */
#line 6311 "parser.y"
                                { push_expr ('P', NULL); }
#line 12002 "parser.c"
    break;

  case 1267: /* expr_token: NEGATIVE  */
#line 6312 "parser.y"
                                { push_expr ('N', NULL); }
#line 12008 "parser.c"
    break;

  case 1279: /* exp_list: exp  */
#line 6324 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 12014 "parser.c"
    break;

  case 1280: /* exp_list: exp_list e_sep exp  */
#line 6325 "parser.y"
                                { yyval = cb_list_add (yyvsp[-2], yyvsp[0]); }
#line 12020 "parser.c"
    break;

  case 1284: /* exp: arith_x  */
#line 6334 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12026 "parser.c"
    break;

  case 1285: /* exp: exp '+' exp  */
#line 6335 "parser.y"
                                { yyval = cb_build_binary_op (yyvsp[-2], '+', yyvsp[0]); }
#line 12032 "parser.c"
    break;

  case 1286: /* exp: exp '-' exp  */
#line 6336 "parser.y"
                                { yyval = cb_build_binary_op (yyvsp[-2], '-', yyvsp[0]); }
#line 12038 "parser.c"
    break;

  case 1287: /* exp: exp '*' exp  */
#line 6337 "parser.y"
                                { yyval = cb_build_binary_op (yyvsp[-2], '*', yyvsp[0]); }
#line 12044 "parser.c"
    break;

  case 1288: /* exp: exp '/' exp  */
#line 6338 "parser.y"
                                { yyval = cb_build_binary_op (yyvsp[-2], '/', yyvsp[0]); }
#line 12050 "parser.c"
    break;

  case 1289: /* exp: '+' exp  */
#line 6339 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12056 "parser.c"
    break;

  case 1290: /* exp: '-' exp  */
#line 6340 "parser.y"
                                { yyval = cb_build_binary_op (cb_zero, '-', yyvsp[0]); }
#line 12062 "parser.c"
    break;

  case 1291: /* exp: exp '^' exp  */
#line 6341 "parser.y"
                                { yyval = cb_build_binary_op (yyvsp[-2], '^', yyvsp[0]); }
#line 12068 "parser.c"
    break;

  case 1292: /* exp: '(' exp ')'  */
#line 6342 "parser.y"
                                { yyval = yyvsp[-1]; }
#line 12074 "parser.c"
    break;

  case 1293: /* linage_counter: "LINAGE-COUNTER"  */
#line 6354 "parser.y"
  {
	if (current_linage > 1) {
		cb_error (_("LINAGE-COUNTER must be qualified here"));
		yyval = cb_error_node;
	} else if (current_linage == 0) {
		cb_error (_("Invalid LINAGE-COUNTER usage"));
		yyval = cb_error_node;
	} else {
		yyval = linage_file->linage_ctr;
	}
  }
#line 12090 "parser.c"
    break;

  case 1294: /* linage_counter: "LINAGE-COUNTER" in_of "Identifier"  */
#line 6366 "parser.y"
  {
	if (CB_FILE_P (cb_ref (yyvsp[0]))) {
		yyval = CB_FILE (cb_ref (yyvsp[0]))->linage_ctr;
	} else {
		cb_error_x (yyvsp[0], _("'%s' is not a file name"), CB_NAME (yyvsp[0]));
		yyval = cb_error_node;
	}
  }
#line 12103 "parser.c"
    break;

  case 1295: /* arithmetic_x_list: arithmetic_x  */
#line 6380 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12109 "parser.c"
    break;

  case 1296: /* arithmetic_x_list: arithmetic_x_list arithmetic_x  */
#line 6382 "parser.y"
                                { yyval = cb_list_append (yyvsp[-1], yyvsp[0]); }
#line 12115 "parser.c"
    break;

  case 1297: /* arithmetic_x: x flag_rounded  */
#line 6386 "parser.y"
                                { yyval = cb_build_pair (yyvsp[0], yyvsp[-1]); }
#line 12121 "parser.c"
    break;

  case 1298: /* record_name: qualified_word  */
#line 6392 "parser.y"
                                { cb_build_identifier (yyvsp[0]); }
#line 12127 "parser.c"
    break;

  case 1299: /* table_name: qualified_word  */
#line 6399 "parser.y"
  {
	cb_tree x;

	x = cb_ref (yyvsp[0]);
	if (!CB_FIELD_P (x)) {
		yyval = cb_error_node;
	} else if (!CB_FIELD (x)->index_list) {
		cb_error_x (yyvsp[0], _("'%s' not indexed"), cb_name (yyvsp[0]));
		cb_error_x (x, _("'%s' defined here"), cb_name (x));
		yyval = cb_error_node;
	} else {
		yyval = yyvsp[0];
	}
  }
#line 12146 "parser.c"
    break;

  case 1300: /* file_name_list: file_name  */
#line 6419 "parser.y"
  {
	yyval = cb_list_init (yyvsp[0]);
  }
#line 12154 "parser.c"
    break;

  case 1301: /* file_name_list: file_name_list file_name  */
#line 6423 "parser.y"
  {
	cb_tree		l;

	if (yyvsp[0] != cb_error_node) {
		for (l = yyvsp[-1]; l; l = CB_CHAIN (l)) {
			if (!strcasecmp (CB_NAME (yyvsp[0]), CB_NAME (CB_VALUE (l)))) {
				cb_error_x (yyvsp[0], _("Multiple reference to '%s' "), CB_NAME (yyvsp[0]));
			}
		}
		yyval = cb_list_add (yyvsp[-1], yyvsp[0]);
	}
  }
#line 12171 "parser.c"
    break;

  case 1302: /* file_name: "Identifier"  */
#line 6439 "parser.y"
  {
	if (CB_FILE_P (cb_ref (yyvsp[0]))) {
		yyval = yyvsp[0];
	} else {
		cb_error_x (yyvsp[0], _("'%s' is not a file name"), CB_NAME (yyvsp[0]));
		yyval = cb_error_node;
	}
  }
#line 12184 "parser.c"
    break;

  case 1303: /* mnemonic_name_list: mnemonic_name  */
#line 6452 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 12190 "parser.c"
    break;

  case 1304: /* mnemonic_name_list: mnemonic_name_list mnemonic_name  */
#line 6454 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 12196 "parser.c"
    break;

  case 1305: /* mnemonic_name: "MNEMONIC NAME"  */
#line 6458 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12202 "parser.c"
    break;

  case 1306: /* procedure_name_list: %empty  */
#line 6464 "parser.y"
                                { yyval = NULL; }
#line 12208 "parser.c"
    break;

  case 1307: /* procedure_name_list: procedure_name_list procedure_name  */
#line 6466 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 12214 "parser.c"
    break;

  case 1308: /* procedure_name: label  */
#line 6471 "parser.y"
  {
	yyval = yyvsp[0];
	CB_REFERENCE (yyval)->offset = CB_TREE (current_section);
	current_program->label_list = cb_cons (yyval, current_program->label_list);
  }
#line 12224 "parser.c"
    break;

  case 1312: /* integer_label: "Literal"  */
#line 6486 "parser.y"
  {
	yyval = cb_build_reference ((char *)(CB_LITERAL (yyvsp[0])->data));
	yyval->source_file = yyvsp[0]->source_file;
	yyval->source_line = yyvsp[0]->source_line;
  }
#line 12234 "parser.c"
    break;

  case 1313: /* reference_list: reference  */
#line 6496 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 12240 "parser.c"
    break;

  case 1314: /* reference_list: reference_list reference  */
#line 6497 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 12246 "parser.c"
    break;

  case 1315: /* reference: qualified_word  */
#line 6502 "parser.y"
  {
	yyval = yyvsp[0];
	current_program->reference_list = cb_cons (yyval, current_program->reference_list);
  }
#line 12255 "parser.c"
    break;

  case 1316: /* opt_reference: %empty  */
#line 6509 "parser.y"
                                { yyval = NULL; }
#line 12261 "parser.c"
    break;

  case 1317: /* opt_reference: reference  */
#line 6510 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12267 "parser.c"
    break;

  case 1320: /* undefined_word: "Identifier"  */
#line 6522 "parser.y"
  {
	yyval = yyvsp[0];
	if (CB_REFERENCE (yyval)->word->count > 0) {
		redefinition_error (yyval);
		yyval = cb_error_node;
	}
  }
#line 12279 "parser.c"
    break;

  case 1321: /* target_x_list: target_x  */
#line 6541 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 12285 "parser.c"
    break;

  case 1322: /* target_x_list: target_x_list target_x  */
#line 6542 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 12291 "parser.c"
    break;

  case 1324: /* target_x: ADDRESS _of identifier_1  */
#line 6547 "parser.y"
                                { yyval = cb_build_address (yyvsp[0]); }
#line 12297 "parser.c"
    break;

  case 1325: /* x_list: x  */
#line 6551 "parser.y"
                                { yyval = cb_list_init (yyvsp[0]); }
#line 12303 "parser.c"
    break;

  case 1326: /* x_list: x_list x  */
#line 6552 "parser.y"
                                { yyval = cb_list_add (yyvsp[-1], yyvsp[0]); }
#line 12309 "parser.c"
    break;

  case 1328: /* x: LENGTH _of identifier_1  */
#line 6557 "parser.y"
                                                { yyval = cb_build_length (yyvsp[0]); }
#line 12315 "parser.c"
    break;

  case 1329: /* x: LENGTH _of basic_literal  */
#line 6558 "parser.y"
                                                { yyval = cb_build_length (yyvsp[0]); }
#line 12321 "parser.c"
    break;

  case 1330: /* x: LENGTH _of function  */
#line 6559 "parser.y"
                                                { yyval = cb_build_length (yyvsp[0]); }
#line 12327 "parser.c"
    break;

  case 1331: /* x: ADDRESS _of prog_or_entry alnum_or_id  */
#line 6560 "parser.y"
                                                { yyval = cb_build_ppointer (yyvsp[0]); }
#line 12333 "parser.c"
    break;

  case 1332: /* x: ADDRESS _of identifier_1  */
#line 6561 "parser.y"
                                                { yyval = cb_build_address (yyvsp[0]); }
#line 12339 "parser.c"
    break;

  case 1337: /* arith_x: LENGTH _of identifier_1  */
#line 6569 "parser.y"
                                                { yyval = cb_build_length (yyvsp[0]); }
#line 12345 "parser.c"
    break;

  case 1338: /* arith_x: LENGTH _of basic_literal  */
#line 6570 "parser.y"
                                                { yyval = cb_build_length (yyvsp[0]); }
#line 12351 "parser.c"
    break;

  case 1339: /* arith_x: LENGTH _of function  */
#line 6571 "parser.y"
                                                { yyval = cb_build_length (yyvsp[0]); }
#line 12357 "parser.c"
    break;

  case 1345: /* alnum_or_id: identifier_1  */
#line 6583 "parser.y"
                        { yyval = yyvsp[0]; }
#line 12363 "parser.c"
    break;

  case 1346: /* alnum_or_id: "Literal"  */
#line 6584 "parser.y"
                        { yyval = yyvsp[0]; }
#line 12369 "parser.c"
    break;

  case 1358: /* num_id_or_lit: ZERO  */
#line 6618 "parser.y"
                                { yyval = cb_zero; }
#line 12375 "parser.c"
    break;

  case 1359: /* identifier: identifier_1  */
#line 6626 "parser.y"
                                { yyval = cb_build_identifier (yyvsp[0]); }
#line 12381 "parser.c"
    break;

  case 1360: /* identifier_1: qualified_word  */
#line 6630 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12387 "parser.c"
    break;

  case 1361: /* identifier_1: qualified_word subref  */
#line 6631 "parser.y"
                                { yyval = yyvsp[-1]; }
#line 12393 "parser.c"
    break;

  case 1362: /* identifier_1: qualified_word refmod  */
#line 6632 "parser.y"
                                { yyval = yyvsp[-1]; }
#line 12399 "parser.c"
    break;

  case 1363: /* identifier_1: qualified_word subref refmod  */
#line 6633 "parser.y"
                                { yyval = yyvsp[-2]; }
#line 12405 "parser.c"
    break;

  case 1364: /* qualified_word: "Identifier"  */
#line 6637 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12411 "parser.c"
    break;

  case 1365: /* qualified_word: "Identifier" in_of qualified_word  */
#line 6638 "parser.y"
                                { yyval = yyvsp[-2]; CB_REFERENCE (yyvsp[-2])->chain = yyvsp[0]; }
#line 12417 "parser.c"
    break;

  case 1366: /* subref: '(' exp_list ')'  */
#line 6643 "parser.y"
  {
	yyval = yyvsp[-3];
	CB_REFERENCE (yyvsp[-3])->subs = cb_list_reverse (yyvsp[-1]);
  }
#line 12426 "parser.c"
    break;

  case 1367: /* refmod: '(' exp ':' ')'  */
#line 6651 "parser.y"
  {
	CB_REFERENCE (yyvsp[-4])->offset = yyvsp[-2];
  }
#line 12434 "parser.c"
    break;

  case 1368: /* refmod: '(' exp ':' exp ')'  */
#line 6655 "parser.y"
  {
	CB_REFERENCE (yyvsp[-5])->offset = yyvsp[-3];
	CB_REFERENCE (yyvsp[-5])->length = yyvsp[-1];
  }
#line 12443 "parser.c"
    break;

  case 1369: /* integer: "Literal"  */
#line 6667 "parser.y"
  {
	if (cb_tree_category (yyvsp[0]) != CB_CATEGORY_NUMERIC) {
		cb_error (_("Integer value expected"));
	} else if (CB_LITERAL (yyvsp[0])->sign < 0 || CB_LITERAL (yyvsp[0])->scale) {
		cb_error (_("Integer value expected"));
	}
	yyval = yyvsp[0];
  }
#line 12456 "parser.c"
    break;

  case 1370: /* literal: basic_literal  */
#line 6678 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12462 "parser.c"
    break;

  case 1371: /* literal: ALL basic_value  */
#line 6680 "parser.y"
  {
	yyval = yyvsp[0];
	if (CB_LITERAL_P (yyvsp[0])) {
		CB_LITERAL (yyvsp[0])->all = 1;
	}
  }
#line 12473 "parser.c"
    break;

  case 1372: /* basic_literal: basic_value  */
#line 6689 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12479 "parser.c"
    break;

  case 1373: /* basic_literal: basic_literal '&' basic_value  */
#line 6690 "parser.y"
                                { yyval = cb_concat_literals (yyvsp[-2], yyvsp[0]); }
#line 12485 "parser.c"
    break;

  case 1374: /* basic_value: "Literal"  */
#line 6694 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12491 "parser.c"
    break;

  case 1375: /* basic_value: SPACE  */
#line 6695 "parser.y"
                                { yyval = cb_space; }
#line 12497 "parser.c"
    break;

  case 1376: /* basic_value: ZERO  */
#line 6696 "parser.y"
                                { yyval = cb_zero; }
#line 12503 "parser.c"
    break;

  case 1377: /* basic_value: QUOTE  */
#line 6697 "parser.y"
                                { yyval = cb_quote; }
#line 12509 "parser.c"
    break;

  case 1378: /* basic_value: "HIGH-VALUE"  */
#line 6698 "parser.y"
                                { yyval = cb_high; }
#line 12515 "parser.c"
    break;

  case 1379: /* basic_value: "LOW-VALUE"  */
#line 6699 "parser.y"
                                { yyval = cb_low; }
#line 12521 "parser.c"
    break;

  case 1380: /* basic_value: "NULL"  */
#line 6700 "parser.y"
                                { yyval = cb_null; }
#line 12527 "parser.c"
    break;

  case 1381: /* function: "FUNCTION CURRENT-DATE" func_refmod  */
#line 6709 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-1], NULL, yyvsp[0]);
  }
#line 12535 "parser.c"
    break;

  case 1382: /* function: "FUNCTION WHEN-COMPILED" func_refmod  */
#line 6713 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-1], NULL, yyvsp[0]);
  }
#line 12543 "parser.c"
    break;

  case 1383: /* function: "FUNCTION UPPER-CASE" '(' exp ')' func_refmod  */
#line 6717 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], cb_list_init (yyvsp[-2]), yyvsp[0]);
  }
#line 12551 "parser.c"
    break;

  case 1384: /* function: "FUNCTION LOWER-CASE" '(' exp ')' func_refmod  */
#line 6721 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], cb_list_init (yyvsp[-2]), yyvsp[0]);
  }
#line 12559 "parser.c"
    break;

  case 1385: /* function: "FUNCTION REVERSE" '(' exp ')' func_refmod  */
#line 6725 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], cb_list_init (yyvsp[-2]), yyvsp[0]);
  }
#line 12567 "parser.c"
    break;

  case 1386: /* function: "FUNCTION CONCATENATE" '(' exp_list ')' func_refmod  */
#line 6729 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  }
#line 12575 "parser.c"
    break;

  case 1387: /* function: "FUNCTION SUBSTITUTE" '(' exp_list ')' func_refmod  */
#line 6733 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  }
#line 12583 "parser.c"
    break;

  case 1388: /* function: "FUNCTION SUBSTITUTE-CASE" '(' exp_list ')' func_refmod  */
#line 6737 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  }
#line 12591 "parser.c"
    break;

  case 1389: /* function: "FUNCTION TRIM" '(' trim_args ')' func_refmod  */
#line 6741 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  }
#line 12599 "parser.c"
    break;

  case 1390: /* function: "FUNCTION NUMVALC" '(' numvalc_args ')'  */
#line 6745 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-3], yyvsp[-1], NULL);
  }
#line 12607 "parser.c"
    break;

  case 1391: /* function: "FUNCTION LOCALE" '(' locale_dt_args ')' func_refmod  */
#line 6749 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-4], yyvsp[-2], yyvsp[0]);
  }
#line 12615 "parser.c"
    break;

  case 1392: /* function: "FUNCTION" func_args  */
#line 6753 "parser.y"
  {
	yyval = cb_build_intrinsic (yyvsp[-1], yyvsp[0], NULL);
  }
#line 12623 "parser.c"
    break;

  case 1393: /* func_refmod: %empty  */
#line 6759 "parser.y"
                                { yyval = NULL; }
#line 12629 "parser.c"
    break;

  case 1394: /* func_refmod: '(' exp ':' ')'  */
#line 6760 "parser.y"
                                { yyval = cb_build_pair (yyvsp[-2], NULL); }
#line 12635 "parser.c"
    break;

  case 1395: /* func_refmod: '(' exp ':' exp ')'  */
#line 6761 "parser.y"
                                { yyval = cb_build_pair (yyvsp[-3], yyvsp[-1]); }
#line 12641 "parser.c"
    break;

  case 1396: /* func_args: %empty  */
#line 6765 "parser.y"
                                { yyval = NULL; }
#line 12647 "parser.c"
    break;

  case 1397: /* func_args: '(' list_func_args ')'  */
#line 6766 "parser.y"
                                { yyval = yyvsp[-1]; }
#line 12653 "parser.c"
    break;

  case 1398: /* list_func_args: %empty  */
#line 6770 "parser.y"
                                { yyval = NULL; }
#line 12659 "parser.c"
    break;

  case 1399: /* list_func_args: exp_list  */
#line 6771 "parser.y"
                                { yyval = yyvsp[0]; }
#line 12665 "parser.c"
    break;

  case 1400: /* trim_args: exp  */
#line 6777 "parser.y"
  {
	cb_tree	x;

	x = cb_list_init (yyvsp[0]);
	yyval = cb_list_add (x, cb_int0);
  }
#line 12676 "parser.c"
    break;

  case 1401: /* trim_args: exp e_sep LEADING  */
#line 6784 "parser.y"
  {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, cb_int1);
  }
#line 12687 "parser.c"
    break;

  case 1402: /* trim_args: exp e_sep TRAILING  */
#line 6791 "parser.y"
  {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, cb_int2);
  }
#line 12698 "parser.c"
    break;

  case 1403: /* numvalc_args: exp  */
#line 6801 "parser.y"
  {
	cb_tree	x;

	x = cb_list_init (yyvsp[0]);
	yyval = cb_list_add (x, cb_null);
  }
#line 12709 "parser.c"
    break;

  case 1404: /* numvalc_args: exp e_sep exp  */
#line 6808 "parser.y"
  {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, yyvsp[0]);
  }
#line 12720 "parser.c"
    break;

  case 1405: /* locale_dt_args: exp  */
#line 6818 "parser.y"
  {
	cb_tree	x;

	x = cb_list_init (yyvsp[0]);
	yyval = cb_list_add (x, cb_null);
  }
#line 12731 "parser.c"
    break;

  case 1406: /* locale_dt_args: exp e_sep reference  */
#line 6825 "parser.y"
  {
	cb_tree	x;

	x = cb_list_init (yyvsp[-2]);
	yyval = cb_list_add (x, cb_ref (yyvsp[0]));
  }
#line 12742 "parser.c"
    break;

  case 1407: /* not_const_word: %empty  */
#line 6838 "parser.y"
  {
	non_const_word = 1;
  }
#line 12750 "parser.c"
    break;

  case 1408: /* flag_all: %empty  */
#line 6848 "parser.y"
                                { yyval = cb_int0; }
#line 12756 "parser.c"
    break;

  case 1409: /* flag_all: ALL  */
#line 6849 "parser.y"
                                { yyval = cb_int1; }
#line 12762 "parser.c"
    break;

  case 1410: /* flag_duplicates: %empty  */
#line 6853 "parser.y"
                                { yyval = cb_int0; }
#line 12768 "parser.c"
    break;

  case 1411: /* flag_duplicates: with_dups  */
#line 6854 "parser.y"
                                { yyval = cb_int1; }
#line 12774 "parser.c"
    break;

  case 1412: /* flag_initialized: %empty  */
#line 6858 "parser.y"
                                { yyval = NULL; }
#line 12780 "parser.c"
    break;

  case 1413: /* flag_initialized: INITIALIZED  */
#line 6859 "parser.y"
                                { yyval = cb_int1; }
#line 12786 "parser.c"
    break;

  case 1414: /* flag_next: %empty  */
#line 6863 "parser.y"
                                { yyval = cb_int0; }
#line 12792 "parser.c"
    break;

  case 1415: /* flag_next: NEXT  */
#line 6864 "parser.y"
                                { yyval = cb_int1; }
#line 12798 "parser.c"
    break;

  case 1416: /* flag_next: PREVIOUS  */
#line 6865 "parser.y"
                                { yyval = cb_int2; }
#line 12804 "parser.c"
    break;

  case 1417: /* flag_not: %empty  */
#line 6869 "parser.y"
                                { yyval = cb_int0; }
#line 12810 "parser.c"
    break;

  case 1418: /* flag_not: NOT  */
#line 6870 "parser.y"
                                { yyval = cb_int1; }
#line 12816 "parser.c"
    break;

  case 1419: /* flag_optional: %empty  */
#line 6874 "parser.y"
                                { yyval = cb_int0; }
#line 12822 "parser.c"
    break;

  case 1420: /* flag_optional: OPTIONAL  */
#line 6875 "parser.y"
                                { yyval = cb_int1; }
#line 12828 "parser.c"
    break;

  case 1421: /* flag_rounded: %empty  */
#line 6879 "parser.y"
                                { yyval = cb_int0; }
#line 12834 "parser.c"
    break;

  case 1422: /* flag_rounded: ROUNDED  */
#line 6880 "parser.y"
                                { yyval = cb_int1; }
#line 12840 "parser.c"
    break;

  case 1423: /* flag_separate: %empty  */
#line 6884 "parser.y"
                                { yyval = cb_int0; }
#line 12846 "parser.c"
    break;

  case 1424: /* flag_separate: SEPARATE _character  */
#line 6885 "parser.y"
                                { yyval = cb_int1; }
#line 12852 "parser.c"
    break;


#line 12856 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= TOKEN_EOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == TOKEN_EOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 6941 "parser.y"

