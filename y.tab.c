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
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int yylex();
    int yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    
    typedef struct node
    {
        char* token;
        struct node* left;
        struct node* right;
    } node;
    node* mknode(char* token, node* left, node* right);
    void printTree(node* tree, int level);
    void visualize_ast(node* root, const char* branch_prefix, int is_left_branch);

#line 92 "y.tab.c"

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

#line 250 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);



/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INTEGER = 3,                    /* INTEGER  */
  YYSYMBOL_REAL = 4,                       /* REAL  */
  YYSYMBOL_CHAR_LITERAL = 5,               /* CHAR_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 6,             /* STRING_LITERAL  */
  YYSYMBOL_IDENTIFIER = 7,                 /* IDENTIFIER  */
  YYSYMBOL_BOOL = 8,                       /* BOOL  */
  YYSYMBOL_CHAR = 9,                       /* CHAR  */
  YYSYMBOL_INT = 10,                       /* INT  */
  YYSYMBOL_REAL_TYPE = 11,                 /* REAL_TYPE  */
  YYSYMBOL_STRING = 12,                    /* STRING  */
  YYSYMBOL_INT_PTR = 13,                   /* INT_PTR  */
  YYSYMBOL_CHAR_PTR = 14,                  /* CHAR_PTR  */
  YYSYMBOL_REAL_PTR = 15,                  /* REAL_PTR  */
  YYSYMBOL_TYPE = 16,                      /* TYPE  */
  YYSYMBOL_MODULO = 17,                    /* MODULO  */
  YYSYMBOL_IF = 18,                        /* IF  */
  YYSYMBOL_ELIF = 19,                      /* ELIF  */
  YYSYMBOL_ELSE = 20,                      /* ELSE  */
  YYSYMBOL_WHILE = 21,                     /* WHILE  */
  YYSYMBOL_FOR = 22,                       /* FOR  */
  YYSYMBOL_VAR = 23,                       /* VAR  */
  YYSYMBOL_PAR = 24,                       /* PAR  */
  YYSYMBOL_RETURN = 25,                    /* RETURN  */
  YYSYMBOL_NULL_TOKEN = 26,                /* NULL_TOKEN  */
  YYSYMBOL_DO = 27,                        /* DO  */
  YYSYMBOL_RETURNS = 28,                   /* RETURNS  */
  YYSYMBOL_BEGIN_TOKEN = 29,               /* BEGIN_TOKEN  */
  YYSYMBOL_END = 30,                       /* END  */
  YYSYMBOL_DEF = 31,                       /* DEF  */
  YYSYMBOL_CALL = 32,                      /* CALL  */
  YYSYMBOL_AND = 33,                       /* AND  */
  YYSYMBOL_NOT = 34,                       /* NOT  */
  YYSYMBOL_OR = 35,                        /* OR  */
  YYSYMBOL_EQ = 36,                        /* EQ  */
  YYSYMBOL_NE = 37,                        /* NE  */
  YYSYMBOL_GE = 38,                        /* GE  */
  YYSYMBOL_LE = 39,                        /* LE  */
  YYSYMBOL_GT = 40,                        /* GT  */
  YYSYMBOL_LT = 41,                        /* LT  */
  YYSYMBOL_ASSIGN = 42,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 43,                      /* PLUS  */
  YYSYMBOL_MINUS = 44,                     /* MINUS  */
  YYSYMBOL_MULT = 45,                      /* MULT  */
  YYSYMBOL_DIV = 46,                       /* DIV  */
  YYSYMBOL_AMPERSAND = 47,                 /* AMPERSAND  */
  YYSYMBOL_TRUE = 48,                      /* TRUE  */
  YYSYMBOL_FALSE = 49,                     /* FALSE  */
  YYSYMBOL_MAIN = 50,                      /* MAIN  */
  YYSYMBOL_51_ = 51,                       /* '('  */
  YYSYMBOL_52_ = 52,                       /* ')'  */
  YYSYMBOL_53_ = 53,                       /* ':'  */
  YYSYMBOL_54_ = 54,                       /* ';'  */
  YYSYMBOL_55_ = 55,                       /* ','  */
  YYSYMBOL_56_ = 56,                       /* '['  */
  YYSYMBOL_57_ = 57,                       /* ']'  */
  YYSYMBOL_YYACCEPT = 58,                  /* $accept  */
  YYSYMBOL_code = 59,                      /* code  */
  YYSYMBOL_functions = 60,                 /* functions  */
  YYSYMBOL_function = 61,                  /* function  */
  YYSYMBOL_parameters = 62,                /* parameters  */
  YYSYMBOL_parameter_list = 63,            /* parameter_list  */
  YYSYMBOL_parameter = 64,                 /* parameter  */
  YYSYMBOL_var = 65,                       /* var  */
  YYSYMBOL_declaration_list = 66,          /* declaration_list  */
  YYSYMBOL_declaration = 67,               /* declaration  */
  YYSYMBOL_type = 68,                      /* type  */
  YYSYMBOL_id_list = 69,                   /* id_list  */
  YYSYMBOL_statements = 70,                /* statements  */
  YYSYMBOL_nested_function = 71,           /* nested_function  */
  YYSYMBOL_statement = 72,                 /* statement  */
  YYSYMBOL_assignment_statement = 73,      /* assignment_statement  */
  YYSYMBOL_if_statement = 74,              /* if_statement  */
  YYSYMBOL_while_statement = 75,           /* while_statement  */
  YYSYMBOL_do_while_statement = 76,        /* do_while_statement  */
  YYSYMBOL_for_statement = 77,             /* for_statement  */
  YYSYMBOL_for_header = 78,                /* for_header  */
  YYSYMBOL_update_exp = 79,                /* update_exp  */
  YYSYMBOL_block_statement = 80,           /* block_statement  */
  YYSYMBOL_return_statement = 81,          /* return_statement  */
  YYSYMBOL_function_call_statement = 82,   /* function_call_statement  */
  YYSYMBOL_function_call = 83,             /* function_call  */
  YYSYMBOL_expr_list = 84,                 /* expr_list  */
  YYSYMBOL_expression = 85                 /* expression  */
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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   676

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  101
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  242

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      51,    52,     2,     2,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    53,    54,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    57,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    57,    57,    59,    60,    63,    64,    65,    69,    70,
      73,    74,    77,    79,    80,    83,    84,    87,    90,    91,
      92,    93,    94,    95,    96,    97,   100,   101,   102,   103,
     104,   109,   114,   119,   126,   127,   128,   129,   134,   136,
     140,   141,   142,   143,   144,   145,   146,   147,   151,   152,
     158,   159,   160,   161,   166,   169,   175,   176,   177,   178,
     182,   186,   190,   191,   195,   201,   213,   214,   218,   219,
     223,   224,   228,   229,   233,   234,   238,   243,   248,   249,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276
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
  "\"end of file\"", "error", "\"invalid token\"", "INTEGER", "REAL",
  "CHAR_LITERAL", "STRING_LITERAL", "IDENTIFIER", "BOOL", "CHAR", "INT",
  "REAL_TYPE", "STRING", "INT_PTR", "CHAR_PTR", "REAL_PTR", "TYPE",
  "MODULO", "IF", "ELIF", "ELSE", "WHILE", "FOR", "VAR", "PAR", "RETURN",
  "NULL_TOKEN", "DO", "RETURNS", "BEGIN_TOKEN", "END", "DEF", "CALL",
  "AND", "NOT", "OR", "EQ", "NE", "GE", "LE", "GT", "LT", "ASSIGN", "PLUS",
  "MINUS", "MULT", "DIV", "AMPERSAND", "TRUE", "FALSE", "MAIN", "'('",
  "')'", "':'", "';'", "','", "'['", "']'", "$accept", "code", "functions",
  "function", "parameters", "parameter_list", "parameter", "var",
  "declaration_list", "declaration", "type", "id_list", "statements",
  "nested_function", "statement", "assignment_statement", "if_statement",
  "while_statement", "do_while_statement", "for_statement", "for_header",
  "update_exp", "block_statement", "return_statement",
  "function_call_statement", "function_call", "expr_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-106)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -25,    -2,    22,  -106,   -25,    -5,     7,  -106,  -106,     2,
      -9,   244,    -3,  -106,    17,    20,  -106,  -106,  -106,  -106,
    -106,  -106,  -106,  -106,    21,    39,     2,    71,    88,    29,
    -106,    80,    69,  -106,   244,    70,   244,  -106,    80,   344,
      71,   344,    48,  -106,   -27,   187,   187,    51,    61,    54,
     344,   102,   104,   106,    85,    86,   344,   344,  -106,  -106,
    -106,  -106,  -106,  -106,  -106,  -106,    63,    89,    90,   112,
     163,   187,  -106,  -106,  -106,  -106,    66,   187,   197,   116,
     187,  -106,   530,   555,   117,    73,  -106,   355,     1,    98,
      78,    92,    95,   344,  -106,  -106,  -106,  -106,   344,  -106,
     -28,    77,    87,   132,    94,   380,   234,   187,    -1,    66,
    -106,    84,   605,   187,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,     1,     1,   108,     1,
    -106,   123,  -106,     2,   129,   187,   121,   122,   187,   112,
     143,  -106,  -106,    16,  -106,  -106,   111,   249,   187,  -106,
    -106,   541,   341,   615,   615,    -8,    -8,    -8,    -8,    -1,
      -1,  -106,  -106,    43,  -106,   187,    18,  -106,   187,   103,
    -106,   107,   279,   405,  -106,  -106,   309,  -106,    97,  -106,
     217,  -106,   264,   187,   105,   430,   344,  -106,   455,   109,
    -106,   187,  -106,   112,    36,   118,   124,   128,   480,  -106,
     580,     1,   187,   126,  -106,    32,  -106,  -106,   154,   112,
    -106,  -106,  -106,  -106,     1,  -106,   505,  -106,   244,   134,
     110,  -106,   151,   168,    71,   344,   112,   130,   135,   133,
     155,   157,  -106,     1,   187,  -106,   344,  -106,  -106,   630,
     176,  -106
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     0,     1,     4,     8,
       0,     0,     0,     9,    10,     0,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,    13,     0,    13,
      11,     0,     0,    12,     0,     0,     0,    14,    15,     0,
      13,     0,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    36,    34,    40,    41,
      42,    44,    43,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    76,    77,    79,    78,    80,     0,     0,     0,
       0,   101,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,     0,     0,     5,    37,    35,    70,     0,     7,
      26,     0,     0,     0,   101,     0,     0,     0,    86,    80,
      90,    87,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      68,     0,    66,     8,     0,     0,     0,     0,     0,     0,
       0,    17,    52,    87,    71,    48,     0,     0,     0,    91,
      85,    98,    99,    92,    93,    94,    95,    96,    97,    81,
      82,    83,    84,    56,    60,     0,     0,    62,     0,     0,
      72,     0,    74,     0,    67,     6,    28,    27,     0,    51,
       0,   100,     0,     0,     0,     0,     0,    63,     0,     0,
      73,     0,    50,     0,    30,    76,    79,    78,     0,    88,
       0,     0,     0,     0,    61,    13,    75,    29,     0,     0,
      53,    49,    54,    55,     0,    57,     0,    66,     0,     0,
      32,    31,    58,     0,    13,     0,     0,     0,     0,     0,
       0,     0,    33,     0,     0,    64,     0,    39,    59,    65,
       0,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -106,  -106,   205,  -106,    79,   185,  -106,   -26,   175,  -106,
     -13,  -105,   -37,  -106,  -106,  -106,  -106,  -106,  -106,  -106,
    -106,  -106,   -76,  -106,  -106,   -39,    24,   -38
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    12,    13,    14,    54,    37,    38,
      24,   101,    55,    56,    57,    58,    59,    60,    61,    62,
      85,   229,    63,    64,    65,    81,   171,   172
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      66,    32,    66,    35,    68,     5,     1,    82,    83,   113,
      87,    66,   131,    89,    67,    70,   113,    66,    66,    95,
      96,    40,     7,    42,    31,   138,    11,   139,   140,    71,
      50,   104,   105,   106,   177,   122,   123,   124,   125,   108,
     110,    31,   112,    15,   124,   125,     9,   186,     6,    25,
     163,   164,    31,   167,    66,    31,   136,    34,    10,    66,
     218,   137,   183,   184,    72,    73,    74,    75,    76,   147,
     179,    26,   148,    27,    28,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   207,   208,
     187,   209,    29,    52,    31,    33,    36,   173,    39,    41,
     176,    69,    84,   166,   221,    77,    78,    88,    79,    90,
     182,    91,    80,    92,    93,    86,    94,    97,    98,   100,
      99,   232,   107,   111,   128,   215,   129,   185,   132,   133,
     188,   141,    72,    73,    74,    75,    76,   135,   222,   143,
     148,   142,   198,   134,   168,   200,   178,    66,   144,   203,
     165,   174,   175,   180,   194,   189,   217,   238,   201,   190,
     220,    52,   205,   225,   216,   226,    72,    73,    74,    75,
      76,   227,   210,    77,    78,   228,    79,   234,   211,   219,
      80,   170,   212,   233,   236,   235,    66,   237,   231,   102,
      72,    73,    74,    75,    76,    52,   239,    66,   230,   240,
      72,    73,    74,    75,   109,   224,   241,    77,    78,     8,
     103,    30,   169,    43,    80,   206,     0,     0,     0,    52,
     195,    73,   196,   197,    76,     0,     0,     0,     0,    52,
       0,    77,    78,     0,    79,     0,     0,     0,    80,     0,
       0,    77,    78,     0,    79,     0,     0,     0,    80,    52,
       0,   113,    16,    17,    18,    19,    20,    21,    22,    23,
       0,    77,    78,     0,    79,     0,   113,   114,    80,   115,
     116,   117,   118,   119,   120,   121,     0,   122,   123,   124,
     125,   113,   114,     0,   115,   116,   117,   118,   119,   120,
     121,   146,   122,   123,   124,   125,   113,   114,     0,   115,
     116,   117,   118,   119,   120,   121,   181,   122,   123,   124,
     125,     0,   114,     0,   115,   116,   117,   118,   119,   120,
     121,   199,   122,   123,   124,   125,   113,     0,     0,     0,
       0,     0,     0,     0,   191,     0,     0,     0,     0,     0,
       0,     0,   114,     0,   115,   116,   117,   118,   119,   120,
     121,    44,   122,   123,   124,   125,     0,     0,   113,     0,
       0,     0,    45,     0,   193,    46,    47,    31,     0,    48,
       0,    49,   113,    50,   114,    51,    52,   116,   117,   118,
     119,   120,   121,     0,   122,   123,   124,   125,   114,    53,
     115,   116,   117,   118,   119,   120,   121,   113,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,   130,
       0,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   113,   122,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,   145,     0,     0,     0,   114,     0,
     115,   116,   117,   118,   119,   120,   121,   113,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,   192,
       0,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   113,   122,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,   202,     0,     0,     0,   114,     0,
     115,   116,   117,   118,   119,   120,   121,   113,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,   204,
       0,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   113,   122,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,   213,     0,     0,     0,   114,     0,
     115,   116,   117,   118,   119,   120,   121,   113,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,   113,   223,
       0,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   113,   122,   123,   124,   125,   116,   117,   118,
     119,   120,   121,   126,   122,   123,   124,   125,   114,     0,
     115,   116,   117,   118,   119,   120,   121,   113,   122,   123,
     124,   125,     0,     0,     0,     0,     0,     0,   127,     0,
       0,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,   113,   122,   123,   124,   125,     0,     0,     0,
       0,     0,   113,   214,     0,     0,     0,     0,   114,     0,
     115,   116,   117,   118,   119,   120,   121,   113,   122,   123,
     124,   125,     0,   118,   119,   120,   121,   149,   122,   123,
     124,   125,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     0,   122,   123,   124,   125
};

static const yytype_int16 yycheck[] =
{
      39,    27,    41,    29,    41,     7,    31,    45,    46,    17,
      48,    50,    88,    50,    40,    42,    17,    56,    57,    56,
      57,    34,     0,    36,    23,    53,    24,    55,    56,    56,
      29,    70,    70,    71,   139,    43,    44,    45,    46,    77,
      78,    23,    80,    52,    45,    46,    51,    29,    50,    52,
     126,   127,    23,   129,    93,    23,    93,    28,    51,    98,
      28,    98,    19,    20,     3,     4,     5,     6,     7,   107,
      54,    54,    56,    53,    53,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   193,    53,
     166,    55,    53,    32,    23,     7,    16,   135,    29,    29,
     138,    53,    51,   129,   209,    44,    45,    53,    47,     7,
     148,     7,    51,     7,    29,    54,    30,    54,    29,     7,
      30,   226,    56,     7,     7,   201,    53,   165,    30,    51,
     168,    54,     3,     4,     5,     6,     7,    42,   214,     7,
      56,    54,   180,    51,    21,   183,     3,   186,    54,   186,
      42,    30,    30,    42,    57,    52,    30,   233,    53,    52,
       6,    32,    53,    29,   202,    55,     3,     4,     5,     6,
       7,    20,    54,    44,    45,     7,    47,    42,    54,   205,
      51,    52,    54,    53,    29,    52,   225,    30,   225,    26,
       3,     4,     5,     6,     7,    32,   234,   236,   224,   236,
       3,     4,     5,     6,     7,   218,    30,    44,    45,     4,
      47,    26,   133,    38,    51,   191,    -1,    -1,    -1,    32,
       3,     4,     5,     6,     7,    -1,    -1,    -1,    -1,    32,
      -1,    44,    45,    -1,    47,    -1,    -1,    -1,    51,    -1,
      -1,    44,    45,    -1,    47,    -1,    -1,    -1,    51,    32,
      -1,    17,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    44,    45,    -1,    47,    -1,    17,    33,    51,    35,
      36,    37,    38,    39,    40,    41,    -1,    43,    44,    45,
      46,    17,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    57,    43,    44,    45,    46,    17,    33,    -1,    35,
      36,    37,    38,    39,    40,    41,    57,    43,    44,    45,
      46,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,    57,    43,    44,    45,    46,    17,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    -1,    35,    36,    37,    38,    39,    40,
      41,     7,    43,    44,    45,    46,    -1,    -1,    17,    -1,
      -1,    -1,    18,    -1,    55,    21,    22,    23,    -1,    25,
      -1,    27,    17,    29,    33,    31,    32,    36,    37,    38,
      39,    40,    41,    -1,    43,    44,    45,    46,    33,    45,
      35,    36,    37,    38,    39,    40,    41,    17,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    17,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    17,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    17,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    17,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    17,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    -1,    -1,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    17,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    17,    54,
      -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    17,    43,    44,    45,    46,    36,    37,    38,
      39,    40,    41,    53,    43,    44,    45,    46,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    17,    43,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,
      -1,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    17,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    17,    53,    -1,    -1,    -1,    -1,    33,    -1,
      35,    36,    37,    38,    39,    40,    41,    17,    43,    44,
      45,    46,    -1,    38,    39,    40,    41,    52,    43,    44,
      45,    46,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    31,    59,    60,    61,     7,    50,     0,    60,    51,
      51,    24,    62,    63,    64,    52,     8,     9,    10,    11,
      12,    13,    14,    15,    68,    52,    54,    53,    53,    53,
      63,    23,    65,     7,    28,    65,    16,    66,    67,    29,
      68,    29,    68,    66,     7,    18,    21,    22,    25,    27,
      29,    31,    32,    45,    65,    70,    71,    72,    73,    74,
      75,    76,    77,    80,    81,    82,    83,    65,    70,    53,
      42,    56,     3,     4,     5,     6,     7,    44,    45,    47,
      51,    83,    85,    85,    51,    78,    54,    85,    53,    70,
       7,     7,     7,    29,    30,    70,    70,    54,    29,    30,
       7,    69,    26,    47,    83,    85,    85,    56,    85,     7,
      85,     7,    85,    17,    33,    35,    36,    37,    38,    39,
      40,    41,    43,    44,    45,    46,    53,    53,     7,    53,
      54,    80,    30,    51,    51,    42,    70,    70,    53,    55,
      56,    54,    54,     7,    54,    54,    57,    85,    56,    52,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    80,    80,    42,    65,    80,    21,    62,
      52,    84,    85,    85,    30,    30,    85,    69,     3,    54,
      42,    57,    85,    19,    20,    85,    29,    80,    85,    52,
      52,    55,    54,    55,    57,     3,     5,     6,    85,    57,
      85,    53,    54,    70,    54,    53,    84,    69,    53,    55,
      54,    54,    54,    54,    53,    80,    85,    30,    28,    65,
       6,    69,    80,    54,    68,    29,    55,    20,     7,    79,
      65,    70,    69,    53,    42,    52,    29,    30,    80,    85,
      70,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    58,    59,    60,    60,    61,    61,    61,    62,    62,
      63,    63,    64,    65,    65,    66,    66,    67,    68,    68,
      68,    68,    68,    68,    68,    68,    69,    69,    69,    69,
      69,    69,    69,    69,    70,    70,    70,    70,    71,    71,
      72,    72,    72,    72,    72,    72,    72,    72,    73,    73,
      73,    73,    73,    73,    73,    73,    74,    74,    74,    74,
      75,    76,    77,    77,    78,    79,    80,    80,    81,    81,
      82,    82,    83,    83,    84,    84,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85,    85,    85,    85,    85,    85,    85,    85,    85,
      85,    85
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     9,    12,    10,     0,     1,
       1,     3,     4,     0,     2,     1,     2,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     5,
       4,     6,     6,     8,     1,     2,     1,     2,    12,    10,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     7,
       5,     5,     4,     7,     7,     7,     4,     7,     8,    11,
       4,     6,     4,     5,     9,     3,     3,     4,     3,     2,
       2,     4,     4,     5,     1,     3,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     2,     2,     5,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,     1
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
  case 2: /* code: functions  */
#line 57 "parser.y"
                {(yyval.nodePtr) = mknode("code", (yyvsp[0].nodePtr), NULL); visualize_ast((yyvsp[0].nodePtr), "", 1);}
#line 1557 "y.tab.c"
    break;

  case 3: /* functions: function  */
#line 59 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1563 "y.tab.c"
    break;

  case 4: /* functions: function functions  */
#line 60 "parser.y"
                             {(yyval.nodePtr) = mknode("functions", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1569 "y.tab.c"
    break;

  case 5: /* function: DEF MAIN '(' ')' ':' var BEGIN_TOKEN statements END  */
#line 63 "parser.y"
                                                              {(yyval.nodePtr) = mknode("FUNC", mknode("main", NULL, (yyvsp[-3].nodePtr)), mknode("body", (yyvsp[-1].nodePtr), NULL));}
#line 1575 "y.tab.c"
    break;

  case 6: /* function: DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END  */
#line 64 "parser.y"
                                                                                            {(yyval.nodePtr) = mknode("FUNC", mknode((yyvsp[-10].stringVal), (yyvsp[-8].nodePtr), mknode("ret", (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr))), mknode("body", (yyvsp[-1].nodePtr), NULL));}
#line 1581 "y.tab.c"
    break;

  case 7: /* function: DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END  */
#line 66 "parser.y"
          {(yyval.nodePtr) = mknode("FUNC", mknode((yyvsp[-8].stringVal), (yyvsp[-6].nodePtr), NULL), mknode("body", (yyvsp[-1].nodePtr), NULL));}
#line 1587 "y.tab.c"
    break;

  case 8: /* parameters: %empty  */
#line 69 "parser.y"
                        {(yyval.nodePtr) = NULL;}
#line 1593 "y.tab.c"
    break;

  case 9: /* parameters: parameter_list  */
#line 70 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1599 "y.tab.c"
    break;

  case 10: /* parameter_list: parameter  */
#line 73 "parser.y"
                          {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1605 "y.tab.c"
    break;

  case 11: /* parameter_list: parameter ';' parameter_list  */
#line 74 "parser.y"
                                       {(yyval.nodePtr) = mknode("PARAMS", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1611 "y.tab.c"
    break;

  case 12: /* parameter: PAR type ':' IDENTIFIER  */
#line 77 "parser.y"
                                   {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), (yyvsp[-2].nodePtr), NULL);}
#line 1617 "y.tab.c"
    break;

  case 13: /* var: %empty  */
#line 79 "parser.y"
                 {(yyval.nodePtr) = NULL;}
#line 1623 "y.tab.c"
    break;

  case 14: /* var: VAR declaration_list  */
#line 80 "parser.y"
                           {(yyval.nodePtr) = mknode("VAR", (yyvsp[0].nodePtr), NULL);}
#line 1629 "y.tab.c"
    break;

  case 15: /* declaration_list: declaration  */
#line 83 "parser.y"
                              {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1635 "y.tab.c"
    break;

  case 16: /* declaration_list: declaration declaration_list  */
#line 84 "parser.y"
                                   {(yyval.nodePtr) = mknode("decls", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1641 "y.tab.c"
    break;

  case 17: /* declaration: TYPE type ':' id_list ';'  */
#line 87 "parser.y"
                                       {(yyval.nodePtr) = mknode("DECL", (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr));}
#line 1647 "y.tab.c"
    break;

  case 18: /* type: BOOL  */
#line 90 "parser.y"
               { (yyval.nodePtr) = mknode("BOOL", NULL, NULL); }
#line 1653 "y.tab.c"
    break;

  case 19: /* type: CHAR  */
#line 91 "parser.y"
                 { (yyval.nodePtr) = mknode("CHAR", NULL, NULL); }
#line 1659 "y.tab.c"
    break;

  case 20: /* type: INT  */
#line 92 "parser.y"
                 { (yyval.nodePtr) = mknode("INT", NULL, NULL); }
#line 1665 "y.tab.c"
    break;

  case 21: /* type: REAL_TYPE  */
#line 93 "parser.y"
                 { (yyval.nodePtr) = mknode("REAL", NULL, NULL); }
#line 1671 "y.tab.c"
    break;

  case 22: /* type: STRING  */
#line 94 "parser.y"
                 { (yyval.nodePtr) = mknode("STRING", NULL, NULL); }
#line 1677 "y.tab.c"
    break;

  case 23: /* type: INT_PTR  */
#line 95 "parser.y"
                 { (yyval.nodePtr) = mknode("INT_PTR", NULL, NULL); }
#line 1683 "y.tab.c"
    break;

  case 24: /* type: CHAR_PTR  */
#line 96 "parser.y"
                 { (yyval.nodePtr) = mknode("CHAR_PTR", NULL, NULL); }
#line 1689 "y.tab.c"
    break;

  case 25: /* type: REAL_PTR  */
#line 97 "parser.y"
                 { (yyval.nodePtr) = mknode("REAL_PTR", NULL, NULL); }
#line 1695 "y.tab.c"
    break;

  case 26: /* id_list: IDENTIFIER  */
#line 100 "parser.y"
                    {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);}
#line 1701 "y.tab.c"
    break;

  case 27: /* id_list: IDENTIFIER ',' id_list  */
#line 101 "parser.y"
                             {(yyval.nodePtr) = mknode((yyvsp[-2].stringVal), NULL, (yyvsp[0].nodePtr));}
#line 1707 "y.tab.c"
    break;

  case 28: /* id_list: IDENTIFIER ':' expression  */
#line 102 "parser.y"
                                {(yyval.nodePtr) = mknode((yyvsp[-2].stringVal), (yyvsp[0].nodePtr), NULL);}
#line 1713 "y.tab.c"
    break;

  case 29: /* id_list: IDENTIFIER ':' expression ',' id_list  */
#line 103 "parser.y"
                                            {(yyval.nodePtr) = mknode((yyvsp[-4].stringVal), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1719 "y.tab.c"
    break;

  case 30: /* id_list: IDENTIFIER '[' INTEGER ']'  */
#line 104 "parser.y"
                                 {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-1].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-3].stringVal), mknode(int_str, NULL, NULL), NULL);
    }
#line 1729 "y.tab.c"
    break;

  case 31: /* id_list: IDENTIFIER '[' INTEGER ']' ',' id_list  */
#line 109 "parser.y"
                                             {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-3].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-5].stringVal), mknode(int_str, NULL, NULL), (yyvsp[0].nodePtr));
    }
#line 1739 "y.tab.c"
    break;

  case 32: /* id_list: IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL  */
#line 114 "parser.y"
                                                    {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-3].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-5].stringVal), mknode(int_str, NULL, NULL), mknode((yyvsp[0].stringVal), NULL, NULL));
    }
#line 1749 "y.tab.c"
    break;

  case 33: /* id_list: IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL ',' id_list  */
#line 119 "parser.y"
                                                                {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-5].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-7].stringVal), mknode(int_str, NULL, NULL), mknode((yyvsp[-2].stringVal), NULL, (yyvsp[0].nodePtr)));
    }
#line 1759 "y.tab.c"
    break;

  case 34: /* statements: statement  */
#line 126 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1765 "y.tab.c"
    break;

  case 35: /* statements: statement statements  */
#line 127 "parser.y"
                           {(yyval.nodePtr) = mknode("statements", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1771 "y.tab.c"
    break;

  case 36: /* statements: nested_function  */
#line 128 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1777 "y.tab.c"
    break;

  case 37: /* statements: nested_function statements  */
#line 129 "parser.y"
                                 {(yyval.nodePtr) = mknode("statements", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1783 "y.tab.c"
    break;

  case 38: /* nested_function: DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END  */
#line 135 "parser.y"
    {(yyval.nodePtr) = mknode("nested_func", mknode((yyvsp[-10].stringVal), (yyvsp[-8].nodePtr), mknode("ret", (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr))), mknode("body", (yyvsp[-1].nodePtr), NULL));}
#line 1789 "y.tab.c"
    break;

  case 39: /* nested_function: DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END  */
#line 137 "parser.y"
    {(yyval.nodePtr) = mknode("nested_func", mknode((yyvsp[-8].stringVal), (yyvsp[-6].nodePtr), NULL), mknode("body", (yyvsp[-1].nodePtr), NULL));}
#line 1795 "y.tab.c"
    break;

  case 40: /* statement: assignment_statement  */
#line 140 "parser.y"
                                {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1801 "y.tab.c"
    break;

  case 41: /* statement: if_statement  */
#line 141 "parser.y"
                   {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1807 "y.tab.c"
    break;

  case 42: /* statement: while_statement  */
#line 142 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1813 "y.tab.c"
    break;

  case 43: /* statement: for_statement  */
#line 143 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1819 "y.tab.c"
    break;

  case 44: /* statement: do_while_statement  */
#line 144 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1825 "y.tab.c"
    break;

  case 45: /* statement: block_statement  */
#line 145 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1831 "y.tab.c"
    break;

  case 46: /* statement: return_statement  */
#line 146 "parser.y"
                       {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1837 "y.tab.c"
    break;

  case 47: /* statement: function_call_statement  */
#line 147 "parser.y"
                              {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1843 "y.tab.c"
    break;

  case 48: /* assignment_statement: IDENTIFIER ASSIGN expression ';'  */
#line 151 "parser.y"
                                     {(yyval.nodePtr) = mknode("assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 1849 "y.tab.c"
    break;

  case 49: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN CHAR_LITERAL ';'  */
#line 152 "parser.y"
                                                            {
        char char_str[2];
        char_str[0] = (yyvsp[-1].charVal);
        char_str[1] = '\0';
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode(char_str, NULL, NULL));
    }
#line 1860 "y.tab.c"
    break;

  case 50: /* assignment_statement: MULT IDENTIFIER ASSIGN expression ';'  */
#line 158 "parser.y"
                                            {(yyval.nodePtr) = mknode("pointer_assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 1866 "y.tab.c"
    break;

  case 51: /* assignment_statement: IDENTIFIER ASSIGN AMPERSAND IDENTIFIER ';'  */
#line 159 "parser.y"
                                                 {(yyval.nodePtr) = mknode("ref_assign", mknode((yyvsp[-4].stringVal), NULL, NULL), mknode((yyvsp[-1].stringVal), NULL, NULL));}
#line 1872 "y.tab.c"
    break;

  case 52: /* assignment_statement: IDENTIFIER ASSIGN NULL_TOKEN ';'  */
#line 160 "parser.y"
                                       {(yyval.nodePtr) = mknode("null_assign", mknode((yyvsp[-3].stringVal), NULL, NULL), mknode("null", NULL, NULL));}
#line 1878 "y.tab.c"
    break;

  case 53: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN INTEGER ';'  */
#line 161 "parser.y"
                                                       {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-1].intVal));
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode(int_str, NULL, NULL));
    }
#line 1888 "y.tab.c"
    break;

  case 54: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN STRING_LITERAL ';'  */
#line 166 "parser.y"
                                                              {
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode((yyvsp[-1].stringVal), NULL, NULL));
    }
#line 1896 "y.tab.c"
    break;

  case 55: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN expression ';'  */
#line 169 "parser.y"
                                                          {
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), (yyvsp[-1].nodePtr));
    }
#line 1904 "y.tab.c"
    break;

  case 56: /* if_statement: IF expression ':' block_statement  */
#line 175 "parser.y"
                                      {(yyval.nodePtr) = mknode("if", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1910 "y.tab.c"
    break;

  case 57: /* if_statement: IF expression ':' block_statement ELSE ':' block_statement  */
#line 176 "parser.y"
                                                                 {(yyval.nodePtr) = mknode("if-else", (yyvsp[-5].nodePtr), mknode("then", (yyvsp[-3].nodePtr), mknode("else", (yyvsp[0].nodePtr), NULL)));}
#line 1916 "y.tab.c"
    break;

  case 58: /* if_statement: IF expression ':' block_statement ELIF expression ':' block_statement  */
#line 177 "parser.y"
                                                                            {(yyval.nodePtr) = mknode("if-elif", (yyvsp[-6].nodePtr), mknode("then", (yyvsp[-4].nodePtr), mknode("elif-cond", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr))));}
#line 1922 "y.tab.c"
    break;

  case 59: /* if_statement: IF expression ':' block_statement ELIF expression ':' block_statement ELSE ':' block_statement  */
#line 178 "parser.y"
                                                                                                     {(yyval.nodePtr) = mknode("if-elif-else", (yyvsp[-9].nodePtr), mknode("then", (yyvsp[-7].nodePtr), mknode("elif-cond", (yyvsp[-5].nodePtr), mknode("elif-then", (yyvsp[-3].nodePtr), mknode("else", (yyvsp[0].nodePtr), NULL)))));}
#line 1928 "y.tab.c"
    break;

  case 60: /* while_statement: WHILE expression ':' block_statement  */
#line 182 "parser.y"
                                         {(yyval.nodePtr) = mknode("while", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1934 "y.tab.c"
    break;

  case 61: /* do_while_statement: DO ':' block_statement WHILE expression ';'  */
#line 186 "parser.y"
                                                {(yyval.nodePtr) = mknode("do-while", (yyvsp[-3].nodePtr), mknode("cond", (yyvsp[-1].nodePtr), NULL));}
#line 1940 "y.tab.c"
    break;

  case 62: /* for_statement: FOR for_header ':' block_statement  */
#line 190 "parser.y"
                                       {(yyval.nodePtr) = mknode("for", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1946 "y.tab.c"
    break;

  case 63: /* for_statement: FOR for_header ':' var block_statement  */
#line 191 "parser.y"
                                             {(yyval.nodePtr) = mknode("for", (yyvsp[-3].nodePtr), mknode("block", (yyvsp[0].nodePtr), (yyvsp[-1].nodePtr)));}
#line 1952 "y.tab.c"
    break;

  case 64: /* for_header: '(' IDENTIFIER ASSIGN expression ';' expression ';' update_exp ')'  */
#line 196 "parser.y"
    {(yyval.nodePtr) = mknode("for-header", mknode("init", mknode((yyvsp[-7].stringVal), NULL, NULL), (yyvsp[-5].nodePtr)), 
                             mknode("loop", (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr)));}
#line 1959 "y.tab.c"
    break;

  case 65: /* update_exp: IDENTIFIER ASSIGN expression  */
#line 201 "parser.y"
                                 {(yyval.nodePtr) = mknode("update", mknode((yyvsp[-2].stringVal), NULL, NULL), (yyvsp[0].nodePtr));}
#line 1965 "y.tab.c"
    break;

  case 66: /* block_statement: BEGIN_TOKEN statements END  */
#line 213 "parser.y"
                               {(yyval.nodePtr) = mknode("block", (yyvsp[-1].nodePtr), NULL);}
#line 1971 "y.tab.c"
    break;

  case 67: /* block_statement: var BEGIN_TOKEN statements END  */
#line 214 "parser.y"
                                     {(yyval.nodePtr) = mknode("block", (yyvsp[-1].nodePtr), (yyvsp[-3].nodePtr));}
#line 1977 "y.tab.c"
    break;

  case 68: /* return_statement: RETURN expression ';'  */
#line 218 "parser.y"
                          {(yyval.nodePtr) = mknode("return_val", (yyvsp[-1].nodePtr), NULL);}
#line 1983 "y.tab.c"
    break;

  case 69: /* return_statement: RETURN ';'  */
#line 219 "parser.y"
                 {(yyval.nodePtr) = mknode("return_void", NULL, NULL);}
#line 1989 "y.tab.c"
    break;

  case 70: /* function_call_statement: function_call ';'  */
#line 223 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[-1].nodePtr);}
#line 1995 "y.tab.c"
    break;

  case 71: /* function_call_statement: IDENTIFIER ASSIGN function_call ';'  */
#line 224 "parser.y"
                                          {(yyval.nodePtr) = mknode("assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2001 "y.tab.c"
    break;

  case 72: /* function_call: CALL IDENTIFIER '(' ')'  */
#line 228 "parser.y"
                            {(yyval.nodePtr) = mknode("call", mknode((yyvsp[-2].stringVal), NULL, NULL), NULL);}
#line 2007 "y.tab.c"
    break;

  case 73: /* function_call: CALL IDENTIFIER '(' expr_list ')'  */
#line 229 "parser.y"
                                        {(yyval.nodePtr) = mknode("call", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2013 "y.tab.c"
    break;

  case 74: /* expr_list: expression  */
#line 233 "parser.y"
               {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2019 "y.tab.c"
    break;

  case 75: /* expr_list: expression ',' expr_list  */
#line 234 "parser.y"
                               {(yyval.nodePtr) = mknode("expr_list", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2025 "y.tab.c"
    break;

  case 76: /* expression: INTEGER  */
#line 238 "parser.y"
            {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[0].intVal));
        (yyval.nodePtr) = mknode(int_str, NULL, NULL);
    }
#line 2035 "y.tab.c"
    break;

  case 77: /* expression: REAL  */
#line 243 "parser.y"
           {
        char real_str[30];
        sprintf(real_str, "%f", (yyvsp[0].realVal));
        (yyval.nodePtr) = mknode(real_str, NULL, NULL);
    }
#line 2045 "y.tab.c"
    break;

  case 78: /* expression: STRING_LITERAL  */
#line 248 "parser.y"
                     {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);}
#line 2051 "y.tab.c"
    break;

  case 79: /* expression: CHAR_LITERAL  */
#line 249 "parser.y"
                   {
        char char_str[2];
        char_str[0] = (yyvsp[0].charVal);
        char_str[1] = '\0';
        (yyval.nodePtr) = mknode(char_str, NULL, NULL);
    }
#line 2062 "y.tab.c"
    break;

  case 80: /* expression: IDENTIFIER  */
#line 255 "parser.y"
                 {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);}
#line 2068 "y.tab.c"
    break;

  case 81: /* expression: expression PLUS expression  */
#line 256 "parser.y"
                                 {(yyval.nodePtr) = mknode("+", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2074 "y.tab.c"
    break;

  case 82: /* expression: expression MINUS expression  */
#line 257 "parser.y"
                                  {(yyval.nodePtr) = mknode("-", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2080 "y.tab.c"
    break;

  case 83: /* expression: expression MULT expression  */
#line 258 "parser.y"
                                 {(yyval.nodePtr) = mknode("*", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2086 "y.tab.c"
    break;

  case 84: /* expression: expression DIV expression  */
#line 259 "parser.y"
                                {(yyval.nodePtr) = mknode("/", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2092 "y.tab.c"
    break;

  case 85: /* expression: expression MODULO expression  */
#line 260 "parser.y"
                                   {(yyval.nodePtr) = mknode("%", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2098 "y.tab.c"
    break;

  case 86: /* expression: MINUS expression  */
#line 261 "parser.y"
                       {(yyval.nodePtr) = mknode("unary-", (yyvsp[0].nodePtr), NULL);}
#line 2104 "y.tab.c"
    break;

  case 87: /* expression: AMPERSAND IDENTIFIER  */
#line 262 "parser.y"
                           {(yyval.nodePtr) = mknode("&", mknode((yyvsp[0].stringVal), NULL, NULL), NULL);}
#line 2110 "y.tab.c"
    break;

  case 88: /* expression: AMPERSAND IDENTIFIER '[' expression ']'  */
#line 263 "parser.y"
                                              {(yyval.nodePtr) = mknode("&", mknode("index", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr)), NULL);}
#line 2116 "y.tab.c"
    break;

  case 89: /* expression: MULT IDENTIFIER  */
#line 264 "parser.y"
                      {(yyval.nodePtr) = mknode("deref", mknode((yyvsp[0].stringVal), NULL, NULL), NULL);}
#line 2122 "y.tab.c"
    break;

  case 90: /* expression: MULT expression  */
#line 265 "parser.y"
                      {(yyval.nodePtr) = mknode("*", (yyvsp[0].nodePtr), NULL);}
#line 2128 "y.tab.c"
    break;

  case 91: /* expression: '(' expression ')'  */
#line 266 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[-1].nodePtr);}
#line 2134 "y.tab.c"
    break;

  case 92: /* expression: expression EQ expression  */
#line 267 "parser.y"
                               {(yyval.nodePtr) = mknode("==", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2140 "y.tab.c"
    break;

  case 93: /* expression: expression NE expression  */
#line 268 "parser.y"
                               {(yyval.nodePtr) = mknode("!=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2146 "y.tab.c"
    break;

  case 94: /* expression: expression GE expression  */
#line 269 "parser.y"
                               {(yyval.nodePtr) = mknode(">=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2152 "y.tab.c"
    break;

  case 95: /* expression: expression LE expression  */
#line 270 "parser.y"
                               {(yyval.nodePtr) = mknode("<=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2158 "y.tab.c"
    break;

  case 96: /* expression: expression GT expression  */
#line 271 "parser.y"
                               {(yyval.nodePtr) = mknode(">", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2164 "y.tab.c"
    break;

  case 97: /* expression: expression LT expression  */
#line 272 "parser.y"
                               {(yyval.nodePtr) = mknode("<", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2170 "y.tab.c"
    break;

  case 98: /* expression: expression AND expression  */
#line 273 "parser.y"
                                {(yyval.nodePtr) = mknode("and", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2176 "y.tab.c"
    break;

  case 99: /* expression: expression OR expression  */
#line 274 "parser.y"
                               {(yyval.nodePtr) = mknode("or", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2182 "y.tab.c"
    break;

  case 100: /* expression: IDENTIFIER '[' expression ']'  */
#line 275 "parser.y"
                                    {(yyval.nodePtr) = mknode("index", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2188 "y.tab.c"
    break;

  case 101: /* expression: function_call  */
#line 276 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2194 "y.tab.c"
    break;


#line 2198 "y.tab.c"

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

#line 279 "parser.y"


int main()
{
    yyparse();
    return 0;
}

node* mknode(char* token, node* left, node* right)
{
    node* newNode = (node*)malloc(sizeof(node));
    if (!newNode) {
        fprintf(stderr, "Memory allocation failed for node\n");
        exit(1);
    }
    
    char* newStr = (char*)malloc(strlen(token) + 1);
    if (!newStr) {
        fprintf(stderr, "Memory allocation failed for token\n");
        free(newNode);
        exit(1);
    }
    
    strcpy(newStr, token);
    newNode->left = left;
    newNode->right = right;
    newNode->token = newStr;
    return newNode;
}

void printTree(node* tree, int level)
{
    if (!tree) return;
    
    for (int i = 0; i < level; i++) {
        printf("  "); // Two spaces per level for indentation
    }
    
    if (tree->token) {
        printf("%s\n", tree->token);
    }
    
    if (tree->left) {
        printTree(tree->left, level + 1);
    }
    
    if (tree->right) {
        printTree(tree->right, level + 1);
    }
}

int yyerror(const char* s)
{
    fprintf(stderr, "Error: %s at line %d near token '%s'\n", s, yylineno, yytext);
    return 0;
}

void visualize_ast(node* root, const char* branch_prefix, int is_left_branch) {
    if (!root) return;

    // Print current node with appropriate branch connector
    printf("%s", branch_prefix);
    printf(is_left_branch ? "├── " : "└── ");
    printf("%s\n", root->token);

    // Create new prefix for child nodes
    char child_prefix[1024];
    snprintf(child_prefix, sizeof(child_prefix), "%s%s", 
             branch_prefix, 
             is_left_branch ? "│   " : "    ");

    // Handle different child node cases
    if (root->left && root->right) {
        // Both children exist - left child is not last
        visualize_ast(root->left, child_prefix, 1);
        visualize_ast(root->right, child_prefix, 0);
    } else if (root->left) {
        // Only left child exists
        visualize_ast(root->left, child_prefix, 0);
    } else if (root->right) {
        // Only right child exists
        visualize_ast(root->right, child_prefix, 0);
    }
}
