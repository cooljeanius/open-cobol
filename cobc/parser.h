/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    TOKEN_EOF = 0,                 /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ACCEPT = 258,                  /* ACCEPT  */
    ACCESS = 259,                  /* ACCESS  */
    ADD = 260,                     /* ADD  */
    ADDRESS = 261,                 /* ADDRESS  */
    ADVANCING = 262,               /* ADVANCING  */
    AFTER = 263,                   /* AFTER  */
    ALL = 264,                     /* ALL  */
    ALLOCATE = 265,                /* ALLOCATE  */
    ALPHABET = 266,                /* ALPHABET  */
    ALPHABETIC = 267,              /* ALPHABETIC  */
    ALPHABETIC_LOWER = 268,        /* "ALPHABETIC-LOWER"  */
    ALPHABETIC_UPPER = 269,        /* "ALPHABETIC-UPPER"  */
    ALPHANUMERIC = 270,            /* ALPHANUMERIC  */
    ALPHANUMERIC_EDITED = 271,     /* "ALPHANUMERIC-EDITED"  */
    ALSO = 272,                    /* ALSO  */
    ALTER = 273,                   /* ALTER  */
    ALTERNATE = 274,               /* ALTERNATE  */
    AND = 275,                     /* AND  */
    ANY = 276,                     /* ANY  */
    ARE = 277,                     /* ARE  */
    AREA = 278,                    /* AREA  */
    ARGUMENT_NUMBER = 279,         /* "ARGUMENT-NUMBER"  */
    ARGUMENT_VALUE = 280,          /* "ARGUMENT-VALUE"  */
    AS = 281,                      /* AS  */
    ASCENDING = 282,               /* ASCENDING  */
    ASSIGN = 283,                  /* ASSIGN  */
    AT = 284,                      /* AT  */
    AUTO = 285,                    /* AUTO  */
    AUTOMATIC = 286,               /* AUTOMATIC  */
    BACKGROUND_COLOR = 287,        /* "BACKGROUND-COLOR"  */
    BASED = 288,                   /* BASED  */
    BEFORE = 289,                  /* BEFORE  */
    BELL = 290,                    /* BELL  */
    BINARY = 291,                  /* BINARY  */
    BINARY_C_LONG = 292,           /* "BINARY-C-LONG"  */
    BINARY_CHAR = 293,             /* "BINARY-CHAR"  */
    BINARY_DOUBLE = 294,           /* "BINARY-DOUBLE"  */
    BINARY_LONG = 295,             /* "BINARY-LONG"  */
    BINARY_SHORT = 296,            /* "BINARY-SHORT"  */
    BLANK = 297,                   /* BLANK  */
    BLANK_LINE = 298,              /* "BLANK-LINE"  */
    BLANK_SCREEN = 299,            /* "BLANK-SCREEN"  */
    BLINK = 300,                   /* BLINK  */
    BLOCK = 301,                   /* BLOCK  */
    BOTTOM = 302,                  /* BOTTOM  */
    BY = 303,                      /* BY  */
    BYTE_LENGTH = 304,             /* "BYTE-LENGTH"  */
    CALL = 305,                    /* CALL  */
    CANCEL = 306,                  /* CANCEL  */
    CH = 307,                      /* CH  */
    CHAINING = 308,                /* CHAINING  */
    CHARACTER = 309,               /* CHARACTER  */
    CHARACTERS = 310,              /* CHARACTERS  */
    CLASS = 311,                   /* CLASS  */
    CLOSE = 312,                   /* CLOSE  */
    CODE = 313,                    /* CODE  */
    CODE_SET = 314,                /* "CODE-SET"  */
    COLLATING = 315,               /* COLLATING  */
    COL = 316,                     /* COL  */
    COLS = 317,                    /* COLS  */
    COLUMN = 318,                  /* COLUMN  */
    COLUMNS = 319,                 /* COLUMNS  */
    COMMA = 320,                   /* COMMA  */
    COMMAND_LINE = 321,            /* "COMMAND-LINE"  */
    COMMA_DELIM = 322,             /* "comma delimiter"  */
    COMMIT = 323,                  /* COMMIT  */
    COMMON = 324,                  /* COMMON  */
    COMP = 325,                    /* COMP  */
    COMPUTE = 326,                 /* COMPUTE  */
    COMP_1 = 327,                  /* "COMP-1"  */
    COMP_2 = 328,                  /* "COMP-2"  */
    COMP_3 = 329,                  /* "COMP-3"  */
    COMP_4 = 330,                  /* "COMP-4"  */
    COMP_5 = 331,                  /* "COMP-5"  */
    COMP_X = 332,                  /* "COMP-X"  */
    CONCATENATE_FUNC = 333,        /* "FUNCTION CONCATENATE"  */
    CONFIGURATION = 334,           /* CONFIGURATION  */
    CONSTANT = 335,                /* CONSTANT  */
    CONTAINS = 336,                /* CONTAINS  */
    CONTENT = 337,                 /* CONTENT  */
    CONTINUE = 338,                /* CONTINUE  */
    CONTROL = 339,                 /* CONTROL  */
    CONTROLS = 340,                /* CONTROLS  */
    CONTROL_FOOTING = 341,         /* "CONTROL FOOTING"  */
    CONTROL_HEADING = 342,         /* "CONTROL HEADING"  */
    CONVERTING = 343,              /* CONVERTING  */
    CORRESPONDING = 344,           /* CORRESPONDING  */
    COUNT = 345,                   /* COUNT  */
    CRT = 346,                     /* CRT  */
    CURRENCY = 347,                /* CURRENCY  */
    CURRENT_DATE_FUNC = 348,       /* "FUNCTION CURRENT-DATE"  */
    CURSOR = 349,                  /* CURSOR  */
    CYCLE = 350,                   /* CYCLE  */
    DATA = 351,                    /* DATA  */
    DATE = 352,                    /* DATE  */
    DAY = 353,                     /* DAY  */
    DAY_OF_WEEK = 354,             /* "DAY-OF-WEEK"  */
    DE = 355,                      /* DE  */
    DEBUGGING = 356,               /* DEBUGGING  */
    DECIMAL_POINT = 357,           /* "DECIMAL-POINT"  */
    DECLARATIVES = 358,            /* DECLARATIVES  */
    DEFAULT = 359,                 /* DEFAULT  */
    DELETE = 360,                  /* DELETE  */
    DELIMITED = 361,               /* DELIMITED  */
    DELIMITER = 362,               /* DELIMITER  */
    DEPENDING = 363,               /* DEPENDING  */
    DESCENDING = 364,              /* DESCENDING  */
    DETAIL = 365,                  /* DETAIL  */
    DISK = 366,                    /* DISK  */
    DISPLAY = 367,                 /* DISPLAY  */
    DIVIDE = 368,                  /* DIVIDE  */
    DIVISION = 369,                /* DIVISION  */
    DOWN = 370,                    /* DOWN  */
    DUPLICATES = 371,              /* DUPLICATES  */
    DYNAMIC = 372,                 /* DYNAMIC  */
    EBCDIC = 373,                  /* EBCDIC  */
    ELSE = 374,                    /* ELSE  */
    END = 375,                     /* END  */
    END_ACCEPT = 376,              /* "END-ACCEPT"  */
    END_ADD = 377,                 /* "END-ADD"  */
    END_CALL = 378,                /* "END-CALL"  */
    END_COMPUTE = 379,             /* "END-COMPUTE"  */
    END_DELETE = 380,              /* "END-DELETE"  */
    END_DISPLAY = 381,             /* "END-DISPLAY"  */
    END_DIVIDE = 382,              /* "END-DIVIDE"  */
    END_EVALUATE = 383,            /* "END-EVALUATE"  */
    END_FUNCTION = 384,            /* "END FUNCTION"  */
    END_IF = 385,                  /* "END-IF"  */
    END_MULTIPLY = 386,            /* "END-MULTIPLY"  */
    END_PERFORM = 387,             /* "END-PERFORM"  */
    END_PROGRAM = 388,             /* "END PROGRAM"  */
    END_READ = 389,                /* "END-READ"  */
    END_RETURN = 390,              /* "END-RETURN"  */
    END_REWRITE = 391,             /* "END-REWRITE"  */
    END_SEARCH = 392,              /* "END-SEARCH"  */
    END_START = 393,               /* "END-START"  */
    END_STRING = 394,              /* "END-STRING"  */
    END_SUBTRACT = 395,            /* "END-SUBTRACT"  */
    END_UNSTRING = 396,            /* "END-UNSTRING"  */
    END_WRITE = 397,               /* "END-WRITE"  */
    ENTRY = 398,                   /* ENTRY  */
    ENVIRONMENT = 399,             /* ENVIRONMENT  */
    ENVIRONMENT_NAME = 400,        /* "ENVIRONMENT-NAME"  */
    ENVIRONMENT_VALUE = 401,       /* "ENVIRONMENT-VALUE"  */
    EOL = 402,                     /* EOL  */
    EOP = 403,                     /* EOP  */
    EOS = 404,                     /* EOS  */
    EQUAL = 405,                   /* EQUAL  */
    EQUALS = 406,                  /* EQUALS  */
    ERASE = 407,                   /* ERASE  */
    ERROR = 408,                   /* ERROR  */
    ESCAPE = 409,                  /* ESCAPE  */
    EVALUATE = 410,                /* EVALUATE  */
    EVENT_STATUS = 411,            /* "EVENT-STATUS"  */
    EXCEPTION = 412,               /* EXCEPTION  */
    EXCLUSIVE = 413,               /* EXCLUSIVE  */
    EXIT = 414,                    /* EXIT  */
    EXTEND = 415,                  /* EXTEND  */
    EXTERNAL = 416,                /* EXTERNAL  */
    FD = 417,                      /* FD  */
    FILE_CONTROL = 418,            /* "FILE-CONTROL"  */
    FILE_ID = 419,                 /* "FILE-ID"  */
    FILLER = 420,                  /* FILLER  */
    FINAL = 421,                   /* FINAL  */
    FIRST = 422,                   /* FIRST  */
    FOOTING = 423,                 /* FOOTING  */
    FOR = 424,                     /* FOR  */
    FOREGROUND_COLOR = 425,        /* "FOREGROUND-COLOR"  */
    FOREVER = 426,                 /* FOREVER  */
    FREE = 427,                    /* FREE  */
    FROM = 428,                    /* FROM  */
    FULL = 429,                    /* FULL  */
    FUNCTION = 430,                /* FUNCTION  */
    FUNCTION_ID = 431,             /* "FUNCTION-ID"  */
    FUNCTION_NAME = 432,           /* "FUNCTION"  */
    GE = 433,                      /* GE  */
    GENERATE = 434,                /* GENERATE  */
    GIVING = 435,                  /* GIVING  */
    GLOBAL = 436,                  /* GLOBAL  */
    GO = 437,                      /* GO  */
    GOBACK = 438,                  /* GOBACK  */
    GREATER = 439,                 /* GREATER  */
    GROUP = 440,                   /* GROUP  */
    HEADING = 441,                 /* HEADING  */
    HIGHLIGHT = 442,               /* HIGHLIGHT  */
    HIGH_VALUE = 443,              /* "HIGH-VALUE"  */
    IDENTIFICATION = 444,          /* IDENTIFICATION  */
    IF = 445,                      /* IF  */
    IGNORE = 446,                  /* IGNORE  */
    IGNORING = 447,                /* IGNORING  */
    IN = 448,                      /* IN  */
    INDEX = 449,                   /* INDEX  */
    INDEXED = 450,                 /* INDEXED  */
    INDICATE = 451,                /* INDICATE  */
    INITIALIZE = 452,              /* INITIALIZE  */
    INITIALIZED = 453,             /* INITIALIZED  */
    INITIATE = 454,                /* INITIATE  */
    INPUT = 455,                   /* INPUT  */
    INPUT_OUTPUT = 456,            /* "INPUT-OUTPUT"  */
    INSPECT = 457,                 /* INSPECT  */
    INTO = 458,                    /* INTO  */
    INTRINSIC = 459,               /* INTRINSIC  */
    INVALID = 460,                 /* INVALID  */
    INVALID_KEY = 461,             /* "INVALID KEY"  */
    IS = 462,                      /* IS  */
    I_O = 463,                     /* "I-O"  */
    I_O_CONTROL = 464,             /* "I-O-CONTROL"  */
    JUSTIFIED = 465,               /* JUSTIFIED  */
    KEY = 466,                     /* KEY  */
    LABEL = 467,                   /* LABEL  */
    LAST = 468,                    /* LAST  */
    LAST_DETAIL = 469,             /* "LAST DETAIL"  */
    LE = 470,                      /* LE  */
    LEADING = 471,                 /* LEADING  */
    LEFT = 472,                    /* LEFT  */
    LENGTH = 473,                  /* LENGTH  */
    LESS = 474,                    /* LESS  */
    LIMIT = 475,                   /* LIMIT  */
    LIMITS = 476,                  /* LIMITS  */
    LINAGE = 477,                  /* LINAGE  */
    LINAGE_COUNTER = 478,          /* "LINAGE-COUNTER"  */
    LINE = 479,                    /* LINE  */
    LINES = 480,                   /* LINES  */
    LINKAGE = 481,                 /* LINKAGE  */
    LITERAL = 482,                 /* "Literal"  */
    LOCALE = 483,                  /* LOCALE  */
    LOCALE_DT_FUNC = 484,          /* "FUNCTION LOCALE"  */
    LOCAL_STORAGE = 485,           /* "LOCAL-STORAGE"  */
    LOCK = 486,                    /* LOCK  */
    LOWER_CASE_FUNC = 487,         /* "FUNCTION LOWER-CASE"  */
    LOWLIGHT = 488,                /* LOWLIGHT  */
    LOW_VALUE = 489,               /* "LOW-VALUE"  */
    MANUAL = 490,                  /* MANUAL  */
    MEMORY = 491,                  /* MEMORY  */
    MERGE = 492,                   /* MERGE  */
    MINUS = 493,                   /* MINUS  */
    MNEMONIC_NAME = 494,           /* "MNEMONIC NAME"  */
    MODE = 495,                    /* MODE  */
    MOVE = 496,                    /* MOVE  */
    MULTIPLE = 497,                /* MULTIPLE  */
    MULTIPLY = 498,                /* MULTIPLY  */
    NATIONAL = 499,                /* NATIONAL  */
    NATIONAL_EDITED = 500,         /* "NATIONAL-EDITED"  */
    NATIVE = 501,                  /* NATIVE  */
    NE = 502,                      /* NE  */
    NEGATIVE = 503,                /* NEGATIVE  */
    NEXT = 504,                    /* NEXT  */
    NEXT_SENTENCE = 505,           /* "NEXT SENTENCE"  */
    NO = 506,                      /* NO  */
    NOT = 507,                     /* NOT  */
    NOT_END = 508,                 /* "NOT END"  */
    NOT_EOP = 509,                 /* "NOT EOP"  */
    NOT_EXCEPTION = 510,           /* "NOT EXCEPTION"  */
    NOT_INVALID_KEY = 511,         /* "NOT INVALID KEY"  */
    NOT_OVERFLOW = 512,            /* "NOT OVERFLOW"  */
    NOT_SIZE_ERROR = 513,          /* "NOT SIZE ERROR"  */
    NO_ADVANCING = 514,            /* "NO ADVANCING"  */
    NUMBER = 515,                  /* NUMBER  */
    NUMBERS = 516,                 /* NUMBERS  */
    NUMERIC = 517,                 /* NUMERIC  */
    NUMERIC_EDITED = 518,          /* "NUMERIC-EDITED"  */
    NUMVALC_FUNC = 519,            /* "FUNCTION NUMVALC"  */
    OBJECT_COMPUTER = 520,         /* "OBJECT-COMPUTER"  */
    OCCURS = 521,                  /* OCCURS  */
    OF = 522,                      /* OF  */
    OFF = 523,                     /* OFF  */
    OMITTED = 524,                 /* OMITTED  */
    ON = 525,                      /* ON  */
    ONLY = 526,                    /* ONLY  */
    OPEN = 527,                    /* OPEN  */
    OPTIONAL = 528,                /* OPTIONAL  */
    OR = 529,                      /* OR  */
    ORDER = 530,                   /* ORDER  */
    ORGANIZATION = 531,            /* ORGANIZATION  */
    OTHER = 532,                   /* OTHER  */
    OUTPUT = 533,                  /* OUTPUT  */
    OVERFLOW = 534,                /* OVERFLOW  */
    OVERLINE = 535,                /* OVERLINE  */
    PACKED_DECIMAL = 536,          /* "PACKED-DECIMAL"  */
    PADDING = 537,                 /* PADDING  */
    PAGE = 538,                    /* PAGE  */
    PAGE_FOOTING = 539,            /* "PAGE FOOTING"  */
    PAGE_HEADING = 540,            /* "PAGE HEADING"  */
    PARAGRAPH = 541,               /* PARAGRAPH  */
    PERFORM = 542,                 /* PERFORM  */
    PICTURE = 543,                 /* PICTURE  */
    PLUS = 544,                    /* PLUS  */
    POINTER = 545,                 /* POINTER  */
    POSITION = 546,                /* POSITION  */
    POSITIVE = 547,                /* POSITIVE  */
    PRESENT = 548,                 /* PRESENT  */
    PREVIOUS = 549,                /* PREVIOUS  */
    PRINTER = 550,                 /* PRINTER  */
    PRINTING = 551,                /* PRINTING  */
    PROCEDURE = 552,               /* PROCEDURE  */
    PROCEDURES = 553,              /* PROCEDURES  */
    PROCEED = 554,                 /* PROCEED  */
    PROGRAM = 555,                 /* PROGRAM  */
    PROGRAM_ID = 556,              /* "PROGRAM-ID"  */
    PROGRAM_NAME = 557,            /* "Program name"  */
    PROGRAM_POINTER = 558,         /* "PROGRAM-POINTER"  */
    PROMPT = 559,                  /* PROMPT  */
    QUOTE = 560,                   /* QUOTE  */
    RANDOM = 561,                  /* RANDOM  */
    RD = 562,                      /* RD  */
    READ = 563,                    /* READ  */
    RECORD = 564,                  /* RECORD  */
    RECORDING = 565,               /* RECORDING  */
    RECORDS = 566,                 /* RECORDS  */
    RECURSIVE = 567,               /* RECURSIVE  */
    REDEFINES = 568,               /* REDEFINES  */
    REEL = 569,                    /* REEL  */
    REFERENCE = 570,               /* REFERENCE  */
    RELATIVE = 571,                /* RELATIVE  */
    RELEASE = 572,                 /* RELEASE  */
    REMAINDER = 573,               /* REMAINDER  */
    REMOVAL = 574,                 /* REMOVAL  */
    RENAMES = 575,                 /* RENAMES  */
    REPLACING = 576,               /* REPLACING  */
    REPORT = 577,                  /* REPORT  */
    REPORTING = 578,               /* REPORTING  */
    REPORTS = 579,                 /* REPORTS  */
    REPORT_FOOTING = 580,          /* "REPORT FOOTING"  */
    REPORT_HEADING = 581,          /* "REPORT HEADING"  */
    REPOSITORY = 582,              /* REPOSITORY  */
    REQUIRED = 583,                /* REQUIRED  */
    RESERVE = 584,                 /* RESERVE  */
    RETURN = 585,                  /* RETURN  */
    RETURNING = 586,               /* RETURNING  */
    REVERSE_FUNC = 587,            /* "FUNCTION REVERSE"  */
    REVERSE_VIDEO = 588,           /* "REVERSE-VIDEO"  */
    REWIND = 589,                  /* REWIND  */
    REWRITE = 590,                 /* REWRITE  */
    RIGHT = 591,                   /* RIGHT  */
    ROLLBACK = 592,                /* ROLLBACK  */
    ROUNDED = 593,                 /* ROUNDED  */
    RUN = 594,                     /* RUN  */
    SAME = 595,                    /* SAME  */
    SCREEN = 596,                  /* SCREEN  */
    SCREEN_CONTROL = 597,          /* "SCREEN-CONTROL"  */
    SCROLL = 598,                  /* SCROLL  */
    SD = 599,                      /* SD  */
    SEARCH = 600,                  /* SEARCH  */
    SECTION = 601,                 /* SECTION  */
    SECURE = 602,                  /* SECURE  */
    SEGMENT_LIMIT = 603,           /* "SEGMENT-LIMIT"  */
    SELECT = 604,                  /* SELECT  */
    SEMI_COLON = 605,              /* "semi-colon"  */
    SENTENCE = 606,                /* SENTENCE  */
    SEPARATE = 607,                /* SEPARATE  */
    SEQUENCE = 608,                /* SEQUENCE  */
    SEQUENTIAL = 609,              /* SEQUENTIAL  */
    SET = 610,                     /* SET  */
    SHARING = 611,                 /* SHARING  */
    SIGN = 612,                    /* SIGN  */
    SIGNED = 613,                  /* SIGNED  */
    SIGNED_INT = 614,              /* "SIGNED-INT"  */
    SIGNED_LONG = 615,             /* "SIGNED-LONG"  */
    SIGNED_SHORT = 616,            /* "SIGNED-SHORT"  */
    SIZE = 617,                    /* SIZE  */
    SIZE_ERROR = 618,              /* "SIZE ERROR"  */
    SORT = 619,                    /* SORT  */
    SORT_MERGE = 620,              /* "SORT-MERGE"  */
    SOURCE = 621,                  /* SOURCE  */
    SOURCE_COMPUTER = 622,         /* "SOURCE-COMPUTER"  */
    SPACE = 623,                   /* SPACE  */
    SPECIAL_NAMES = 624,           /* "SPECIAL-NAMES"  */
    STANDARD = 625,                /* STANDARD  */
    STANDARD_1 = 626,              /* "STANDARD-1"  */
    STANDARD_2 = 627,              /* "STANDARD-2"  */
    START = 628,                   /* START  */
    STATUS = 629,                  /* STATUS  */
    STOP = 630,                    /* STOP  */
    STRING = 631,                  /* STRING  */
    SUBSTITUTE_FUNC = 632,         /* "FUNCTION SUBSTITUTE"  */
    SUBSTITUTE_CASE_FUNC = 633,    /* "FUNCTION SUBSTITUTE-CASE"  */
    SUBTRACT = 634,                /* SUBTRACT  */
    SUM = 635,                     /* SUM  */
    SUPPRESS = 636,                /* SUPPRESS  */
    SYMBOLIC = 637,                /* SYMBOLIC  */
    SYNCHRONIZED = 638,            /* SYNCHRONIZED  */
    TALLYING = 639,                /* TALLYING  */
    TAPE = 640,                    /* TAPE  */
    TERMINATE = 641,               /* TERMINATE  */
    TEST = 642,                    /* TEST  */
    THAN = 643,                    /* THAN  */
    THEN = 644,                    /* THEN  */
    THRU = 645,                    /* THRU  */
    TIME = 646,                    /* TIME  */
    TIMES = 647,                   /* TIMES  */
    TO = 648,                      /* TO  */
    TOK_FALSE = 649,               /* "FALSE"  */
    TOK_FILE = 650,                /* "FILE"  */
    TOK_INITIAL = 651,             /* "INITIAL"  */
    TOK_NULL = 652,                /* "NULL"  */
    TOK_TRUE = 653,                /* "TRUE"  */
    TOP = 654,                     /* TOP  */
    TRAILING = 655,                /* TRAILING  */
    TRANSFORM = 656,               /* TRANSFORM  */
    TRIM_FUNCTION = 657,           /* "FUNCTION TRIM"  */
    TYPE = 658,                    /* TYPE  */
    UNDERLINE = 659,               /* UNDERLINE  */
    UNIT = 660,                    /* UNIT  */
    UNLOCK = 661,                  /* UNLOCK  */
    UNSIGNED = 662,                /* UNSIGNED  */
    UNSIGNED_INT = 663,            /* "UNSIGNED-INT"  */
    UNSIGNED_LONG = 664,           /* "UNSIGNED-LONG"  */
    UNSIGNED_SHORT = 665,          /* "UNSIGNED-SHORT"  */
    UNSTRING = 666,                /* UNSTRING  */
    UNTIL = 667,                   /* UNTIL  */
    UP = 668,                      /* UP  */
    UPDATE = 669,                  /* UPDATE  */
    UPON = 670,                    /* UPON  */
    UPON_ARGUMENT_NUMBER = 671,    /* "UPON ARGUMENT-NUMBER"  */
    UPON_COMMAND_LINE = 672,       /* "UPON COMMAND-LINE"  */
    UPON_ENVIRONMENT_NAME = 673,   /* "UPON ENVIRONMENT-NAME"  */
    UPON_ENVIRONMENT_VALUE = 674,  /* "UPON ENVIRONMENT-VALUE"  */
    UPPER_CASE_FUNC = 675,         /* "FUNCTION UPPER-CASE"  */
    USAGE = 676,                   /* USAGE  */
    USE = 677,                     /* USE  */
    USING = 678,                   /* USING  */
    VALUE = 679,                   /* VALUE  */
    VARYING = 680,                 /* VARYING  */
    WAIT = 681,                    /* WAIT  */
    WHEN = 682,                    /* WHEN  */
    WHEN_COMPILED_FUNC = 683,      /* "FUNCTION WHEN-COMPILED"  */
    WITH = 684,                    /* WITH  */
    WORD = 685,                    /* "Identifier"  */
    WORDS = 686,                   /* WORDS  */
    WORKING_STORAGE = 687,         /* "WORKING-STORAGE"  */
    WRITE = 688,                   /* WRITE  */
    YYYYDDD = 689,                 /* YYYYDDD  */
    YYYYMMDD = 690,                /* YYYYMMDD  */
    ZERO = 691,                    /* ZERO  */
    UNARY_SIGN = 692               /* UNARY_SIGN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_H_INCLUDED  */
