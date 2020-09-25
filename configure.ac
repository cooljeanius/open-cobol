dnl#                                                       -*- Autoconf -*-
dnl# Process this file with autoconf to produce a configure script.

# Copyright (C) 2001-2009 Keisuke Nishida
# Copyright (C) 2007-2009 Roger While
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to
# the Free Software Foundation, 51 Franklin Street, Fifth Floor
# Boston, MA 02110-1301 USA

AC_PREREQ([2.69.185-b502e])dnl

AC_INIT([OpenCOBOL],[1.1],[open-cobol-list@lists.sourceforge.net],[open-cobol])
AC_CONFIG_SRCDIR([libcob.h])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_TESTDIR([tests])
AC_CONFIG_MACRO_DIR([m4])
AC_CANONICAL_TARGET dnl# calls "_HOST" version of it

# Note for SUN Solaris (gcc)
# export/setenv CFLAGS "-m64 -mptr64"
# export/setenv LDFLAGS "-m64 -mptr64 -L/usr/local/lib/sparcv9"
# ./configure --libdir=/usr/local/lib/sparcv9
#
# Hack for AIX 64 bit (gcc)
# Required -
# export/setenv CFLAGS=-maix64
# export/setenv LDFLAGS=-maix64

if echo ${CFLAGS} | grep 'aix64' 1>/dev/null 2>&1
then
	if test -f /usr/ccs/bin/ar
	then
		AR="/usr/ccs/bin/ar -X64"
	else
		AR="ar -X64"
	fi
	NM="/usr/ccs/bin/nm -X64 -B"
fi

AM_INIT_AUTOMAKE([gnits no-texinfo.tex])
AM_MAINTAINER_MODE
AM_SANITY_CHECK
AC_SEARCH_LIBS([strerror],[cposix])
AM_SET_LEADING_DOT
AC_EXEEXT
AM_MAKE_INCLUDE
# AX_* macros require the autoconf-archive package
AX_CHECK_GNU_MAKE

dnl# Autoheader templates:
AH_TEMPLATE([WITH_DB],[Compile with the Berkeley DB library])dnl
AH_TEMPLATE([USE_DB41],[Use Berkeley DB library new features])dnl
AH_TEMPLATE([WITH_INDEX_EXTFH],[Compile with an external ISAM handler])dnl
AH_TEMPLATE([WITH_SEQRA_EXTFH],[Compile with an external SEQ/RAN handler])dnl
AH_TEMPLATE([WITH_CISAM],[Use CISAM as ISAM handler])dnl
AH_TEMPLATE([WITH_DISAM],[Use DISAM as ISAM handler])dnl
AH_TEMPLATE([WITH_VBISAM],[Use VBISAM as ISAM handler])dnl
AH_TEMPLATE([WITH_LFS64],[Compile with large file system 64])dnl
AH_TEMPLATE([COB_EXPERIMENTAL],
            [Enable experimemental code (Developers only!)])dnl
AH_TEMPLATE([COB_PARAM_CHECK],[Enable CALL parameter checking])dnl
AH_TEMPLATE([COB_EXPORT_DYN],[Compile/link option for exporting symbols])dnl
AH_TEMPLATE([COB_PIC_FLAGS],[Compile/link option for PIC code])dnl
AH_TEMPLATE([COB_SHARED_OPT],[Compile/link option for shared code])dnl
AH_TEMPLATE([COB_STRIP_CMD],[Strip command])dnl
AH_TEMPLATE([USE_LIBDL],[Use system dynamic loader])dnl
AH_TEMPLATE([PATCH_LEVEL],[Define a patch level])dnl
AH_TEMPLATE([WITH_VARSEQ],[Define variable sequential file format])dnl
AH_TEMPLATE([DLLHIDDEN],[Has visibility attribute])dnl
AH_TEMPLATE([HAVE_PSIGN_OPT],[Has -Wno-pointer-sign])dnl
AH_TEMPLATE([HAVE_ATTRIBUTE_ALIGNED],[Has __attribute__((aligned))])dnl
AH_TEMPLATE([HAVE_TIMEZONE],[Has timezone variable])dnl
AH_TEMPLATE([COB_EXEEXT],[Executable extension])dnl
AH_TEMPLATE([COB_EXTRA_FLAGS],[Extra Compiler Flags])dnl
AH_TEMPLATE([__USE_STRING_INLINES],[Compiler optimization])dnl
AH_TEMPLATE([COB_HAS_INLINE],[Can use inline keyword])dnl
AH_TEMPLATE([COB_NO_SELFOPEN],[Can not dlopen self])dnl
AH_TEMPLATE([COB_STRFTIME],[Can use strftime for timezone])dnl
AH_TEMPLATE([COB_LI_IS_LL],[long int is long long])dnl
AH_TEMPLATE([HAVE_COLOR_SET],[curses has color_set function])dnl

AC_DEFINE([__USE_STRING_INLINES])dnl

LIBCOB_LIBS="-lm"
LIBCOB_CFLAGS="${lt_prog_compiler_pic}"

save_libs="${LIBS}"

AC_PROG_CC([gcc xlc cc])
AM_PROG_CC_C_O
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_YACC
AC_PROG_EGREP
AC_PROG_GCC_TRADITIONAL

# Configure options.

COB_CC=""
AC_ARG_WITH([cc],
  [AS_HELP_STRING([--with-cc=<cc>],
                  [(OpenCOBOL) specify the C compiler used by cobc])],
  [COB_CC=${withval}],[COB_CC=${CC}])dnl

AC_ARG_WITH([seqra-extfh],
  [AS_HELP_STRING([--with-seqra-extfh],
                  [(OpenCOBOL) Use external SEQ/RAN file handler])],
  [if test "x${with_seqra_extfh}" = "xyes"
   then
	AC_DEFINE([WITH_SEQRA_EXTFH])
   fi],[])dnl

AC_ARG_WITH([cisam],
  [AS_HELP_STRING([--with-cisam],[(OpenCOBOL) Use CISAM for ISAM I/O])],
  [if test "x${with_cisam}" = "xyes"
   then
	AC_CHECK_HEADERS([isam.h],[],
                         [AC_MSG_ERROR([isam.h is required for CISAM])])
	AC_CHECK_LIB([ifisam],[isopen],[],
                     [AC_MSG_ERROR([libifisam is required for CISAM])],
                     [ifisamx])
	AC_DEFINE([WITH_CISAM])
	LIBCOB_LIBS="${LIBCOB_LIBS} -lifisam -lifisamx"
   fi],[])dnl

if test "x${with_cisam}" != "xyes"
then
 AC_ARG_WITH([disam],
  [AS_HELP_STRING([--with-disam],[(OpenCOBOL) Use DISAM for ISAM I/O])],
  [if test "x${with_disam}" = "xyes"
   then
	AC_CHECK_HEADERS([disam.h],[],
                         [AC_MSG_ERROR([disam.h is required for DISAM])])
	AC_CHECK_LIB([disam],[isopen],[],
                     [AC_MSG_ERROR([libdisam is required for DISAM])])
	AC_DEFINE([WITH_DISAM])
	LIBCOB_LIBS="${LIBCOB_LIBS} -ldisam"
   fi],[])
fi

if test "x${with_cisam}" != "yes" -a "x${with_disam}" != "yes"
then
AC_ARG_WITH([vbisam],
  [AS_HELP_STRING([--with-vbisam],[(OpenCOBOL) Use VBISAM for ISAM I/O])],
  [if test "x${with_vbisam}" = "xyes"
   then
	AC_CHECK_HEADERS([vbisam.h],[],
                         [AC_MSG_ERROR([vbisam.h is required for VBISAM])])
	AC_CHECK_LIB([vbisam],[isopen],[],
                     [AC_MSG_ERROR([libvbisam is required for VBISAM])])
	AC_DEFINE([WITH_VBISAM])
	LIBCOB_LIBS="${LIBCOB_LIBS} -lvbisam"
   fi],[])
fi

LIBDB=""

if test "x${with_cisam}" != "xyes" -a "x${with_disam}" != "xyes" -a "x${with_vbisam}" != "xyes"
then
 AC_ARG_WITH([index-extfh],
  [AS_HELP_STRING([--with-index-extfh],
                  [(OpenCOBOL) Use external ISAM file handler])],
  [if test "x${with_index_extfh}" = "xyes"
   then
	AC_DEFINE([WITH_INDEX_EXTFH])
   fi],
  [AC_ARG_WITH([db1],
   [AS_HELP_STRING([--with-db1],
                   [(OpenCOBOL) use Berkeley DB 1.85 (libdb-1.85)])],
   [LIBDB="1"
    AC_DEFINE([WITH_DB],[1])],
	[AC_ARG_WITH([db],
		[AS_HELP_STRING([--with-db],
                                [(OpenCOBOL) use Berkeley DB 3.0 or later (libdb)(default)])],
		[if test "x${with_db}" = "xyes"
		 then
		 LIBDB="3"
		 AC_DEFINE([WITH_DB],[3])
		 fi],
		[LIBDB="3"
		 AC_DEFINE([WITH_DB],[3])])])])
fi

AC_ARG_WITH([lfs64],
  [AS_HELP_STRING([--with-lfs64],
                  [(OpenCOBOL) use large file system for file I/O (default)])],
  [if test "x${with_lfs64}" = "xyes"
   then
	AC_DEFINE([WITH_LFS64])
   fi],
  [AC_DEFINE([WITH_LFS64])])dnl

DEFINE_DL="no"
COB_TRY_DL="yes"

AC_ARG_WITH([dl],
  [AS_HELP_STRING([--with-dl],
                  [(OpenCOBOL) use system dynamic loader (default)])],
  [case ${with_dl} in  
    yes)	COB_TRY_DL="yes"
		;;
    no)		COB_TRY_DL="no"
		;;
    *)		AC_MSG_ERROR(["--with/without-dl can not have a value"])
		;;
  esac])dnl

GEN_DEBUG_OPT="no"
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
                  [(OpenCOBOL) enable -g C compiler debug option])],
  [if test "x${enable_debug}" = "xyes"
   then
	GEN_DEBUG_OPT="yes"
   fi])dnl

AC_ARG_ENABLE([experimental],
  [AS_HELP_STRING([--enable-experimental],
                  [(OpenCOBOL) enable experimental code (Developers only!)])],
  [if test "x${enable_experimental}" = "xyes"
   then
	AC_DEFINE([COB_EXPERIMENTAL])
   fi])dnl

AC_ARG_ENABLE([param-check],
  [AS_HELP_STRING([--enable-param-check],
                  [(OpenCOBOL) enable CALL parameter checking])],
  [if test "x${enable_param_check}" = "xyes"
   then
	AC_DEFINE([COB_PARAM_CHECK])
   fi])dnl

PATCH_LEVEL=0
AC_ARG_WITH([patch-level],
  [AS_HELP_STRING([--with-patch-level],
                  [(OpenCOBOL) define a patch level (default 0)])],
[case ${with_patch_level} in  
    yes)	AC_MSG_ERROR(["You must give --with-patch-level an argument."])
		;;
    no)		AC_MSG_ERROR(["--without-patch-level not supported."])
		;;
    [[0-9]]*)	PATCH_LEVEL=${with_patch_level}
		;;
    *)		AC_MSG_ERROR(["You must use a numeric patch level"])
		;;
esac])
AC_DEFINE_UNQUOTED([PATCH_LEVEL],[${PATCH_LEVEL}])dnl

WITH_VARSEQ=0
AC_ARG_WITH([varseq],
[AS_HELP_STRING([--with-varseq],
                [(OpenCOBOL) define variable sequential format (default 0)])],
[case ${with_varseq} in  
    yes)	AC_MSG_ERROR(["You must give --with-varseq an argument."])
		;;
    no)		AC_MSG_ERROR(["--without-varseq not supported."])
		;;
    [[0-3]])	WITH_VARSEQ=${with_varseq}
		;;
    *)		AC_MSG_ERROR(["Invalid --with-varseq argument"])
		;;
esac])
AC_DEFINE_UNQUOTED([WITH_VARSEQ],[${WITH_VARSEQ}])dnl

# Checks for programs.
# Stop the stupid tests for C++ and Fortran
AC_PROVIDE([AC_PROG_F77])dnl
AC_PROVIDE([AC_PROG_CXX])dnl
  with_tags=""
AC_PROG_LN_S
AC_PROG_INSTALL
LT_INIT([win32-dll dlopen])
LT_LANG([C])
AC_PROG_MAKE_SET
AC_PROG_LEX
AC_PROG_RANLIB
PKG_PROG_PKG_CONFIG
LTVERSION_VERSION

# Checks for libraries.
AC_CHECK_LIB([c],[printf])
AC_CHECK_LIB([m],[sqrt])dnl

# Checks for header files.
# Autoupdate added the following line to ensure that your configure
# script's behavior did not change.  It is probably safe to remove.
AC_CHECK_INCLUDES_DEFAULT
AC_CHECK_HEADERS([dlfcn.h fcntl.h langinfo.h libintl.h locale.h \
                  malloc.h malloc/malloc.h signal.h stddef.h stdlib.h \
                  stdint.h string.h strings.h sys/time.h sys/timeb.h \
                  sys/types.h unistd.h wchar.h])dnl

# Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_BIGENDIAN
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_STRUCT_TM
# AX_* macros require the autoconf-archive package
AX_C___ATTRIBUTE__
AC_C_INLINE
if test "x${ac_cv_c_inline}" != "xno" 
then
	AC_DEFINE([COB_HAS_INLINE],[1])
fi


# Checks for library functions.
AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([fcntl getcwd gettimeofday memmove memset mkdir modf \
                nl_langinfo pow putenv rmdir select setlocale sqrt \
                strcasecmp strchr strdup strerror strncasecmp strpbrk \
                strrchr strstr strtol])dnl

# Check for timezone
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#include <time.h>]],
                                   [[timezone = 3600;]])],
	[AC_DEFINE([HAVE_TIMEZONE],[1])],
	[])dnl

# Checks for internationalization stuff
AM_ICONV
AM_LANGINFO_CODESET

# Checks for getopt_long.
# Cygwin has getopt_long_only prototype in kpathsea/getopt.h
# FreeBSD has gnugetopt library - needs checking

AC_CHECK_FUNC([getopt_long_only],
  [AC_CHECK_HEADERS([kpathsea/getopt.h getopt.h],[],[])],
  [AC_LIBOBJ([getopt])
   AC_LIBOBJ([getopt1])
   AC_LIBSOURCE([getopt.h])])dnl

# Checks for ppl (which depends on gmp)
AM_PATH_PPL

# Checks for gmp.
AC_CHECK_HEADERS([gmp.h],[],[AC_MSG_ERROR([gmp.h is required])])
AC_CHECK_HEADERS([gmpxx.h])
AC_CHECK_LIB([gmp],[main])
AC_CHECK_LIB([gmpxx],[main])
AC_CHECK_LIB([gmp],[__gmp_randinit],[],
             [AC_MSG_WARN([GMP 3 or later is required])])
LIBCOB_LIBS="${LIBCOB_LIBS} -lgmp"

# Solaris has nanosleep in other libraries
AC_LINK_IFELSE([AC_LANG_PROGRAM([[#include <time.h>]],
  [[nanosleep(NULL, NULL);]])],
  [],
  [AC_CHECK_LIB([rt],[nanosleep])
   if test "x${ac_cv_lib_rt_nanosleep}" = "xyes"
   then
     LIBCOB_LIBS="${LIBCOB_LIBS} -lrt"
   else
     AC_CHECK_LIB([posix4],[nanosleep])
     if test "x${ac_cv_lib_posix4_nanosleep}" = "xyes"
     then
       LIBCOB_LIBS="${LIBCOB_LIBS} -lposix4"
     fi
   fi])dnl

# Checks for gettext.
AM_GNU_GETTEXT([external])
AM_GNU_GETTEXT_VERSION([0.18.3])
if test "x${LTLIBINTL}" != "x"
then
  COBC_LIBS="${COBC_LIBS} ${LTLIBINTL}"
  LIBCOB_LIBS="${LIBCOB_LIBS} ${LTLIBINTL}"
fi

# Checks for ncurses/pdcurses/curses.
USE_NCURSES="no"
AC_CHECK_LIB([ncurses],[initscr])
if test "x${ac_cv_lib_ncurses_initscr}" = "xyes"
then
  LIBCOB_LIBS="${LIBCOB_LIBS} -lncurses"
  AC_CHECK_HEADERS([ncurses.h],[USE_NCURSES="yes"],
    [AC_CHECK_HEADERS([ncurses/ncurses.h],[USE_NCURSES="ncurses"],[],[])],[])
else
  AC_CHECK_LIB([pdcurses],[initscr])
  if test "x${ac_cv_lib_pdcurses_initscr}" = "xyes"
  then
    LIBCOB_LIBS="${LIBCOB_LIBS} -lpdcurses"
    AC_CHECK_HEADERS([pdcurses.h],[USE_NCURSES="pdcurses"],[],[])
  else
    AC_CHECK_LIB([curses],[initscr])
    if test "x${ac_cv_lib_curses_initscr}" = "xyes"
    then
      LIBCOB_LIBS="${LIBCOB_LIBS} -lcurses"
      AC_CHECK_HEADERS([curses.h],[USE_NCURSES="curses"],[],[])
    fi
  fi
fi

if test "${USE_NCURSES}" != "no"
then
  AC_LINK_IFELSE([AC_LANG_PROGRAM([[
  #ifdef HAVE_NCURSES_H
  #include <ncurses.h>
  #elif defined(HAVE_NCURSES_NCURSES_H)
  #include <ncurses/ncurses.h>
  #elif defined(HAVE_PDCURSES_H)
  #include <pdcurses.h>
  #elif defined(HAVE_CURSES_H)
  #include <curses.h>
  #endif]],[[
  color_set(0, NULL);]])],
  [AC_DEFINE([HAVE_COLOR_SET])],
  [],
  [])
fi

# Checks for db.
# AX_* macros require the autoconf-archive package
AX_BERKELEY_DB
USE_DB="no"
HAS_DB41="no"
AC_SUBST([LIBDB])
if test "${LIBDB}" = "1"
then
       AC_CHECK_HEADERS([db1/db.h],
         [AC_DEFINE(HAVE_DB1_DB_H)],
         [AC_MSG_ERROR([db1/db.h is required])])
       AC_CHECK_LIB([db1],[dbopen],
         [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb1"],
         [AC_MSG_ERROR([libdb1 is required])])
elif test "${LIBDB}" = "3"
then
	AC_RUN_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>
		#include <stdlib.h>
		#include <db.h>]],[[
		printf("checking for BDB db.h version >= 4.1 ... ");
		#if (DB_VERSION_MAJOR > 4) || ((DB_VERSION_MAJOR == 4) && (DB_VERSION_MINOR > 0))
		printf("yes (%d.%d)\n", DB_VERSION_MAJOR, DB_VERSION_MINOR);
		return 0;
		#else
		printf("no (%d.%d)\n", DB_VERSION_MAJOR, DB_VERSION_MINOR);
		return 1;
		#endif]])],
		[HAS_DB41="yes"],
		[HAS_DB41="no"],
		[HAS_DB41="unknown"])
	if test "${HAS_DB41}" = "yes"
	then
		AC_DEFINE([USE_DB41])
		MYOLDLIBS="${LIBS}"
		export MYOCLIBS
		for MYOCLIBS in db db-4.5 db-4.4 db-4.3 db-4.2 db-4.1
		do
			LIBS="${MYOLDLIBS} -l${MYOCLIBS}"
			AC_RUN_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>
			#include <stdlib.h>
			#include <db.h>]],[[
			int major, minor, patch;
			printf("checking for BDB 4.1 compatibility in %s ... ", getenv("MYOCLIBS"));
			db_version(&major, &minor, &patch);
			if (major == DB_VERSION_MAJOR && minor == DB_VERSION_MINOR) {
				printf("yes\n");
				return 0;
			}
			printf("no\n");
			return 1;]])],
			[USE_DB="yes"],
			[USE_DB="no"],
			[USE_DB="no"])
			if test "${USE_DB}" != "no"
			then
				LIBCOB_LIBS="${LIBCOB_LIBS} -l${MYOCLIBS}"
				break
			fi
		done
		LIBS="${MYOLDLIBS}"
		if test "${USE_DB}" != "yes"
		then
			AC_MSG_ERROR([Include file db.h implies version >=4.1 but no library found])
		fi
	else
		AC_CHECK_HEADERS([db.h db_185.h db3/db_185.h db4/db_185.h \
                    db4.1/db_185.h db4.2/db_185.h db4.3/db_185.h db44/db.h \
                    db44/db_cxx.h db4.4/db_185.h db4.5/db_185.h \
                    db4.5/db_185.h db46/db.h db46/db_cxx.h db4.6/db_185.h])
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-6.0],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-6.0"],
		  [AC_CHECK_LIB([db-6.0],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-6.0"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-5.3],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-5.3"],
		  [AC_CHECK_LIB([db-5.3],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-5.3"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-5.1],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-5.1"],
		  [AC_CHECK_LIB([db-5.1],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-5.1"],[])])
		fi
		if test "$USE_DB" != "yes"
		then
		AC_CHECK_LIB([db-4.8],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.8"],
		  [AC_CHECK_LIB([db-4.8],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.8"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-4.7],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.7"],
		  [AC_CHECK_LIB([db-4.7],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.7"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-4.6],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.6"],
		  [AC_CHECK_LIB([db-4.6],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.6"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-4.5],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.5"],
		  [AC_CHECK_LIB([db-4.5],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.5"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-4.4],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.4"],
		  [AC_CHECK_LIB([db-4.4],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.4"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-4.3],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.3"],
		  [AC_CHECK_LIB([db-4.3],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.3"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-4.2],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.2"],
		  [AC_CHECK_LIB([db-4.2],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.2"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db-4.1],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.1"],
		  [AC_CHECK_LIB([db-4.1],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4.1"],[])])
		fi
		if test "${USE_DB}" != "yes"
		then
			if test "${HAS_DB41}" != "no"
			then
				AC_MSG_WARN([Include file db.h implies version >=4.1 but no library found])
			fi
		AC_CHECK_LIB([db-4],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4"],
		  [AC_CHECK_LIB([db-4],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb-4"],[])])
		fi
		
		if test "${USE_DB}" != "yes"
		then
		AC_CHECK_LIB([db],[__db_open],
		[USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb"],
		  [AC_CHECK_LIB([db],[dbopen],
		    [USE_DB="yes" LIBCOB_LIBS="${LIBCOB_LIBS} -ldb"],
			[AC_MSG_ERROR([libdb is required])])])
		fi
	fi
fi

# Checks for dl/ltdl.
AC_RUN_IFELSE([AC_LANG_PROGRAM([[]],[[
  #ifdef _WIN32
   return 0;
  #else
   return 1;
  #endif]])],
  [DEFINE_DL="yes"],
  [DEFINE_DL="no"],
  [DEFINE_DL="no"])dnl

if test "${DEFINE_DL}" = "no" -a "${COB_TRY_DL}" = "yes"
then
  if test "x${ac_cv_header_dlfcn_h}" = "xyes"
  then
    AC_CHECK_LIB([c],[dlopen],[DEFINE_DL="yes"],[])
    if test "${DEFINE_DL}" = "no"
    then
      AC_CHECK_LIB([dl],[dlopen],[DEFINE_DL="yes"],[])
      if test "${DEFINE_DL}" = "yes"
      then
	AC_DEFINE([USE_LIBDL])
	LIBCOB_LIBS="${LIBCOB_LIBS} -ldl"
      fi
    else
	AC_DEFINE([USE_LIBDL])
    fi
  fi
fi
if test "${DEFINE_DL}" = "no"
then
  AC_CHECK_HEADERS([ltdl.h],[],[AC_MSG_ERROR([ltdl.h is required])])
  AC_CHECK_LIB([ltdl],[lt_dlopen],[],[AC_MSG_ERROR([libltdl is required])])
  LIBCOB_LIBS="${LIBCOB_LIBS} -lltdl"
fi

# Checks for workable strftime
AC_RUN_IFELSE([AC_LANG_PROGRAM([[#include <stdio.h>
	#include <time.h>]],[[
	time_t	ticks;
	int	ret;
	char	buff[16];
	ticks = time(NULL);
	ret = strftime(buff, 15, "%z", localtime(&ticks));
	if (ret != 5) {
		return 1;
	}
	if ((buff[0] != '+') && (buff[0] != '-')) {
		return 1;
	}
	return 0;]])],
	[AC_DEFINE([COB_STRFTIME])],
	[:],
	[:])dnl

# Checks for size of long
AC_RUN_IFELSE([AC_LANG_PROGRAM([[]],[[
	if (sizeof(long int) == sizeof(long long))
		return 0;
	return 1;
	]])],
	[AC_DEFINE([COB_LI_IS_LL])],
	[:],
	[:])dnl

# OpenCOBOL Configuration

if test "x${prefix}" = "xNONE"
then
  if test "x${includedir}" = "x\${prefix}/include"
  then
    COB_CFLAGS="-I${ac_default_prefix}/include"
  else
    COB_CFLAGS="-I${includedir}"
  fi
else
  if test "x${includedir}" = "x\${prefix}/include"
  then
    if test "x${prefix}" = "x/usr"
    then
      COB_CFLAGS=""
    else
      COB_CFLAGS="-I${prefix}/include"
    fi
  else
    COB_CFLAGS="-I${includedir}"
  fi
fi

if test "x${CPPFLAGS}" != "x"
then
  COB_CFLAGS="${COB_CFLAGS} ${CPPFLAGS}"
fi

COB_LIBS="-L${libdir} -lcob ${LIBCOB_LIBS}"
COB_LDFLAGS=""
if test "x${LDFLAGS}" != "x"
then
  COB_LIBS="${LDFLAGS} ${COB_LIBS}"
  COB_LDFLAGS="${LDFLAGS}"
fi

COB_CONFIG_DIR="${datadir}/${PACKAGE_TARNAME}/config"
COB_COPY_DIR="${datadir}/${PACKAGE_TARNAME}/copy"
COB_LIBRARY_PATH="${libdir}/${PACKAGE_TARNAME}"
COB_MODULE_EXT=`echo "${shlibext}" | sed -e 's/dll\.a/dll/'`
LIBS="${save_libs}"
COB_EXPORT_DYN="`eval echo ${export_dynamic_flag_spec}`"
COB_PIC_FLAGS=`echo "${lt_prog_compiler_pic}" | sed -e 's/^ //'`
COB_SHARED_OPT="-shared"
COB_EXEEXT="${EXEEXT}"
COB_EXTRA_FLAGS=""

if test "x${GEN_DEBUG_OPT}" = "no"
then
        CFLAGS=`echo "${CFLAGS}" | sed -e 's/^-g//' -e 's/-g$//' -e 's/-g / /'`
fi

# Include CFLAGS in COB_CFLAGS without optimization/debug options

cob_temp_flags=`echo "${CFLAGS}" | sed -e 's/^@<:@+-@:>@O@<:@0-9s@:>@//' -e 's/@<:@+-@:>@O@<:@0-9s@:>@$//' -e 's/@<:@+-@:>@O@<:@0-9s@:>@ / /'`
cob_temp_flags=`echo "${cob_temp_flags}" | sed -e 's/^-O//' -e 's/-O$//' -e 's/-O / /' -e 's/^-g//' -e 's/-g$//' -e 's/-g / /'`

COB_CFLAGS="${COB_CFLAGS} ${cob_temp_flags}"

if test "`basename ${COB_CC}`" = "gcc"
then
	cob_temp_flags="`${COB_CC} ${srcdir}/cpucheck.c -o cpucheck 1>/dev/null 2>&1 && ./cpucheck 2>/dev/null`"
	rm -f cpucheck${EXEEXT}
	if test "x${cob_temp_flags}" != "x"
	then
		CFLAGS="${CFLAGS} ${cob_temp_flags} -finline-functions"
		COB_EXTRA_FLAGS="${cob_temp_flags}"
	else
		CFLAGS="${CFLAGS} -finline-functions"
	fi
fi

# Check gcc 4 option
MYOLDCFLAGS="${CFLAGS}"
CFLAGS="${CFLAGS} -Wno-pointer-sign"
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],[[int testint;]])],
	[AC_DEFINE([HAVE_PSIGN_OPT],[1])],
	[])
CFLAGS="$MYOLDCFLAGS"

# Check if aligned attribute works
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[]],
	[[char testchar[4] __attribute__((aligned));]])],
	[AC_DEFINE([HAVE_ATTRIBUTE_ALIGNED],[1])],
	[])dnl

# Special stuff

AH_VERBATIM([_XOPEN_SOURCE_EXTENDED],
[/* Define to 1 if on HPUX.  */
#ifndef _XOPEN_SOURCE_EXTENDED
# undef _XOPEN_SOURCE_EXTENDED
#endif])dnl

COB_FIX_LIB="${COB_EXPORT_DYN}"
case ${host_os} in
  mingw*)
	if test "x${prefix}" = "xNONE"
	then
	COB_CONFIG_DIR="`cd /usr && pwd -W`/local/share/${PACKAGE_TARNAME}/config"
	COB_COPY_DIR="`cd /usr && pwd -W`/local/share/${PACKAGE_TARNAME}/copy"
	fi
	COB_EXPORT_DYN="-Wl,--export-all-symbols -Wl,--enable-auto-import"
	COB_FIX_LIB="${COB_EXPORT_DYN}"
	;;
  cygwin*)
	COB_EXPORT_DYN="-Wl,--export-all-symbols -Wl,--enable-auto-import"
	COB_FIX_LIB="${COB_EXPORT_DYN}"
	;;
  darwin* | rhapsody*)
	COB_SHARED_OPT="-bundle -flat_namespace -undefined suppress"
	;;
  hpux*)
	if test "`basename ${CC}`" != "gcc"
	then
		COB_SHARED_OPT="-b"
		AC_DEFINE([_XOPEN_SOURCE_EXTENDED],[1])
		rm -f hptest*
		echo 'int main() { return 0; }' > hptest.c
		${CC} ${CFLAGS} +Olit=all -o hptest hptest.c > hptest.out 2>&1
		if test $? -ne 0 -o -s hptest.out
		then
			CFLAGS="${CFLAGS} +ESlit"
			COB_CFLAGS="${COB_CFLAGS} +ESlit -w"
		else
			CFLAGS="${CFLAGS} +Olit=all"
			COB_CFLAGS="${COB_CFLAGS} +Olit=all -w"
		fi
		rm -f hptest*
	fi
	;;
  aix*)
	COB_EXPORT_DYN="-Wl,-bexpfull"
	if test "`basename ${CC}`" != "gcc"
	then
		CFLAGS="${CFLAGS} -O2 -Q -qro -qroconst"
		COB_SHARED_OPT="-G"
		COB_FIX_LIB=""
		# COB_FIX_LIB="-Wc,-G ${COB_EXPORT_DYN}"
		# COB_CFLAGS="${COB_CFLAGS} -qchars=signed"
	else
		COB_FIX_LIB="${COB_EXPORT_DYN}"
	fi
	;;
  solaris*)
	if test "`basename ${CC}`" != "gcc"
	then
		COB_SHARED_OPT="-G"
	fi
	;;
esac

if test "`basename ${CC}`" = "gcc"
then
	CFLAGS="${CFLAGS} -fsigned-char -Wall -Wwrite-strings -Wmissing-prototypes -Wno-format-y2k"
fi

if test "x${lt_cv_dlopen_self}" != "xyes"
then
	AC_DEFINE([COB_NO_SELFOPEN],[1])
fi

# Generate the output

AC_DEFINE_UNQUOTED([COB_EXPORT_DYN],["${COB_EXPORT_DYN}"])dnl
AC_DEFINE_UNQUOTED([COB_PIC_FLAGS],["${COB_PIC_FLAGS}"])dnl
AC_DEFINE_UNQUOTED([COB_SHARED_OPT],["${COB_SHARED_OPT}"])dnl
AC_DEFINE_UNQUOTED([COB_EXEEXT],["${COB_EXEEXT}"])dnl
AC_DEFINE_UNQUOTED([COB_EXTRA_FLAGS],["${COB_EXTRA_FLAGS}"])dnl
  ## strip:
if test "x${striplib}" != "x"
then
  AC_DEFINE_UNQUOTED([COB_STRIP_CMD],["${striplib}"])
  AC_SUBST([COB_STRIP_CMD])
fi
AC_SUBST([COB_CC])dnl
AC_SUBST([COB_CFLAGS])dnl
AC_SUBST([COB_LDFLAGS])dnl
AC_SUBST([COB_LIBS])dnl
AC_SUBST([COB_CONFIG_DIR])dnl
AC_SUBST([COB_COPY_DIR])dnl
AC_SUBST([COB_LIBRARY_PATH])dnl
AC_SUBST([COB_MODULE_EXT])dnl
AC_SUBST([COBC_LIBS])dnl
AC_SUBST([LIBCOB_CFLAGS])dnl
AC_SUBST([LIBCOB_LIBS])dnl
AC_SUBST([COB_EXPORT_DYN])dnl
AC_SUBST([COB_PIC_FLAGS])dnl
AC_SUBST([COB_SHARED_OPT])dnl
  COB_BIGENDIAN="${ac_cv_c_bigendian}"
AC_SUBST([COB_BIGENDIAN])dnl
AC_SUBST([COB_FIX_LIB])dnl
AC_SUBST([COB_HAS_INLINE])dnl

AC_CONFIG_FILES([cob-config
	Makefile lib/Makefile libcob/Makefile
	cobc/Makefile bin/Makefile po/Makefile.in texi/Makefile config/Makefile
	copy/Makefile tests/atlocal tests/Makefile tests/cobol85/Makefile])
AC_OUTPUT

echo ""
echo "OpenCOBOL Configuration:"
echo ""
echo "  CC                   ${CC}"
echo "  COB_CC               ${COB_CC}"
echo "  CFLAGS               ${CFLAGS}"
echo "  COB_CFLAGS           ${COB_CFLAGS}"
echo "  COB_EXTRA_FLAGS      ${COB_EXTRA_FLAGS}"
echo "  LDFLAGS              ${LDFLAGS}"
echo "  COB_LDFLAGS          ${COB_LDFLAGS}"
if test "x${COBC_LIBS}" != "x"
then
  echo "  COBC_LIBS            ${COBC_LIBS}"
fi
echo "  COB_LIBS             ${COB_LIBS}"
echo "  COB_CONFIG_DIR       ${COB_CONFIG_DIR}"
echo "  COB_COPY_DIR         ${COB_COPY_DIR}"
echo "  COB_LIBRARY_PATH     ${COB_LIBRARY_PATH}"
echo "  COB_MODULE_EXT       ${COB_MODULE_EXT}"
echo "  COB_SHARED_OPT       ${COB_SHARED_OPT}"
echo "  COB_PIC_FLAGS        ${COB_PIC_FLAGS}"
echo "  COB_EXPORT_DYN       ${COB_EXPORT_DYN}"
if test "x${striplib}" != "x"
then
  echo "  COB_STRIP_CMD        ${striplib}"
fi
if test "${DEFINE_DL}" = "yes" 
then
  echo "  Dynamic loading      System"
else
  echo "  Dynamic loading      Libtool"
fi
echo ""
echo "  Use gettext for international messages:      ${USE_NLS}"
if test "x${with_seqra_extfh}" = "xyes"
then
  echo "  Use external SEQ/RAN file handler            yes"
fi
if test "x${with_index_extfh}" = "xyes"
then
  echo "  Use external ISAM file handler               yes"
elif test "x${with_cisam}" = "xyes"
then
  echo "  Use CISAM for file I/O                       yes"
elif test "x${with_disam}" = "xyes"
then
  echo "  Use DISAM for file I/O                       yes"
elif test "x${with_vbisam}" = "xyes"
then
  echo "  Use VBISAM for file I/O                      yes"
else
  echo "  Use Berkeley DB for file I/O:                ${USE_DB}"
  echo "  Use enhanced Berkeley DB (>= 4.1)            ${HAS_DB41}"
fi
echo "  Use fcntl for file locking:                  ${ac_cv_func_fcntl}"
echo "  Use ncurses/pdcurses/curses for screen I/O:  ${USE_NCURSES}"
echo ""
