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

    #define MAX_PARAMS 10

    int yylex();
    int yyerror(const char* s);
    extern int yylineno;
    extern char* yytext;
    
    typedef enum {
        TYPE_INT, TYPE_CHAR, TYPE_REAL, TYPE_STRING, TYPE_BOOL,
        TYPE_INT_PTR, TYPE_CHAR_PTR, TYPE_REAL_PTR, TYPE_INVALID
    } VarType;

    typedef struct Symbol {
        char* name;
        VarType type;
        int is_function;
        VarType return_type;
        VarType param_types[MAX_PARAMS];
        int param_count;
        int scope_level;
        struct Symbol* next;
    } Symbol;

    typedef struct node
    {
        char* token;
        struct node* left;
        struct node* right;
    } node;
    node* mknode(char* token, node* left, node* right);
    void printTree(node* tree, int level);
    void visualize_ast(node* root, const char* branch_prefix, int is_left_branch);
    VarType string_to_type(const char* str);
    void insert_symbol(char* name, VarType type, int is_function, VarType return_type, VarType* param_types, int param_count);
    void enter_scope();
    void exit_scope();

    node* root = NULL;
    Symbol* symbol_table = NULL;
    int current_scope_level = 0;
    int main_count = 0;

#line 119 "y.tab.c"

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
#line 49 "parser.y"

    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
    struct node* nodePtr;
    VarType typeVal;
    VarType paramList[MAX_PARAMS];

#line 279 "y.tab.c"

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
  YYSYMBOL_scope_entry = 80,               /* scope_entry  */
  YYSYMBOL_scoped_block = 81,              /* scoped_block  */
  YYSYMBOL_block_statement = 82,           /* block_statement  */
  YYSYMBOL_return_statement = 83,          /* return_statement  */
  YYSYMBOL_function_call_statement = 84,   /* function_call_statement  */
  YYSYMBOL_function_call = 85,             /* function_call  */
  YYSYMBOL_expr_list = 86,                 /* expr_list  */
  YYSYMBOL_expression = 87                 /* expression  */
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
#define YYLAST   793

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  58
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  105
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  243

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
       0,    89,    89,    91,    92,    95,   109,   128,   148,   149,
     152,   153,   156,   158,   159,   162,   163,   166,   179,   180,
     181,   182,   183,   184,   185,   186,   189,   190,   191,   192,
     193,   198,   203,   208,   215,   216,   217,   218,   223,   236,
     251,   252,   253,   254,   255,   256,   257,   258,   262,   263,
     269,   270,   271,   272,   277,   280,   286,   287,   288,   289,
     293,   297,   301,   302,   306,   312,   323,   326,   330,   334,
     338,   345,   349,   350,   354,   355,   359,   360,   364,   365,
     369,   374,   379,   380,   386,   387,   388,   389,   390,   391,
     392,   393,   394,   395,   396,   397,   398,   399,   400,   401,
     402,   403,   404,   405,   406,   407
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
  "update_exp", "scope_entry", "scoped_block", "block_statement",
  "return_statement", "function_call_statement", "function_call",
  "expr_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-134)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-37)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -20,    -1,    14,  -134,   -20,   -22,   -19,  -134,  -134,    20,
     -11,    11,    12,  -134,    19,    13,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,    23,    31,    20,    47,    78,    34,
    -134,    70,    58,  -134,    11,    60,    11,  -134,    70,   450,
      47,   450,    38,  -134,   -29,   219,   219,    39,    48,    43,
      90,    96,    98,    76,   117,   402,  -134,  -134,  -134,  -134,
    -134,    17,  -134,  -134,  -134,  -134,    53,    79,    93,   102,
     214,   219,  -134,  -134,  -134,  -134,    71,   219,   224,   119,
     219,  -134,   633,   658,   121,    80,  -134,   453,  -134,    81,
      83,    87,  -134,  -134,  -134,   418,   111,  -134,   450,  -134,
      16,    89,    91,   134,   106,   483,   250,   219,    -7,    71,
    -134,    94,   708,   219,   219,   219,   219,   219,   219,   219,
     219,   219,   219,   219,   219,   219,  -134,  -134,   122,    47,
    -134,   140,    20,   164,   219,  -134,   135,   434,   142,   219,
     102,   170,  -134,  -134,   -26,  -134,  -134,   132,   292,   219,
    -134,  -134,   644,   747,   113,   113,    -9,    -9,    -9,    -9,
      -7,    -7,  -134,  -134,    63,  -134,   219,  -134,  -134,   219,
     123,  -134,   124,   342,   508,  -134,  -134,   147,  -134,   367,
    -134,   125,  -134,   273,  -134,   317,   219,   128,   533,  -134,
     558,   131,  -134,   219,  -134,  -134,   102,    26,   136,   137,
     138,   583,  -134,   683,  -134,   219,  -134,    37,  -134,  -134,
     172,   102,  -134,  -134,  -134,  -134,  -134,  -134,   608,    11,
     156,   139,  -134,   166,   186,    47,   450,   102,   146,   153,
     149,   174,   175,  -134,  -134,   219,  -134,   450,  -134,  -134,
     733,   176,  -134
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     0,     1,     4,     8,
       0,     0,     0,     9,    10,     0,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,    13,     0,    13,
      11,     0,     0,    12,     0,     0,     0,    14,    15,    66,
      13,    66,     0,    16,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    66,    66,    40,    41,    42,    44,
      43,     0,    71,    45,    46,    47,     0,     0,     0,     0,
       0,     0,    80,    81,    83,    82,    84,     0,     0,     0,
       0,   105,     0,     0,     0,     0,    73,     0,    66,     0,
       0,     0,     5,    37,    35,    66,     0,    74,    66,     7,
      26,     0,     0,     0,   105,     0,     0,     0,    90,    84,
      94,    91,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    66,    66,     0,    13,
      72,     0,     8,     0,     0,    67,     0,    66,     0,     0,
       0,     0,    17,    52,    91,    75,    48,     0,     0,     0,
      95,    89,   102,   103,    96,    97,    98,    99,   100,   101,
      85,    86,    87,    88,    56,    60,     0,    66,    62,     0,
       0,    76,     0,    78,     0,    68,    69,     0,     6,    28,
      27,     0,    51,     0,   104,     0,     0,     0,     0,    63,
       0,     0,    77,     0,    50,    70,     0,    30,    80,    83,
      82,     0,    92,     0,    66,     0,    61,    13,    79,    29,
       0,     0,    53,    49,    54,    55,    66,    57,     0,     0,
       0,    32,    31,    58,     0,    13,    66,     0,     0,     0,
       0,     0,     0,    33,    66,     0,    64,    66,    39,    59,
      65,     0,    38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,   200,  -134,    75,   184,  -134,   -28,   195,  -134,
     -31,  -133,   -37,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,   -79,  -134,  -134,   -39,    21,    -3
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    12,    13,    14,    32,    37,    38,
      24,   101,    53,    54,    55,    56,    57,    58,    59,    60,
      85,   230,    61,    62,    63,    64,    65,    81,   172,   173
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    35,    66,    40,    68,    42,     5,   180,   113,   131,
     113,     1,    67,    70,     7,    66,    66,    93,    94,    16,
      17,    18,    19,    20,    21,    22,    23,    71,   182,     9,
     149,   104,    10,    96,   122,   123,   124,   125,   124,   125,
      31,    15,    82,    83,    11,    87,    95,   164,   165,     6,
     168,    72,    73,    74,    75,    76,    66,    31,   136,    66,
      31,   138,    34,   209,    25,   219,    27,   105,   106,   139,
      31,   140,   141,    26,   108,   110,    28,   112,   222,   210,
      51,   211,   186,   187,    29,    33,    36,    39,   189,    41,
      84,    69,    77,    78,   233,    79,    88,    89,    66,    80,
     177,   167,    86,    90,   148,    91,    92,    97,    98,   100,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,    99,    44,   217,   111,   107,   128,   134,
     113,   174,   132,   129,   133,    45,   179,   223,    46,    47,
     137,   144,    48,   142,    49,   143,   185,   -36,    50,    51,
     149,   118,   119,   120,   121,   239,   122,   123,   124,   125,
     145,   169,    52,   188,   166,   175,   190,    72,    73,    74,
      75,    76,   178,   181,   183,   191,   192,   195,   221,   220,
     201,   204,   197,   203,   207,   226,   228,    66,   225,   232,
     212,   213,   214,   229,   227,   235,    51,   231,    66,   234,
     241,   236,   218,   237,     8,   238,   242,   170,    77,    78,
      30,    79,     0,     0,   208,    80,   171,    72,    73,    74,
      75,    76,    72,    73,    74,    75,    76,    72,    73,    74,
      75,   109,   240,    43,     0,     0,     0,     0,     0,     0,
     102,     0,     0,     0,     0,     0,    51,     0,     0,     0,
       0,    51,     0,     0,     0,     0,    51,     0,    77,    78,
       0,   103,     0,    77,    78,    80,    79,   113,    77,    78,
      80,    79,     0,     0,     0,    80,   198,    73,   199,   200,
      76,     0,     0,   114,     0,   115,   116,   117,   118,   119,
     120,   121,     0,   122,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,   147,     0,   113,
       0,     0,     0,     0,     0,     0,     0,    77,    78,     0,
      79,     0,     0,     0,    80,   114,     0,   115,   116,   117,
     118,   119,   120,   121,   113,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   184,
     114,     0,   115,   116,   117,   118,   119,   120,   121,   113,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   202,   114,     0,   115,   116,   117,
     118,   119,   120,   121,   113,   122,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,     0,   193,     0,     0,
     114,     0,   115,   116,   117,   118,   119,   120,   121,    44,
     122,   123,   124,   125,     0,     0,     0,     0,     0,     0,
      45,     0,   196,    46,    47,    44,     0,    48,     0,    49,
       0,     0,   -34,    50,    51,     0,    45,     0,     0,    46,
      47,    44,     0,    48,     0,    49,     0,    52,   135,    50,
      51,     0,    45,     0,     0,    46,    47,    44,     0,    48,
       0,    49,     0,    52,   176,    50,    51,     0,    45,     0,
     113,    46,    47,     0,     0,    48,     0,    49,     0,    52,
       0,    50,    51,     0,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,    52,   122,   123,   124,   125,
     113,     0,     0,     0,     0,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   113,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,   146,     0,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
     113,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,     0,   194,     0,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   113,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,   205,     0,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
     113,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,     0,   206,     0,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   113,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,   215,     0,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
     113,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,   113,   224,     0,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   113,   122,   123,   124,   125,
     116,   117,   118,   119,   120,   121,   126,   122,   123,   124,
     125,   114,     0,   115,   116,   117,   118,   119,   120,   121,
     113,   122,   123,   124,   125,     0,     0,     0,     0,     0,
       0,   127,     0,     0,     0,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,   113,   122,   123,   124,   125,
       0,     0,     0,     0,     0,     0,   216,     0,     0,     0,
       0,   114,     0,   115,   116,   117,   118,   119,   120,   121,
     113,   122,   123,   124,   125,     0,     0,     0,     0,     0,
     150,     0,     0,     0,   113,     0,   114,     0,   115,   116,
     117,   118,   119,   120,   121,     0,   122,   123,   124,   125,
     114,     0,     0,   116,   117,   118,   119,   120,   121,     0,
     122,   123,   124,   125
};

static const yytype_int16 yycheck[] =
{
      39,    29,    41,    34,    41,    36,     7,   140,    17,    88,
      17,    31,    40,    42,     0,    54,    55,    54,    55,     8,
       9,    10,    11,    12,    13,    14,    15,    56,    54,    51,
      56,    70,    51,    61,    43,    44,    45,    46,    45,    46,
      23,    52,    45,    46,    24,    48,    29,   126,   127,    50,
     129,     3,     4,     5,     6,     7,    95,    23,    95,    98,
      23,    98,    28,   196,    52,    28,    53,    70,    71,    53,
      23,    55,    56,    54,    77,    78,    53,    80,   211,    53,
      32,    55,    19,    20,    53,     7,    16,    29,   167,    29,
      51,    53,    44,    45,   227,    47,    53,     7,   137,    51,
     137,   129,    54,     7,   107,     7,    30,    54,    29,     7,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,    30,     7,   204,     7,    56,     7,    42,
      17,   134,    51,    53,    51,    18,   139,   216,    21,    22,
      29,     7,    25,    54,    27,    54,   149,    30,    31,    32,
      56,    38,    39,    40,    41,   234,    43,    44,    45,    46,
      54,    21,    45,   166,    42,    30,   169,     3,     4,     5,
       6,     7,    30,     3,    42,    52,    52,    30,     6,   207,
     183,    53,    57,   186,    53,    29,    20,   226,   219,   226,
      54,    54,    54,     7,    55,    42,    32,   225,   237,    53,
     237,    52,   205,    29,     4,    30,    30,   132,    44,    45,
      26,    47,    -1,    -1,   193,    51,    52,     3,     4,     5,
       6,     7,     3,     4,     5,     6,     7,     3,     4,     5,
       6,     7,   235,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    -1,    32,    -1,    44,    45,
      -1,    47,    -1,    44,    45,    51,    47,    17,    44,    45,
      51,    47,    -1,    -1,    -1,    51,     3,     4,     5,     6,
       7,    -1,    -1,    33,    -1,    35,    36,    37,    38,    39,
      40,    41,    -1,    43,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    57,    -1,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      47,    -1,    -1,    -1,    51,    33,    -1,    35,    36,    37,
      38,    39,    40,    41,    17,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,    17,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    57,    33,    -1,    35,    36,    37,
      38,    39,    40,    41,    17,    43,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,
      33,    -1,    35,    36,    37,    38,    39,    40,    41,     7,
      43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      18,    -1,    55,    21,    22,     7,    -1,    25,    -1,    27,
      -1,    -1,    30,    31,    32,    -1,    18,    -1,    -1,    21,
      22,     7,    -1,    25,    -1,    27,    -1,    45,    30,    31,
      32,    -1,    18,    -1,    -1,    21,    22,     7,    -1,    25,
      -1,    27,    -1,    45,    30,    31,    32,    -1,    18,    -1,
      17,    21,    22,    -1,    -1,    25,    -1,    27,    -1,    45,
      -1,    31,    32,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    45,    43,    44,    45,    46,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    17,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      17,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    17,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      17,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    17,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      17,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    54,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    17,    43,    44,    45,    46,
      36,    37,    38,    39,    40,    41,    53,    43,    44,    45,
      46,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      17,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    17,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      17,    43,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    17,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    -1,    43,    44,    45,    46,
      33,    -1,    -1,    36,    37,    38,    39,    40,    41,    -1,
      43,    44,    45,    46
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
      31,    32,    45,    70,    71,    72,    73,    74,    75,    76,
      77,    80,    81,    82,    83,    84,    85,    65,    70,    53,
      42,    56,     3,     4,     5,     6,     7,    44,    45,    47,
      51,    85,    87,    87,    51,    78,    54,    87,    53,     7,
       7,     7,    30,    70,    70,    29,    65,    54,    29,    30,
       7,    69,    26,    47,    85,    87,    87,    56,    87,     7,
      87,     7,    87,    17,    33,    35,    36,    37,    38,    39,
      40,    41,    43,    44,    45,    46,    53,    53,     7,    53,
      54,    82,    51,    51,    42,    30,    70,    29,    70,    53,
      55,    56,    54,    54,     7,    54,    54,    57,    87,    56,
      52,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    82,    82,    42,    65,    82,    21,
      62,    52,    86,    87,    87,    30,    30,    70,    30,    87,
      69,     3,    54,    42,    57,    87,    19,    20,    87,    82,
      87,    52,    52,    55,    54,    30,    55,    57,     3,     5,
       6,    87,    57,    87,    53,    54,    54,    53,    86,    69,
      53,    55,    54,    54,    54,    54,    53,    82,    87,    28,
      65,     6,    69,    82,    54,    68,    29,    55,    20,     7,
      79,    65,    70,    69,    53,    42,    52,    29,    30,    82,
      87,    70,    30
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
      75,    76,    77,    77,    78,    79,    80,    81,    81,    81,
      81,    82,    83,    83,    84,    84,    85,    85,    86,    86,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    87
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
       4,     6,     4,     5,     9,     3,     0,     3,     4,     4,
       5,     1,     3,     2,     2,     4,     4,     5,     1,     3,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       2,     2,     5,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     1
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
#line 89 "parser.y"
                {root = mknode("code", (yyvsp[0].nodePtr), NULL); (yyval.nodePtr) = root;}
#line 1613 "y.tab.c"
    break;

  case 3: /* functions: function  */
#line 91 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1619 "y.tab.c"
    break;

  case 4: /* functions: function functions  */
#line 92 "parser.y"
                             {(yyval.nodePtr) = mknode("functions", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1625 "y.tab.c"
    break;

  case 5: /* function: DEF MAIN '(' ')' ':' var BEGIN_TOKEN statements END  */
#line 95 "parser.y"
                                                              {
            node* stmt = (yyvsp[-1].nodePtr);
            while (stmt) 
            {
                if (strcmp(stmt->token, "return_val") == 0) 
                {
                    yyerror("Semantic Error: _main_ must not contain return statements.");
                    YYERROR;
                }
                stmt = stmt->right;
            }
            insert_symbol("_main_", TYPE_INVALID, 1, TYPE_INVALID, NULL, 0); 
            (yyval.nodePtr) = mknode("FUNC", mknode("main", NULL, (yyvsp[-3].nodePtr)), mknode("body", (yyvsp[-1].nodePtr), NULL));
        }
#line 1644 "y.tab.c"
    break;

  case 6: /* function: DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END  */
#line 109 "parser.y"
                                                                                            {
            // Check if last statement is a return
            node* last_stmt = (yyvsp[-1].nodePtr);
            while (last_stmt && last_stmt->right) {
                last_stmt = last_stmt->right;
            }
            if (!last_stmt || strcmp(last_stmt->token, "return_val") != 0) {
                yyerror("Error: function with RETURNS must end with a return statement");
                YYERROR;
            }
            if (strcmp((yyvsp[-10].stringVal), "_main_") == 0) 
            {
                yyerror("Semantic Error: _main_ must not return a value.");
                YYERROR;
            }
            VarType ret_type = string_to_type((yyvsp[-4].nodePtr)->token);
            insert_symbol((yyvsp[-10].stringVal), TYPE_INVALID, 1, ret_type, NULL, 0);
            (yyval.nodePtr) = mknode("FUNC", mknode((yyvsp[-10].stringVal), (yyvsp[-8].nodePtr), mknode("ret", (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr))), mknode("body", (yyvsp[-1].nodePtr), NULL));
        }
#line 1668 "y.tab.c"
    break;

  case 7: /* function: DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END  */
#line 128 "parser.y"
                                                                               {
            // Check if last statement is a return
            node* last_stmt = (yyvsp[-1].nodePtr);
            while (last_stmt && last_stmt->right) {
                last_stmt = last_stmt->right;
            }
            if (last_stmt && strcmp(last_stmt->token, "return_val") == 0) {
                yyerror("Error: function without RETURNS must not have a return statement");
                YYERROR;
            }
            if (strcmp((yyvsp[-8].stringVal), "_main_") == 0 && (yyvsp[-6].nodePtr) != NULL) 
            {
                yyerror("Semantic Error: _main_ must not have parameters.");
                YYERROR;
            }
            insert_symbol((yyvsp[-8].stringVal), TYPE_INVALID, 1, TYPE_INVALID, NULL, 0);
            (yyval.nodePtr) = mknode("FUNC", mknode((yyvsp[-8].stringVal), (yyvsp[-6].nodePtr), NULL), mknode("body", (yyvsp[-1].nodePtr), NULL));
        }
#line 1691 "y.tab.c"
    break;

  case 8: /* parameters: %empty  */
#line 148 "parser.y"
                        {(yyval.nodePtr) = NULL;}
#line 1697 "y.tab.c"
    break;

  case 9: /* parameters: parameter_list  */
#line 149 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1703 "y.tab.c"
    break;

  case 10: /* parameter_list: parameter  */
#line 152 "parser.y"
                          {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1709 "y.tab.c"
    break;

  case 11: /* parameter_list: parameter ';' parameter_list  */
#line 153 "parser.y"
                                       {(yyval.nodePtr) = mknode("PARAMS", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1715 "y.tab.c"
    break;

  case 12: /* parameter: PAR type ':' IDENTIFIER  */
#line 156 "parser.y"
                                   {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), (yyvsp[-2].nodePtr), NULL);}
#line 1721 "y.tab.c"
    break;

  case 13: /* var: %empty  */
#line 158 "parser.y"
                 {(yyval.nodePtr) = NULL;}
#line 1727 "y.tab.c"
    break;

  case 14: /* var: VAR declaration_list  */
#line 159 "parser.y"
                           {(yyval.nodePtr) = mknode("VAR", (yyvsp[0].nodePtr), NULL);}
#line 1733 "y.tab.c"
    break;

  case 15: /* declaration_list: declaration  */
#line 162 "parser.y"
                              {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1739 "y.tab.c"
    break;

  case 16: /* declaration_list: declaration declaration_list  */
#line 163 "parser.y"
                                   {(yyval.nodePtr) = mknode("decls", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1745 "y.tab.c"
    break;

  case 17: /* declaration: TYPE type ':' id_list ';'  */
#line 166 "parser.y"
                                       {
        VarType vtype = string_to_type((yyvsp[-3].nodePtr)->token);
        node* ids = (yyvsp[-1].nodePtr);
        while (ids) 
        {
            char* var_name = ids->token;
            insert_symbol(var_name, vtype, 0, TYPE_INVALID, NULL, 0);
            ids = ids->right;
        }
        (yyval.nodePtr) = mknode("DECL", (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr));
    }
#line 1761 "y.tab.c"
    break;

  case 18: /* type: BOOL  */
#line 179 "parser.y"
               { (yyval.nodePtr) = mknode("BOOL", NULL, NULL); }
#line 1767 "y.tab.c"
    break;

  case 19: /* type: CHAR  */
#line 180 "parser.y"
                 { (yyval.nodePtr) = mknode("CHAR", NULL, NULL); }
#line 1773 "y.tab.c"
    break;

  case 20: /* type: INT  */
#line 181 "parser.y"
                 { (yyval.nodePtr) = mknode("INT", NULL, NULL); }
#line 1779 "y.tab.c"
    break;

  case 21: /* type: REAL_TYPE  */
#line 182 "parser.y"
                 { (yyval.nodePtr) = mknode("REAL", NULL, NULL); }
#line 1785 "y.tab.c"
    break;

  case 22: /* type: STRING  */
#line 183 "parser.y"
                 { (yyval.nodePtr) = mknode("STRING", NULL, NULL); }
#line 1791 "y.tab.c"
    break;

  case 23: /* type: INT_PTR  */
#line 184 "parser.y"
                 { (yyval.nodePtr) = mknode("INT_PTR", NULL, NULL); }
#line 1797 "y.tab.c"
    break;

  case 24: /* type: CHAR_PTR  */
#line 185 "parser.y"
                 { (yyval.nodePtr) = mknode("CHAR_PTR", NULL, NULL); }
#line 1803 "y.tab.c"
    break;

  case 25: /* type: REAL_PTR  */
#line 186 "parser.y"
                 { (yyval.nodePtr) = mknode("REAL_PTR", NULL, NULL); }
#line 1809 "y.tab.c"
    break;

  case 26: /* id_list: IDENTIFIER  */
#line 189 "parser.y"
                    {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);}
#line 1815 "y.tab.c"
    break;

  case 27: /* id_list: IDENTIFIER ',' id_list  */
#line 190 "parser.y"
                             {(yyval.nodePtr) = mknode((yyvsp[-2].stringVal), NULL, (yyvsp[0].nodePtr));}
#line 1821 "y.tab.c"
    break;

  case 28: /* id_list: IDENTIFIER ':' expression  */
#line 191 "parser.y"
                                {(yyval.nodePtr) = mknode((yyvsp[-2].stringVal), (yyvsp[0].nodePtr), NULL);}
#line 1827 "y.tab.c"
    break;

  case 29: /* id_list: IDENTIFIER ':' expression ',' id_list  */
#line 192 "parser.y"
                                            {(yyval.nodePtr) = mknode((yyvsp[-4].stringVal), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1833 "y.tab.c"
    break;

  case 30: /* id_list: IDENTIFIER '[' INTEGER ']'  */
#line 193 "parser.y"
                                 {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-1].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-3].stringVal), mknode(int_str, NULL, NULL), NULL);
    }
#line 1843 "y.tab.c"
    break;

  case 31: /* id_list: IDENTIFIER '[' INTEGER ']' ',' id_list  */
#line 198 "parser.y"
                                             {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-3].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-5].stringVal), mknode(int_str, NULL, NULL), (yyvsp[0].nodePtr));
    }
#line 1853 "y.tab.c"
    break;

  case 32: /* id_list: IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL  */
#line 203 "parser.y"
                                                    {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-3].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-5].stringVal), mknode(int_str, NULL, NULL), mknode((yyvsp[0].stringVal), NULL, NULL));
    }
#line 1863 "y.tab.c"
    break;

  case 33: /* id_list: IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL ',' id_list  */
#line 208 "parser.y"
                                                                {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-5].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-7].stringVal), mknode(int_str, NULL, NULL), mknode((yyvsp[-2].stringVal), NULL, (yyvsp[0].nodePtr)));
    }
#line 1873 "y.tab.c"
    break;

  case 34: /* statements: statement  */
#line 215 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1879 "y.tab.c"
    break;

  case 35: /* statements: statement statements  */
#line 216 "parser.y"
                           {(yyval.nodePtr) = mknode("statements", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1885 "y.tab.c"
    break;

  case 36: /* statements: nested_function  */
#line 217 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1891 "y.tab.c"
    break;

  case 37: /* statements: nested_function statements  */
#line 218 "parser.y"
                                 {(yyval.nodePtr) = mknode("statements", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1897 "y.tab.c"
    break;

  case 38: /* nested_function: DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END  */
#line 224 "parser.y"
    {
        // Check if last statement is a return
        node* last_stmt = (yyvsp[-1].nodePtr);
        while (last_stmt && last_stmt->right) {
            last_stmt = last_stmt->right;
        }
        if (!last_stmt || strcmp(last_stmt->token, "return_val") != 0) {
            yyerror("Error: function with RETURNS must end with a return statement");
            YYERROR;
        }
        (yyval.nodePtr) = mknode("nested_func", mknode((yyvsp[-10].stringVal), (yyvsp[-8].nodePtr), mknode("ret", (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr))), mknode("body", (yyvsp[-1].nodePtr), NULL));
    }
#line 1914 "y.tab.c"
    break;

  case 39: /* nested_function: DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END  */
#line 237 "parser.y"
    {
        // Check if last statement is a return
        node* last_stmt = (yyvsp[-1].nodePtr);
        while (last_stmt && last_stmt->right) {
            last_stmt = last_stmt->right;
        }
        if (last_stmt && strcmp(last_stmt->token, "return_val") == 0) {
            yyerror("Error: function without RETURNS must not have a return statement");
            YYERROR;
        }
        (yyval.nodePtr) = mknode("nested_func", mknode((yyvsp[-8].stringVal), (yyvsp[-6].nodePtr), NULL), mknode("body", (yyvsp[-1].nodePtr), NULL));
    }
#line 1931 "y.tab.c"
    break;

  case 40: /* statement: assignment_statement  */
#line 251 "parser.y"
                                {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1937 "y.tab.c"
    break;

  case 41: /* statement: if_statement  */
#line 252 "parser.y"
                   {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1943 "y.tab.c"
    break;

  case 42: /* statement: while_statement  */
#line 253 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1949 "y.tab.c"
    break;

  case 43: /* statement: for_statement  */
#line 254 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1955 "y.tab.c"
    break;

  case 44: /* statement: do_while_statement  */
#line 255 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1961 "y.tab.c"
    break;

  case 45: /* statement: block_statement  */
#line 256 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1967 "y.tab.c"
    break;

  case 46: /* statement: return_statement  */
#line 257 "parser.y"
                       {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1973 "y.tab.c"
    break;

  case 47: /* statement: function_call_statement  */
#line 258 "parser.y"
                              {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1979 "y.tab.c"
    break;

  case 48: /* assignment_statement: IDENTIFIER ASSIGN expression ';'  */
#line 262 "parser.y"
                                     {(yyval.nodePtr) = mknode("assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 1985 "y.tab.c"
    break;

  case 49: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN CHAR_LITERAL ';'  */
#line 263 "parser.y"
                                                            {
        char char_str[2];
        char_str[0] = (yyvsp[-1].charVal);
        char_str[1] = '\0';
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode(char_str, NULL, NULL));
    }
#line 1996 "y.tab.c"
    break;

  case 50: /* assignment_statement: MULT IDENTIFIER ASSIGN expression ';'  */
#line 269 "parser.y"
                                            {(yyval.nodePtr) = mknode("pointer_assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2002 "y.tab.c"
    break;

  case 51: /* assignment_statement: IDENTIFIER ASSIGN AMPERSAND IDENTIFIER ';'  */
#line 270 "parser.y"
                                                 {(yyval.nodePtr) = mknode("ref_assign", mknode((yyvsp[-4].stringVal), NULL, NULL), mknode((yyvsp[-1].stringVal), NULL, NULL));}
#line 2008 "y.tab.c"
    break;

  case 52: /* assignment_statement: IDENTIFIER ASSIGN NULL_TOKEN ';'  */
#line 271 "parser.y"
                                       {(yyval.nodePtr) = mknode("null_assign", mknode((yyvsp[-3].stringVal), NULL, NULL), mknode("null", NULL, NULL));}
#line 2014 "y.tab.c"
    break;

  case 53: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN INTEGER ';'  */
#line 272 "parser.y"
                                                       {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-1].intVal));
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode(int_str, NULL, NULL));
    }
#line 2024 "y.tab.c"
    break;

  case 54: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN STRING_LITERAL ';'  */
#line 277 "parser.y"
                                                              {
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode((yyvsp[-1].stringVal), NULL, NULL));
    }
#line 2032 "y.tab.c"
    break;

  case 55: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN expression ';'  */
#line 280 "parser.y"
                                                          {
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), (yyvsp[-1].nodePtr));
    }
#line 2040 "y.tab.c"
    break;

  case 56: /* if_statement: IF expression ':' block_statement  */
#line 286 "parser.y"
                                      {(yyval.nodePtr) = mknode("if", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2046 "y.tab.c"
    break;

  case 57: /* if_statement: IF expression ':' block_statement ELSE ':' block_statement  */
#line 287 "parser.y"
                                                                 {(yyval.nodePtr) = mknode("if-else", (yyvsp[-5].nodePtr), mknode("then", (yyvsp[-3].nodePtr), mknode("else", (yyvsp[0].nodePtr), NULL)));}
#line 2052 "y.tab.c"
    break;

  case 58: /* if_statement: IF expression ':' block_statement ELIF expression ':' block_statement  */
#line 288 "parser.y"
                                                                            {(yyval.nodePtr) = mknode("if-elif", (yyvsp[-6].nodePtr), mknode("then", (yyvsp[-4].nodePtr), mknode("elif-cond", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr))));}
#line 2058 "y.tab.c"
    break;

  case 59: /* if_statement: IF expression ':' block_statement ELIF expression ':' block_statement ELSE ':' block_statement  */
#line 289 "parser.y"
                                                                                                     {(yyval.nodePtr) = mknode("if-elif-else", (yyvsp[-9].nodePtr), mknode("then", (yyvsp[-7].nodePtr), mknode("elif-cond", (yyvsp[-5].nodePtr), mknode("elif-then", (yyvsp[-3].nodePtr), mknode("else", (yyvsp[0].nodePtr), NULL)))));}
#line 2064 "y.tab.c"
    break;

  case 60: /* while_statement: WHILE expression ':' block_statement  */
#line 293 "parser.y"
                                         {(yyval.nodePtr) = mknode("while", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2070 "y.tab.c"
    break;

  case 61: /* do_while_statement: DO ':' block_statement WHILE expression ';'  */
#line 297 "parser.y"
                                                {(yyval.nodePtr) = mknode("do-while", (yyvsp[-3].nodePtr), mknode("cond", (yyvsp[-1].nodePtr), NULL));}
#line 2076 "y.tab.c"
    break;

  case 62: /* for_statement: FOR for_header ':' block_statement  */
#line 301 "parser.y"
                                       {(yyval.nodePtr) = mknode("for", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2082 "y.tab.c"
    break;

  case 63: /* for_statement: FOR for_header ':' var block_statement  */
#line 302 "parser.y"
                                             {(yyval.nodePtr) = mknode("for", (yyvsp[-3].nodePtr), mknode("block", (yyvsp[0].nodePtr), (yyvsp[-1].nodePtr)));}
#line 2088 "y.tab.c"
    break;

  case 64: /* for_header: '(' IDENTIFIER ASSIGN expression ';' expression ';' update_exp ')'  */
#line 307 "parser.y"
    {(yyval.nodePtr) = mknode("for-header", mknode("init", mknode((yyvsp[-7].stringVal), NULL, NULL), (yyvsp[-5].nodePtr)), 
                             mknode("loop", (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr)));}
#line 2095 "y.tab.c"
    break;

  case 65: /* update_exp: IDENTIFIER ASSIGN expression  */
#line 312 "parser.y"
                                 {(yyval.nodePtr) = mknode("update", mknode((yyvsp[-2].stringVal), NULL, NULL), (yyvsp[0].nodePtr));}
#line 2101 "y.tab.c"
    break;

  case 66: /* scope_entry: %empty  */
#line 323 "parser.y"
                           { enter_scope(); (yyval.nodePtr) = NULL; }
#line 2107 "y.tab.c"
    break;

  case 67: /* scoped_block: scope_entry BEGIN_TOKEN END  */
#line 326 "parser.y"
                                {
        exit_scope();
        (yyval.nodePtr) = mknode("block", NULL, NULL);
    }
#line 2116 "y.tab.c"
    break;

  case 68: /* scoped_block: scope_entry BEGIN_TOKEN statements END  */
#line 330 "parser.y"
                                           {
        exit_scope();
        (yyval.nodePtr) = mknode("block", (yyvsp[-1].nodePtr), NULL);
    }
#line 2125 "y.tab.c"
    break;

  case 69: /* scoped_block: scope_entry var BEGIN_TOKEN END  */
#line 334 "parser.y"
                                    {
        exit_scope();
        (yyval.nodePtr) = mknode("block", NULL, (yyvsp[-2].nodePtr));
    }
#line 2134 "y.tab.c"
    break;

  case 70: /* scoped_block: scope_entry var BEGIN_TOKEN statements END  */
#line 338 "parser.y"
                                               {
        exit_scope();
        (yyval.nodePtr) = mknode("block", (yyvsp[-1].nodePtr), (yyvsp[-3].nodePtr));
    }
#line 2143 "y.tab.c"
    break;

  case 71: /* block_statement: scoped_block  */
#line 345 "parser.y"
                 { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2149 "y.tab.c"
    break;

  case 72: /* return_statement: RETURN expression ';'  */
#line 349 "parser.y"
                          {(yyval.nodePtr) = mknode("return_val", (yyvsp[-1].nodePtr), NULL);}
#line 2155 "y.tab.c"
    break;

  case 73: /* return_statement: RETURN ';'  */
#line 350 "parser.y"
                 {(yyval.nodePtr) = mknode("return_void", NULL, NULL);}
#line 2161 "y.tab.c"
    break;

  case 74: /* function_call_statement: function_call ';'  */
#line 354 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[-1].nodePtr);}
#line 2167 "y.tab.c"
    break;

  case 75: /* function_call_statement: IDENTIFIER ASSIGN function_call ';'  */
#line 355 "parser.y"
                                          {(yyval.nodePtr) = mknode("assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2173 "y.tab.c"
    break;

  case 76: /* function_call: CALL IDENTIFIER '(' ')'  */
#line 359 "parser.y"
                            {(yyval.nodePtr) = mknode("call", mknode((yyvsp[-2].stringVal), NULL, NULL), NULL);}
#line 2179 "y.tab.c"
    break;

  case 77: /* function_call: CALL IDENTIFIER '(' expr_list ')'  */
#line 360 "parser.y"
                                        {(yyval.nodePtr) = mknode("call", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2185 "y.tab.c"
    break;

  case 78: /* expr_list: expression  */
#line 364 "parser.y"
               {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2191 "y.tab.c"
    break;

  case 79: /* expr_list: expression ',' expr_list  */
#line 365 "parser.y"
                               {(yyval.nodePtr) = mknode("expr_list", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2197 "y.tab.c"
    break;

  case 80: /* expression: INTEGER  */
#line 369 "parser.y"
            {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[0].intVal));
        (yyval.nodePtr) = mknode(int_str, NULL, NULL);
    }
#line 2207 "y.tab.c"
    break;

  case 81: /* expression: REAL  */
#line 374 "parser.y"
           {
        char real_str[30];
        sprintf(real_str, "%f", (yyvsp[0].realVal));
        (yyval.nodePtr) = mknode(real_str, NULL, NULL);
    }
#line 2217 "y.tab.c"
    break;

  case 82: /* expression: STRING_LITERAL  */
#line 379 "parser.y"
                     {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);}
#line 2223 "y.tab.c"
    break;

  case 83: /* expression: CHAR_LITERAL  */
#line 380 "parser.y"
                   {
        char char_str[2];
        char_str[0] = (yyvsp[0].charVal);
        char_str[1] = '\0';
        (yyval.nodePtr) = mknode(char_str, NULL, NULL);
    }
#line 2234 "y.tab.c"
    break;

  case 84: /* expression: IDENTIFIER  */
#line 386 "parser.y"
                 {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);}
#line 2240 "y.tab.c"
    break;

  case 85: /* expression: expression PLUS expression  */
#line 387 "parser.y"
                                 {(yyval.nodePtr) = mknode("+", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2246 "y.tab.c"
    break;

  case 86: /* expression: expression MINUS expression  */
#line 388 "parser.y"
                                  {(yyval.nodePtr) = mknode("-", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2252 "y.tab.c"
    break;

  case 87: /* expression: expression MULT expression  */
#line 389 "parser.y"
                                 {(yyval.nodePtr) = mknode("*", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2258 "y.tab.c"
    break;

  case 88: /* expression: expression DIV expression  */
#line 390 "parser.y"
                                {(yyval.nodePtr) = mknode("/", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2264 "y.tab.c"
    break;

  case 89: /* expression: expression MODULO expression  */
#line 391 "parser.y"
                                   {(yyval.nodePtr) = mknode("%", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2270 "y.tab.c"
    break;

  case 90: /* expression: MINUS expression  */
#line 392 "parser.y"
                       {(yyval.nodePtr) = mknode("unary-", (yyvsp[0].nodePtr), NULL);}
#line 2276 "y.tab.c"
    break;

  case 91: /* expression: AMPERSAND IDENTIFIER  */
#line 393 "parser.y"
                           {(yyval.nodePtr) = mknode("&", mknode((yyvsp[0].stringVal), NULL, NULL), NULL);}
#line 2282 "y.tab.c"
    break;

  case 92: /* expression: AMPERSAND IDENTIFIER '[' expression ']'  */
#line 394 "parser.y"
                                              {(yyval.nodePtr) = mknode("&", mknode("index", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr)), NULL);}
#line 2288 "y.tab.c"
    break;

  case 93: /* expression: MULT IDENTIFIER  */
#line 395 "parser.y"
                      {(yyval.nodePtr) = mknode("deref", mknode((yyvsp[0].stringVal), NULL, NULL), NULL);}
#line 2294 "y.tab.c"
    break;

  case 94: /* expression: MULT expression  */
#line 396 "parser.y"
                      {(yyval.nodePtr) = mknode("*", (yyvsp[0].nodePtr), NULL);}
#line 2300 "y.tab.c"
    break;

  case 95: /* expression: '(' expression ')'  */
#line 397 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[-1].nodePtr);}
#line 2306 "y.tab.c"
    break;

  case 96: /* expression: expression EQ expression  */
#line 398 "parser.y"
                               {(yyval.nodePtr) = mknode("==", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2312 "y.tab.c"
    break;

  case 97: /* expression: expression NE expression  */
#line 399 "parser.y"
                               {(yyval.nodePtr) = mknode("!=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2318 "y.tab.c"
    break;

  case 98: /* expression: expression GE expression  */
#line 400 "parser.y"
                               {(yyval.nodePtr) = mknode(">=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2324 "y.tab.c"
    break;

  case 99: /* expression: expression LE expression  */
#line 401 "parser.y"
                               {(yyval.nodePtr) = mknode("<=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2330 "y.tab.c"
    break;

  case 100: /* expression: expression GT expression  */
#line 402 "parser.y"
                               {(yyval.nodePtr) = mknode(">", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2336 "y.tab.c"
    break;

  case 101: /* expression: expression LT expression  */
#line 403 "parser.y"
                               {(yyval.nodePtr) = mknode("<", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2342 "y.tab.c"
    break;

  case 102: /* expression: expression AND expression  */
#line 404 "parser.y"
                                {(yyval.nodePtr) = mknode("and", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2348 "y.tab.c"
    break;

  case 103: /* expression: expression OR expression  */
#line 405 "parser.y"
                               {(yyval.nodePtr) = mknode("or", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2354 "y.tab.c"
    break;

  case 104: /* expression: IDENTIFIER '[' expression ']'  */
#line 406 "parser.y"
                                    {(yyval.nodePtr) = mknode("index", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2360 "y.tab.c"
    break;

  case 105: /* expression: function_call  */
#line 407 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2366 "y.tab.c"
    break;


#line 2370 "y.tab.c"

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

#line 410 "parser.y"


int main()
{
    if (yyparse() == 0) {
        if (main_count == 0) 
        {
            fprintf(stderr, "Semantic Error: Missing '_main_' function.\n");
            return 1;
        } else if (main_count > 1) 
        {
            fprintf(stderr, "Semantic Error: Multiple '_main_' functions are not allowed.\n");
            return 1;
        }
        visualize_ast(root, "", 1);
        printf("Semantic checks passed.\n");
    }

    
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

// Part 2
VarType string_to_type(const char* str) 
{
    if (strcmp(str, "int") == 0) return TYPE_INT;
    if (strcmp(str, "char") == 0) return TYPE_CHAR;
    if (strcmp(str, "real") == 0) return TYPE_REAL;
    if (strcmp(str, "string") == 0) return TYPE_STRING;
    if (strcmp(str, "bool") == 0) return TYPE_BOOL;
    if (strcmp(str, "int*") == 0) return TYPE_INT_PTR;
    if (strcmp(str, "char*") == 0) return TYPE_CHAR_PTR;
    if (strcmp(str, "real*") == 0) return TYPE_REAL_PTR;
    return TYPE_INVALID;
}

void insert_symbol(char* name, VarType type, int is_function, VarType return_type, VarType* param_types, int param_count) 
{
    // Check for redefinition in the same scope
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->scope_level == current_scope_level && strcmp(sym->name, name) == 0) {
            fprintf(stderr, "Semantic Error: Redefinition of '%s' in the same scope.\n", name);
            exit(1);
        }
        sym = sym->next;
    }

    // Create new symbol
    Symbol* new_sym = (Symbol*)malloc(sizeof(Symbol));
    new_sym->name = strdup(name);
    new_sym->type = type;
    new_sym->is_function = is_function;
    new_sym->return_type = return_type;
    new_sym->param_count = param_count;
    for (int i = 0; i < param_count; i++) {
        new_sym->param_types[i] = param_types[i];
    }
    new_sym->scope_level = current_scope_level;
    new_sym->next = symbol_table;
    symbol_table = new_sym;

    // Handle main function count
    if (is_function && strcmp(name, "_main_") == 0) {
        main_count++;
    }
}

void enter_scope() {
    current_scope_level++;
}

void exit_scope() {
    Symbol* sym = symbol_table;
    while (sym && sym->scope_level == current_scope_level) {
        Symbol* to_delete = sym;
        sym = sym->next;
        free(to_delete->name);
        free(to_delete);
    }
    symbol_table = sym;
    current_scope_level--;
}

