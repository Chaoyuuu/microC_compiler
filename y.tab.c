/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "compiler_hw3.y" /* yacc.c:339  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "y.tab.h"

int table_depth = 0;
const char *type_f = "function";
const char *type_p = "parameter";
const char *type_v = "variable";

struct Entry{
    struct Entry * entry_next;
    struct Entry * entry_pre;

    int index;
    char name[20];     
    char kind[20];
    char type[20];
    int scope;
    char attribute[50];

    Value entry_val;
};

struct Table{
    int table_depth;
    struct Entry * entry_header;
    struct Entry * entry_current;
    struct Table * pre;
};

struct Table *table_header = NULL;
struct Table *table_current = NULL;
struct Table *table_dump = NULL;

struct Func{
    char f_name[50];
    Symbol_type f_type;
    struct Func * f_pre;
    int f_count;
    char f_attr[50];
};

struct Func * f_header = NULL;
struct Func * f_current = NULL;

extern int yylineno;
extern int yylex();
extern char* yytext;   // Get current token from lex
extern char buf[500];  // Get current code line from lex
extern char syntax_buf[500];
extern int error_flag; //1.redefined 2.undefined
extern int syntax_flag;
extern char error_msg[500];
extern int dump_flag;
extern void yyerror(char *s);

int func_flag = 0;
int remove_flag = 0;


// int cast_flag = 0;          // flag for arith casting
char func_buf[5000];         // buf for jasmin function
char func_para[50];         // buf for function parameter
char func_para_2[50];
char label_buf[500];        // buf for if-else {compond statement}
int label_index = 0;        // index of if-else label
int func_input_num = 0;     // index of func_para_type[]
Value func_para_type[10]; // buf for function input parameter
Value trash_var;     // for trash value parameter
FILE *file;         // To generate .j file for Jasmin


/* Symbol table function - you can add new function if needed. */
void get_attribute(struct Entry * tmp);
void create_symbol();
void lookup_symbol();
void lookup_function();
void insert_symbol();
void dump_symbol();
void dump_table();


/* expression function */
Value switch_mul_op();
Value switch_addition_op();
Value switch_postfix_op();
Value switch_assign_op();
Value switch_relation_op();
Value get_id_value();    //get id type & value
Value get_id_entry();    //get id type structure

//arithmetic
Value mul_arith(Value v1, Value v2);
Value div_arith(Value v1, Value v2);
Value mod_arith(Value v1, Value v2);
Value add_arith(Value v1, Value v2);
Value minus_arith(Value v1, Value v2);

//error detecting && tool
Value gencode_funcall();  //function checking and return is_arith & type
int func_return_checking();
void create_func_table();
void set_func_para();

//code generation function
Value gencode_global_1();
Value gencode_global_2();
Value gencode_local_1();
Value gencode_local_2();
Value gencode_parameter();
void gencode_func();
void gencode_print();
void gencode_return();
void gencode_iload();
void gencode_istore();
void gencode_if_arith();
void gencode_while();


#line 189 "y.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "y.tab.h".  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    BOOL = 258,
    FLOAT = 259,
    INT = 260,
    VOID = 261,
    STRING = 262,
    INC_OP = 263,
    DEC_OP = 264,
    GE_OP = 265,
    LE_OP = 266,
    EQ_OP = 267,
    NE_OP = 268,
    AND_OP = 269,
    OR_OP = 270,
    ADD_ASSIGN = 271,
    SUB_ASSIGN = 272,
    MUL_ASSIGN = 273,
    DIV_ASSIGN = 274,
    MOD_ASSIGN = 275,
    PRINT = 276,
    RETURN = 277,
    IF = 278,
    ELSE = 279,
    FOR = 280,
    WHILE = 281,
    SEMICOLON = 282,
    QUOTA = 283,
    I_CONST = 284,
    F_CONST = 285,
    STRING_CONST = 286,
    ID = 287,
    TRUE = 288,
    FALSE = 289
  };
#endif
/* Tokens.  */
#define BOOL 258
#define FLOAT 259
#define INT 260
#define VOID 261
#define STRING 262
#define INC_OP 263
#define DEC_OP 264
#define GE_OP 265
#define LE_OP 266
#define EQ_OP 267
#define NE_OP 268
#define AND_OP 269
#define OR_OP 270
#define ADD_ASSIGN 271
#define SUB_ASSIGN 272
#define MUL_ASSIGN 273
#define DIV_ASSIGN 274
#define MOD_ASSIGN 275
#define PRINT 276
#define RETURN 277
#define IF 278
#define ELSE 279
#define FOR 280
#define WHILE 281
#define SEMICOLON 282
#define QUOTA 283
#define I_CONST 284
#define F_CONST 285
#define STRING_CONST 286
#define ID 287
#define TRUE 288
#define FALSE 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 128 "compiler_hw3.y" /* yacc.c:355  */

    
    Value val;
    Operator op;


#line 304 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 321 "y.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   189

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  48
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  39
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    42,     2,     2,
      36,    37,    40,    45,    47,    46,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      44,    35,    43,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,    39,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   159,   159,   160,   161,   165,   166,   167,   168,   169,
     173,   178,   186,   191,   197,   198,   199,   200,   204,   204,
     207,   206,   210,   209,   216,   217,   215,   230,   234,   235,
     239,   240,   244,   245,   249,   250,   254,   255,   259,   260,
     260,   262,   266,   267,   271,   272,   273,   277,   278,   279,
     280,   281,   282,   286,   287,   291,   292,   293,   294,   295,
     296,   300,   301,   305,   305,   317,   317,   332,   332,   334,
     334,   339,   341,   346,   347,   351,   356,   364,   365,   366,
     367,   368,   369,   380,   381,   382,   383,   384
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOL", "FLOAT", "INT", "VOID", "STRING",
  "INC_OP", "DEC_OP", "GE_OP", "LE_OP", "EQ_OP", "NE_OP", "AND_OP",
  "OR_OP", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN",
  "MOD_ASSIGN", "PRINT", "RETURN", "IF", "ELSE", "FOR", "WHILE",
  "SEMICOLON", "QUOTA", "I_CONST", "F_CONST", "STRING_CONST", "ID", "TRUE",
  "FALSE", "'='", "'('", "')'", "'{'", "'}'", "'*'", "'/'", "'%'", "'>'",
  "'<'", "'+'", "'-'", "','", "$accept", "program", "stat", "declaration",
  "print_func", "compound_stat", "expression_stat", "selection_statement",
  "$@1", "$@2", "$@3", "while_statement", "$@4", "$@5", "expression",
  "assign_expr", "comparison_expr", "add_expr", "mul_expr", "postfix_expr",
  "parenthesis_expr", "$@6", "postfix_op", "mul_op", "relation_op",
  "addition_op", "assign_op", "return_statement", "function_declaration",
  "$@7", "$@8", "declarator", "$@9", "$@10", "identifier_list",
  "declarator2", "identifier_list2", "initializer", "type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,    61,    40,    41,   123,   125,
      42,    47,    37,    62,    60,    43,    45,    44
};
# endif

#define YYPACT_NINF -103

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-103)))

#define YYTABLE_NINF -70

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      12,  -103,    88,  -103,  -103,  -103,  -103,  -103,  -103,   -28,
     105,  -103,  -103,   -20,  -103,  -103,   -22,  -103,  -103,   146,
      51,  -103,  -103,  -103,  -103,  -103,     1,  -103,     5,   -13,
      16,   -15,    56,  -103,    67,  -103,  -103,  -103,     7,   155,
    -103,    22,    15,    34,    50,    63,    49,   124,    77,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,   146,  -103,  -103,  -103,
    -103,  -103,  -103,   146,  -103,  -103,   146,  -103,  -103,  -103,
     146,  -103,  -103,  -103,    26,  -103,    64,  -103,   146,   146,
    -103,   136,  -103,  -103,  -103,  -103,    66,    16,   -15,    56,
    -103,  -103,   146,    68,    79,    80,    71,    75,  -103,  -103,
     -27,    83,  -103,    86,    60,    78,    66,    96,  -103,    66,
    -103,  -103,   146,   146,  -103,     0,    93,  -103,  -103,  -103,
    -103,    66,  -103,    99,  -103,    60,  -103,  -103,    66,   108,
    -103,  -103
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     3,     0,     1,    85,    84,    83,    87,    86,     0,
       0,    18,    24,     0,    77,    78,    82,    80,    81,     0,
       0,     2,     5,     8,     6,     7,    14,    15,     0,    27,
      28,    30,    32,    34,    36,    17,     9,    38,     0,     0,
      62,     0,     0,     0,     0,     0,     0,     0,    20,    16,
      55,    56,    57,    58,    59,    60,     0,    49,    50,    51,
      52,    47,    48,     0,    53,    54,     0,    44,    45,    46,
       0,    42,    43,    37,     0,    82,     0,    61,     0,     0,
      79,     0,    40,    41,    13,    22,     0,    29,    31,    33,
      35,    11,     0,    67,    63,     0,     0,     0,    74,    76,
       0,     0,    21,     0,     0,     0,     0,     0,    12,     0,
      25,    73,     0,     0,    10,     0,     0,    70,    64,    66,
      19,     0,    75,     0,    68,     0,    72,    26,     0,     0,
      23,    71
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -103,   122,  -103,  -103,  -103,   -85,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,   -10,  -103,    87,    81,    82,    85,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,  -103,
    -103,  -103,  -103,  -103,  -103,  -103,  -103,   110,  -102
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,    21,    22,    23,    24,    25,    26,    42,    86,
     101,    27,    43,   121,    28,    29,    30,    31,    32,    33,
      34,    45,    73,    70,    63,    66,    56,    35,    36,   106,
     107,    94,   104,   105,   115,    82,   100,    37,    38
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      41,   102,   116,    50,    51,    52,    53,    54,    39,    46,
     111,    44,    -4,     1,   -39,    -4,    -4,    -4,    -4,    -4,
     112,   118,    55,   129,   120,    48,    57,    58,    59,    60,
      64,    65,    49,    -4,    -4,    -4,   127,   124,    -4,    74,
      -4,    -4,    -4,   130,    -4,    -4,    -4,   125,    -4,    77,
      -4,    78,     1,    91,    -4,    -4,    -4,    -4,    -4,    61,
      62,    92,    93,     4,     5,     6,     7,     8,    96,    97,
      79,    99,    -4,    -4,    -4,    71,    72,    -4,    80,    -4,
      -4,    -4,   103,    -4,    -4,    -4,    83,    -4,     3,    -4,
      -4,     4,     5,     6,     7,     8,    67,    68,    69,    81,
      85,    95,   122,   123,    20,   -69,   -65,   108,   109,     9,
      10,    11,   110,   114,    12,   117,    13,    14,    15,   113,
      16,    17,    18,   119,    19,   126,    20,     4,     5,     6,
       7,     8,    40,    13,    14,    15,   128,    16,    17,    18,
     131,    19,    47,    87,    88,     9,    10,    11,    89,    76,
      12,     0,    13,    14,    15,    90,    16,    17,    18,     0,
      19,     0,    20,    84,    13,    14,    15,     0,    16,    17,
      18,     0,    19,    98,    13,    14,    15,     0,    16,    17,
      18,     0,    19,    13,    14,    15,     0,    75,    17,    18
};

static const yytype_int16 yycheck[] =
{
      10,    86,   104,    16,    17,    18,    19,    20,    36,    19,
      37,    31,     0,     1,    36,     3,     4,     5,     6,     7,
      47,   106,    35,   125,   109,    24,    10,    11,    12,    13,
      45,    46,    27,    21,    22,    23,   121,    37,    26,    32,
      28,    29,    30,   128,    32,    33,    34,    47,    36,    27,
      38,    36,     1,    27,     3,     4,     5,     6,     7,    43,
      44,    35,    36,     3,     4,     5,     6,     7,    78,    79,
      36,    81,    21,    22,    23,     8,     9,    26,    28,    28,
      29,    30,    92,    32,    33,    34,    37,    36,     0,    38,
      39,     3,     4,     5,     6,     7,    40,    41,    42,    36,
      23,    37,   112,   113,    38,    37,    27,    27,    37,    21,
      22,    23,    37,    27,    26,    37,    28,    29,    30,    36,
      32,    33,    34,    27,    36,    32,    38,     3,     4,     5,
       6,     7,    27,    28,    29,    30,    37,    32,    33,    34,
      32,    36,    20,    56,    63,    21,    22,    23,    66,    39,
      26,    -1,    28,    29,    30,    70,    32,    33,    34,    -1,
      36,    -1,    38,    39,    28,    29,    30,    -1,    32,    33,
      34,    -1,    36,    37,    28,    29,    30,    -1,    32,    33,
      34,    -1,    36,    28,    29,    30,    -1,    32,    33,    34
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    49,     0,     3,     4,     5,     6,     7,    21,
      22,    23,    26,    28,    29,    30,    32,    33,    34,    36,
      38,    50,    51,    52,    53,    54,    55,    59,    62,    63,
      64,    65,    66,    67,    68,    75,    76,    85,    86,    36,
      27,    62,    56,    60,    31,    69,    62,    49,    24,    27,
      16,    17,    18,    19,    20,    35,    74,    10,    11,    12,
      13,    43,    44,    72,    45,    46,    73,    40,    41,    42,
      71,     8,     9,    70,    32,    32,    85,    27,    36,    36,
      28,    36,    83,    37,    39,    23,    57,    64,    65,    66,
      67,    27,    35,    36,    79,    37,    62,    62,    37,    62,
      84,    58,    53,    62,    80,    81,    77,    78,    27,    37,
      37,    37,    47,    36,    27,    82,    86,    37,    53,    27,
      53,    61,    62,    62,    37,    47,    32,    53,    37,    86,
      53,    32
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    48,    49,    49,    49,    50,    50,    50,    50,    50,
      51,    51,    52,    53,    54,    54,    54,    54,    56,    55,
      57,    55,    58,    55,    60,    61,    59,    62,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    69,
      68,    68,    70,    70,    71,    71,    71,    72,    72,    72,
      72,    72,    72,    73,    73,    74,    74,    74,    74,    74,
      74,    75,    75,    77,    76,    78,    76,    80,    79,    81,
      79,    82,    82,    83,    83,    84,    84,    85,    85,    85,
      85,    85,    85,    86,    86,    86,    86,    86
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     0,     1,     1,     1,     1,     1,
       5,     3,     5,     3,     1,     1,     2,     1,     0,     6,
       0,     4,     0,     8,     0,     0,     7,     1,     1,     3,
       1,     3,     1,     3,     1,     3,     1,     2,     1,     0,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     2,     0,     5,     0,     5,     0,     4,     0,
       3,     4,     2,     3,     2,     3,     1,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 10:
#line 173 "compiler_hw3.y" /* yacc.c:1646  */
    { lookup_symbol((yyvsp[-3].val).id_name, 1); 
                                          if(error_flag != 1){
                                            insert_symbol((yyvsp[-4].val), (yyvsp[-3].val), type_v, (yyvsp[-1].val));
                                          }
                                        }
#line 1514 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 178 "compiler_hw3.y" /* yacc.c:1646  */
    { lookup_symbol((yyvsp[-1].val).id_name, 1); 
                          if(error_flag != 1){
                            insert_symbol((yyvsp[-2].val), (yyvsp[-1].val), type_v, trash_var); 
                          }
                        }
#line 1524 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 186 "compiler_hw3.y" /* yacc.c:1646  */
    { gencode_print((yyvsp[-2].val)); }
#line 1530 "y.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 193 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_table(); dump_flag = 1;}
#line 1536 "y.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 197 "compiler_hw3.y" /* yacc.c:1646  */
    { /* printf("&&&&&&&& is select\n"); */}
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 199 "compiler_hw3.y" /* yacc.c:1646  */
    { /* printf("&&&&&&&&is  expression\n"); */}
#line 1548 "y.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 204 "compiler_hw3.y" /* yacc.c:1646  */
    { create_symbol(); }
#line 1554 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 207 "compiler_hw3.y" /* yacc.c:1646  */
    { create_symbol(); }
#line 1560 "y.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 210 "compiler_hw3.y" /* yacc.c:1646  */
    { create_symbol(); }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 216 "compiler_hw3.y" /* yacc.c:1646  */
    { create_symbol(); }
#line 1572 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 217 "compiler_hw3.y" /* yacc.c:1646  */
    { gencode_while((yyvsp[-1].val)); }
#line 1578 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 218 "compiler_hw3.y" /* yacc.c:1646  */
    { char ttmp[50]; 
                              memset(ttmp, 0, sizeof(ttmp));
                              sprintf(ttmp, "\tgoto label_%d\n",label_index - 2 );
                              strcat(func_buf, ttmp);
                              memset(ttmp, 0, sizeof(ttmp));
                              sprintf(ttmp, "label_%d:\n",label_index );
                              strcat(func_buf, ttmp);
                            }
#line 1591 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 234 "compiler_hw3.y" /* yacc.c:1646  */
    {}
#line 1597 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 235 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = switch_assign_op((yyvsp[-2].val), (yyvsp[-1].op), (yyvsp[0].val)); }
#line 1603 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 239 "compiler_hw3.y" /* yacc.c:1646  */
    {}
#line 1609 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 240 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = switch_relation_op((yyvsp[-2].val), (yyvsp[-1].op), (yyvsp[0].val)); }
#line 1615 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 244 "compiler_hw3.y" /* yacc.c:1646  */
    {}
#line 1621 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 245 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = switch_addition_op((yyvsp[-2].val), (yyvsp[-1].op), (yyvsp[0].val)); }
#line 1627 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 249 "compiler_hw3.y" /* yacc.c:1646  */
    {}
#line 1633 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 250 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = switch_mul_op((yyvsp[-2].val), (yyvsp[-1].op), (yyvsp[0].val)); }
#line 1639 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 254 "compiler_hw3.y" /* yacc.c:1646  */
    {}
#line 1645 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 255 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = switch_postfix_op((yyvsp[-1].val), (yyvsp[0].op)); }
#line 1651 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 259 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[0].val); }
#line 1657 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 260 "compiler_hw3.y" /* yacc.c:1646  */
    { lookup_function((yyvsp[0].val).id_name, 1); }
#line 1663 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 261 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = gencode_funcall((yyvsp[-2].val)); }
#line 1669 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 262 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = (yyvsp[-1].val); }
#line 1675 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 266 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = INC_OPT; }
#line 1681 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 267 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = DEC_OPT; }
#line 1687 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 271 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = MUL_OPT; }
#line 1693 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 272 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = DIV_OPT; }
#line 1699 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 273 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = MOD_OPT; }
#line 1705 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 277 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = MORE_OPT; }
#line 1711 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 278 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = LESS_OPT; }
#line 1717 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 279 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = GE_OPT; }
#line 1723 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 280 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = LE_OPT; }
#line 1729 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 281 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = EQ_OPT; }
#line 1735 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 282 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = NE_OPT; }
#line 1741 "y.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 286 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = ADD_OPT; }
#line 1747 "y.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 287 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = MINUS_OPT; }
#line 1753 "y.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 291 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = ADD_ASSIGN_OPT; }
#line 1759 "y.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 292 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = SUB_ASSIGN_OPT; }
#line 1765 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 293 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = MUL_ASSIGN_OPT; }
#line 1771 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 294 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = DIV_ASSIGN_OPT; }
#line 1777 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 295 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = MOD_ASSIGN_OPT; }
#line 1783 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 296 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.op) = ASSIGN_OPT; }
#line 1789 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 300 "compiler_hw3.y" /* yacc.c:1646  */
    { gencode_return((yyvsp[-1].val)); }
#line 1795 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 301 "compiler_hw3.y" /* yacc.c:1646  */
    { gencode_return(trash_var); }
#line 1801 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 305 "compiler_hw3.y" /* yacc.c:1646  */
    { func_return_checking((yyvsp[-2].val), (yyvsp[-1].val), 0); }
#line 1807 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 306 "compiler_hw3.y" /* yacc.c:1646  */
    { // lookup_function($2.id_name, 3);      //declare

                                          int a = 1;
                                          if(error_flag != 1)
                                              a = func_return_checking((yyvsp[-4].val), (yyvsp[-3].val), 0); 
                                          if(a == 0){
                                              insert_symbol((yyvsp[-4].val), (yyvsp[-3].val), type_f, trash_var);
                                          }
                                          gencode_func((yyvsp[-4].val), (yyvsp[-3].val));

                                        }
#line 1823 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 317 "compiler_hw3.y" /* yacc.c:1646  */
    { func_return_checking((yyvsp[-2].val), (yyvsp[-1].val), 0); }
#line 1829 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 318 "compiler_hw3.y" /* yacc.c:1646  */
    { dump_table();                             //define
                                      // lookup_function($2.id_name, 2); 
                                    //   int a = func_return_checking($1, $2, 1);
                                      int a = 1;
                                      if(error_flag != 1)
                                            a = func_return_checking((yyvsp[-4].val), (yyvsp[-3].val), 0); 
                                      if(error_flag != 1 && a == 0){
                                            insert_symbol((yyvsp[-4].val), (yyvsp[-3].val), type_f, trash_var);
                                      }
                                      f_current->f_count = 1;
                                    }
#line 1845 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 332 "compiler_hw3.y" /* yacc.c:1646  */
    { create_symbol(); }
#line 1851 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 334 "compiler_hw3.y" /* yacc.c:1646  */
    { create_symbol(); }
#line 1857 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 339 "compiler_hw3.y" /* yacc.c:1646  */
    { insert_symbol((yyvsp[-1].val), (yyvsp[0].val), type_p, trash_var); 
                                     set_func_para((yyvsp[-1].val), 1);}
#line 1864 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 342 "compiler_hw3.y" /* yacc.c:1646  */
    { insert_symbol((yyvsp[-1].val), (yyvsp[0].val), type_p, trash_var); set_func_para((yyvsp[-1].val), 0);}
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 351 "compiler_hw3.y" /* yacc.c:1646  */
    { if((yyvsp[0].val).symbol_type == ID_Type){
                                            func_para_type[func_input_num++] = get_id_entry((yyvsp[0].val));
                                          }else
                                            func_para_type[func_input_num++] = (yyvsp[0].val);
                                        }
#line 1880 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 356 "compiler_hw3.y" /* yacc.c:1646  */
    { if((yyvsp[0].val).symbol_type == ID_Type){
                        func_para_type[func_input_num++] = get_id_entry((yyvsp[0].val));
                      }else
                        func_para_type[func_input_num++] = (yyvsp[0].val); 
                    }
#line 1890 "y.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 364 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1896 "y.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 365 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 366 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1908 "y.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 367 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1914 "y.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 368 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1920 "y.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 369 "compiler_hw3.y" /* yacc.c:1646  */
    { lookup_symbol((yyvsp[0].val).id_name, 2); (yyval.val) = yylval.val; }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 380 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1932 "y.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 381 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1938 "y.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 382 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1944 "y.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 383 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 384 "compiler_hw3.y" /* yacc.c:1646  */
    { (yyval.val) = yylval.val; }
#line 1956 "y.tab.c" /* yacc.c:1646  */
    break;


#line 1960 "y.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 387 "compiler_hw3.y" /* yacc.c:1906  */


/* C code section */
int main(int argc, char** argv)
{
    yylineno = 0;

    //init
    memset(func_buf, 0, sizeof(func_buf));  //init func_buf
    trash_var.symbol_type = T_Type;         //init trash_var

    file = fopen("compiler_hw3.j","w");
    fprintf(file,   ".class public compiler_hw3\n"
                    ".super java/lang/Object\n");
             

    create_symbol();
    yyparse();

    if(syntax_flag != 0){
        // print syntax error msg
        printf("\n|-----------------------------------------------|\n");
        printf("| Error found in line %d: %s\n", yylineno, syntax_buf);
        printf("| %s","syntax error");
        printf("\n|-----------------------------------------------|\n\n");
        return 0;
    } 


    if(remove_flag == 1){  //delete .j
        remove("compiler_hw3.j");
    }
    
    dump_table();
    dump_symbol();
    printf("\nTotal lines: %d \n",yylineno);

    fclose(file);

    return 0;
}

void yyerror(char *s)
{
    remove_flag = 1;
    if(!strcmp(s, "syntax error")){
        // printf("in syntax error");
        memset(syntax_buf, 0, sizeof(syntax_buf));
        strcpy(syntax_buf, buf);
        syntax_flag = 1;
        // printf(" btn %s, num = %d",buf, yylineno);
        
        return;
    }

    printf("\n|-----------------------------------------------|\n");
    printf("| Error found in line %d: %s\n", yylineno, buf);
    printf("| %s",s);
    printf("\n|-----------------------------------------------|\n\n");
    
}

void create_symbol() {
    //initialize symbol_table
    struct Table * ptr = malloc(sizeof(struct Table));

    ptr->table_depth = table_depth++;   //depth == scope
    ptr->entry_header = NULL;
    ptr->entry_current = ptr->entry_header;
    ptr->pre = table_current;

    table_current = ptr;

    if(table_header == NULL){
        table_header = table_current;
    }

    // printf("\n----in create_symbol, depth = %d, current = %p----\n", ptr->table_depth, table_current);
}

void insert_symbol(Value _type, Value _ID, char* k, Value _expr) {
   
    struct Table *ptr = table_current; 
    struct Entry *e_ptr = malloc(sizeof(struct Entry));

    Symbol_type t = _type.symbol_type;
    char *n = _ID.id_name;
    
    // printf("\n----in insert_symbol, %d, %s, %s, %d----\n", t, n, k, ptr->table_depth);

    if(ptr->entry_header == NULL){
        ptr->entry_header = e_ptr;
        e_ptr->entry_pre = NULL;
        e_ptr->entry_next = NULL;
        e_ptr->index = 0;
    }else{
        e_ptr->entry_pre = ptr->entry_current;
        ptr->entry_current->entry_next = e_ptr; 
        e_ptr->index = (ptr->entry_current->index) + 1;
    }
    
    ptr->entry_current = e_ptr;
    //initialize entry
    e_ptr->entry_next = NULL;
    e_ptr->scope = ptr->table_depth;
    memset(e_ptr->type, 0, sizeof(e_ptr->type));
    memset(e_ptr->kind, 0, sizeof(e_ptr->kind));
    memset(e_ptr->name, 0, sizeof(e_ptr->name));
    memset(e_ptr->attribute, 0, sizeof(e_ptr->attribute));

    //set symbol table
    strcpy(e_ptr->kind, k);
    strcpy(e_ptr->name, n);  

    switch (t){
        case V_Type:
            strcpy(e_ptr->type, "void");
            break;
        case I_Type:
            strcpy(e_ptr->type, "int");
            break;
        case F_Type:
            strcpy(e_ptr->type, "float");
            break;
        case S_Type:
            strcpy(e_ptr->type, "String");
            break;
        /*    
        case ID_Type:
            strcpy(e_ptr->type, "ID");
            break;
        */
        case B_Type:
            strcpy(e_ptr->type, "bool");
            break;
        default:
            printf("wrong input in type insert_symbol");
            break;
    }

    // for gencode
    if(strcmp(k, "function") == 0){
        get_attribute(e_ptr);
        create_func_table(_type, _ID);
        // gencode_func(_type, _ID);
    }else if(strcmp(k, "variable") == 0){      
        //paremeter and variable, generate to jasim & set e_ptr->entry_val
        if(table_current->table_depth == 0){
            if(_expr.symbol_type != T_Type)       //int a = 3;
                e_ptr->entry_val = gencode_global_1(_type, _ID, _expr, e_ptr->entry_val);
            else                                //int a;
                e_ptr->entry_val = gencode_global_2(_type, _ID, e_ptr->entry_val);
        }else{
            if(_expr.symbol_type != T_Type)        //int a = 3;
                e_ptr->entry_val = gencode_local_1(_type, _ID, _expr, e_ptr->index, e_ptr->entry_val);
            else                                //int a;
                e_ptr->entry_val = gencode_local_2(_type, _ID, e_ptr->index, e_ptr->entry_val);
        }
    }else if(strcmp(k, "parameter") == 0){      
        //paremeter,only set e_ptr->entry_val, no generate to jasmin
        e_ptr->entry_val = gencode_parameter(_type, _ID, e_ptr->index);
    }else{
        printf("error in -- insert_symbol\n");
    }

    // printf("\n++++%d, %s, %s, %s, %d++++\n", e_ptr->index, e_ptr->name, e_ptr->kind, e_ptr->type, e_ptr->scope);
}

void create_func_table(Value _type, Value _id){
    // printf("in create_function_table\n");

    struct Func * f_ptr = malloc(sizeof(struct Func));
    memset(f_ptr->f_name, 0, sizeof(f_ptr->f_name));
    memset(f_ptr->f_attr, 0, sizeof(f_ptr->f_attr));

    //set value
    strcat(f_ptr->f_name, _id.id_name);   
    strcat(f_ptr->f_attr, func_para);
    f_ptr->f_type = _type.symbol_type;
    f_ptr->f_pre = f_current;
    f_ptr->f_count = 0;
    
    f_current = f_ptr;
  
    if(f_header == NULL){
        f_header = f_current;
    }

    // printf("*** function table, %s %d ***\n", f_ptr->f_name, f_ptr->f_type);
}

int func_return_checking(Value _type, Value _id, int flag){
    // printf("in function_return_checking\n ");
    // declare & defined the same return type ?

    struct Func * f_ptr = f_current;
    while(f_ptr != NULL){
        // printf("hiii, %s, %s\n", f_ptr->f_name, _id.id_name);
        if(strcmp(f_ptr->f_name, _id.id_name) == 0){
            // printf("hiii222\n");
            if(_type.symbol_type != f_ptr->f_type ){
                if(strcmp(f_ptr->f_attr, func_para_2) != 0){
                    // printf("different return type\n");
                    //yyerror
                    memset(error_msg, 0, sizeof(error_msg));
                    strcat(error_msg, "1. function return type is not the same\n");
                    strcat(error_msg, "| 2. function formal patameter is not the same");
                    error_flag = 1;
                }else{
                    //yyerror
                    memset(error_msg, 0, sizeof(error_msg));
                    strcat(error_msg, "function return type is not the same");
                    error_flag = 1;
                }

                return 1;   //find & different return type
            }

            // printf("%s, %s = %s\n", f_ptr->f_name, f_ptr->f_attr, func_para_2);

            if(strcmp(f_ptr->f_attr, func_para_2) != 0){
                // printf("different return type\n");
                //yyerror
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "function formal patameter is not the same");
                error_flag = 1;
            }

            if(f_ptr->f_count == flag){
                // printf("redeclared\n");
                //yyerror
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "Redeclared function ");
                strcat(error_msg, f_ptr->f_name);
                error_flag = 1;
            }
            return 2;   //find
        }
        f_ptr = f_ptr->f_pre;
    }
    return 0; //not find
}

void get_attribute(struct Entry * tmp){
    // get entry_attribute
    struct Entry *e_ptr = tmp;   //add function attribute
    struct Table *dump = table_dump;    //find parameter table
    struct Entry *e_dump = dump->entry_header; //find parameter entry

    memset(func_para, 0, sizeof(func_para));

    while(e_dump != NULL){
        if(strcmp(e_dump->kind, "parameter") == 0){
            //set function attribute to symbol table
            if(strlen(e_ptr->attribute) != 0){  //attribute is not empty
                strcat(e_ptr->attribute, ", ");
            }
            strcat(e_ptr->attribute, e_dump->type);

            //set function parameter type to jasmin
            if(strcmp(e_dump->type, "int") == 0 || strcmp(e_dump->type, "bool") == 0){
                strcat(func_para, "I");
            }else if(strcmp(e_dump->type, "float") == 0){
                strcat(func_para, "F");
            }else if(strcmp(e_dump->type, "string") == 0){
                strcat(func_para, "S");
            }else{
                printf("wrong function parameter , %s\n", e_dump->type);
            }
        }
        e_dump = e_dump->entry_next;
    }
    // printf("\nin get_attribute = %s\n", e_ptr->attribute);

    return;
}

void lookup_symbol(char* name, int flag) {
    // printf("\nin lookup_symbol\n");
    //check semetic_error 

    if(flag == 1){  //check if Redeclared variable
        struct Entry *e_ptr = table_current->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, name) == 0){  // Redeclared variable !!!
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "Redeclared variable ");
                strcat(error_msg, name);
                error_flag = 1;
                break;
            }
            e_ptr = e_ptr->entry_next;
        }
    }else{      //check if Undeclared variable
        struct Table *ptr = table_current;
        while(ptr != NULL){
            struct Entry *e_ptr = ptr->entry_header;
            while(e_ptr != NULL){
                if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, name) == 0){ //declared variable
                    return;
                }
                /*
                printf("%-10d%-10s%-12s%-10s%-10d%-10s\n",
                   e_ptr->index, e_ptr->name, e_ptr->kind, e_ptr->type, e_ptr->scope, e_ptr->attribute);
                */
                e_ptr = e_ptr->entry_next;
            }
            ptr = ptr->pre;
        }
        // Undeclared variable !!!
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Undeclared variable ");
        strcat(error_msg, name);
        error_flag = 1;
    }
}

void lookup_function(char *name, int flag){
    // printf("\nin lookup_function\n");
    struct Table * ptr = table_current;

    if(flag == 1){   //Undeclared function
        while(ptr != NULL){
            struct Entry * e_ptr = ptr->entry_header;
            while(e_ptr != NULL){
                if(strcmp(e_ptr->kind, "function") == 0 && strcmp(e_ptr->name, name)== 0 ){
                    // printf("function declared !!!");
                    return;
                }
                e_ptr = e_ptr->entry_next;
            }
            ptr = ptr->pre;
        }

        // printf("\nno declared\n");
        // printf("num = %d, buf = %s\n", yylineno, buf);
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Undeclared function ");
        strcat(error_msg, name);
        error_flag = 1;
    }else{   //redeclared function
    /*
        struct Entry * e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") == 0 && strcmp(e_ptr->name, name)== 0){
                // redeclared
                memset(error_msg, 0, sizeof(error_msg));
                strcat(error_msg, "Redeclared function ");
                strcat(error_msg, name); 
                
                if(flag == 3)
                    func_flag = 1;
                else
                    error_flag = 1;
        
                return;
            }
            e_ptr = e_ptr->entry_next;
        }  
    */
    /*
        struct Func *f_ptr = f_current;
        while(f_ptr != NULL){
            if(strcmp(f_ptr->f_name, name) == 0){
                // redeclared
                if(f_ptr->f_count == 1){
                    //yyerror
                    memset(error_msg, 0, sizeof(error_msg));
                    strcat(error_msg, "Redeclared function ");
                    strcat(error_msg, name);
                    error_flag = 1;
                }
                break;
            }
            f_ptr = f_ptr->f_pre;
        }  
        */

    }

}

void set_func_para(Value _type, int flag){
    if(flag == 0){ // init
        memset(func_para_2, 0, sizeof(func_para_2));
    }

    switch(_type.symbol_type){
        case I_Type:
            strcat(func_para_2, "I");
            break;
        case B_Type:
            strcat(func_para_2, "I");
            break;
        case F_Type:
            strcat(func_para_2, "F");
            break;
        case S_Type:
            strcat(func_para_2, "Ljava/lang/String;");
            break;
        default:
            printf(" in set_func_para\n");
            break;
    }
}

void dump_table(){
    // printf("\n----in dump_table, depth = %d, current = %p----\n", table_current->table_depth, table_current);
    table_dump = table_current;
    table_current = table_current->pre;
    table_depth --;
}
void dump_symbol() {
    // printf("\n----in dump_symbol\n");
    struct Table *ptr = table_dump;
    
    if(ptr->entry_header == NULL){ 
        //not entry, print nothing and drop the table
        // printf(", depth = %d, current = %p----\n", ptr->table_depth, ptr);
    }else{
        //print symbol_table && delete it
        printf("\n%-10s%-10s%-12s%-10s%-10s%-10s\n\n",
            "Index", "Name", "Kind", "Type", "Scope", "Attribute");
        
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            printf("%-10d%-10s%-12s%-10s%-10d",
            e_ptr->index, e_ptr->name, e_ptr->kind, e_ptr->type, e_ptr->scope);
            if(strlen(e_ptr->attribute) != 0)
                printf("%s", e_ptr->attribute);
            
            printf("\n");
            e_ptr = e_ptr->entry_next;
        }
        printf("\n");
    
    }
}

//code generation function
Value gencode_global_1(Value _type, Value _id, Value _expr, Value vval){
    // printf("in gencode_1\n");
    fprintf(file, ".field public static");
    /* Example:
      a. only const
      b. no need to casting
    */
    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 1;

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
    
    switch (_type.symbol_type){
        case B_Type:  
            sprintf(input_tmp, " %s I = %d\n", _id.id_name, _expr.i);  
            _val.id_i = _expr.i;
            break;
        case I_Type:
            sprintf(input_tmp, " %s I = %d\n", _id.id_name, _expr.i);
            _val.id_i = _expr.i;
            break;
        case F_Type:
            sprintf(input_tmp, " %s F = %f\n", _id.id_name, _expr.f);
            _val.id_f = _expr.f;
            break;    
        case S_Type:
            sprintf(input_tmp, " %s Ljava/lang/String; = \"%s\"\n", _id.id_name, _expr.s);
            _val.id_s = _expr.s;
            break;
        default:
            printf("wrong input in type, gencode_global_1, %d\n",_type.symbol_type);
            break;
    }

    fprintf(file, "%s", input_tmp);
    // printf("%s", input_tmp);
    return _val;
}

Value gencode_global_2(Value _type, Value _id, Value vval){
    // printf("in gencode_2\n");
    fprintf(file, ".field public static");

    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 1;
    
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    switch (_type.symbol_type){
        case B_Type:
            sprintf(input_tmp, " %s I\n", _id.id_name);
            _val.id_i = 0;  
            break;
        case I_Type:
            sprintf(input_tmp, " %s I\n", _id.id_name);
            _val.id_i = 0;
            break;
        case F_Type:
            sprintf(input_tmp, " %s F\n", _id.id_name);
            _val.id_i = 0.0;
            break;
        default:
            printf("wrong input in type, gencode_global_2, %d\n", _type.symbol_type);
            break;
    }

    fprintf(file, "%s", input_tmp);
    // printf("%s", input_tmp);    
    // printf("%s, _id = %s, %d\n", input_tmp, _val.id_name, _val.id_symbol_type);
    return _val;
}

Value gencode_local_1(Value _type, Value _id, Value _expr, int index, Value vval){
    // printf("in gencode_local_1\n");
    /* Example:
       a. int a = 5;        ldc const
       b. int a = b;        find b ID
       c. int a = 3 + 4;    is_arith
       d. int a = sqrt(d);  return what??
       e. int a = 2.0;      ldc & casting

       Exapmle: int d = 3;
       ldc 0
       istore 0
    */
    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 0;
    _val.id_index = index;

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    if(_expr.is_arith == 1){  //case c, d
        switch(_type.symbol_type){
            case I_Type:
                if(_expr.symbol_type == F_Type){
                    sprintf(input_tmp, "\tf2i\n\tistore %d\n", index);
                    _val.id_i = (int)_expr.f;
                }else{
                    sprintf(input_tmp, "\tistore %d\n", index);
                    _val.id_i = _expr.i; 
                }
                break;
            case F_Type:
                if(_expr.symbol_type == I_Type){
                    sprintf(input_tmp, "\ti2f\n\tfstore %d\n", index);
                    _val.id_f = (float)_expr.i;
                }else{
                    sprintf(input_tmp, "\tfstore %d\n", index);
                    _val.id_f = _expr.f;
                }
                break;
            default:
                printf("wrong input in type, gencode_local_1 1, %d\n", _type.symbol_type);
                break;
        }
    }else if(_expr.symbol_type == ID_Type){  //case b
        Value v1 = get_id_value(_expr);
        _expr = get_id_entry(_expr);
        gencode_iload(_expr);
        switch(_type.symbol_type){
            case I_Type:
                if(v1.symbol_type == F_Type){
                    sprintf(input_tmp, "\tf2i\n\tistore %d\n", index);
                    _val.id_i = (int)_expr.f;
                }else{
                    sprintf(input_tmp, "\tistore %d\n", index);
                    _val.id_i = _expr.i; 
                }
                break;
            case F_Type:
                if(_expr.symbol_type == I_Type){
                    sprintf(input_tmp, "\ti2f\n\tfstore %d\n", index);
                    _val.id_f = (float)_expr.i;
                }else{
                    sprintf(input_tmp, "\tfstore %d\n", index);
                    _val.id_f = _expr.f;
                }
                break;
            default:
                printf("wrong input in type, gencode_local_1 2, %d\n", _type.symbol_type);
                break;
        }              
    }else{ //case a, e
        switch (_type.symbol_type){
            case B_Type:
                sprintf(input_tmp, "\tldc %d\n\tistore %d\n", _expr.i, index);
                _val.id_i = _expr.i; 
                break;
            case I_Type:
                if(_expr.symbol_type == F_Type){
                    sprintf(input_tmp, "\tldc %f\n\tf2i\n\tistore %d\n", _expr.f, index);
                    _val.id_i = (int)_expr.f;
                }else{
                    sprintf(input_tmp, "\tldc %d\n\tistore %d\n", _expr.i, index);
                    _val.id_i = _expr.i; 
                }
                break;
            case F_Type:
                if(_expr.symbol_type == I_Type){
                    sprintf(input_tmp, "\tldc %d\n\ti2f\n\tfstore %d\n", _expr.i, index);
                    _val.id_f = (float)_expr.i;
                }else{
                    sprintf(input_tmp, "\tldc %f\n\tfstore %d\n", _expr.f, index);
                    _val.id_f = _expr.f;
                }
                break;
            case S_Type:
                sprintf(input_tmp, "\tldc \"%s\"\n\tastore %d\n", _expr.s, index);
                _val.id_s = _expr.s;
                break;
            default:
                printf("wrong input in type, gencode_local_1 3, %d\n", _type.symbol_type);
                break;
        }
    }
    
    strcat(func_buf, input_tmp);
    // printf("%s", input_tmp);
    return _val;
}

Value gencode_local_2(Value _type, Value _id, int index, Value vval){
    // printf("in gencode_local_2\n");

    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 0;
    _val.id_index = index;

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));
    /*Example: int a; 
      a. initial value 0 
      b. no init empty string
    */
    switch (_type.symbol_type){
        case B_Type:
            sprintf(input_tmp, "\tldc 0\nistore %d\n", index);
            _val.id_i = 0;
            break;
        case I_Type:
            sprintf(input_tmp, "\tldc 0\n\tistore %d\n", index);
            _val.id_i = 0;
            break;
        case F_Type:
            sprintf(input_tmp, "\tldc 0.0\n\tfstore %d\n", index);
            _val.id_f = 0.0;
            break;
        default:
            printf("wrong input in type, gencode_local_2, %d\n", _type.symbol_type);
            break;
    }

    strcat(func_buf, input_tmp);
    // printf("%s", input_tmp);
    return _val;
}

Value gencode_parameter(Value _type, Value _id, int index){
    // printf("in gencode_parameter\n");

    Value _val;
    _val.id_name = _id.id_name;
    _val.id_symbol_type = _type.symbol_type;
    _val.is_global = 0;
    _val.id_index = index;

    return _val;
}

void gencode_func(Value _type, Value _id){
    // printf("in gencode_func\n");
    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));

    if(strcmp(_id.id_name, "main") == 0){   //if main function
        // printf(" ohhhh\n");
        fprintf(file, ".method public static main([Ljava/lang/String;)V\n");
        // printf(" ohhhh\n");
    }else{
        switch (_type.symbol_type){
            case B_Type:
                sprintf(input_tmp, ".method public static %s(%s)I\n", _id.id_name, func_para);  
                break;
            case I_Type:
                sprintf(input_tmp, ".method public static %s(%s)I\n", _id.id_name, func_para);
                break;
            case F_Type:
                sprintf(input_tmp, ".method public static %s(%s)F\n", _id.id_name, func_para);
                break;
            case V_Type:
                sprintf(input_tmp, ".method public static %s(%s)V\n", _id.id_name, func_para);
                break;
            default:
                printf("wrong input in type, gencode function\n");
                break;
        }    
        fprintf(file, "%s", input_tmp);
        // printf("%s", input_tmp);
    }

    fprintf(file, ".limit stack 50\n.limit locals 50\n");
    fprintf(file, "%s", func_buf);
    fprintf(file, ".end method\n");

    // printf("%s", ".limit stack 50\n.limit locals 50\n");
    // printf("%s", func_buf);
    // printf(".end method\n");

    memset(func_buf, 0, sizeof(func_buf));       
    return;
}

void gencode_return(Value v){
    // printf("in gencode_return\n");
    /* Example: 
       a. return;
       b. return a;
       c. return 3;
       d. teturm a + 3;
       e. return foo(a);
       iload 0 / getstatic / is_arith ... <- get_id_value
       ireturn    
    */
    
    //special case
    if(v.symbol_type == T_Type){
        v.symbol_type = V_Type;
    }

    if(v.is_arith == 1){ //case d, e
        switch(v.symbol_type){
            case I_Type:
            case B_Type: 
                strcat(func_buf, "\tireturn\n"); 
                break;
            case F_Type:
                strcat(func_buf, "\tfreturn\n");
                break;
            default:
                printf("wrong return type 1 -- gencode_return, %d\n", v.symbol_type);
                break;
        }
    }else if(v.symbol_type == ID_Type){ //case b
        Value v1 = get_id_value(v);
        v = get_id_entry(v);
        gencode_iload(v);
        switch(v1.symbol_type){
            case I_Type:
            case B_Type:
                strcat(func_buf, "\tireturn\n"); 
                break;
            case F_Type:
                strcat(func_buf, "\tfreturn\n");
                break;
            default:
                printf("wrong return type 2 -- gencode_return, %d\n", v.symbol_type);
                break;
        }
    }else{ //case a, c
        switch(v.symbol_type){
            case I_Type:
            case B_Type:
                gencode_iload(v); 
                strcat(func_buf, "\tireturn\n"); 
                break;
            case F_Type:
                gencode_iload(v);
                strcat(func_buf, "\tfreturn\n");
                break;
            case V_Type:
                strcat(func_buf, "\treturn\n");
                break;
            default:
                printf("wrong return type 3 -- gencode_return, %d\n", v.symbol_type);
                break;
        }
    }
    return;
}

void gencode_print(Value v){ 
    // printf("in gencode_print\n");
    /* Example: only print int, float, string variables and constants
       a. print(1);
       b. print("HELLO");
       c. print(a);

       * not test:
       print(a+b);  -->grammar can't handle
       print(TRUE); -->no print bool

       * todo
       1. put something on TOS
       2. getstatic java/lang/System/out Ljava/io/PrintStream; 
          swap
       3. invokevirtural java/io/PrintStream/println(I)V
    */

    Value tmp;
    if(v.symbol_type == ID_Type){
        tmp = get_id_value(v);
        v = get_id_entry(v);
    }else{
        tmp.symbol_type = v.symbol_type;
    }

    // todo step
    gencode_iload(v);
    strcat(func_buf, "\tgetstatic java/lang/System/out Ljava/io/PrintStream;\n\tswap\n");
    switch(tmp.symbol_type){
        case I_Type:
        case B_Type:
            strcat(func_buf, "\tinvokevirtual java/io/PrintStream/println(I)V\n");
            break;
        case F_Type:
            strcat(func_buf, "\tinvokevirtual java/io/PrintStream/println(F)V\n");
            break;
        case S_Type:
            strcat(func_buf, "\tinvokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
            break;
        default:
            printf("wrong case -- gencode_print, %d\n", tmp.symbol_type);
            break;
    }
    return;
}

//expression function
Value switch_mul_op(Value v1, Operator op, Value v2){
    // printf("in switch_mul_op\n");
    
    switch (op){
        case MUL_OPT:
            return mul_arith(v1, v2);
        case DIV_OPT:
            return div_arith(v1, v2);
        case MOD_OPT:
            return mod_arith(v1, v2);
        default:
            printf("wrong case in mul_arith\n");
            break;
    }
}

Value switch_addition_op(Value v1, Operator op, Value v2){
    // printf("in switch_addition_op\n");
    switch (op) {
        case ADD_OPT:
            return add_arith(v1, v2);
        case MINUS_OPT:
            return minus_arith(v1, v2);
        default:
            printf("wrong case in addition_op\n");
            break;
    }
}

Value switch_postfix_op(Value v1, Operator op){
    // printf("in switch_postfix_op\n");
    Value tmp;
    tmp.symbol_type = I_Type;
    tmp.i = 1;

    switch (op){
        case INC_OPT: // a = a + 1;
            tmp =  add_arith(v1, tmp);
            break;

        case DEC_OPT:
            tmp =  minus_arith(v1, tmp);
            break;
        default:
            printf("wrong case in postfix_op\n");
            break;
    }

    v1 = get_id_entry(v1);
    gencode_istore(v1);

    return tmp;
}

Value switch_assign_op(Value v1, Operator op, Value v2){
    // printf("in switch_assign_op\n");
    // LHS_val = RHS_val
    Value RHS_val;
    Value LHS_val;

    //get LHS_val type, (v1 must be an ID)
    LHS_val = get_id_value(v1);
    v1 = get_id_entry(v1);

    if(op == ASSIGN_OPT){
        /* Example
            a. x = y + 3;
            b. x = y;
            c. x = 12;
        */
        if(v2.symbol_type == ID_Type){  //case b
            RHS_val = get_id_value(v2);
            v2 = get_id_entry(v2);
            gencode_iload(v2);
        }else if(v2.is_arith == 1){ // case a
            RHS_val = v2;
        }else{ //case c
            gencode_iload(v2);
            RHS_val = v2;
        }
    }else{
        switch (op){
            case ADD_ASSIGN_OPT:
                RHS_val = add_arith(v1, v2);
                break;
            case SUB_ASSIGN_OPT:
                RHS_val = minus_arith(v1, v2);
                break;
            case MUL_ASSIGN_OPT:
                RHS_val = mul_arith(v1, v2);
                break;
            case DIV_ASSIGN_OPT:
                RHS_val = div_arith(v1, v2);
                break;
            default:
                printf("wrong case -- assign_op, %d\n", op);
                break;
        }
    }

    //type casting
    if(LHS_val.symbol_type == I_Type && RHS_val.symbol_type == F_Type){
        strcat(func_buf, "\tf2i\n");
    }else if(LHS_val.symbol_type == F_Type && RHS_val.symbol_type == I_Type){
        strcat(func_buf, "\ti2f\n");
    }

    gencode_istore(v1);
    return LHS_val;  ///set RHS_val to LHS_val ????? cheating ???
}

Value switch_relation_op(Value A, Operator op, Value B){
    // printf("in switch_relation_op\n");
    /* Example:
       a. x == y
       b. x != 3
       c. (2+x) > (x+y)
       d. 5 > 6
       *not to consider if x, y is different type
       *return 0/1
       * todo Example: a > b
        iload a           ---> get_id_value
        iload b           ---> get_id_value
        if_icmpgt label_1 ---> if_XXcmp & label
        **FALSE           ---> store in label_buf
        goto label_next
        label_1:
        **TRUE
        label_next:
        ...
    */

    Value tmp;
    tmp.symbol_type = B_Type; 

    char input_tmp[100];
    memset(input_tmp, 0, sizeof(input_tmp));


    sprintf(input_tmp, "label_%d:\n", ++label_index);
    strcat(func_buf, input_tmp);
    memset(input_tmp, 0, sizeof(input_tmp));

    
    if(A.is_arith == 0 && B.is_arith == 0){
        A = get_id_entry(A);
        gencode_iload(A);
        B = get_id_entry(B);
        gencode_iload(B);
    }else if(A.is_arith == 1 && B.is_arith == 0){
        B = get_id_entry(B);
        gencode_iload(B);
    }else if(A.is_arith == 0 && B.is_arith == 1){
        A = get_id_entry(A);
        gencode_iload(A);
    }
    
    
   
    switch (op){
        case MORE_OPT: // >
            sprintf(input_tmp, "\tif_icmpgt label_%d\n", ++label_index);
            break;
        case LESS_OPT: // <
            sprintf(input_tmp, "\tif_icmplt label_%d\n", ++label_index);
            break;
        case GE_OPT: // >=
            sprintf(input_tmp, "\tif_icmpge label_%d\n", ++label_index);
            break;
        case LE_OPT: // <=
            sprintf(input_tmp, "\tif_icmple label_%d\n", ++label_index);
            break;
        case EQ_OPT: // ==
            sprintf(input_tmp, "\tif_icmpeq label_%d\n", ++label_index);
            break;
        case NE_OPT: // !=
            sprintf(input_tmp, "\tif_icmpne label_%d\n", ++label_index);
            break;
        default:
            printf("wrong case in relation_op\n");
            break;
    }

    strcat(func_buf, input_tmp);
    memset(input_tmp, 0, sizeof(input_tmp));

    // int label_next = label_index + 1;

    //for while
    sprintf(input_tmp, "\tgoto label_%d\n", ++label_index);
    strcat(func_buf, input_tmp);


    // sprintf(input_tmp, "\tiload FALSE\n\tgoto label_%d\n\tlabel_%d:\n\tiload TRUE\n\tlabel_%d:\n"
                    //  , label_next, label_index, label_next);
    
    // strcat(func_buf, input_tmp);

    // label_index = label_next + 1;
    return tmp;
}

//arithmetic function
Value mul_arith(Value A, Value B){
    // printf("in mul_arith\n");
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);
    
    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)*(v2.i);
        strcat(func_buf, "\timul\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)*(v2.f);
        strcat(func_buf, "\tfmul\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)*(v2.i);
        strcat(func_buf, "\tfmul\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)*(v2.f);
        strcat(func_buf, "\tfmul\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value div_arith(Value A, Value B){
    // printf("in div_arith\n");
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    Value v_tmp;

    //cannot divide by zero
    if((v2.symbol_type == I_Type && v2.i == 0)
        || (v2.symbol_type == F_Type && v2.f == 0.0)){
        // printf("cannot divide by zero!!\n ");
        //yyerror
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Arithmetic errors - cannot divided by zero");
        error_flag = 1;
        return A;
    }

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)/(v2.i);
        strcat(func_buf, "\tidiv\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)/(v2.f);
        strcat(func_buf, "\tfdiv\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)/(v2.i);
        strcat(func_buf, "\tfdiv\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)/(v2.f);
        strcat(func_buf, "\tfdiv\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value mod_arith(Value A, Value B){
    // printf("in mod_arith\n");

    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)%(v2.i);
        strcat(func_buf, "\tirem\n");
    }else{
        // printf("wrong -- only int can mod\n");
        //yyerror
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "Arithmetic errors - Modulo operator only for interger");
        error_flag = 1;
    }

    v_tmp.is_arith = 1;
    
    return A;
}

Value add_arith(Value A, Value B){
    // printf("in add_arith\n");
    // printf("%d, %d, %s,,,%d\n", A.symbol_type, A.id_symbol_type, A.id_name, B.symbol_type);
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    // printf("%d, %d, %s,,,%d\n", A.symbol_type, A.id_symbol_type, A.id_name, B.symbol_type);

    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)+(v2.i);
        strcat(func_buf, "\tiadd\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)+(v2.f);
        strcat(func_buf, "\tfadd\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)+(v2.i);
        strcat(func_buf, "\tfadd\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)+(v2.f);
        strcat(func_buf, "\tfadd\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value minus_arith(Value A, Value B){
    // printf("in minus_arith\n");
    
    Value v1 = get_id_value(A, 1);
    Value v2 = get_id_value(B, 1);
    A = get_id_entry(A);
    B = get_id_entry(B);

    Value v_tmp;

    if(v1.symbol_type == I_Type && v2.symbol_type == I_Type){       //II
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = I_Type;
        v_tmp.i = (v1.i)-(v2.i);
        strcat(func_buf, "\tisub\n");
    }else if(v1.symbol_type == I_Type && v2.symbol_type == F_Type){ //IF
        gencode_if_arith(A, B, 2);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.i)-(v2.f);
        strcat(func_buf, "\tfsub\n");
    }else if(v1.symbol_type == F_Type && v2.symbol_type == I_Type){ //FI
        gencode_if_arith(A, B, 3);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)-(v2.i);
        strcat(func_buf, "\tfsub\n");
    }else{ //FF
        gencode_if_arith(A, B, 1);
        v_tmp.symbol_type = F_Type;
        v_tmp.f = (v1.f)-(v2.f);
        strcat(func_buf, "\tfsub\n");
    }

    v_tmp.is_arith = 1;
    return v_tmp;
}

Value get_id_value(Value v, int flag){

    if(v.symbol_type != ID_Type)
        return v;

    struct Table *ptr = table_current;
    Value _val;
    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, v.id_name) == 0){ 
                //declared variable && find id & gencode 
                Value tmp = e_ptr->entry_val;
                // set _val
                switch(tmp.id_symbol_type){
                    case I_Type:
                    case B_Type:
                        _val.i = tmp.id_i;
                        break;
                    case F_Type:
                        _val.f = tmp.id_f;
                        break;
                    case S_Type:
                        _val.s = tmp.id_s;
                        break;
                    default:
                        printf("wrong id type -- get_id_value\n");
                        break;
                }
                _val.symbol_type = tmp.id_symbol_type;
                return _val;
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }
    // printf("Not Find ID -- get_id_value !!!!\n");
    return _val;
}

Value get_id_entry(Value v){

    if(v.symbol_type != ID_Type)
        return v;

    struct Table *ptr = table_current;
    Value _val;
    while(ptr != NULL){
        struct Entry *e_ptr = ptr->entry_header;
        while(e_ptr != NULL){
            if(strcmp(e_ptr->kind, "function") != 0 && strcmp(e_ptr->name, v.id_name) == 0){ 
                //declared variable && find id & gencode 
                _val = e_ptr->entry_val;
                _val.symbol_type = ID_Type;
                _val.is_arith = v.is_arith;
                return _val;    
            }
            e_ptr = e_ptr->entry_next;
        }
        ptr = ptr->pre;
    }
    // printf("Not Find ID -- get_id_entry !!!!\n");
    return v;
}

void gencode_iload(Value v){
    char input_tmp[100];
    memset(input_tmp, 0 ,sizeof(input_tmp));
    // printf("----type %d\n", v.symbol_type);

    if(v.symbol_type == ID_Type){
        // printf(" ==== type %d\n", v.id_symbol_type);
        if(v.is_global == 1){
            switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tgetstatic compiler_hw3/%s I\n", v.id_name);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tgetstatic compiler_hw3/%s F\n", v.id_name);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\tgetstatic compiler_hw3/%s Ljava/lang/String;\n", v.id_name);
                    break;
                default:
                    printf("wrong id type -- iload global\n");
                    break;
            }
        }else{
            switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tiload %d\n", v.id_index);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tfload %d\n", v.id_index);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\taload %d\n", v.id_index);
                    break;
                default:
                    printf("wrong id type -- iload loacl\n");
                    break;
            }
        }
    }else{  // the const
        switch(v.symbol_type){
            case I_Type:
            case B_Type:
                sprintf(input_tmp, "\tldc %d\n", v.i);
                break;
            case F_Type:
                sprintf(input_tmp, "\tldc %f\n", v.f);
                break;
            case S_Type:
                sprintf(input_tmp, "\tldc \"%s\"\n", v.s);
                break;
            default:
                printf("wrong id type -- iload const\n");
                break;
        }
    }

    strcat(func_buf, input_tmp);
    return;
}

void gencode_istore (Value v){
    char input_tmp[100];
    memset(input_tmp, 0 ,sizeof(input_tmp));
    
    if(v.symbol_type == ID_Type){
        if(v.is_global == 1){
           switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tputstatic compiler_hw3/%s I\n", v.id_name);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tputstatic compiler_hw3/%s F\n", v.id_name);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\tputstatic compiler_hw3/%s Ljava/lang/String;\n", v.id_name);
                    break;
                default:
                    printf("wrong id type -- gencode_istore, %d\n", v.id_symbol_type );
                    break;
            }
        }else{
            switch(v.id_symbol_type){
                case I_Type:
                case B_Type:
                    sprintf(input_tmp, "\tistore %d\n", v.id_index);
                    break;
                case F_Type:
                    sprintf(input_tmp, "\tfstore %d\n", v.id_index);
                    break;
                case S_Type:
                    sprintf(input_tmp, "\tastore %d\n", v.id_index);
                    break;
                default:
                    printf("wrong id type -- gencode_istore, %d\n", v.id_symbol_type);
                    break;
            }
        }
    }else{  // the const
        // printf("store in const ??? -- gencode_istore\n");
    }

    strcat(func_buf, input_tmp);
    return;
}

void gencode_if_arith(Value A, Value B, int flag){
    if(A.is_arith == 0 && B.is_arith == 0){
        switch(flag){
            case 1:
                gencode_iload(A);
                gencode_iload(B);
                break;
            case 2:
                gencode_iload(A);
                strcat(func_buf, "\ti2f\n");
                gencode_iload(B);
                break;
            case 3:
                gencode_iload(A);
                gencode_iload(B);
                strcat(func_buf, "\ti2f\n");
                break;
            default:
                printf("wrong in -- gencode_if_arith 1, %d\n", flag);
                break;
        }   
    }else if(A.is_arith == 1 && B.is_arith == 0){
        switch(flag){
            case 1:
                gencode_iload(B);
                break;
            case 2:
                strcat(func_buf, "\ti2f\n");
                gencode_iload(B);
                break;
            case 3:
                gencode_iload(B);
                strcat(func_buf, "\ti2f\n");
                break;
            default:
                printf("wrong in -- gencode_if_arith 2, %d\n", flag);
                break;
        }   
    }else if(A.is_arith == 0 && B.is_arith == 1){
        switch(flag){
            case 1:
                gencode_iload(A);
                break;
            case 2:
                gencode_iload(A);
                strcat(func_buf, "\ti2f\n");
                break;
            case 3:
                strcat(func_buf, "\ti2f\n");
                gencode_iload(A);
                break;
            default:
                printf("wrong in -- gencode_if_arith 3, %d\n", flag);
                break;
        }   
    }else if(A.is_arith == 1 && B.is_arith == 1){
        switch(flag){
            case 1:
                break;
            case 2:
                // printf("in speeeeeical case\n");
                strcat(func_buf, "\tswap\n\ti2f\n");
                break;
            case 3:
                strcat(func_buf, "\ti2f\n");
                break;
            default:
                printf("wrong in -- gencode_if_arith 4, %d\n", flag);
                break;
        }   
    }else{
        // printf("error in -- gencode_if_arith\n");
    }
    return;
}

Value gencode_funcall(Value _val){     
    // printf("in gencode_funcall\n");
    /* Example: a = foo(6);
       ldc 6
       invokestatic compiler_hw3/foo(I)I
       istore 0

       * todo
       1. checking input parameter type
       2. generate function call code (invokestatic)
    */
    char input_tmp[200];
    memset(input_tmp, 0, sizeof(input_tmp));
    Value v;

    //cut attribute
    char *delim = ", ";
    char *token;
    char str[50];
    char para_tmp[50];
    memset(str, 0, sizeof(str));
    memset(para_tmp, 0, sizeof(para_tmp));

    //creat function parameter array from symbol table
    Symbol_type tmp[10];
    int tmp_index = 0;
       

    struct Entry *e_ptr = table_header->entry_header;

    while(e_ptr != NULL){
        if(strcmp(e_ptr->kind, "function") == 0 && strcmp(e_ptr->name, _val .id_name) == 0){ //declared variable
            //find attribute & cut token to make tmp[]
            strcat(str, e_ptr->attribute);
            token = strtok(str, delim);
            while (token != NULL)
            {
                if(strcmp(token, "int") == 0){
                    tmp[tmp_index++] = I_Type;
                    strcat(para_tmp, "I");
                }else if(strcmp(token, "float") == 0){
                    tmp[tmp_index++] = F_Type;
                    strcat(para_tmp, "F");
                }else if(strcmp(token, "string") == 0){
                    tmp[tmp_index++] = S_Type;
                    strcat(para_tmp, "Ljava/lang/String;");
                }else if(strcmp(token, "bool") == 0){
                    tmp[tmp_index++] = B_Type;
                    strcat(para_tmp, "I");
                }else{
                    // printf("wrong !!!\n");
                }
                token = strtok (NULL, delim);
            } 

            //get function type & gencode
            if(strcmp(e_ptr->type, "int") == 0 || strcmp(e_ptr->type, "bool") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)I\n", e_ptr->name, para_tmp);
                v.symbol_type = I_Type;
            }else if(strcmp(e_ptr->type, "float") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)F\n", e_ptr->name, para_tmp);
                v.symbol_type = F_Type;
            }else if(strcmp(e_ptr->type, "void") == 0){
                sprintf(input_tmp, "\tinvokestatic compiler_hw3/%s(%s)V\n", e_ptr->name, para_tmp);
                v.symbol_type = V_Type;
            }else{
                // printf("wrong !!!\n");
            }
            break;
        }
        e_ptr = e_ptr->entry_next;
    }

    //is same # of parameter ?
    if(tmp_index != func_input_num){
        // printf("different index num %d, %d\n", tmp_index, func_input_num);
        //yyerror
        memset(error_msg, 0, sizeof(error_msg));
        strcat(error_msg, "function formal parameter is not the same");
        error_flag = 1;
    }

    //type casting
    Symbol_type _type;
    for(int i=0; i<tmp_index; i++){
        if(func_para_type[i].symbol_type == ID_Type){
            _type = func_para_type[i].id_symbol_type;
        }else{
            _type = func_para_type[i].symbol_type;
        }

        if(_type != tmp[i]){
            // printf("error is different inptut type\n");
            //yyerror
            memset(error_msg, 0, sizeof(error_msg));
            strcat(error_msg, "function formal parameter is not the same");
            error_flag = 1;
        }

        //gencode
        gencode_iload(func_para_type[i]);
    }

    strcat(func_buf, input_tmp);
    func_input_num = 0;
    v.is_arith = 1;
    return v;
}

void gencode_while(Value v){
    // printf("in gencode_while\n");

    char input_tmp[200];
    memset(input_tmp, 0, sizeof(input_tmp));

    // printf("the index_num = %d\n", label_index);

    sprintf(input_tmp, "label_%d:\n", label_index -1);
    strcat(func_buf, input_tmp);





}
