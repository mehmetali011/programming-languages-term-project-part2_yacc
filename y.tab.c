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
#line 1 "plainscript.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customStructs.h" 


//Variable array size:100 can be extended in future.
#define SYMBOL_LIMIT 100
Variable symbolTable[SYMBOL_LIMIT];
int symbolCount = 0;

FILE* logFile = NULL;
extern int currentLine;

#define ERROR(fmt, ...) do { \
    if (logFile) fprintf(logFile, "[Error] Line %d: " fmt "\n", currentLine, ##__VA_ARGS__); \
} while(0)

#define INFO(fmt, ...) do { \
    if (logFile) fprintf(logFile, "[Info] Line %d: " fmt "\n", currentLine, ##__VA_ARGS__); \
} while(0)




int skip_level = 0; 


int in_try_block = 0;
int exception_thrown = 0;
int catch_block_skipped = 0;
char* exception_message = NULL;


static int if_chain_executed_flag = 0; 


static int mra1_if_block_skipped = 0;      
static int mra3_elseif_block_skipped = 0;   
static int mra5_else_block_skipped = 0;    



void updateSymbolVal(char* name, int type, TypedValue val);
TypedValue symbolVal(char* name);
TypedValue callFunction(char* name, TypedValue* args, int argCount);
void addVariable(char* name, int type);
void inputHandler(char* name, char* message); 	
void printHandler(TypedValue value); 	
int evaluateCondition(TypedValue left, int operator, TypedValue right);
int evaluateLogic(int leftCondition, int operator, int rightCondition); 

void yyerror(const char *s);
int yylex(void);

#line 128 "y.tab.c"

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

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 60 "plainscript.y"

	#include "customStructs.h"

#line 167 "y.tab.c"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DO = 258,                      /* DO  */
    DECLARE = 259,                 /* DECLARE  */
    AS = 260,                      /* AS  */
    SET = 261,                     /* SET  */
    ASK = 262,                     /* ASK  */
    RETURN = 263,                  /* RETURN  */
    THROW = 264,                   /* THROW  */
    TRY = 265,                     /* TRY  */
    CATCH = 266,                   /* CATCH  */
    FINALLY = 267,                 /* FINALLY  */
    ISIT = 268,                    /* ISIT  */
    MAYBE = 269,                   /* MAYBE  */
    OTHERWISE = 270,               /* OTHERWISE  */
    DURING = 271,                  /* DURING  */
    COUNT = 272,                   /* COUNT  */
    FROM = 273,                    /* FROM  */
    TO = 274,                      /* TO  */
    SAY = 275,                     /* SAY  */
    TYPE_NUMBER = 276,             /* TYPE_NUMBER  */
    TYPE_TEXT = 277,               /* TYPE_TEXT  */
    TYPE_LOGIC = 278,              /* TYPE_LOGIC  */
    LOGIC_TRUE = 279,              /* LOGIC_TRUE  */
    LOGIC_FALSE = 280,             /* LOGIC_FALSE  */
    NUMBER = 281,                  /* NUMBER  */
    STRING = 282,                  /* STRING  */
    IDENTIFIER = 283,              /* IDENTIFIER  */
    PLUS = 284,                    /* PLUS  */
    MINUS = 285,                   /* MINUS  */
    TIMES = 286,                   /* TIMES  */
    DIVIDE = 287,                  /* DIVIDE  */
    SAME = 288,                    /* SAME  */
    DIFFERENT = 289,               /* DIFFERENT  */
    SMALLER = 290,                 /* SMALLER  */
    BIGGER = 291,                  /* BIGGER  */
    SMALLER_EQUAL = 292,           /* SMALLER_EQUAL  */
    BIGGER_EQUAL = 293,            /* BIGGER_EQUAL  */
    BOTH = 294,                    /* BOTH  */
    EITHER = 295                   /* EITHER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define DO 258
#define DECLARE 259
#define AS 260
#define SET 261
#define ASK 262
#define RETURN 263
#define THROW 264
#define TRY 265
#define CATCH 266
#define FINALLY 267
#define ISIT 268
#define MAYBE 269
#define OTHERWISE 270
#define DURING 271
#define COUNT 272
#define FROM 273
#define TO 274
#define SAY 275
#define TYPE_NUMBER 276
#define TYPE_TEXT 277
#define TYPE_LOGIC 278
#define LOGIC_TRUE 279
#define LOGIC_FALSE 280
#define NUMBER 281
#define STRING 282
#define IDENTIFIER 283
#define PLUS 284
#define MINUS 285
#define TIMES 286
#define DIVIDE 287
#define SAME 288
#define DIFFERENT 289
#define SMALLER 290
#define BIGGER 291
#define SMALLER_EQUAL 292
#define BIGGER_EQUAL 293
#define BOTH 294
#define EITHER 295

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 65 "plainscript.y"

    int boolean;
    double number;
    char* string;
    char* identifier;
    int num;
    TypedValue typedval;
    struct param_list_node* paramList;
    struct expr_list_node* exprList;

#line 278 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_DO = 3,                         /* DO  */
  YYSYMBOL_DECLARE = 4,                    /* DECLARE  */
  YYSYMBOL_AS = 5,                         /* AS  */
  YYSYMBOL_SET = 6,                        /* SET  */
  YYSYMBOL_ASK = 7,                        /* ASK  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_THROW = 9,                      /* THROW  */
  YYSYMBOL_TRY = 10,                       /* TRY  */
  YYSYMBOL_CATCH = 11,                     /* CATCH  */
  YYSYMBOL_FINALLY = 12,                   /* FINALLY  */
  YYSYMBOL_ISIT = 13,                      /* ISIT  */
  YYSYMBOL_MAYBE = 14,                     /* MAYBE  */
  YYSYMBOL_OTHERWISE = 15,                 /* OTHERWISE  */
  YYSYMBOL_DURING = 16,                    /* DURING  */
  YYSYMBOL_COUNT = 17,                     /* COUNT  */
  YYSYMBOL_FROM = 18,                      /* FROM  */
  YYSYMBOL_TO = 19,                        /* TO  */
  YYSYMBOL_SAY = 20,                       /* SAY  */
  YYSYMBOL_TYPE_NUMBER = 21,               /* TYPE_NUMBER  */
  YYSYMBOL_TYPE_TEXT = 22,                 /* TYPE_TEXT  */
  YYSYMBOL_TYPE_LOGIC = 23,                /* TYPE_LOGIC  */
  YYSYMBOL_LOGIC_TRUE = 24,                /* LOGIC_TRUE  */
  YYSYMBOL_LOGIC_FALSE = 25,               /* LOGIC_FALSE  */
  YYSYMBOL_NUMBER = 26,                    /* NUMBER  */
  YYSYMBOL_STRING = 27,                    /* STRING  */
  YYSYMBOL_IDENTIFIER = 28,                /* IDENTIFIER  */
  YYSYMBOL_PLUS = 29,                      /* PLUS  */
  YYSYMBOL_MINUS = 30,                     /* MINUS  */
  YYSYMBOL_TIMES = 31,                     /* TIMES  */
  YYSYMBOL_DIVIDE = 32,                    /* DIVIDE  */
  YYSYMBOL_SAME = 33,                      /* SAME  */
  YYSYMBOL_DIFFERENT = 34,                 /* DIFFERENT  */
  YYSYMBOL_SMALLER = 35,                   /* SMALLER  */
  YYSYMBOL_BIGGER = 36,                    /* BIGGER  */
  YYSYMBOL_SMALLER_EQUAL = 37,             /* SMALLER_EQUAL  */
  YYSYMBOL_BIGGER_EQUAL = 38,              /* BIGGER_EQUAL  */
  YYSYMBOL_BOTH = 39,                      /* BOTH  */
  YYSYMBOL_EITHER = 40,                    /* EITHER  */
  YYSYMBOL_41_ = 41,                       /* '!'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* '{'  */
  YYSYMBOL_45_ = 45,                       /* '}'  */
  YYSYMBOL_46_ = 46,                       /* ','  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_program = 48,                   /* program  */
  YYSYMBOL_statement_list = 49,            /* statement_list  */
  YYSYMBOL_statement = 50,                 /* statement  */
  YYSYMBOL_assignment = 51,                /* assignment  */
  YYSYMBOL_func_decl = 52,                 /* func_decl  */
  YYSYMBOL_param_list = 53,                /* param_list  */
  YYSYMBOL_func_call = 54,                 /* func_call  */
  YYSYMBOL_arg_list = 55,                  /* arg_list  */
  YYSYMBOL_var_decl = 56,                  /* var_decl  */
  YYSYMBOL_input_stmt = 57,                /* input_stmt  */
  YYSYMBOL_print_stmt = 58,                /* print_stmt  */
  YYSYMBOL_type = 59,                      /* type  */
  YYSYMBOL_term = 60,                      /* term  */
  YYSYMBOL_expression = 61,                /* expression  */
  YYSYMBOL_condition = 62,                 /* condition  */
  YYSYMBOL_operator = 63,                  /* operator  */
  YYSYMBOL_logic_operator = 64,            /* logic_operator  */
  YYSYMBOL_if_stmt = 65,                   /* if_stmt  */
  YYSYMBOL_66_1 = 66,                      /* $@1  */
  YYSYMBOL_67_2 = 67,                      /* $@2  */
  YYSYMBOL_68_3 = 68,                      /* $@3  */
  YYSYMBOL_optional_elseif_list = 69,      /* optional_elseif_list  */
  YYSYMBOL_70_4 = 70,                      /* $@4  */
  YYSYMBOL_optional_else_clause = 71,      /* optional_else_clause  */
  YYSYMBOL_72_5 = 72,                      /* $@5  */
  YYSYMBOL_throw_stmt = 73,                /* throw_stmt  */
  YYSYMBOL_try_stmt = 74,                  /* try_stmt  */
  YYSYMBOL_75_6 = 75,                      /* $@6  */
  YYSYMBOL_76_7 = 76,                      /* $@7  */
  YYSYMBOL_optional_catch_clause = 77,     /* optional_catch_clause  */
  YYSYMBOL_78_8 = 78,                      /* $@8  */
  YYSYMBOL_optional_finally_clause = 79,   /* optional_finally_clause  */
  YYSYMBOL_80_9 = 80                       /* $@9  */
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
typedef yytype_uint8 yy_state_t;

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
#define YYFINAL  29
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   160

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  73
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  148

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    41,     2,     2,     2,     2,     2,     2,
      42,    43,     2,     2,    46,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    44,     2,    45,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   108,   108,   111,   113,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   129,   138,   154,   161,   175,   183,
     190,   204,   213,   219,   228,   237,   238,   239,   243,   247,
     251,   255,   259,   265,   266,   307,   316,   325,   339,   342,
     345,   354,   358,   362,   363,   364,   375,   375,   375,   375,
     375,   375,   378,   378,   385,   389,   408,   385,   419,   422,
     421,   453,   456,   455,   486,   517,   524,   516,   536,   539,
     538,   587,   590,   589
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
  "\"end of file\"", "error", "\"invalid token\"", "DO", "DECLARE", "AS",
  "SET", "ASK", "RETURN", "THROW", "TRY", "CATCH", "FINALLY", "ISIT",
  "MAYBE", "OTHERWISE", "DURING", "COUNT", "FROM", "TO", "SAY",
  "TYPE_NUMBER", "TYPE_TEXT", "TYPE_LOGIC", "LOGIC_TRUE", "LOGIC_FALSE",
  "NUMBER", "STRING", "IDENTIFIER", "PLUS", "MINUS", "TIMES", "DIVIDE",
  "SAME", "DIFFERENT", "SMALLER", "BIGGER", "SMALLER_EQUAL",
  "BIGGER_EQUAL", "BOTH", "EITHER", "'!'", "'('", "')'", "'{'", "'}'",
  "','", "$accept", "program", "statement_list", "statement", "assignment",
  "func_decl", "param_list", "func_call", "arg_list", "var_decl",
  "input_stmt", "print_stmt", "type", "term", "expression", "condition",
  "operator", "logic_operator", "if_stmt", "$@1", "$@2", "$@3",
  "optional_elseif_list", "$@4", "optional_else_clause", "$@5",
  "throw_stmt", "try_stmt", "$@6", "$@7", "optional_catch_clause", "$@8",
  "optional_finally_clause", "$@9", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-95)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-55)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       6,   -26,   -16,   -28,   -22,   -95,    -2,    -1,    32,   -95,
       6,   -95,   -95,   -95,   -95,   -95,   -95,   -95,    38,   -95,
     -95,    30,    79,    75,     3,    45,     3,     3,     3,   -95,
     -95,    70,    82,   100,   -35,   -95,   -95,   -95,   -95,    72,
       3,   -95,    -8,     6,    27,    49,    81,    23,    22,   120,
      83,   -95,   -95,   -95,    86,    88,   101,     3,    31,     3,
       3,     3,     3,    90,    89,    91,   -95,    92,     3,    28,
      48,    43,    64,    66,   100,    93,   -95,   -95,    95,    96,
     -95,    12,    12,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,     3,   -95,   -95,   -95,
      22,    94,     6,   102,   -95,   125,    87,    97,    26,    82,
      99,   -95,   103,   130,     6,   -95,   -95,   118,   -95,   -95,
     104,   105,   106,   -95,   -95,     6,   -95,   107,   108,    61,
       6,   -95,   110,   -95,   -95,   109,    22,   111,   -95,    68,
       6,   -95,   112,   114,   -95,     6,   115,   -95
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     0,     0,    65,     0,     0,     0,     2,
       3,     5,    10,    11,     6,     7,     8,     9,     0,    13,
      12,     0,     0,     0,     0,     0,     0,     0,     0,     1,
       4,     0,     0,     0,     0,    30,    31,    28,    29,    32,
       0,    33,     0,     3,     0,     0,     0,    19,     0,     0,
       0,    25,    26,    27,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    14,     0,     0,    30,
      31,    32,     0,     0,     0,     0,    21,    22,     0,     0,
      38,    34,    35,    36,    37,    64,    66,    24,    18,    20,
      46,    47,    48,    49,    50,    51,     0,    52,    53,    55,
       0,    16,     3,     0,    40,    68,    41,     0,    42,     0,
       0,    23,     0,    71,     3,    17,    15,     0,    72,    67,
       0,     0,     0,    56,    69,     3,    58,     0,     0,    61,
       3,    73,     0,    62,    57,     0,     0,     0,    70,     0,
       3,    59,     0,     0,    63,     3,     0,    60
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -95,   -95,   -10,   -95,   -95,   -95,    47,   -95,   -50,   -95,
     -95,   -95,    73,   -95,   -23,   -94,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,   -95,
     -95,   -95,   -95,   -95
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     8,     9,    10,    11,    12,    50,    13,    46,    14,
      15,    16,    54,    41,    47,    73,    96,   100,    17,    18,
     107,   126,   129,   143,   134,   137,    19,    20,    25,   105,
     113,   127,   119,   122
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      30,    42,    21,    44,    45,    27,   108,    79,    55,     1,
       2,    56,    22,     3,    23,     4,     5,    58,    89,   -54,
      24,    59,    60,    61,    62,    72,     6,    35,    36,    37,
      38,    39,    29,    64,     7,    63,    81,    82,    83,    84,
      26,    28,   139,    61,    62,    40,    69,    70,    37,    38,
      71,    31,    59,    60,    61,    62,    59,    60,    61,    62,
      59,    60,    61,    62,    40,    97,    98,   -43,   -43,    68,
      65,   -43,    32,   106,    80,   132,   133,    72,    59,    60,
      61,    62,   -45,   -45,    33,    57,   -45,   -44,   -44,    43,
      66,   -44,   110,    59,    60,    61,    62,    90,    91,    92,
      93,    94,    95,    34,   120,    97,    98,    97,    98,    99,
      49,   141,    48,    72,    57,   128,    59,    60,    61,    62,
     135,    51,    52,    53,    67,    74,    75,    76,    78,    77,
     142,    85,    87,    88,    86,   146,   112,   102,   103,   104,
     109,   114,   118,   111,   116,   117,   121,   101,   124,   123,
     125,   130,   136,   131,   138,   140,   115,   144,   145,     0,
     147
};

static const yytype_int16 yycheck[] =
{
      10,    24,    28,    26,    27,     6,   100,    57,    43,     3,
       4,    46,    28,     7,    42,     9,    10,    40,    68,    13,
      42,    29,    30,    31,    32,    48,    20,    24,    25,    26,
      27,    28,     0,    43,    28,    43,    59,    60,    61,    62,
      42,    42,   136,    31,    32,    42,    24,    25,    26,    27,
      28,    13,    29,    30,    31,    32,    29,    30,    31,    32,
      29,    30,    31,    32,    42,    39,    40,    39,    40,    46,
      43,    43,    42,    96,    43,    14,    15,   100,    29,    30,
      31,    32,    39,    40,     5,    42,    43,    39,    40,    44,
      41,    43,   102,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    28,   114,    39,    40,    39,    40,    43,
      28,    43,    42,   136,    42,   125,    29,    30,    31,    32,
     130,    21,    22,    23,    43,     5,    43,    41,    27,    41,
     140,    41,    41,    41,    45,   145,    11,    44,    43,    43,
      46,    44,    12,    41,    45,    42,    28,    74,    43,    45,
      44,    44,    42,    45,    45,    44,   109,    45,    44,    -1,
      45
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     7,     9,    10,    20,    28,    48,    49,
      50,    51,    52,    54,    56,    57,    58,    65,    66,    73,
      74,    28,    28,    42,    42,    75,    42,     6,    42,     0,
      49,    13,    42,     5,    28,    24,    25,    26,    27,    28,
      42,    60,    61,    44,    61,    61,    55,    61,    42,    28,
      53,    21,    22,    23,    59,    43,    46,    42,    61,    29,
      30,    31,    32,    43,    49,    43,    41,    43,    46,    24,
      25,    28,    61,    62,     5,    43,    41,    41,    27,    55,
      43,    61,    61,    61,    61,    41,    45,    41,    41,    55,
      33,    34,    35,    36,    37,    38,    63,    39,    40,    43,
      64,    59,    44,    43,    43,    76,    61,    67,    62,    46,
      49,    41,    11,    77,    44,    53,    45,    42,    12,    79,
      49,    28,    80,    45,    43,    44,    68,    78,    49,    69,
      44,    45,    14,    15,    71,    49,    42,    72,    45,    62,
      44,    43,    49,    70,    45,    44,    49,    45
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    51,    52,    53,    53,    54,    55,
      55,    56,    57,    57,    58,    59,    59,    59,    60,    60,
      60,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    62,    62,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    64,    64,    66,    67,    68,    65,    69,    70,
      69,    71,    72,    71,    73,    75,    76,    74,    77,    78,
      77,    79,    80,    79
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     8,     3,     5,     5,     1,
       3,     5,     5,     7,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     1,
       4,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     0,     0,    12,     0,     0,
       9,     0,     0,     5,     5,     0,     0,     8,     0,     0,
       8,     0,     0,     5
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

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
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
  case 14: /* assignment: IDENTIFIER SET expression '!'  */
#line 130 "plainscript.y"
        {
		if(skip_level == 0) {
			updateSymbolVal((yyvsp[-3].identifier), (yyvsp[-1].typedval).type, (yyvsp[-1].typedval));
		}
	}
#line 1444 "y.tab.c"
    break;

  case 15: /* func_decl: DO IDENTIFIER '(' param_list ')' '{' statement_list '}'  */
#line 139 "plainscript.y"
    {
        if (functionCount >= 50) {
            ERROR("Function limit reached.");
            exit(1);
        }

        functionTable[functionCount].name = strdup((yyvsp[-6].identifier));
        functionTable[functionCount].paramCount = (yyvsp[-4].paramList)->count;
        functionTable[functionCount].paramNames = (yyvsp[-4].paramList)->names;
        INFO("Function defined: %s", (yyvsp[-6].identifier));
        functionCount++;
    }
#line 1461 "y.tab.c"
    break;

  case 16: /* param_list: IDENTIFIER AS type  */
#line 155 "plainscript.y"
    {
        (yyval.paramList) = malloc(sizeof(struct param_list_node));
        (yyval.paramList)->count = 1;
        (yyval.paramList)->names = malloc(sizeof(char*));
        (yyval.paramList)->names[0] = (yyvsp[-2].identifier);
    }
#line 1472 "y.tab.c"
    break;

  case 17: /* param_list: IDENTIFIER AS type ',' param_list  */
#line 162 "plainscript.y"
    {
        (yyval.paramList) = malloc(sizeof(struct param_list_node));
        (yyval.paramList)->count = (yyvsp[0].paramList)->count + 1;
        (yyval.paramList)->names = malloc(sizeof(char*) * (yyval.paramList)->count);
        (yyval.paramList)->names[0] = (yyvsp[-4].identifier);
        for (int i = 0; i < (yyvsp[0].paramList)->count; i++) {
            (yyval.paramList)->names[i + 1] = (yyvsp[0].paramList)->names[i];
        }
        free((yyvsp[0].paramList));
    }
#line 1487 "y.tab.c"
    break;

  case 18: /* func_call: IDENTIFIER '(' arg_list ')' '!'  */
#line 176 "plainscript.y"
    {
        TypedValue result = callFunction((yyvsp[-4].identifier), (yyvsp[-2].exprList)->args, (yyvsp[-2].exprList)->count);
        // sonucu SAY ile yazdırmak istersen printHandler(result);
    }
#line 1496 "y.tab.c"
    break;

  case 19: /* arg_list: expression  */
#line 184 "plainscript.y"
    {
        (yyval.exprList) = malloc(sizeof(struct expr_list_node));
        (yyval.exprList)->count = 1;
        (yyval.exprList)->args = malloc(sizeof(TypedValue));
        (yyval.exprList)->args[0] = (yyvsp[0].typedval);
    }
#line 1507 "y.tab.c"
    break;

  case 20: /* arg_list: expression ',' arg_list  */
#line 191 "plainscript.y"
    {
        (yyval.exprList) = malloc(sizeof(struct expr_list_node));
        (yyval.exprList)->count = (yyvsp[0].exprList)->count + 1;
        (yyval.exprList)->args = malloc(sizeof(TypedValue) * (yyval.exprList)->count);
        (yyval.exprList)->args[0] = (yyvsp[-2].typedval);
        for (int i = 0; i < (yyvsp[0].exprList)->count; i++) {
            (yyval.exprList)->args[i + 1] = (yyvsp[0].exprList)->args[i];
        }
        free((yyvsp[0].exprList));
    }
#line 1522 "y.tab.c"
    break;

  case 21: /* var_decl: DECLARE IDENTIFIER AS type '!'  */
#line 205 "plainscript.y"
        {
		if(skip_level == 0) {
			addVariable((yyvsp[-3].identifier), (yyvsp[-1].num));
		}
	}
#line 1532 "y.tab.c"
    break;

  case 22: /* input_stmt: ASK '(' IDENTIFIER ')' '!'  */
#line 214 "plainscript.y"
        {
		if(skip_level == 0) {
			inputHandler((yyvsp[-2].identifier), " \" Enter a value: \" "); 
		}
	}
#line 1542 "y.tab.c"
    break;

  case 23: /* input_stmt: ASK '(' IDENTIFIER ',' STRING ')' '!'  */
#line 220 "plainscript.y"
        {
		if(skip_level == 0) {
			inputHandler((yyvsp[-4].identifier), (yyvsp[-2].string));
		}
	}
#line 1552 "y.tab.c"
    break;

  case 24: /* print_stmt: SAY '(' expression ')' '!'  */
#line 229 "plainscript.y"
        {
		if(skip_level == 0) {
			printHandler((yyvsp[-2].typedval));
		}
	}
#line 1562 "y.tab.c"
    break;

  case 25: /* type: TYPE_NUMBER  */
#line 237 "plainscript.y"
                    { (yyval.num) = 1; }
#line 1568 "y.tab.c"
    break;

  case 26: /* type: TYPE_TEXT  */
#line 238 "plainscript.y"
                    { (yyval.num) = 2; }
#line 1574 "y.tab.c"
    break;

  case 27: /* type: TYPE_LOGIC  */
#line 239 "plainscript.y"
                     { (yyval.num) = 3; }
#line 1580 "y.tab.c"
    break;

  case 28: /* term: NUMBER  */
#line 243 "plainscript.y"
               {
		(yyval.typedval) = (TypedValue){ .type = 1 };
		(yyval.typedval).value.number = (yyvsp[0].number);
	}
#line 1589 "y.tab.c"
    break;

  case 29: /* term: STRING  */
#line 247 "plainscript.y"
                 {
		(yyval.typedval) = (TypedValue){ .type = 2 };
		(yyval.typedval).value.text = (yyvsp[0].string);
	}
#line 1598 "y.tab.c"
    break;

  case 30: /* term: LOGIC_TRUE  */
#line 251 "plainscript.y"
                     {
		(yyval.typedval) = (TypedValue){ .type = 3 };
		(yyval.typedval).value.logic = 1;
	}
#line 1607 "y.tab.c"
    break;

  case 31: /* term: LOGIC_FALSE  */
#line 255 "plainscript.y"
                      {
		(yyval.typedval) = (TypedValue){ .type = 3 };
		(yyval.typedval).value.logic = 0;
	}
#line 1616 "y.tab.c"
    break;

  case 32: /* term: IDENTIFIER  */
#line 259 "plainscript.y"
                     {
		(yyval.typedval) = symbolVal((yyvsp[0].identifier));
	}
#line 1624 "y.tab.c"
    break;

  case 34: /* expression: expression PLUS expression  */
#line 266 "plainscript.y"
                                 {
    if ((yyvsp[-2].typedval).type == 1 && (yyvsp[0].typedval).type == 1) {
        // NUMBER + NUMBER
        (yyval.typedval) = (TypedValue){ .type = 1 };
        (yyval.typedval).value.number = (yyvsp[-2].typedval).value.number + (yyvsp[0].typedval).value.number;
    } else if ((yyvsp[-2].typedval).type == 2 && (yyvsp[0].typedval).type == 2) {
        const char* s1 = (yyvsp[-2].typedval).value.text;
        const char* s2 = (yyvsp[0].typedval).value.text;

        size_t len1 = strlen(s1);
        size_t len2 = strlen(s2);

        const char* core1 = s1;
        size_t core1_len = len1;
        if (s1[0] == '"' && s1[len1 - 1] == '"') {
            core1 = s1 + 1;
            core1_len = len1 - 2;
        }

        const char* core2 = s2;
        size_t core2_len = len2;
        if (s2[0] == '"' && s2[len2 - 1] == '"') {
            core2 = s2 + 1;
            core2_len = len2 - 2;
        }

        char* result = malloc(core1_len + core2_len + 3); // quotes + null terminator
        if (!result) {
            ERROR("Memory allocation failed in string concatenation.");
            exit(1);
        }

        sprintf(result, "\"%.*s%.*s\"", (int)core1_len, core1, (int)core2_len, core2);

        (yyval.typedval) = (TypedValue){ .type = 2 };
        (yyval.typedval).value.text = result;
    } else {
        ERROR("Type mismatch in PLUS operation: left type %d, right type %d.", (yyvsp[-2].typedval).type, (yyvsp[0].typedval).type);
        exit(1);
    }
}
#line 1670 "y.tab.c"
    break;

  case 35: /* expression: expression MINUS expression  */
#line 307 "plainscript.y"
                                  {
        if ((yyvsp[-2].typedval).type == 1 && (yyvsp[0].typedval).type == 1) {
            (yyval.typedval) = (TypedValue){ .type = 1 };
            (yyval.typedval).value.number = (yyvsp[-2].typedval).value.number - (yyvsp[0].typedval).value.number;
        } else {
            ERROR("MINUS operation only supported for NUMBER type.");
            exit(1);
        }
    }
#line 1684 "y.tab.c"
    break;

  case 36: /* expression: expression TIMES expression  */
#line 316 "plainscript.y"
                                  {
        if ((yyvsp[-2].typedval).type == 1 && (yyvsp[0].typedval).type == 1) {
            (yyval.typedval) = (TypedValue){ .type = 1 };
            (yyval.typedval).value.number = (yyvsp[-2].typedval).value.number * (yyvsp[0].typedval).value.number;
        } else {
            ERROR("TIMES operation only supported for NUMBER type.");
            exit(1);
        }
    }
#line 1698 "y.tab.c"
    break;

  case 37: /* expression: expression DIVIDE expression  */
#line 325 "plainscript.y"
                                   {
        if ((yyvsp[-2].typedval).type == 1 && (yyvsp[0].typedval).type == 1) {
            if ((yyvsp[0].typedval).value.number == 0) {
                ERROR("Division by zero.");
                (yyval.typedval) = (TypedValue){ .type = 1, .value.number = 0 };
            } else {
                (yyval.typedval) = (TypedValue){ .type = 1 };
                (yyval.typedval).value.number = (yyvsp[-2].typedval).value.number / (yyvsp[0].typedval).value.number;
            }
        } else {
            ERROR("DIVIDE operation only supported for NUMBER type.");
            exit(1);
        }
    }
#line 1717 "y.tab.c"
    break;

  case 38: /* expression: '(' expression ')'  */
#line 339 "plainscript.y"
                         {
        (yyval.typedval) = (yyvsp[-1].typedval);
    }
#line 1725 "y.tab.c"
    break;

  case 39: /* expression: IDENTIFIER  */
#line 342 "plainscript.y"
                 {
        (yyval.typedval) = symbolVal((yyvsp[0].identifier));
    }
#line 1733 "y.tab.c"
    break;

  case 40: /* expression: IDENTIFIER '(' arg_list ')'  */
#line 345 "plainscript.y"
                                  {
        (yyval.typedval) = callFunction((yyvsp[-3].identifier), (yyvsp[-1].exprList)->args, (yyvsp[-1].exprList)->count);
    }
#line 1741 "y.tab.c"
    break;

  case 41: /* condition: expression operator expression  */
#line 355 "plainscript.y"
        {
		(yyval.boolean) = evaluateCondition((yyvsp[-2].typedval), (yyvsp[-1].num), (yyvsp[0].typedval));
	}
#line 1749 "y.tab.c"
    break;

  case 42: /* condition: condition logic_operator condition  */
#line 359 "plainscript.y"
        {
		(yyval.boolean) = evaluateLogic((yyvsp[-2].boolean), (yyvsp[-1].num), (yyvsp[0].boolean));
	}
#line 1757 "y.tab.c"
    break;

  case 43: /* condition: LOGIC_TRUE  */
#line 362 "plainscript.y"
                 {(yyval.boolean) = 1;}
#line 1763 "y.tab.c"
    break;

  case 44: /* condition: LOGIC_FALSE  */
#line 363 "plainscript.y"
                  {(yyval.boolean) = 0;}
#line 1769 "y.tab.c"
    break;

  case 45: /* condition: IDENTIFIER  */
#line 364 "plainscript.y"
                 {
    TypedValue temp = symbolVal((yyvsp[0].identifier));
    if (temp.type != 3) {
        ERROR("Non-LOGIC variable used in condition: %s", (yyvsp[0].identifier));
        exit(1);
    }
    (yyval.boolean) = temp.value.logic == 1 ? 1 : 0;
    }
#line 1782 "y.tab.c"
    break;

  case 46: /* operator: SAME  */
#line 375 "plainscript.y"
             { (yyval.num)= 1; }
#line 1788 "y.tab.c"
    break;

  case 47: /* operator: DIFFERENT  */
#line 375 "plainscript.y"
                                    {(yyval.num) = 2; }
#line 1794 "y.tab.c"
    break;

  case 48: /* operator: SMALLER  */
#line 375 "plainscript.y"
                                                         { (yyval.num)= 3; }
#line 1800 "y.tab.c"
    break;

  case 49: /* operator: BIGGER  */
#line 375 "plainscript.y"
                                                                             {(yyval.num) = 4; }
#line 1806 "y.tab.c"
    break;

  case 50: /* operator: SMALLER_EQUAL  */
#line 375 "plainscript.y"
                                                                                                        { (yyval.num)= 5; }
#line 1812 "y.tab.c"
    break;

  case 51: /* operator: BIGGER_EQUAL  */
#line 375 "plainscript.y"
                                                                                                                                  {(yyval.num) = 6; }
#line 1818 "y.tab.c"
    break;

  case 52: /* logic_operator: BOTH  */
#line 378 "plainscript.y"
             { (yyval.num)= 1; }
#line 1824 "y.tab.c"
    break;

  case 53: /* logic_operator: EITHER  */
#line 378 "plainscript.y"
                                 {(yyval.num) = 2; }
#line 1830 "y.tab.c"
    break;

  case 54: /* $@1: %empty  */
#line 385 "plainscript.y"
        {
		if_chain_executed_flag = 0; 
	}
#line 1838 "y.tab.c"
    break;

  case 55: /* $@2: %empty  */
#line 389 "plainscript.y"
        {   
		
		int condition_result = (yyvsp[-1].boolean); 
		int execute_this_block = 0;

		if (skip_level == 0 && if_chain_executed_flag == 0 && condition_result) {
			execute_this_block = 1;
			if_chain_executed_flag = 1; 
		}

		if (!execute_this_block && skip_level == 0) {
			 skip_level++;
			 mra1_if_block_skipped = 1; 
		} else {
			 mra1_if_block_skipped = 0; 
		}

	}
#line 1861 "y.tab.c"
    break;

  case 56: /* $@3: %empty  */
#line 408 "plainscript.y"
        {
		if (mra1_if_block_skipped && skip_level > 0) {
			skip_level--;
		}
		mra1_if_block_skipped = 0;
	}
#line 1872 "y.tab.c"
    break;

  case 59: /* $@4: %empty  */
#line 422 "plainscript.y"
        {
	
		int condition_result = (yyvsp[-1].boolean); 
		int execute_this_block = 0; 


		if (skip_level == 0 && if_chain_executed_flag == 0 && condition_result) {
			execute_this_block = 1;
			if_chain_executed_flag = 1; 
           
		} 

		if (!execute_this_block && skip_level == 0) {
			 skip_level++;
			 mra3_elseif_block_skipped = 1;
		} else {
			 mra3_elseif_block_skipped = 0; 
		}
       
	}
#line 1897 "y.tab.c"
    break;

  case 60: /* optional_elseif_list: optional_elseif_list MAYBE '(' condition ')' $@4 '{' statement_list '}'  */
#line 443 "plainscript.y"
        {

		if (mra3_elseif_block_skipped && skip_level > 0) {
			skip_level--;
		}
		mra3_elseif_block_skipped = 0; 

	}
#line 1910 "y.tab.c"
    break;

  case 62: /* $@5: %empty  */
#line 456 "plainscript.y"
        {
		
		int execute_this_block = 0;


		if (skip_level == 0 && if_chain_executed_flag == 0) {
			execute_this_block = 1;
			if_chain_executed_flag = 1; 
		} 


		if (!execute_this_block && skip_level == 0) {
			 skip_level++;
			 mra5_else_block_skipped = 1; 
		} else {
			 mra5_else_block_skipped = 0; 
		}
      
	}
#line 1934 "y.tab.c"
    break;

  case 63: /* optional_else_clause: OTHERWISE $@5 '{' statement_list '}'  */
#line 476 "plainscript.y"
        {
		if (mra5_else_block_skipped && skip_level > 0) {
			skip_level--;
		}
		mra5_else_block_skipped = 0; 

	}
#line 1946 "y.tab.c"
    break;

  case 64: /* throw_stmt: THROW '(' expression ')' '!'  */
#line 487 "plainscript.y"
        {
		if(skip_level == 0) {
			if(in_try_block) {
				exception_thrown = 1;
				
				if((yyvsp[-2].typedval).type == 2) { // TEXT
					if(exception_message != NULL) {
						free(exception_message);
					}
					exception_message = strdup((yyvsp[-2].typedval).value.text);
					if(exception_message == NULL) {
						ERROR("Memory allocation failed for exception message");
						exit(1);
					}
				} else {
					ERROR("Exception message must be of TEXT type");
					exit(1);
				}
				
				skip_level++;
			} else {
				ERROR("THROW statement outside of TRY block");
				exit(1);
			}
		}
	}
#line 1977 "y.tab.c"
    break;

  case 65: /* $@6: %empty  */
#line 517 "plainscript.y"
        {
		if(skip_level == 0) {
			in_try_block = 1;
			exception_thrown = 0;
		}
	}
#line 1988 "y.tab.c"
    break;

  case 66: /* $@7: %empty  */
#line 524 "plainscript.y"
        {
		if(skip_level == 0) {
			in_try_block = 0;
		}
		else if(exception_thrown && skip_level == 1) {
			skip_level--;
		}
	}
#line 2001 "y.tab.c"
    break;

  case 69: /* $@8: %empty  */
#line 539 "plainscript.y"
        {
		if(skip_level == 0) {
			if(exception_thrown) {
				int found = 0;
				for(int i = 0; i < symbolCount; i++) {
					if(strcmp(symbolTable[i].name, (yyvsp[-1].identifier)) == 0) {
						found = 1;
						if(symbolTable[i].type == 2) { // TEXT
							if(symbolTable[i].value.text != NULL) {
								free(symbolTable[i].value.text);
							}
							symbolTable[i].value.text = strdup(exception_message);
							if(symbolTable[i].value.text == NULL) {
								ERROR("Memory allocation failed for exception variable");
								exit(1);
							}
						} else {
							ERROR("Exception variable must be of TEXT type");
							exit(1);
						}
						break;
					}
				}
				if(!found) {
					addVariable((yyvsp[-1].identifier), 2); // TEXT type
					TypedValue tv;
					tv.type = 2;
					tv.value.text = strdup(exception_message);
					updateSymbolVal((yyvsp[-1].identifier), 2, tv);
				}
				
				exception_thrown = 0;
				catch_block_skipped = 0;
			} else {
				skip_level++;
				catch_block_skipped = 1;
			}
		}
	}
#line 2045 "y.tab.c"
    break;

  case 70: /* optional_catch_clause: CATCH '(' IDENTIFIER ')' $@8 '{' statement_list '}'  */
#line 579 "plainscript.y"
        {
		if(catch_block_skipped && skip_level > 0) {
			skip_level--;
			catch_block_skipped = 0;
		}
	}
#line 2056 "y.tab.c"
    break;

  case 72: /* $@9: %empty  */
#line 590 "plainscript.y"
        {
		if(skip_level > 0 && !in_try_block) {
			skip_level = 0;
		}
	}
#line 2066 "y.tab.c"
    break;


#line 2070 "y.tab.c"

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

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
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

#line 601 "plainscript.y"


void addVariable(char* name, int type) {

    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            ERROR("Variable '%s' already declared.", name);
            exit(1);
        }
    }

    if (symbolCount >= SYMBOL_LIMIT) {
        ERROR("Symbol table overflow.");
        exit(1);
    }

    symbolTable[symbolCount].name = strdup(name);
    if (symbolTable[symbolCount].name == NULL) {
        ERROR("Memory allocation failed for variable '%s'.", name);
        exit(1);
    }
    symbolTable[symbolCount].type = type;
    symbolCount++;
    INFO("Declared variable: %s (type %d)", name, type);
}

TypedValue symbolVal(char* name) {
    TypedValue result;
    result.type = 0; // default olarak invalid yapalım

    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            result.type = symbolTable[i].type;

            switch (symbolTable[i].type) {
                case 1: // NUMBER
                    result.value.number = symbolTable[i].value.number;
                    break;
                case 2: // TEXT
                    result.value.text = symbolTable[i].value.text;
                    break;
                case 3: // LOGIC
                    result.value.logic = symbolTable[i].value.logic;
                    break;
                default:
                    ERROR("Unknown type for variable '%s'.", name);
                    exit(1);
            }

            return result;
        }
    }

    ERROR("Undeclared variable: '%s'", name);
    return result;
}


void updateSymbolVal(char* name, int type, TypedValue val) {
    if (name == NULL) {
        ERROR("Invalid variable name for update.");
        exit(1);
    }

    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            if (symbolTable[i].type != type) {
                ERROR("Type mismatch when assigning to '%s'.", name);
                exit(1);
            }

            switch (type) {
                case 1: // NUMBER
                    symbolTable[i].value.number = val.value.number;
                    break;
                case 2: // TEXT
                    if (symbolTable[i].value.text != NULL) {
                        free(symbolTable[i].value.text);
                    }
                    symbolTable[i].value.text = strdup(val.value.text);
                    if (symbolTable[i].value.text == NULL) {
                        ERROR("Memory allocation failed during update for '%s'.", name);
                        exit(1);
                    }
                    break;
                case 3: // LOGIC
                    symbolTable[i].value.logic = val.value.logic;
                    break;
                default:
                    ERROR("Unknown type in update for '%s'.", name);
                    exit(1);
            }
            INFO("Assigned variable: %s", name);
            return;
        }
    }

    ERROR("Undeclared variable: '%s'", name);
    exit(1);
}



void inputHandler(char* name, char* message) {
    int i;

    for (i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, name) == 0) {
            break;
        }
    }

    if (i == symbolCount) {
        ERROR("Variable '%s' not found for input.", name);
        exit(1);
    }

    char buffer[256];
    printf("%.*s\n", (int)(strlen(message) - 2), message + 1); 

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        ERROR("Failed to read input for '%s'.", name);
        exit(1);
    }

    buffer[strcspn(buffer, "\n")] = 0;

    switch (symbolTable[i].type) {
        case 1: // NUMBER
        {
            double tempNumber;
            if (sscanf(buffer, "%lf", &tempNumber) == 1) {
                symbolTable[i].value.number = tempNumber;
                INFO("Input assigned to variable '%s' (NUMBER)", name);
            } else {
                ERROR("Type mismatch: Expected NUMBER for '%s'.", name);
                exit(1);
            }
            break;
        }
        case 2: // TEXT
        {
            if (buffer[0] == '"' && buffer[strlen(buffer) - 1] == '"') {
                if (symbolTable[i].value.text != NULL) {
                    free(symbolTable[i].value.text); 
                }
                symbolTable[i].value.text = strdup(buffer);
                if (symbolTable[i].value.text == NULL) {
                    ERROR("Memory allocation failed for input TEXT of '%s'.", name);
                    exit(1);
                }
                INFO("Input assigned to variable '%s' (TEXT)", name);
            } else {
                ERROR("Type mismatch: Expected quoted TEXT for '%s'.", name);
                exit(1);
            }
            break;
        }
        case 3: // LOGIC
        {
            int tempLogic;
            if (sscanf(buffer, "%d", &tempLogic) == 1 && (tempLogic == 0 || tempLogic == 1)) {
                symbolTable[i].value.logic = tempLogic;
                INFO("Input assigned to variable '%s' (LOGIC)", name);
            } else {
                ERROR("Type mismatch: Expected LOGIC (0 or 1) for '%s'.", name);
                exit(1);
            }
            break;
        }
        default:
            ERROR("Unknown type for variable '%s' during input.", name);
            exit(1);
    }
}


void printHandler(TypedValue value) {
    switch (value.type) {
        case 1: // NUMBER
            if (value.value.number == (int)value.value.number) {
                printf("%d\n", (int)value.value.number);
            } else {
                printf("%f\n", value.value.number);
            }
            break;

        case 2: // TEXT
            printf("%.*s\n", (int)(strlen(value.value.text) - 2), value.value.text + 1);
            break;

        case 3: // LOGIC
            if (value.value.logic == 1) {
                printf("RIGHT\n");
            } else {
                printf("WRONG\n");
            }
            break;

        default:
            ERROR("Unknown type for SAY statement.");
            exit(1);
    }
}


int evaluateCondition(TypedValue left, int operator, TypedValue right) {
    if (left.type != right.type) {
        ERROR("Type mismatch in condition: left.type = %d, right.type = %d", left.type, right.type);
        exit(1);
    }

    switch (left.type) {
        case 1: // NUMBER
            switch (operator) {
                case 1: return left.value.number == right.value.number;
                case 2: return left.value.number != right.value.number;
                case 3: return left.value.number < right.value.number;
                case 4: return left.value.number > right.value.number;
                case 5: return left.value.number <= right.value.number;
                case 6: return left.value.number >= right.value.number;
                default:
                    ERROR("Unknown operator '%d' in NUMBER condition.", operator);
                    exit(1);
            }

        case 2: // TEXT
            switch (operator) {
                case 1: return strcmp(left.value.text, right.value.text) == 0;
                case 2: return strcmp(left.value.text, right.value.text) != 0;
                default:
                    ERROR("Unknown operator '%d' in TEXT condition.", operator);
                    exit(1);
            }

        case 3: // LOGIC
            switch (operator) {
                case 1: return left.value.logic == right.value.logic;
                case 2: return left.value.logic != right.value.logic;
                default:
                    ERROR("Unknown operator '%d' in LOGIC condition.", operator);
                    exit(1);
            }

        default:
            ERROR("Unknown type '%d' in condition.", left.type);
            exit(1);
    }
}

int evaluateLogic(int leftCondition, int operator, int rightCondition) {
    switch (operator) {
        case 1: // BOTH 
            return leftCondition && rightCondition;
        case 2: // EITHER
            return leftCondition || rightCondition;
        default:
            ERROR("Unknown logic operator '%d'.", operator);
            exit(1);
    }
}


void yyerror(const char *s) {
    fprintf(stderr, "Parser error: %s\n", s);
}

int main() {
    logFile = fopen("program_log.txt" , "w");

    if (logFile == NULL) {
        printf("Failed to open log file.\n");
        return 1;
    }

    int result = yyparse();
    if(result == 1){
        fprintf(logFile, "\nSyntax Error at line %d.",currentLine);
    }
    fclose(logFile);

    return result;
}
