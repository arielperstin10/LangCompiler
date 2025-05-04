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
    #include <ctype.h>

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
    int is_function_defined(const char* name);
    int is_variable_defined(const char* name);
    int get_function_param_count(const char* name);
    int count_params(node* param_node);
    void extract_param_types(node* param_node, VarType* types);
    VarType infer_type(node* expr);
    const char* type_to_string(VarType type);
    Symbol* find_function_symbol(const char* name);

    node* root = NULL;
    Symbol* symbol_table = NULL;
    int current_scope_level = 0;
    int main_count = 0;

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
#line 58 "parser.y"

    int intVal;
    float realVal;
    char charVal;
    char* stringVal;
    struct node* nodePtr;
    VarType typeVal;
    VarType paramList[MAX_PARAMS];

#line 288 "y.tab.c"

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
  YYSYMBOL_58_ = 58,                       /* '|'  */
  YYSYMBOL_YYACCEPT = 59,                  /* $accept  */
  YYSYMBOL_code = 60,                      /* code  */
  YYSYMBOL_functions = 61,                 /* functions  */
  YYSYMBOL_function = 62,                  /* function  */
  YYSYMBOL_parameters = 63,                /* parameters  */
  YYSYMBOL_parameter_list = 64,            /* parameter_list  */
  YYSYMBOL_parameter = 65,                 /* parameter  */
  YYSYMBOL_var = 66,                       /* var  */
  YYSYMBOL_declaration_list = 67,          /* declaration_list  */
  YYSYMBOL_declaration = 68,               /* declaration  */
  YYSYMBOL_type = 69,                      /* type  */
  YYSYMBOL_id_list = 70,                   /* id_list  */
  YYSYMBOL_statements = 71,                /* statements  */
  YYSYMBOL_nested_function = 72,           /* nested_function  */
  YYSYMBOL_73_1 = 73,                      /* $@1  */
  YYSYMBOL_74_2 = 74,                      /* $@2  */
  YYSYMBOL_75_3 = 75,                      /* $@3  */
  YYSYMBOL_statement = 76,                 /* statement  */
  YYSYMBOL_assignment_statement = 77,      /* assignment_statement  */
  YYSYMBOL_if_statement = 78,              /* if_statement  */
  YYSYMBOL_while_statement = 79,           /* while_statement  */
  YYSYMBOL_do_while_statement = 80,        /* do_while_statement  */
  YYSYMBOL_for_statement = 81,             /* for_statement  */
  YYSYMBOL_for_header = 82,                /* for_header  */
  YYSYMBOL_update_exp = 83,                /* update_exp  */
  YYSYMBOL_scope_entry = 84,               /* scope_entry  */
  YYSYMBOL_scoped_block = 85,              /* scoped_block  */
  YYSYMBOL_block_statement = 86,           /* block_statement  */
  YYSYMBOL_return_statement = 87,          /* return_statement  */
  YYSYMBOL_function_call_statement = 88,   /* function_call_statement  */
  YYSYMBOL_function_call = 89,             /* function_call  */
  YYSYMBOL_expr_list = 90,                 /* expr_list  */
  YYSYMBOL_expression = 91                 /* expression  */
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
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  33
/* YYNRULES -- Number of rules.  */
#define YYNRULES  114
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  255

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
       2,     2,     2,     2,    58,     2,     2,     2,     2,     2,
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
       0,    98,    98,   100,   101,   104,   118,   161,   184,   185,
     188,   189,   192,   194,   195,   198,   199,   202,   215,   216,
     217,   218,   219,   220,   221,   222,   225,   226,   227,   228,
     229,   234,   239,   244,   251,   252,   253,   254,   255,   261,
     270,   260,   311,   310,   333,   334,   335,   336,   337,   338,
     339,   340,   344,   377,   408,   445,   481,   504,   532,   540,
     572,   582,   592,   608,   627,   639,   651,   652,   656,   668,
     679,   682,   686,   690,   694,   701,   705,   706,   710,   711,
     715,   730,   777,   778,   782,   787,   792,   793,   799,   800,
     801,   808,   809,   810,   811,   812,   813,   814,   821,   835,
     842,   843,   843,   852,   853,   854,   855,   856,   857,   858,
     859,   860,   861,   891,   899
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
  "')'", "':'", "';'", "','", "'['", "']'", "'|'", "$accept", "code",
  "functions", "function", "parameters", "parameter_list", "parameter",
  "var", "declaration_list", "declaration", "type", "id_list",
  "statements", "nested_function", "$@1", "$@2", "$@3", "statement",
  "assignment_statement", "if_statement", "while_statement",
  "do_while_statement", "for_statement", "for_header", "update_exp",
  "scope_entry", "scoped_block", "block_statement", "return_statement",
  "function_call_statement", "function_call", "expr_list", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-122)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-35)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       8,     0,    40,  -122,     8,   -10,    -6,  -122,  -122,    23,
       3,   122,    12,  -122,     7,    -7,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,    15,    26,    23,    57,    74,    -4,
    -122,    82,    54,  -122,   122,    73,   122,  -122,    82,   418,
      57,   418,    50,  -122,   -36,   248,   248,    58,    67,    64,
     112,   115,   116,    94,   418,   418,  -122,  -122,  -122,  -122,
    -122,   -15,  -122,  -122,  -122,  -122,    85,   111,   114,   135,
     184,   248,  -122,  -122,  -122,  -122,    90,   248,   248,   266,
     140,  -122,  -122,   248,   248,  -122,   633,   658,   141,    96,
    -122,   453,  -122,    99,   100,   110,  -122,  -122,  -122,   434,
     124,  -122,   418,  -122,    22,   102,   106,   147,   119,   483,
     308,   248,  -122,    -8,    90,  -122,   118,   708,   126,   248,
     248,   248,   248,   248,   248,   248,   248,   248,   248,   248,
     248,   248,  -122,  -122,   134,    57,  -122,   157,    23,   216,
     248,  -122,   138,   450,   149,   248,   135,   177,  -122,  -122,
     -33,  -122,  -122,   139,   323,   248,  -122,  -122,  -122,   200,
     747,    13,    13,    83,    83,    83,    83,    -8,    -8,  -122,
    -122,     9,  -122,   248,  -122,  -122,   248,   130,  -122,   131,
     353,   508,  -122,  -122,   155,  -122,   383,  -122,   136,  -122,
     284,  -122,   338,   248,   143,   533,  -122,   558,   144,  -122,
     248,  -122,  -122,   135,   -21,   145,   151,   152,   583,  -122,
     683,  -122,   248,  -122,    -1,  -122,  -122,   186,   135,  -122,
    -122,  -122,  -122,  -122,  -122,   608,   122,   165,   146,  -122,
     178,   196,    57,  -122,   135,   159,   166,   162,   195,   418,
    -122,  -122,   248,  -122,  -122,   197,  -122,   733,   418,  -122,
     204,  -122,   418,   217,  -122
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     0,     1,     4,     8,
       0,     0,     0,     9,    10,     0,    18,    19,    20,    21,
      22,    23,    24,    25,     0,     0,     0,    13,     0,    13,
      11,     0,     0,    12,     0,     0,     0,    14,    15,    70,
      13,    70,     0,    16,     0,   101,   101,     0,   101,     0,
       0,     0,     0,     0,    70,    70,    44,    45,    46,    48,
      47,     0,    75,    49,    50,    51,     0,     0,     0,     0,
     101,   101,    84,    85,    87,    86,    90,   101,   101,   101,
       0,    88,    89,   101,   101,   114,     0,     0,     0,     0,
      77,     0,    70,     0,     0,     0,     5,    38,    36,    70,
       0,    78,    70,     7,    26,     0,     0,     0,   114,     0,
       0,   101,   102,    96,    90,   100,    97,     0,     0,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,    70,    70,     0,    13,    76,     0,     8,   101,
     101,    71,     0,    70,     0,   101,     0,     0,    17,    56,
      97,    79,    52,     0,     0,   101,   103,   113,    95,   110,
     111,   104,   105,   106,   107,   108,   109,    91,    92,    93,
      94,    60,    64,   101,    70,    66,   101,     0,    80,     0,
      82,     0,    72,    73,     0,     6,    28,    27,     0,    55,
     101,   112,     0,   101,     0,     0,    67,     0,     0,    81,
     101,    54,    74,     0,    30,    84,    87,    86,     0,    98,
       0,    70,   101,    65,    13,    83,    29,     0,     0,    57,
      53,    58,    59,    70,    61,     0,     0,     0,    32,    31,
      62,     0,    13,    42,     0,     0,     0,     0,     0,    70,
      33,    70,   101,    68,    39,     0,    63,    69,    70,    43,
       0,    40,    70,     0,    41
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -122,  -122,   221,  -122,    88,   223,  -122,   -28,   192,  -122,
     -31,  -121,   -37,  -122,  -122,  -122,  -122,  -122,  -122,  -122,
    -122,  -122,  -122,  -122,  -122,  -122,  -122,   -66,  -122,  -122,
     -39,    56,   -35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     4,    12,    13,    14,    32,    37,    38,
      24,   105,    53,    54,   248,   252,   239,    55,    56,    57,
      58,    59,    60,    89,   237,    61,    62,    63,    64,    65,
      85,   179,   180
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      66,    35,    66,    40,    68,    42,    70,     5,    31,   119,
      86,    87,    67,    91,    99,    66,    66,    97,    98,    31,
      71,   189,    31,   155,    34,   187,   137,   226,   193,   194,
     119,   108,   217,   100,   218,   109,   110,   130,   131,     1,
       7,     9,   112,   113,   115,    10,    27,    11,   117,   118,
       6,   124,   125,   126,   127,    15,   128,   129,   130,   131,
      66,    26,   142,    66,    25,   144,   171,   172,    28,   175,
      72,    73,    74,    75,    76,   145,   154,   146,   147,    29,
      31,    33,   216,    39,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   229,    36,    51,
     119,    77,    41,    69,    66,   181,   184,   174,   196,    88,
     186,    78,    79,   240,    80,    81,    82,    92,    83,    93,
     192,    90,    94,    95,    96,    84,   128,   129,   130,   131,
      16,    17,    18,    19,    20,    21,    22,    23,   195,   101,
     102,   197,   104,   119,   103,   224,   111,   116,   134,   135,
     138,   139,   140,   143,   150,   208,   148,   230,   210,   120,
     149,   121,   122,   123,   124,   125,   126,   127,   182,   128,
     129,   130,   131,   151,   155,   246,   173,   225,   176,   185,
     188,   190,   198,   199,   157,   202,   227,    72,    73,    74,
      75,    76,   228,   204,   233,   232,   211,   214,   235,   219,
      66,   234,   245,   236,   238,   220,   221,   247,   242,    66,
     106,   250,   241,    66,   243,   253,    51,   119,    77,    72,
      73,    74,    75,    76,   244,     8,   177,   249,    78,    79,
      43,   107,    81,    82,   251,    83,   122,   123,   124,   125,
     126,   127,    84,   128,   129,   130,   131,   254,    51,    30,
      77,    72,    73,    74,    75,    76,   215,     0,     0,     0,
      78,    79,     0,    80,    81,    82,     0,    83,   178,    72,
      73,    74,    75,   114,    84,     0,     0,     0,     0,     0,
      51,     0,    77,     0,     0,     0,     0,   205,    73,   206,
     207,    76,    78,    79,     0,    80,    81,    82,    51,    83,
      77,     0,     0,     0,     0,     0,    84,     0,     0,     0,
      78,    79,     0,    80,    81,    82,    51,    83,    77,     0,
       0,     0,     0,     0,    84,   119,     0,     0,    78,    79,
       0,    80,    81,    82,     0,    83,     0,     0,     0,     0,
     119,   120,    84,   121,   122,   123,   124,   125,   126,   127,
       0,   128,   129,   130,   131,   119,   120,     0,   121,   122,
     123,   124,   125,   126,   127,   153,   128,   129,   130,   131,
     119,   120,     0,   121,   122,   123,   124,   125,   126,   127,
     191,   128,   129,   130,   131,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,   209,   128,   129,   130,   131,
     119,     0,     0,     0,     0,     0,     0,     0,   200,     0,
       0,     0,     0,     0,     0,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,    44,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,    45,     0,   203,    46,
      47,    44,     0,    48,     0,    49,     0,     0,   -34,    50,
      51,     0,    45,     0,     0,    46,    47,    44,     0,    48,
       0,    49,     0,    52,   141,    50,    51,     0,    45,     0,
     119,    46,    47,     0,     0,    48,     0,    49,     0,    52,
     183,    50,    51,     0,     0,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,    52,   128,   129,   130,   131,
     119,     0,     0,     0,     0,     0,     0,   136,     0,     0,
       0,     0,     0,     0,     0,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,   119,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,     0,   152,     0,     0,
       0,   120,     0,   121,   122,   123,   124,   125,   126,   127,
     119,   128,   129,   130,   131,     0,     0,     0,     0,     0,
       0,     0,   201,     0,     0,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,   119,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,     0,   212,     0,     0,
       0,   120,     0,   121,   122,   123,   124,   125,   126,   127,
     119,   128,   129,   130,   131,     0,     0,     0,     0,     0,
       0,     0,   213,     0,     0,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,   119,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,     0,   222,     0,     0,
       0,   120,     0,   121,   122,   123,   124,   125,   126,   127,
     119,   128,   129,   130,   131,     0,     0,     0,     0,     0,
       0,     0,   231,     0,     0,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,   119,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,   132,     0,     0,     0,
       0,   120,     0,   121,   122,   123,   124,   125,   126,   127,
     119,   128,   129,   130,   131,     0,     0,     0,     0,     0,
       0,   133,     0,     0,     0,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,   119,   128,   129,   130,   131,
       0,     0,     0,     0,     0,     0,   223,     0,     0,     0,
       0,   120,     0,   121,   122,   123,   124,   125,   126,   127,
     119,   128,   129,   130,   131,     0,     0,     0,     0,     0,
     156,     0,     0,     0,   119,     0,   120,     0,   121,   122,
     123,   124,   125,   126,   127,     0,   128,   129,   130,   131,
     120,     0,     0,   122,   123,   124,   125,   126,   127,     0,
     128,   129,   130,   131
};

static const yytype_int16 yycheck[] =
{
      39,    29,    41,    34,    41,    36,    42,     7,    23,    17,
      45,    46,    40,    48,    29,    54,    55,    54,    55,    23,
      56,    54,    23,    56,    28,   146,    92,    28,    19,    20,
      17,    70,    53,    61,    55,    70,    71,    45,    46,    31,
       0,    51,    77,    78,    79,    51,    53,    24,    83,    84,
      50,    38,    39,    40,    41,    52,    43,    44,    45,    46,
      99,    54,    99,   102,    52,   102,   132,   133,    53,   135,
       3,     4,     5,     6,     7,    53,   111,    55,    56,    53,
      23,     7,   203,    29,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   218,    16,    32,
      17,    34,    29,    53,   143,   140,   143,   135,   174,    51,
     145,    44,    45,   234,    47,    48,    49,    53,    51,     7,
     155,    54,     7,     7,    30,    58,    43,    44,    45,    46,
       8,     9,    10,    11,    12,    13,    14,    15,   173,    54,
      29,   176,     7,    17,    30,   211,    56,     7,     7,    53,
      51,    51,    42,    29,     7,   190,    54,   223,   193,    33,
      54,    35,    36,    37,    38,    39,    40,    41,    30,    43,
      44,    45,    46,    54,    56,   241,    42,   212,    21,    30,
       3,    42,    52,    52,    58,    30,   214,     3,     4,     5,
       6,     7,     6,    57,    29,   226,    53,    53,    20,    54,
     239,    55,   239,     7,   232,    54,    54,   242,    42,   248,
      26,   248,    53,   252,    52,   252,    32,    17,    34,     3,
       4,     5,     6,     7,    29,     4,   138,    30,    44,    45,
      38,    47,    48,    49,    30,    51,    36,    37,    38,    39,
      40,    41,    58,    43,    44,    45,    46,    30,    32,    26,
      34,     3,     4,     5,     6,     7,   200,    -1,    -1,    -1,
      44,    45,    -1,    47,    48,    49,    -1,    51,    52,     3,
       4,     5,     6,     7,    58,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    34,    -1,    -1,    -1,    -1,     3,     4,     5,
       6,     7,    44,    45,    -1,    47,    48,    49,    32,    51,
      34,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      44,    45,    -1,    47,    48,    49,    32,    51,    34,    -1,
      -1,    -1,    -1,    -1,    58,    17,    -1,    -1,    44,    45,
      -1,    47,    48,    49,    -1,    51,    -1,    -1,    -1,    -1,
      17,    33,    58,    35,    36,    37,    38,    39,    40,    41,
      -1,    43,    44,    45,    46,    17,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    57,    43,    44,    45,    46,
      17,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
      57,    43,    44,    45,    46,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    57,    43,    44,    45,    46,
      17,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,     7,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    55,    21,
      22,     7,    -1,    25,    -1,    27,    -1,    -1,    30,    31,
      32,    -1,    18,    -1,    -1,    21,    22,     7,    -1,    25,
      -1,    27,    -1,    45,    30,    31,    32,    -1,    18,    -1,
      17,    21,    22,    -1,    -1,    25,    -1,    27,    -1,    45,
      30,    31,    32,    -1,    -1,    -1,    33,    -1,    35,    36,
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
      -1,    -1,    54,    -1,    -1,    -1,    33,    -1,    35,    36,
      37,    38,    39,    40,    41,    17,    43,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,
      -1,    33,    -1,    35,    36,    37,    38,    39,    40,    41,
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
       0,    31,    60,    61,    62,     7,    50,     0,    61,    51,
      51,    24,    63,    64,    65,    52,     8,     9,    10,    11,
      12,    13,    14,    15,    69,    52,    54,    53,    53,    53,
      64,    23,    66,     7,    28,    66,    16,    67,    68,    29,
      69,    29,    69,    67,     7,    18,    21,    22,    25,    27,
      31,    32,    45,    71,    72,    76,    77,    78,    79,    80,
      81,    84,    85,    86,    87,    88,    89,    66,    71,    53,
      42,    56,     3,     4,     5,     6,     7,    34,    44,    45,
      47,    48,    49,    51,    58,    89,    91,    91,    51,    82,
      54,    91,    53,     7,     7,     7,    30,    71,    71,    29,
      66,    54,    29,    30,     7,    70,    26,    47,    89,    91,
      91,    56,    91,    91,     7,    91,     7,    91,    91,    17,
      33,    35,    36,    37,    38,    39,    40,    41,    43,    44,
      45,    46,    53,    53,     7,    53,    54,    86,    51,    51,
      42,    30,    71,    29,    71,    53,    55,    56,    54,    54,
       7,    54,    54,    57,    91,    56,    52,    58,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    86,    86,    42,    66,    86,    21,    63,    52,    90,
      91,    91,    30,    30,    71,    30,    91,    70,     3,    54,
      42,    57,    91,    19,    20,    91,    86,    91,    52,    52,
      55,    54,    30,    55,    57,     3,     5,     6,    91,    57,
      91,    53,    54,    54,    53,    90,    70,    53,    55,    54,
      54,    54,    54,    53,    86,    91,    28,    66,     6,    70,
      86,    54,    69,    29,    55,    20,     7,    83,    66,    75,
      70,    53,    42,    52,    29,    71,    86,    91,    73,    30,
      71,    30,    74,    71,    30
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    62,    63,    63,
      64,    64,    65,    66,    66,    67,    67,    68,    69,    69,
      69,    69,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    71,    71,    71,    71,    71,    73,
      74,    72,    75,    72,    76,    76,    76,    76,    76,    76,
      76,    76,    77,    77,    77,    77,    77,    77,    77,    77,
      78,    78,    78,    78,    79,    80,    81,    81,    82,    83,
      84,    85,    85,    85,    85,    86,    87,    87,    88,    88,
      89,    89,    90,    90,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    91,    91,    91,    91
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     9,    12,    10,     0,     1,
       1,     3,     4,     0,     2,     1,     2,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     5,
       4,     6,     6,     8,     0,     1,     2,     1,     2,     0,
       0,    16,     0,    11,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     7,     5,     5,     4,     7,     7,     7,
       4,     7,     8,    11,     4,     6,     4,     5,     9,     3,
       0,     3,     4,     4,     5,     1,     3,     2,     2,     4,
       4,     5,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     2,     2,     5,     2,
       2,     0,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     4,     3,     1
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
#line 98 "parser.y"
                {root = mknode("code", (yyvsp[0].nodePtr), NULL); (yyval.nodePtr) = root;}
#line 1634 "y.tab.c"
    break;

  case 3: /* functions: function  */
#line 100 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1640 "y.tab.c"
    break;

  case 4: /* functions: function functions  */
#line 101 "parser.y"
                             {(yyval.nodePtr) = mknode("functions", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1646 "y.tab.c"
    break;

  case 5: /* function: DEF MAIN '(' ')' ':' var BEGIN_TOKEN statements END  */
#line 104 "parser.y"
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
#line 1665 "y.tab.c"
    break;

  case 6: /* function: DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN statements END  */
#line 118 "parser.y"
                                                                                            {
            node* last_stmt = (yyvsp[-1].nodePtr);
            while (last_stmt && strcmp(last_stmt->token, "statements") == 0 && last_stmt->right) {
                last_stmt = last_stmt->right;
            }
            node* final = (last_stmt && strcmp(last_stmt->token, "statements") == 0) ? last_stmt->left : last_stmt;

            if (!final || (strcmp(final->token, "return_val") != 0 && strcmp(final->token, "return_void") != 0)) {
                yyerror("Error: function with RETURNS must end with a return statement");
                YYERROR;
            }

            if (strcmp((yyvsp[-10].stringVal), "_main_") == 0) {
                yyerror("Semantic Error: _main_ must not return a value.");
                YYERROR;
            }

            VarType declared_type = string_to_type((yyvsp[-4].nodePtr)->token);
            VarType param_types[MAX_PARAMS];
            int param_count = count_params((yyvsp[-8].nodePtr));
            extract_param_types((yyvsp[-8].nodePtr), param_types);
            insert_symbol((yyvsp[-10].stringVal), TYPE_INVALID, 1, declared_type, param_types, param_count);

            if (declared_type == TYPE_STRING) {
                fprintf(stderr, "Semantic Error: functions cannot return type 'string'.\n");
                exit(1);
            }

            if (strcmp(final->token, "return_void") == 0) {
                fprintf(stderr, "Semantic Error: function declared to return '%s' but returned nothing.\n", type_to_string(declared_type));
                exit(1);
            }

            VarType actual_type = infer_type(final->left);
            if (actual_type != declared_type) {
                fprintf(stderr, "Semantic Error: return type mismatch — expected '%s', got '%s'.\n",
                        type_to_string(declared_type), type_to_string(actual_type));
                exit(1);
            }

            
            (yyval.nodePtr) = mknode("FUNC", mknode((yyvsp[-10].stringVal), (yyvsp[-8].nodePtr), mknode("ret", (yyvsp[-4].nodePtr), (yyvsp[-3].nodePtr))), mknode("body", (yyvsp[-1].nodePtr), NULL));
        }
#line 1713 "y.tab.c"
    break;

  case 7: /* function: DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN statements END  */
#line 161 "parser.y"
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
            int param_count = count_params((yyvsp[-6].nodePtr));
            VarType param_types[MAX_PARAMS];
            extract_param_types((yyvsp[-6].nodePtr), param_types);
            insert_symbol((yyvsp[-8].stringVal), TYPE_INVALID, 1, TYPE_INVALID, param_types, param_count);
            (yyval.nodePtr) = mknode("FUNC", mknode((yyvsp[-8].stringVal), (yyvsp[-6].nodePtr), NULL), mknode("body", (yyvsp[-1].nodePtr), NULL));
        }
#line 1739 "y.tab.c"
    break;

  case 8: /* parameters: %empty  */
#line 184 "parser.y"
                        {(yyval.nodePtr) = NULL;}
#line 1745 "y.tab.c"
    break;

  case 9: /* parameters: parameter_list  */
#line 185 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1751 "y.tab.c"
    break;

  case 10: /* parameter_list: parameter  */
#line 188 "parser.y"
                          {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1757 "y.tab.c"
    break;

  case 11: /* parameter_list: parameter ';' parameter_list  */
#line 189 "parser.y"
                                       {(yyval.nodePtr) = mknode("PARAMS", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1763 "y.tab.c"
    break;

  case 12: /* parameter: PAR type ':' IDENTIFIER  */
#line 192 "parser.y"
                                   {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), (yyvsp[-2].nodePtr), NULL);}
#line 1769 "y.tab.c"
    break;

  case 13: /* var: %empty  */
#line 194 "parser.y"
                 {(yyval.nodePtr) = NULL;}
#line 1775 "y.tab.c"
    break;

  case 14: /* var: VAR declaration_list  */
#line 195 "parser.y"
                           {(yyval.nodePtr) = mknode("VAR", (yyvsp[0].nodePtr), NULL);}
#line 1781 "y.tab.c"
    break;

  case 15: /* declaration_list: declaration  */
#line 198 "parser.y"
                              {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1787 "y.tab.c"
    break;

  case 16: /* declaration_list: declaration declaration_list  */
#line 199 "parser.y"
                                   {(yyval.nodePtr) = mknode("decls", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1793 "y.tab.c"
    break;

  case 17: /* declaration: TYPE type ':' id_list ';'  */
#line 202 "parser.y"
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
#line 1809 "y.tab.c"
    break;

  case 18: /* type: BOOL  */
#line 215 "parser.y"
               { (yyval.nodePtr) = mknode("bool", NULL, NULL); }
#line 1815 "y.tab.c"
    break;

  case 19: /* type: CHAR  */
#line 216 "parser.y"
                 { (yyval.nodePtr) = mknode("char", NULL, NULL); }
#line 1821 "y.tab.c"
    break;

  case 20: /* type: INT  */
#line 217 "parser.y"
                 { (yyval.nodePtr) = mknode("int", NULL, NULL); }
#line 1827 "y.tab.c"
    break;

  case 21: /* type: REAL_TYPE  */
#line 218 "parser.y"
                 { (yyval.nodePtr) = mknode("real", NULL, NULL); }
#line 1833 "y.tab.c"
    break;

  case 22: /* type: STRING  */
#line 219 "parser.y"
                 { (yyval.nodePtr) = mknode("string", NULL, NULL); }
#line 1839 "y.tab.c"
    break;

  case 23: /* type: INT_PTR  */
#line 220 "parser.y"
                 { (yyval.nodePtr) = mknode("int*", NULL, NULL); }
#line 1845 "y.tab.c"
    break;

  case 24: /* type: CHAR_PTR  */
#line 221 "parser.y"
                 { (yyval.nodePtr) = mknode("char*", NULL, NULL); }
#line 1851 "y.tab.c"
    break;

  case 25: /* type: REAL_PTR  */
#line 222 "parser.y"
                 { (yyval.nodePtr) = mknode("real*", NULL, NULL); }
#line 1857 "y.tab.c"
    break;

  case 26: /* id_list: IDENTIFIER  */
#line 225 "parser.y"
                    {(yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);}
#line 1863 "y.tab.c"
    break;

  case 27: /* id_list: IDENTIFIER ',' id_list  */
#line 226 "parser.y"
                             {(yyval.nodePtr) = mknode((yyvsp[-2].stringVal), NULL, (yyvsp[0].nodePtr));}
#line 1869 "y.tab.c"
    break;

  case 28: /* id_list: IDENTIFIER ':' expression  */
#line 227 "parser.y"
                                {(yyval.nodePtr) = mknode((yyvsp[-2].stringVal), (yyvsp[0].nodePtr), NULL);}
#line 1875 "y.tab.c"
    break;

  case 29: /* id_list: IDENTIFIER ':' expression ',' id_list  */
#line 228 "parser.y"
                                            {(yyval.nodePtr) = mknode((yyvsp[-4].stringVal), (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 1881 "y.tab.c"
    break;

  case 30: /* id_list: IDENTIFIER '[' INTEGER ']'  */
#line 229 "parser.y"
                                 {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-1].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-3].stringVal), mknode(int_str, NULL, NULL), NULL);
    }
#line 1891 "y.tab.c"
    break;

  case 31: /* id_list: IDENTIFIER '[' INTEGER ']' ',' id_list  */
#line 234 "parser.y"
                                             {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-3].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-5].stringVal), mknode(int_str, NULL, NULL), (yyvsp[0].nodePtr));
    }
#line 1901 "y.tab.c"
    break;

  case 32: /* id_list: IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL  */
#line 239 "parser.y"
                                                    {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-3].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-5].stringVal), mknode(int_str, NULL, NULL), mknode((yyvsp[0].stringVal), NULL, NULL));
    }
#line 1911 "y.tab.c"
    break;

  case 33: /* id_list: IDENTIFIER '[' INTEGER ']' ':' STRING_LITERAL ',' id_list  */
#line 244 "parser.y"
                                                                {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-5].intVal));
        (yyval.nodePtr) = mknode((yyvsp[-7].stringVal), mknode(int_str, NULL, NULL), mknode((yyvsp[-2].stringVal), NULL, (yyvsp[0].nodePtr)));
    }
#line 1921 "y.tab.c"
    break;

  case 34: /* statements: %empty  */
#line 251 "parser.y"
                         { (yyval.nodePtr) = NULL; }
#line 1927 "y.tab.c"
    break;

  case 35: /* statements: statement  */
#line 252 "parser.y"
                {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1933 "y.tab.c"
    break;

  case 36: /* statements: statement statements  */
#line 253 "parser.y"
                           {(yyval.nodePtr) = mknode("statements", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1939 "y.tab.c"
    break;

  case 37: /* statements: nested_function  */
#line 254 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 1945 "y.tab.c"
    break;

  case 38: /* statements: nested_function statements  */
#line 255 "parser.y"
                                 {(yyval.nodePtr) = mknode("statements", (yyvsp[-1].nodePtr), (yyvsp[0].nodePtr));}
#line 1951 "y.tab.c"
    break;

  case 39: /* $@1: %empty  */
#line 261 "parser.y"
    {
        VarType ret_type = string_to_type((yyvsp[-2].nodePtr)->token);
        int param_count = count_params((yyvsp[-6].nodePtr));
        VarType param_types[MAX_PARAMS];
        extract_param_types((yyvsp[-6].nodePtr), param_types);
        insert_symbol((yyvsp[-8].stringVal), TYPE_INVALID, 1, ret_type, param_types, param_count);

    }
#line 1964 "y.tab.c"
    break;

  case 40: /* $@2: %empty  */
#line 270 "parser.y"
    {
        VarType ret_type = string_to_type((yyvsp[-5].nodePtr)->token);
        int param_count = count_params((yyvsp[-9].nodePtr));
        VarType param_types[MAX_PARAMS];
        extract_param_types((yyvsp[-9].nodePtr), param_types);
        insert_symbol((yyvsp[-11].stringVal), TYPE_INVALID, 1, ret_type, param_types, param_count);
    }
#line 1976 "y.tab.c"
    break;

  case 41: /* nested_function: DEF IDENTIFIER '(' parameters ')' ':' RETURNS type var BEGIN_TOKEN $@1 statements END $@2 statements END  */
#line 278 "parser.y"
    {
        node* last_stmt = (yyvsp[-4].nodePtr);
        while (last_stmt && strcmp(last_stmt->token, "statements") == 0 && last_stmt->right) {
            last_stmt = last_stmt->right;
        }
        node* final = (last_stmt && strcmp(last_stmt->token, "statements") == 0) ? last_stmt->left : last_stmt;

        if (!final || (strcmp(final->token, "return_val") != 0 && strcmp(final->token, "return_void") != 0)) {
            yyerror("Error: function with RETURNS must end with a return statement");
            YYERROR;
        }

        VarType declared_type = string_to_type((yyvsp[-8].nodePtr)->token);

        if (declared_type == TYPE_STRING) {
            fprintf(stderr, "Semantic Error: functions cannot return type 'string'.\n");
            exit(1);
        }

        if (strcmp(final->token, "return_void") == 0) {
            fprintf(stderr, "Semantic Error: function declared to return '%s' but returned nothing.\n", type_to_string(declared_type));
            exit(1);
        }

        VarType actual_type = infer_type(final->left);
        if (actual_type != declared_type) {
            fprintf(stderr, "Semantic Error: return type mismatch — expected '%s', got '%s'.\n",
                    type_to_string(declared_type), type_to_string(actual_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("nested_func", mknode((yyvsp[-14].stringVal), (yyvsp[-12].nodePtr), mknode("ret", (yyvsp[-8].nodePtr), (yyvsp[-7].nodePtr))), mknode("body", (yyvsp[-4].nodePtr), NULL));
    }
#line 2013 "y.tab.c"
    break;

  case 42: /* $@3: %empty  */
#line 311 "parser.y"
    {
        int param_count = count_params((yyvsp[-4].nodePtr));
        VarType param_types[MAX_PARAMS];
        extract_param_types((yyvsp[-4].nodePtr), param_types);
        insert_symbol((yyvsp[-6].stringVal), TYPE_INVALID, 1, TYPE_INVALID, param_types, param_count);

    }
#line 2025 "y.tab.c"
    break;

  case 43: /* nested_function: DEF IDENTIFIER '(' parameters ')' ':' var BEGIN_TOKEN $@3 statements END  */
#line 319 "parser.y"
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
        (yyval.nodePtr) = mknode("nested_func", mknode((yyvsp[-9].stringVal), (yyvsp[-7].nodePtr), NULL), mknode("body", (yyvsp[-1].nodePtr), NULL));
    }
#line 2042 "y.tab.c"
    break;

  case 44: /* statement: assignment_statement  */
#line 333 "parser.y"
                                {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2048 "y.tab.c"
    break;

  case 45: /* statement: if_statement  */
#line 334 "parser.y"
                   {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2054 "y.tab.c"
    break;

  case 46: /* statement: while_statement  */
#line 335 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2060 "y.tab.c"
    break;

  case 47: /* statement: for_statement  */
#line 336 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2066 "y.tab.c"
    break;

  case 48: /* statement: do_while_statement  */
#line 337 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2072 "y.tab.c"
    break;

  case 49: /* statement: block_statement  */
#line 338 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2078 "y.tab.c"
    break;

  case 50: /* statement: return_statement  */
#line 339 "parser.y"
                       {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2084 "y.tab.c"
    break;

  case 51: /* statement: function_call_statement  */
#line 340 "parser.y"
                              {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2090 "y.tab.c"
    break;

  case 52: /* assignment_statement: IDENTIFIER ASSIGN expression ';'  */
#line 345 "parser.y"
    {
        if (!is_variable_defined((yyvsp[-3].stringVal))) 
        {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-3].stringVal));
            exit(1);
        }

        VarType lhs_type = TYPE_INVALID;
        Symbol* sym = symbol_table;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-3].stringVal)) == 0) {
                lhs_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        VarType rhs_type = infer_type((yyvsp[-1].nodePtr));

        // Allow assignment of NULL to pointer types only
        if (rhs_type == TYPE_INVALID && strcmp((yyvsp[-1].nodePtr)->token, "null") == 0) {
            if (lhs_type != TYPE_INT_PTR && lhs_type != TYPE_CHAR_PTR && lhs_type != TYPE_REAL_PTR) {
                fprintf(stderr, "Semantic Error: 'null' can only be assigned to pointer types, got '%s'.\n", type_to_string(lhs_type));
                exit(1);
            }
        } else if (lhs_type != rhs_type) {
            fprintf(stderr, "Semantic Error: cannot assign '%s' to variable of type '%s'.\n", type_to_string(rhs_type), type_to_string(lhs_type));
            exit(1);
        }

        (yyval.nodePtr) = mknode("assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));
    }
#line 2127 "y.tab.c"
    break;

  case 53: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN CHAR_LITERAL ';'  */
#line 377 "parser.y"
                                                            {

        if (!is_variable_defined((yyvsp[-6].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-6].stringVal));
            exit(1);
        }
        
        VarType index_type = infer_type((yyvsp[-4].nodePtr));
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }
        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-6].stringVal)) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }
        char char_str[2];
        char_str[0] = (yyvsp[-1].charVal);
        char_str[1] = '\0';
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode(char_str, NULL, NULL));
    }
#line 2163 "y.tab.c"
    break;

  case 54: /* assignment_statement: MULT IDENTIFIER ASSIGN expression ';'  */
#line 409 "parser.y"
    {
        if (!is_variable_defined((yyvsp[-3].stringVal))) 
        {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-3].stringVal));
            exit(1);
        }

        // Check pointer type
        Symbol* sym = symbol_table;
        VarType ptr_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-3].stringVal)) == 0) {
                ptr_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        VarType target_type = TYPE_INVALID;
        switch (ptr_type) {
            case TYPE_INT_PTR: target_type = TYPE_INT; break;
            case TYPE_CHAR_PTR: target_type = TYPE_CHAR; break;
            case TYPE_REAL_PTR: target_type = TYPE_REAL; break;
            default:
                fprintf(stderr, "Semantic Error: '*' applied to non-pointer variable '%s'.\n", (yyvsp[-3].stringVal));
                exit(1);
        }

        VarType expr_type = infer_type((yyvsp[-1].nodePtr));
        if (expr_type != target_type) {
            fprintf(stderr, "Semantic Error: cannot assign '%s' to dereferenced '%s'.\n",
                    type_to_string(expr_type), type_to_string(ptr_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("pointer_assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));
    }
#line 2204 "y.tab.c"
    break;

  case 55: /* assignment_statement: IDENTIFIER ASSIGN AMPERSAND IDENTIFIER ';'  */
#line 446 "parser.y"
    {
        if (!is_variable_defined((yyvsp[-4].stringVal)) || !is_variable_defined((yyvsp[-1].stringVal))) {
            fprintf(stderr, "Semantic Error: Undefined variable in reference assignment.\n");
            exit(1);
        }

        // LHS should be pointer to RHS type
        VarType lhs_type = TYPE_INVALID;
        VarType rhs_type = TYPE_INVALID;
        Symbol *sym = symbol_table;

        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-4].stringVal)) == 0) lhs_type = sym->type;
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-1].stringVal)) == 0) rhs_type = sym->type;
            sym = sym->next;
        }

        VarType expected_ptr_type = TYPE_INVALID;
        switch (rhs_type) {
            case TYPE_INT: expected_ptr_type = TYPE_INT_PTR; break;
            case TYPE_CHAR: expected_ptr_type = TYPE_CHAR_PTR; break;
            case TYPE_REAL: expected_ptr_type = TYPE_REAL_PTR; break;
            default:
                fprintf(stderr, "Semantic Error: Cannot take address of variable of type '%s'.\n", type_to_string(rhs_type));
                exit(1);
        }

        if (lhs_type != expected_ptr_type) {
            fprintf(stderr, "Semantic Error: cannot assign address of '%s' to variable of type '%s'.\n",
                    type_to_string(rhs_type), type_to_string(lhs_type));
            exit(1);
        }

        (yyval.nodePtr) = mknode("ref_assign", mknode((yyvsp[-4].stringVal), NULL, NULL), mknode((yyvsp[-1].stringVal), NULL, NULL));
    }
#line 2244 "y.tab.c"
    break;

  case 56: /* assignment_statement: IDENTIFIER ASSIGN NULL_TOKEN ';'  */
#line 482 "parser.y"
    {
        if (!is_variable_defined((yyvsp[-3].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-3].stringVal));
            exit(1);
        }

        Symbol* sym = symbol_table;
        VarType lhs_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-3].stringVal)) == 0) {
                lhs_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (lhs_type != TYPE_INT_PTR && lhs_type != TYPE_CHAR_PTR && lhs_type != TYPE_REAL_PTR) {
            fprintf(stderr, "Semantic Error: 'null' can only be assigned to pointer types, got '%s'.\n", type_to_string(lhs_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("null_assign", mknode((yyvsp[-3].stringVal), NULL, NULL), mknode("null", NULL, NULL));
    }
#line 2271 "y.tab.c"
    break;

  case 57: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN INTEGER ';'  */
#line 504 "parser.y"
                                                       {
        if (!is_variable_defined((yyvsp[-6].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-6].stringVal));
            exit(1);
        }
        VarType index_type = infer_type((yyvsp[-4].nodePtr));
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }
        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-6].stringVal)) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[-1].intVal));
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode(int_str, NULL, NULL));
    }
#line 2304 "y.tab.c"
    break;

  case 58: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN STRING_LITERAL ';'  */
#line 532 "parser.y"
                                                              {
        VarType index_type = infer_type((yyvsp[-4].nodePtr));
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), mknode((yyvsp[-1].stringVal), NULL, NULL));
    }
#line 2317 "y.tab.c"
    break;

  case 59: /* assignment_statement: IDENTIFIER '[' expression ']' ASSIGN expression ';'  */
#line 540 "parser.y"
                                                          {
        if (!is_variable_defined((yyvsp[-6].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-6].stringVal));
            exit(1);
        }

        VarType index_type = infer_type((yyvsp[-4].nodePtr));
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }

        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-6].stringVal)) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }

        (yyval.nodePtr) = mknode("array_assign", mknode((yyvsp[-6].stringVal), (yyvsp[-4].nodePtr), NULL), (yyvsp[-1].nodePtr));
    }
#line 2351 "y.tab.c"
    break;

  case 60: /* if_statement: IF expression ':' block_statement  */
#line 573 "parser.y"
    {
        VarType cond_type = infer_type((yyvsp[-2].nodePtr));
        if (cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("if", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
    }
#line 2365 "y.tab.c"
    break;

  case 61: /* if_statement: IF expression ':' block_statement ELSE ':' block_statement  */
#line 583 "parser.y"
    {
        VarType cond_type = infer_type((yyvsp[-5].nodePtr));
        if (cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if-else' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("if-else", (yyvsp[-5].nodePtr), mknode("then", (yyvsp[-3].nodePtr), mknode("else", (yyvsp[0].nodePtr), NULL)));
    }
#line 2379 "y.tab.c"
    break;

  case 62: /* if_statement: IF expression ':' block_statement ELIF expression ':' block_statement  */
#line 593 "parser.y"
    {
        VarType if_cond_type = infer_type((yyvsp[-6].nodePtr));
        VarType elif_cond_type = infer_type((yyvsp[-2].nodePtr));
        if (if_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if' must be of type 'bool', got '%s'.\n", type_to_string(if_cond_type));
            exit(1);
        }
        if (elif_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'elif' must be of type 'bool', got '%s'.\n", type_to_string(elif_cond_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("if-elif", (yyvsp[-6].nodePtr), mknode("then", (yyvsp[-4].nodePtr), mknode("elif-cond", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr))));
    }
#line 2399 "y.tab.c"
    break;

  case 63: /* if_statement: IF expression ':' block_statement ELIF expression ':' block_statement ELSE ':' block_statement  */
#line 609 "parser.y"
    {
        VarType if_cond_type = infer_type((yyvsp[-9].nodePtr));
        VarType elif_cond_type = infer_type((yyvsp[-5].nodePtr));
        if (if_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'if' must be of type 'bool', got '%s'.\n", type_to_string(if_cond_type));
            exit(1);
        }
        if (elif_cond_type != TYPE_BOOL) 
        {
            fprintf(stderr, "Semantic Error: condition in 'elif' must be of type 'bool', got '%s'.\n", type_to_string(elif_cond_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("if-elif-else", (yyvsp[-9].nodePtr), mknode("then", (yyvsp[-7].nodePtr), mknode("elif-cond", (yyvsp[-5].nodePtr), mknode("elif-then", (yyvsp[-3].nodePtr), mknode("else", (yyvsp[0].nodePtr), NULL)))));
    }
#line 2419 "y.tab.c"
    break;

  case 64: /* while_statement: WHILE expression ':' block_statement  */
#line 628 "parser.y"
    {
        VarType cond_type = infer_type((yyvsp[-2].nodePtr));
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: condition in 'while' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("while", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));
    }
#line 2432 "y.tab.c"
    break;

  case 65: /* do_while_statement: DO ':' block_statement WHILE expression ';'  */
#line 640 "parser.y"
    {
        VarType cond_type = infer_type((yyvsp[-1].nodePtr));
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: condition in 'do-while' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("do-while", (yyvsp[-3].nodePtr), mknode("cond", (yyvsp[-1].nodePtr), NULL));
    }
#line 2445 "y.tab.c"
    break;

  case 66: /* for_statement: FOR for_header ':' block_statement  */
#line 651 "parser.y"
                                       {(yyval.nodePtr) = mknode("for", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2451 "y.tab.c"
    break;

  case 67: /* for_statement: FOR for_header ':' var block_statement  */
#line 652 "parser.y"
                                             {(yyval.nodePtr) = mknode("for", (yyvsp[-3].nodePtr), mknode("block", (yyvsp[0].nodePtr), (yyvsp[-1].nodePtr)));}
#line 2457 "y.tab.c"
    break;

  case 68: /* for_header: '(' IDENTIFIER ASSIGN expression ';' expression ';' update_exp ')'  */
#line 657 "parser.y"
    {
        VarType cond_type = infer_type((yyvsp[-3].nodePtr));
        if (cond_type != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: condition in 'for' must be of type 'bool', got '%s'.\n", type_to_string(cond_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("for-header", mknode("init", mknode((yyvsp[-7].stringVal), NULL, NULL), (yyvsp[-5].nodePtr)), mknode("loop", (yyvsp[-3].nodePtr), (yyvsp[-1].nodePtr)));
    }
#line 2470 "y.tab.c"
    break;

  case 69: /* update_exp: IDENTIFIER ASSIGN expression  */
#line 668 "parser.y"
                                 {(yyval.nodePtr) = mknode("update", mknode((yyvsp[-2].stringVal), NULL, NULL), (yyvsp[0].nodePtr));}
#line 2476 "y.tab.c"
    break;

  case 70: /* scope_entry: %empty  */
#line 679 "parser.y"
                           { enter_scope(); (yyval.nodePtr) = NULL; }
#line 2482 "y.tab.c"
    break;

  case 71: /* scoped_block: scope_entry BEGIN_TOKEN END  */
#line 682 "parser.y"
                                {
        exit_scope();
        (yyval.nodePtr) = mknode("block", NULL, NULL);
    }
#line 2491 "y.tab.c"
    break;

  case 72: /* scoped_block: scope_entry BEGIN_TOKEN statements END  */
#line 686 "parser.y"
                                           {
        exit_scope();
        (yyval.nodePtr) = mknode("block", (yyvsp[-1].nodePtr), NULL);
    }
#line 2500 "y.tab.c"
    break;

  case 73: /* scoped_block: scope_entry var BEGIN_TOKEN END  */
#line 690 "parser.y"
                                    {
        exit_scope();
        (yyval.nodePtr) = mknode("block", NULL, (yyvsp[-2].nodePtr));
    }
#line 2509 "y.tab.c"
    break;

  case 74: /* scoped_block: scope_entry var BEGIN_TOKEN statements END  */
#line 694 "parser.y"
                                               {
        exit_scope();
        (yyval.nodePtr) = mknode("block", (yyvsp[-1].nodePtr), (yyvsp[-3].nodePtr));
    }
#line 2518 "y.tab.c"
    break;

  case 75: /* block_statement: scoped_block  */
#line 701 "parser.y"
                 { (yyval.nodePtr) = (yyvsp[0].nodePtr); }
#line 2524 "y.tab.c"
    break;

  case 76: /* return_statement: RETURN expression ';'  */
#line 705 "parser.y"
                          {(yyval.nodePtr) = mknode("return_val", (yyvsp[-1].nodePtr), NULL);}
#line 2530 "y.tab.c"
    break;

  case 77: /* return_statement: RETURN ';'  */
#line 706 "parser.y"
                 {(yyval.nodePtr) = mknode("return_void", NULL, NULL);}
#line 2536 "y.tab.c"
    break;

  case 78: /* function_call_statement: function_call ';'  */
#line 710 "parser.y"
                      {(yyval.nodePtr) = (yyvsp[-1].nodePtr);}
#line 2542 "y.tab.c"
    break;

  case 79: /* function_call_statement: IDENTIFIER ASSIGN function_call ';'  */
#line 711 "parser.y"
                                          {(yyval.nodePtr) = mknode("assign", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));}
#line 2548 "y.tab.c"
    break;

  case 80: /* function_call: CALL IDENTIFIER '(' ')'  */
#line 716 "parser.y"
    {
        if (!is_function_defined((yyvsp[-2].stringVal))) 
        {
            fprintf(stderr, "Semantic Error: Function '%s' used before its definition.\n", (yyvsp[-2].stringVal));
            exit(1);
        }
        int expected = get_function_param_count((yyvsp[-2].stringVal));
        if (expected != 0) 
        {
            fprintf(stderr, "Semantic Error: Function '%s' called with incorrect number of arguments (expected %d, got 0).\n", (yyvsp[-2].stringVal), expected);
            exit(1);
        }
        (yyval.nodePtr) = mknode("call", mknode((yyvsp[-2].stringVal), NULL, NULL), NULL);
    }
#line 2567 "y.tab.c"
    break;

  case 81: /* function_call: CALL IDENTIFIER '(' expr_list ')'  */
#line 731 "parser.y"
    {
        if (!is_function_defined((yyvsp[-3].stringVal))) 
        {
            fprintf(stderr, "Semantic Error: Function '%s' used before its definition.\n", (yyvsp[-3].stringVal));
            exit(1);
        }

        int count = 1;
        node* temp = (yyvsp[-1].nodePtr);
        while (temp && strcmp(temp->token, "expr_list") == 0) 
        {
            count++;
            temp = temp->right;
        }

        Symbol* func = find_function_symbol((yyvsp[-3].stringVal));
        if (!func) {
            fprintf(stderr, "Semantic Error: Function '%s' not found.\n", (yyvsp[-3].stringVal));
            exit(1);
        }

        if (func->param_count != count) {
            fprintf(stderr, "Semantic Error: Function '%s' called with incorrect number of arguments (expected %d, got %d).\n",
                    (yyvsp[-3].stringVal), func->param_count, count);
            exit(1);
        }

        node* expr = (yyvsp[-1].nodePtr);
        int i = 0;
        while (expr && i < func->param_count) {
            node* current_expr = (strcmp(expr->token, "expr_list") == 0) ? expr->left : expr;
            VarType actual_type = infer_type(current_expr);
            if (actual_type != func->param_types[i]) {
                fprintf(stderr, "Semantic Error: Function '%s', argument %d type mismatch (expected %s, got %s).\n",
                        (yyvsp[-3].stringVal), i + 1, type_to_string(func->param_types[i]), type_to_string(actual_type));
                exit(1);
            }
            expr = (strcmp(expr->token, "expr_list") == 0) ? expr->right : NULL;
            i++;
        }
        
        (yyval.nodePtr) = mknode("call", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));
    }
#line 2615 "y.tab.c"
    break;

  case 82: /* expr_list: expression  */
#line 777 "parser.y"
               {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2621 "y.tab.c"
    break;

  case 83: /* expr_list: expression ',' expr_list  */
#line 778 "parser.y"
                               {(yyval.nodePtr) = mknode("expr_list", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2627 "y.tab.c"
    break;

  case 84: /* expression: INTEGER  */
#line 782 "parser.y"
            {
        char int_str[20];
        sprintf(int_str, "%d", (yyvsp[0].intVal));
        (yyval.nodePtr) = mknode(int_str, NULL, NULL);
    }
#line 2637 "y.tab.c"
    break;

  case 85: /* expression: REAL  */
#line 787 "parser.y"
           {
        char real_str[30];
        sprintf(real_str, "%f", (yyvsp[0].realVal));
        (yyval.nodePtr) = mknode(real_str, NULL, NULL);
    }
#line 2647 "y.tab.c"
    break;

  case 86: /* expression: STRING_LITERAL  */
#line 792 "parser.y"
                     {(yyval.nodePtr) = mknode("STRING_LITERAL", mknode((yyvsp[0].stringVal), NULL, NULL), NULL);}
#line 2653 "y.tab.c"
    break;

  case 87: /* expression: CHAR_LITERAL  */
#line 793 "parser.y"
                   {
        char char_str[2];
        char_str[0] = (yyvsp[0].charVal);
        char_str[1] = '\0';
        (yyval.nodePtr) = mknode(char_str, NULL, NULL);
    }
#line 2664 "y.tab.c"
    break;

  case 88: /* expression: TRUE  */
#line 799 "parser.y"
           { (yyval.nodePtr) = mknode("TRUE", NULL, NULL); }
#line 2670 "y.tab.c"
    break;

  case 89: /* expression: FALSE  */
#line 800 "parser.y"
            { (yyval.nodePtr) = mknode("FALSE", NULL, NULL); }
#line 2676 "y.tab.c"
    break;

  case 90: /* expression: IDENTIFIER  */
#line 801 "parser.y"
                 {
        if (!is_variable_defined((yyvsp[0].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[0].stringVal));
            exit(1);
        }
        (yyval.nodePtr) = mknode((yyvsp[0].stringVal), NULL, NULL);
    }
#line 2688 "y.tab.c"
    break;

  case 91: /* expression: expression PLUS expression  */
#line 808 "parser.y"
                                 {(yyval.nodePtr) = mknode("+", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2694 "y.tab.c"
    break;

  case 92: /* expression: expression MINUS expression  */
#line 809 "parser.y"
                                  {(yyval.nodePtr) = mknode("-", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2700 "y.tab.c"
    break;

  case 93: /* expression: expression MULT expression  */
#line 810 "parser.y"
                                 {(yyval.nodePtr) = mknode("*", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2706 "y.tab.c"
    break;

  case 94: /* expression: expression DIV expression  */
#line 811 "parser.y"
                                {(yyval.nodePtr) = mknode("/", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2712 "y.tab.c"
    break;

  case 95: /* expression: expression MODULO expression  */
#line 812 "parser.y"
                                   {(yyval.nodePtr) = mknode("%", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2718 "y.tab.c"
    break;

  case 96: /* expression: MINUS expression  */
#line 813 "parser.y"
                       {(yyval.nodePtr) = mknode("unary-", (yyvsp[0].nodePtr), NULL);}
#line 2724 "y.tab.c"
    break;

  case 97: /* expression: AMPERSAND IDENTIFIER  */
#line 814 "parser.y"
                           {
        if (!is_variable_defined((yyvsp[0].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[0].stringVal));
            exit(1);
        }
        (yyval.nodePtr) = mknode("&", mknode((yyvsp[0].stringVal), NULL, NULL), NULL);
    }
#line 2736 "y.tab.c"
    break;

  case 98: /* expression: AMPERSAND IDENTIFIER '[' expression ']'  */
#line 822 "parser.y"
    {
        if (!is_variable_defined((yyvsp[-3].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-3].stringVal));
            exit(1);
        }
        VarType index_type = infer_type((yyvsp[-1].nodePtr));
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }

        (yyval.nodePtr) = mknode("&", mknode("index", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr)), NULL);
    }
#line 2754 "y.tab.c"
    break;

  case 99: /* expression: MULT IDENTIFIER  */
#line 835 "parser.y"
                      {
        if (!is_variable_defined((yyvsp[0].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[0].stringVal));
            exit(1);
        }
        (yyval.nodePtr) = mknode("deref", mknode((yyvsp[0].stringVal), NULL, NULL), NULL);
    }
#line 2766 "y.tab.c"
    break;

  case 100: /* expression: MULT expression  */
#line 842 "parser.y"
                      {(yyval.nodePtr) = mknode("*", (yyvsp[0].nodePtr), NULL);}
#line 2772 "y.tab.c"
    break;

  case 102: /* expression: NOT expression  */
#line 844 "parser.y"
    {
        VarType t = infer_type((yyvsp[0].nodePtr));
        if (t != TYPE_BOOL) {
            fprintf(stderr, "Semantic Error: '!' operator can only be used on bool, got '%s'.\n", type_to_string(t));
            exit(1);
        }
            (yyval.nodePtr) = mknode("not", (yyvsp[0].nodePtr), NULL);
    }
#line 2785 "y.tab.c"
    break;

  case 103: /* expression: '(' expression ')'  */
#line 852 "parser.y"
                         {(yyval.nodePtr) = (yyvsp[-1].nodePtr);}
#line 2791 "y.tab.c"
    break;

  case 104: /* expression: expression EQ expression  */
#line 853 "parser.y"
                               {(yyval.nodePtr) = mknode("==", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2797 "y.tab.c"
    break;

  case 105: /* expression: expression NE expression  */
#line 854 "parser.y"
                               {(yyval.nodePtr) = mknode("!=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2803 "y.tab.c"
    break;

  case 106: /* expression: expression GE expression  */
#line 855 "parser.y"
                               {(yyval.nodePtr) = mknode(">=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2809 "y.tab.c"
    break;

  case 107: /* expression: expression LE expression  */
#line 856 "parser.y"
                               {(yyval.nodePtr) = mknode("<=", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2815 "y.tab.c"
    break;

  case 108: /* expression: expression GT expression  */
#line 857 "parser.y"
                               {(yyval.nodePtr) = mknode(">", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2821 "y.tab.c"
    break;

  case 109: /* expression: expression LT expression  */
#line 858 "parser.y"
                               {(yyval.nodePtr) = mknode("<", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2827 "y.tab.c"
    break;

  case 110: /* expression: expression AND expression  */
#line 859 "parser.y"
                                {(yyval.nodePtr) = mknode("and", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2833 "y.tab.c"
    break;

  case 111: /* expression: expression OR expression  */
#line 860 "parser.y"
                               {(yyval.nodePtr) = mknode("or", (yyvsp[-2].nodePtr), (yyvsp[0].nodePtr));}
#line 2839 "y.tab.c"
    break;

  case 112: /* expression: IDENTIFIER '[' expression ']'  */
#line 862 "parser.y"
    {
        if (!is_variable_defined((yyvsp[-3].stringVal))) {
            fprintf(stderr, "Semantic Error: Variable '%s' used before its definition.\n", (yyvsp[-3].stringVal));
            exit(1);
        }

        VarType index_type = infer_type((yyvsp[-1].nodePtr));
        if (index_type != TYPE_INT) {
            fprintf(stderr, "Semantic Error: array index must be of type 'int', got '%s'.\n", type_to_string(index_type));
            exit(1);
        }

        Symbol* sym = symbol_table;
        VarType base_type = TYPE_INVALID;
        while (sym) {
            if (!sym->is_function && strcmp(sym->name, (yyvsp[-3].stringVal)) == 0) {
                base_type = sym->type;
                break;
            }
            sym = sym->next;
        }

        if (base_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: index operator '[]' is only allowed on strings, got '%s'.\n", type_to_string(base_type));
            exit(1);
        }

        (yyval.nodePtr) = mknode("index", mknode((yyvsp[-3].stringVal), NULL, NULL), (yyvsp[-1].nodePtr));
    }
#line 2873 "y.tab.c"
    break;

  case 113: /* expression: '|' expression '|'  */
#line 891 "parser.y"
                         {
        VarType inner_type = infer_type((yyvsp[-1].nodePtr));
        if (inner_type != TYPE_STRING) {
            fprintf(stderr, "Semantic Error: absolute value operator '||' can only be used on strings, got '%s'.\n", type_to_string(inner_type));
            exit(1);
        }
        (yyval.nodePtr) = mknode("strlen", (yyvsp[-1].nodePtr), NULL);  // or name it "abs" if preferred
    }
#line 2886 "y.tab.c"
    break;

  case 114: /* expression: function_call  */
#line 899 "parser.y"
                    {(yyval.nodePtr) = (yyvsp[0].nodePtr);}
#line 2892 "y.tab.c"
    break;


#line 2896 "y.tab.c"

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

#line 902 "parser.y"


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

int is_function_defined(const char* name) {
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->is_function && strcmp(sym->name, name) == 0) {
            return 1; // Found
        }
        sym = sym->next;
    }
    return 0; // Not found
}

int is_variable_defined(const char* name) {
    Symbol* sym = symbol_table;
    while (sym) {
        if (!sym->is_function && strcmp(sym->name, name) == 0) {
            return 1;
        }
        sym = sym->next;
    }
    return 0;
}

int get_function_param_count(const char* name) 
{
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->is_function && strcmp(sym->name, name) == 0) {
            return sym->param_count;
        }
        sym = sym->next;
    }
    return -1; // Not found
}

int count_params(node* param_node) {
    int count = 0;
    node* temp = param_node;
    while (temp) {
        count++;
        temp = temp->right;
    }
    return count;
}

void extract_param_types(node* param_node, VarType* types) 
{
    int i = 0;

    void helper(node* n) {
        if (!n || i >= MAX_PARAMS) return;

        if (strcmp(n->token, "PARAMS") == 0) {
            helper(n->left);
            helper(n->right);
        } else {
            if (n->left && n->left->token)
                types[i++] = string_to_type(n->left->token);
            else
                types[i++] = TYPE_INVALID;
        }
    }

    helper(param_node);
}

VarType infer_type(node* expr) {
    if (!expr || !expr->token) return TYPE_INVALID;

    // Boolean literals
    if (strcmp(expr->token, "TRUE") == 0 || strcmp(expr->token, "FALSE") == 0) {
        return TYPE_BOOL;
    }

    // Integer literal
    if (strspn(expr->token, "0123456789") == strlen(expr->token)) {
        return TYPE_INT;
    }

    // Real literal (e.g., "3.14")
    if (strchr(expr->token, '.') != NULL) {
        return TYPE_REAL;
    }
    /*
    if (strlen(expr->token) == 1 && isprint(expr->token[0])) {
        return TYPE_CHAR;
    }
    */
    // String literal node
    if (strcmp(expr->token, "STRING_LITERAL") == 0 && expr->left && expr->left->token) {
        return TYPE_STRING;
    }

    // Unary minus
    if (strcmp(expr->token, "unary-") == 0 && expr->left) {
        VarType t = infer_type(expr->left);
        if (t == TYPE_INT || t == TYPE_REAL) return t;
        fprintf(stderr, "Semantic Error: unary '-' expects int or real, got '%s'.\n", type_to_string(t));
        exit(1);
    }

    // Logical NOT
    if (strcmp(expr->token, "not") == 0 && expr->left) {
        VarType t = infer_type(expr->left);
        if (t == TYPE_BOOL) return TYPE_BOOL;
        fprintf(stderr, "Semantic Error: 'not' expects bool, got '%s'.\n", type_to_string(t));
        exit(1);
    }

    // Absolute value
    if (strcmp(expr->token, "|") == 0 && expr->left) {
        VarType t = infer_type(expr->left);
        if (t == TYPE_INT || t == TYPE_REAL || t == TYPE_STRING) return TYPE_INT;
        fprintf(stderr, "Semantic Error: '|' operator expects int, real, or string, got '%s'.\n", type_to_string(t));
        exit(1);
    }

    // Binary arithmetic operators
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if ((l == TYPE_INT || l == TYPE_REAL) && (r == TYPE_INT || r == TYPE_REAL)) {
            return (l == TYPE_REAL || r == TYPE_REAL) ? TYPE_REAL : TYPE_INT;
        }
        fprintf(stderr, "Semantic Error: '%s' operands must be int or real, got '%s' and '%s'.\n",
                expr->token, type_to_string(l), type_to_string(r));
        exit(1);
    }

    if (strcmp(expr->token, "%") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if (l == TYPE_INT && r == TYPE_INT) return TYPE_INT;
        fprintf(stderr, "Semantic Error: '%%' operands must be int, got '%s' and '%s'.\n", type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Comparison operators
    if (strcmp(expr->token, ">") == 0 || strcmp(expr->token, "<") == 0 ||
        strcmp(expr->token, ">=") == 0 || strcmp(expr->token, "<=") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if ((l == TYPE_INT || l == TYPE_REAL) && (r == TYPE_INT || r == TYPE_REAL)) {
            return TYPE_BOOL;
        }
        fprintf(stderr, "Semantic Error: Comparison requires int or real operands, got '%s' and '%s'.\n",
                type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Equality
    if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if (l == r) return TYPE_BOOL;
        fprintf(stderr, "Semantic Error: Equality operands must match, got '%s' and '%s'.\n",
                type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Absolute value or string length operator (|expr| becomes strlen node)
    if (strcmp(expr->token, "strlen") == 0) {
        VarType inner = infer_type(expr->left);
        if (inner == TYPE_STRING)
            return TYPE_INT;
        return TYPE_INVALID;
    }

    // Logical operators
    if (strcmp(expr->token, "and") == 0 || strcmp(expr->token, "or") == 0) {
        VarType l = infer_type(expr->left);
        VarType r = infer_type(expr->right);
        if (l == TYPE_BOOL && r == TYPE_BOOL) return TYPE_BOOL;
        fprintf(stderr, "Semantic Error: Logical '%s' expects bool operands, got '%s' and '%s'.\n",
                expr->token, type_to_string(l), type_to_string(r));
        exit(1);
    }

    // Pointer dereference
    if (strcmp(expr->token, "deref") == 0 && expr->left) {
        VarType inner = infer_type(expr->left);
        switch (inner) {
            case TYPE_INT_PTR: return TYPE_INT;
            case TYPE_CHAR_PTR: return TYPE_CHAR;
            case TYPE_REAL_PTR: return TYPE_REAL;
            default:
                fprintf(stderr, "Semantic Error: unary '*' can only be applied to pointer types, got '%s'.\n", type_to_string(inner));
                exit(1);
        }
    }

    // Address-of
    if (strcmp(expr->token, "&") == 0 && expr->left) {
        VarType inner = infer_type(expr->left);
        if (inner == TYPE_INT) return TYPE_INT_PTR;
        if (inner == TYPE_CHAR) return TYPE_CHAR_PTR;
        if (inner == TYPE_REAL) return TYPE_REAL_PTR;
        fprintf(stderr, "Semantic Error: '&' expects int, char or real type, got '%s'.\n", type_to_string(inner));
        exit(1);
    }

    // Indexing
    if (strcmp(expr->token, "index") == 0 && expr->left) {
        return infer_type(expr->left);
    }

    // Function call
    if (strcmp(expr->token, "call") == 0 && expr->left && expr->left->token) {
        Symbol* sym = find_function_symbol(expr->left->token);
        if (sym) return sym->return_type;
    }

    // Variable lookup
    Symbol* sym = symbol_table;
    while (sym) {
        if (!sym->is_function && strcmp(sym->name, expr->token) == 0) {
            return sym->type;
        }
        sym = sym->next;
    }

    if (strcmp(expr->token, "&") == 0 && expr->left) {
        VarType inner_type = TYPE_INVALID;

        if (strcmp(expr->left->token, "index") == 0) {
            // Check if this is &something[index]
            node* base = expr->left->left;
            Symbol* sym = symbol_table;
            while (sym) {
                if (!sym->is_function && strcmp(sym->name, base->token) == 0) {
                    inner_type = sym->type;
                    break;
                }
                sym = sym->next;
            }

            if (inner_type != TYPE_STRING) {
                fprintf(stderr, "Semantic Error: '&' can only be applied to indexed strings, got '%s'.\n", type_to_string(inner_type));
                exit(1);
            }

            return TYPE_CHAR_PTR;
        } else {
            // Check for &x
            Symbol* sym = symbol_table;
            while (sym) {
                if (!sym->is_function && strcmp(sym->name, expr->left->token) == 0) {
                    inner_type = sym->type;
                    break;
                }
                sym = sym->next;
            }

            if (inner_type == TYPE_INT) return TYPE_INT_PTR;
            if (inner_type == TYPE_CHAR) return TYPE_CHAR_PTR;
            if (inner_type == TYPE_REAL) return TYPE_REAL_PTR;

            fprintf(stderr, "Semantic Error: '&' operator can only be applied to variables of type int, char, or real, got '%s'.\n", type_to_string(inner_type));
            exit(1);
        }
    }

    return TYPE_INVALID;
}




const char* type_to_string(VarType type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_CHAR: return "char";
        case TYPE_REAL: return "real";
        case TYPE_STRING: return "string";
        case TYPE_BOOL: return "bool";
        case TYPE_INT_PTR: return "int*";
        case TYPE_CHAR_PTR: return "char*";
        case TYPE_REAL_PTR: return "real*";
        default: return "unknown";
    }
}

Symbol* find_function_symbol(const char* name) {
    Symbol* sym = symbol_table;
    while (sym) {
        if (sym->is_function && strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    return NULL;
}
