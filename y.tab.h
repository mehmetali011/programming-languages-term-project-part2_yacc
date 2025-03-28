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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    DECLARE = 258,                 /* DECLARE  */
    AS = 259,                      /* AS  */
    SET = 260,                     /* SET  */
    ASK = 261,                     /* ASK  */
    RETURN = 262,                  /* RETURN  */
    THROW = 263,                   /* THROW  */
    TRY = 264,                     /* TRY  */
    CATCH = 265,                   /* CATCH  */
    FINALLY = 266,                 /* FINALLY  */
    ISIT = 267,                    /* ISIT  */
    MAYBE = 268,                   /* MAYBE  */
    OTHERWISE = 269,               /* OTHERWISE  */
    DURING = 270,                  /* DURING  */
    COUNT = 271,                   /* COUNT  */
    FROM = 272,                    /* FROM  */
    TO = 273,                      /* TO  */
    SAY = 274,                     /* SAY  */
    DO = 275,                      /* DO  */
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
#define DECLARE 258
#define AS 259
#define SET 260
#define ASK 261
#define RETURN 262
#define THROW 263
#define TRY 264
#define CATCH 265
#define FINALLY 266
#define ISIT 267
#define MAYBE 268
#define OTHERWISE 269
#define DURING 270
#define COUNT 271
#define FROM 272
#define TO 273
#define SAY 274
#define DO 275
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
#line 41 "plainscript.y"

    int boolean;
    double number;
    char* string;
    char* identifier;
    int num;
    TypedValue typedval;

#line 156 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
