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
    INTEGER = 258,                 /* INTEGER  */
    REAL = 259,                    /* REAL  */
    CHAR_LITERAL = 260,            /* CHAR_LITERAL  */
    STRING_LITERAL = 261,          /* STRING_LITERAL  */
    IDENTIFIER = 262,              /* IDENTIFIER  */
    BOOL = 263,                    /* BOOL  */
    CHAR = 264,                    /* CHAR  */
    INT = 265,                     /* INT  */
    REAL_TYPE = 266,               /* REAL_TYPE  */
    STRING = 267,                  /* STRING  */
    INT_PTR = 268,                 /* INT_PTR  */
    CHAR_PTR = 269,                /* CHAR_PTR  */
    REAL_PTR = 270,                /* REAL_PTR  */
    TYPE = 271,                    /* TYPE  */
    MODULO = 272,                  /* MODULO  */
    IF = 273,                      /* IF  */
    ELIF = 274,                    /* ELIF  */
    ELSE = 275,                    /* ELSE  */
    WHILE = 276,                   /* WHILE  */
    FOR = 277,                     /* FOR  */
    VAR = 278,                     /* VAR  */
    PAR = 279,                     /* PAR  */
    RETURN = 280,                  /* RETURN  */
    NULL_TOKEN = 281,              /* NULL_TOKEN  */
    DO = 282,                      /* DO  */
    RETURNS = 283,                 /* RETURNS  */
    BEGIN_TOKEN = 284,             /* BEGIN_TOKEN  */
    END = 285,                     /* END  */
    DEF = 286,                     /* DEF  */
    CALL = 287,                    /* CALL  */
    AND = 288,                     /* AND  */
    NOT = 289,                     /* NOT  */
    OR = 290,                      /* OR  */
    EQ = 291,                      /* EQ  */
    NE = 292,                      /* NE  */
    GE = 293,                      /* GE  */
    LE = 294,                      /* LE  */
    GT = 295,                      /* GT  */
    LT = 296,                      /* LT  */
    ASSIGN = 297,                  /* ASSIGN  */
    PLUS = 298,                    /* PLUS  */
    MINUS = 299,                   /* MINUS  */
    MULT = 300,                    /* MULT  */
    DIV = 301,                     /* DIV  */
    AMPERSAND = 302,               /* AMPERSAND  */
    TRUE = 303,                    /* TRUE  */
    FALSE = 304,                   /* FALSE  */
    MAIN = 305                     /* MAIN  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define INTEGER 258
#define REAL 259
#define CHAR_LITERAL 260
#define STRING_LITERAL 261
#define IDENTIFIER 262
#define BOOL 263
#define CHAR 264
#define INT 265
#define REAL_TYPE 266
#define STRING 267
#define INT_PTR 268
#define CHAR_PTR 269
#define REAL_PTR 270
#define TYPE 271
#define MODULO 272
#define IF 273
#define ELIF 274
#define ELSE 275
#define WHILE 276
#define FOR 277
#define VAR 278
#define PAR 279
#define RETURN 280
#define NULL_TOKEN 281
#define DO 282
#define RETURNS 283
#define BEGIN_TOKEN 284
#define END 285
#define DEF 286
#define CALL 287
#define AND 288
#define NOT 289
#define OR 290
#define EQ 291
#define NE 292
#define GE 293
#define LE 294
#define GT 295
#define LT 296
#define ASSIGN 297
#define PLUS 298
#define MINUS 299
#define MULT 300
#define DIV 301
#define AMPERSAND 302
#define TRUE 303
#define FALSE 304
#define MAIN 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "parser.y"

    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
    struct node* nodePtr;

#line 175 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
