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
#line 1 "bison.y" /* yacc.c:339  */

     #include <stdio.h>
     #include <string>
     #include <vector>
     #include <string.h>
     #include <stdlib.h>
     #include <stdio.h>
     #include <stdlib.h>
     #include <sstream>
       #include <iostream>

     namespace patch
    {
        template < typename T > std::string to_string( const T& n )
        {
            std::ostringstream stm ;
            stm << n ;
            return stm.str() ;
        }
    }


     extern FILE * yyin;
     extern int yylex(void);
     void yyerror(const char * msg);
     extern int current_line;

     char * indentifierToken;
     int numberToken;
     int count_names = 0;
     static int temp_count = 0;

     enum Type {
       Integer,
       Array
     };

     struct Symbol {
       std::string name;
       Type type;
     };

     struct Function {
       std::string name;
       std::vector < Symbol > declarations;
     };

     std::vector < Function > symbol_table;
     char numbers[5] = {'0', '1', '2', '3', '4',};

     // remember that Bison is a bottom up parser: that it parses leaf nodes first before
     // parsing the parent nodes. So control flow begins at the leaf grammar nodes
     // and propagates up to the parents.
     Function * get_function() {
       int last = symbol_table.size() - 1;
       if (last < 0) {
         printf("***Error. Attempt to call get_function with an empty symbol table\n");
         printf("Create a 'Function' object using 'add_function_to_symbol_table' before\n");
         printf("calling 'find' or 'add_variable_to_symbol_table'");
         exit(1);
       }
       return & symbol_table[last];
     }

     // find a particular variable using the symbol table.
     // grab the most recent function, and linear search to
     // find the symbol you are looking for.
     // you may want to extend "find" to handle different types of "Integer" vs "Array"
     bool find(std::string & value) {
       Function * f = get_function();
       for (int i = 0; i < f -> declarations.size(); i++) {
         Symbol * s = & f -> declarations[i];
         if (s -> name == value) {
           return true;
         }
       }
       return false;
     }

     // when you see a function declaration inside the grammar, add
     // the function name to the symbol table
     void add_function_to_symbol_table(std::string & value) {
      // Check for reserved words
      if (value == "if") {
        printf("***Error. Cannot use reserved word 'if' as a function name\n");
        exit(1);
      }
      if (value == "else") {
        printf("***Error. Cannot use reserved word 'else' as a function name\n");
        exit(1);
      }
      if (value == "while") {
        printf("***Error. Cannot use reserved word 'while' as a function name\n");
        exit(1);
      }
      if (value == "return") {
        printf("***Error. Cannot use reserved word 'return' as a function name\n");
        exit(1);
      }
      if (value == "print") {
        printf("***Error. Cannot use reserved word 'print' as a function name\n");
        exit(1);
      }
      if (value == "get") {
        printf("***Error. Cannot use reserved word 'read' as a function name\n");
        exit(1);
      }
      if (value == "Array") {
        printf("***Error. Cannot use reserved word 'Array' as a function name\n");
        exit(1);
      }
      if (value == "Integer") {
        printf("***Error. Cannot use reserved word 'Integer' as a function name\n");
        exit(1);
      }

      
       Function f;
       f.name = value;
       symbol_table.push_back(f);
     }

     bool check_if_function_in_symbol_table(std::string& value) {
        for (int i = 0; i < symbol_table.size(); i++) {
          Function * f = & symbol_table[i];
          if (f->name == value) {
            return true;
          }
        }
        return false;
     } 

     // when you see a symbol declaration inside the grammar, add
     // the symbol name as well as some type information to the symbol table
     void add_variable_to_symbol_table(std::string & value, Type t) {
      if (value == "main") {
        printf("***Error. Cannot use reserved word 'main' as a variable name\n");
        exit(1);
      }
      if (value == "if") {
        printf("***Error. Cannot use reserved word 'if' as a variable name\n");
        exit(1);
      }
      if (value == "else") {
        printf("***Error. Cannot use reserved word 'else' as a variable name\n");
        exit(1);
      }
      if (value == "while") {
        printf("***Error. Cannot use reserved word 'while' as a variable name\n");
        exit(1);
      }
      if (value == "return") {
        printf("***Error. Cannot use reserved word 'return' as a variable name\n");
        exit(1);
      }
      if (value == "print") {
        printf("***Error. Cannot use reserved word 'print' as a variable name\n");
        exit(1);
      }
      if (value == "get") {
        printf("***Error. Cannot use reserved word 'read' as a variable name\n");
        exit(1);
      }
      if (value == "Array") {
        printf("***Error. Cannot use reserved word 'Array' as a variable name\n");
        exit(1);
      }
      if (value == "Integer") {
        printf("***Error. Cannot use reserved word 'Integer' as a variable name\n");
        exit(1);
      }
       Symbol s;
       s.name = value;
       s.type = t;
       Function * f = get_function();
       f -> declarations.push_back(s);
     }

     bool check_if_variable_in_symbol_table(std::string & temp, Type t) {
        Function * f = get_function();
        for (int i = 0; i < f -> declarations.size(); i++) {
          Symbol * s = & f -> declarations[i];
          if (s -> name == temp && s -> type == t) {
            return true;
          }
        }
        return false;
     }

     void variable_exist(std::string & temp, Type t) {
        if (!check_if_variable_in_symbol_table(temp, t)) {
          if (t == Integer)
            printf("***Error. Variable %s does not exist\n", temp.c_str());
          else 
            printf("***Error. Array %s does not exist\n", temp.c_str());
          exit(1);
        }
     }

     // a function to print out the symbol table to the screen
     // largely for debugging purposes.
     void print_symbol_table(void) {
       printf("symbol table:\n");
       printf("--------------------\n");
       for (int i = 0; i < symbol_table.size(); i++) {
         printf("function: %s\n", symbol_table[i].name.c_str());
         for (int j = 0; j < symbol_table[i].declarations.size(); j++) {
           printf("  locals: %s\n", symbol_table[i].declarations[j].name.c_str());
         }
       }
       printf("--------------------\n");
     }

     bool has_main() {
      bool has_main_b = false;
      for (int i = 0; i < symbol_table.size(); i++) {
        Function * f = & symbol_table[i];
        if (f->name == "main") {
          has_main_b = true;
        }
      }
      return has_main_b;
     }

     void printer(const char* h) {
        return;
     }

     std::string create_temp() {
        std::string temp = "_temporary" + patch::to_string(temp_count);
        temp_count++;
        add_variable_to_symbol_table(temp, Integer);
        return temp;
     }
     std::string create_temp_with_code(std::string& code) {
        std::string temp = create_temp();
        std::string create = ". " + temp + "\n";
        code += create;
        return temp;
     }
     std::string build_temp(std::string temp, std::string value) {
        std::string create = ". " + temp + "\n";
        std::string assign = "= " + temp + ", " + value + "\n";
        return create + assign;
     }

     struct CodeNode {
       std::string code; // generated code as a string.
       std::string name;
       std::string temp;
     };

#line 319 "bison.tab.c" /* yacc.c:339  */

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
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "bison.tab.h".  */
#ifndef YY_YY_BISON_TAB_H_INCLUDED
# define YY_YY_BISON_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    FUNCTION = 258,
    ARRAY = 259,
    INTEGERVAR = 260,
    ARRAYFILL = 261,
    RETURN = 262,
    SEMICOLON = 263,
    COMMA = 264,
    IF = 265,
    ELSE = 266,
    WHILE = 267,
    TRUE = 268,
    FALSE = 269,
    CONTINUE = 270,
    BREAK = 271,
    GET = 272,
    PRINT = 273,
    NOT = 274,
    COLON = 275,
    L_PAREN = 276,
    R_PAREN = 277,
    L_SQUARE_BRACKET = 278,
    R_SQUARE_BRACKET = 279,
    ASSIGN = 280,
    LBRACE = 281,
    RBRACE = 282,
    ADD = 283,
    SUB = 284,
    MULT = 285,
    DIV = 286,
    MOD = 287,
    EQ = 288,
    NEQ = 289,
    LT = 290,
    GT = 291,
    LTE = 292,
    GTE = 293,
    INTEGER = 294,
    IDENTIFIER = 295
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 255 "bison.y" /* yacc.c:355  */

  char *op_val;
  struct CodeNode *node;

#line 405 "bison.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_BISON_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 422 "bison.tab.c" /* yacc.c:358  */

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   150

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  60
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   295

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
static const yytype_uint16 yyrline[] =
{
       0,   293,   293,   303,   309,   319,   343,   345,   353,   361,
     377,   381,   389,   396,   403,   410,   417,   424,   431,   437,
     443,   451,   460,   470,   487,   499,   520,   541,   545,   553,
     561,   569,   580,   597,   620,   653,   665,   682,   692,   705,
     713,   722,   731,   741,   748,   756,   769,   782,   795,   808,
     821,   831,   844,   857,   870,   883,   896,   909,   921,   936,
     942
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNCTION", "ARRAY", "INTEGERVAR",
  "ARRAYFILL", "RETURN", "SEMICOLON", "COMMA", "IF", "ELSE", "WHILE",
  "TRUE", "FALSE", "CONTINUE", "BREAK", "GET", "PRINT", "NOT", "COLON",
  "L_PAREN", "R_PAREN", "L_SQUARE_BRACKET", "R_SQUARE_BRACKET", "ASSIGN",
  "LBRACE", "RBRACE", "ADD", "SUB", "MULT", "DIV", "MOD", "EQ", "NEQ",
  "LT", "GT", "LTE", "GTE", "INTEGER", "IDENTIFIER", "$accept",
  "prog_start", "functions", "function", "arguments", "argument",
  "statements", "statement", "declaration", "function_call", "params",
  "param", "if_statement", "while_statement", "return_statement",
  "assign_statement", "expression", "integerexpression",
  "booleanexpression", "arrayexpression",
  "integer_expression_actual_number", "function_indentifier", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295
};
# endif

#define YYPACT_NINF -39

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-39)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       2,   -30,    15,   -39,     2,   -39,    17,   -39,   -39,    37,
       9,    28,    42,   -39,    26,    37,     7,   -39,    38,    39,
      56,    55,    59,    73,    75,    56,    63,    -5,    58,     7,
      78,    79,   -39,   -39,    80,    84,    66,    68,    56,    56,
     -39,    20,   -39,    94,   -39,   -39,   -39,   -39,    56,    56,
     -39,   -39,    -2,    86,    36,   -38,    56,    56,   -39,   -39,
     -39,   -39,   -39,   -39,    74,    56,    94,    94,    82,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    87,   111,   -39,   -39,   -39,   -39,   -39,   112,    96,
      83,    94,   100,    94,   -39,   113,    94,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,   109,   110,   -39,
     -38,   114,    69,   -39,     7,     7,   -39,    56,   116,   115,
     117,    94,   -39,   127,   -39,   119,     7,   120,   -39
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     2,     3,    60,     0,     1,     4,     6,
       0,     0,     8,     9,     0,     6,    10,     7,     0,     0,
      35,     0,     0,     0,     0,     0,     0,     0,     0,    10,
       0,     0,    14,    15,     0,     0,     0,    24,     0,     0,
      59,    39,    50,    36,    40,    41,    42,    43,     0,     0,
      18,    19,     0,    59,     0,    27,     0,     0,     5,    11,
      12,    13,    16,    17,     0,     0,    57,     0,    40,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,    41,    22,    21,    20,    30,    31,     0,    29,
       0,    37,     0,    23,    44,    40,    45,    46,    47,    48,
      49,    51,    52,    53,    54,    55,    56,     0,     0,    26,
      27,     0,     0,    58,    10,    10,    28,     0,     0,     0,
       0,    38,    25,    32,    34,     0,    10,     0,    33
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -39,   -39,   137,   -39,   128,   -39,   -25,   -39,   -39,   -16,
      40,   -39,   -39,   -39,   -39,   -39,   -17,   -32,    -3,   -39,
     -39,   -39
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    11,    12,    28,    29,    30,    42,
      88,    89,    32,    33,    34,    35,    67,    44,    45,    46,
      47,     6
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,    86,    87,    43,    59,     1,    83,    68,    52,    54,
       5,    18,    19,    31,    20,     7,    55,    21,    56,    22,
      57,    66,    23,    24,    25,    26,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    95,     9,    90,
      91,    55,    10,    69,    85,    81,    82,    27,    93,    13,
      14,    15,    16,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   105,   106,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    38,    48,    39,    36,    37,
      49,    50,    38,    51,    39,    58,    60,    61,    62,   119,
     120,    64,    63,    65,    84,    40,    41,    92,    31,    31,
     121,   127,    53,    41,    94,   110,   112,   111,   118,   107,
      31,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,   108,   109,   114,   115,   113,   125,   117,
     122,     8,   123,    17,   124,   126,     0,   128,     0,     0,
     116
};

static const yytype_int8 yycheck[] =
{
      16,    39,    40,    20,    29,     3,     8,    39,    25,    26,
      40,     4,     5,    29,     7,     0,    21,    10,    23,    12,
      25,    38,    15,    16,    17,    18,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    69,    21,    56,
      57,    21,     5,    23,     8,    48,    49,    40,    65,    40,
      22,     9,    26,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    19,    21,    21,    40,    40,
      21,     8,    19,     8,    21,    27,     8,     8,     8,   114,
     115,    25,     8,    25,     8,    39,    40,    23,   114,   115,
     117,   126,    39,    40,    22,     9,     6,    24,    39,    22,
     126,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    22,    22,    26,    26,    24,    11,    25,
      24,     4,    27,    15,    27,    26,    -1,    27,    -1,    -1,
     110
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,    42,    43,    44,    40,    62,     0,    43,    21,
       5,    45,    46,    40,    22,     9,    26,    45,     4,     5,
       7,    10,    12,    15,    16,    17,    18,    40,    47,    48,
      49,    50,    53,    54,    55,    56,    40,    40,    19,    21,
      39,    40,    50,    57,    58,    59,    60,    61,    21,    21,
       8,     8,    57,    39,    57,    21,    23,    25,    27,    47,
       8,     8,     8,     8,    25,    25,    57,    57,    58,    23,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    59,    59,     8,     8,     8,    39,    40,    51,    52,
      57,    57,    23,    57,    22,    58,    57,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    22,    22,    22,
       9,    24,     6,    24,    26,    26,    51,    25,    39,    47,
      47,    57,    24,    27,    27,    11,    26,    47,    27
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    45,    45,    46,
      47,    47,    48,    48,    48,    48,    48,    48,    48,    48,
      48,    48,    48,    49,    49,    49,    50,    51,    51,    51,
      52,    52,    53,    53,    54,    55,    55,    56,    56,    57,
      57,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    59,    59,    59,    59,    59,    59,    59,    60,    61,
      62
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     8,     0,     3,     1,     2,
       0,     2,     2,     2,     1,     1,     2,     2,     2,     2,
       3,     3,     3,     4,     2,     7,     4,     0,     3,     1,
       1,     1,     7,    11,     7,     1,     2,     3,     6,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     2,     4,     1,
       1
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
        case 2:
#line 293 "bison.y" /* yacc.c:1646  */
    {
    CodeNode *node = (yyvsp[0].node);
    std::string code = node->code;
    if (!has_main()) {
      printf("Error: No main function found\n");
      exit(1);
    }
    printf("%s\n", code.c_str());
}
#line 1601 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 304 "bison.y" /* yacc.c:1646  */
    { 
    CodeNode *node = new CodeNode;
    (yyval.node) = node;
}
#line 1610 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 309 "bison.y" /* yacc.c:1646  */
    {
    CodeNode *func  = (yyvsp[-1].node);
    CodeNode *funcs = (yyvsp[0].node);
    std::string code = func->code + funcs->code;

    CodeNode *node = new CodeNode;
    node->code = code;
    (yyval.node) = node;
}
#line 1624 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 320 "bison.y" /* yacc.c:1646  */
    {
            std::string func_name = (yyvsp[-6].op_val);

            CodeNode *arguments = (yyvsp[-4].node);
            CodeNode *statements = (yyvsp[-1].node);
            std::string code = std::string("func ") + func_name + std::string("\n");
            int num_args = 0;
            for (int i = 0; i < arguments->code.size(); i++) {
                if (arguments->code[i] == '@') {
                    code += patch::to_string(num_args);
                    num_args++;
                }
                else {
                  code += arguments->code[i];
                }
            }
            code += statements->code;
            code += std::string("endfunc\n");

            CodeNode *node = new CodeNode;
            node->code = code;
            (yyval.node) = node;
           }
#line 1652 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 344 "bison.y" /* yacc.c:1646  */
    { CodeNode *node = new CodeNode; (yyval.node) = node;}
#line 1658 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 345 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *arg = (yyvsp[-2].node);
            CodeNode *args = (yyvsp[0].node);
            std::string code = arg->code + args->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            (yyval.node) = node;
         }
#line 1671 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 353 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *arg = (yyvsp[0].node);
            std::string code = arg->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            (yyval.node) = node;
         }
#line 1683 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 361 "bison.y" /* yacc.c:1646  */
    {
            std::string var_name = (yyvsp[0].op_val);
            if (check_if_variable_in_symbol_table(var_name, Integer)) {
              printf("Error: Arguments have same variable name: %s\n", var_name.c_str());
              exit(1);
            }
            // @ is a special token that we will use in functin above.
            std::string code = std::string(". ") + var_name + std::string("\n");
            std::string code2 = std::string("= ") + var_name + std::string(", $@\n");
            add_variable_to_symbol_table(var_name, Integer);
            CodeNode *node = new CodeNode;
            node->code = code + code2;
            (yyval.node) = node;
         }
#line 1702 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 377 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            (yyval.node) = node;
          }
#line 1711 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 381 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *statement = (yyvsp[-1].node);
            CodeNode *statements = (yyvsp[0].node);
            std::string code = statement->code + statements->code;
            node->code = code;
            (yyval.node) = node;
          }
#line 1724 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 389 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *declaration = (yyvsp[-1].node);
            std::string code = declaration->code;
            node->code = code;
            (yyval.node) = node;
}
#line 1736 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 396 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *function_call = (yyvsp[-1].node);
            std::string code = function_call->code;
            node->code = code;
            (yyval.node) = node;
         }
#line 1748 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 403 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *if_statement = (yyvsp[0].node);
            std::string code = if_statement->code;
            node->code = code;
            (yyval.node) = node;
}
#line 1760 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 410 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *while_statement = (yyvsp[0].node);
            std::string code = while_statement->code;
            node->code = code;
            (yyval.node) = node;
}
#line 1772 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 417 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *return_statement = (yyvsp[-1].node);
            std::string code = return_statement->code;
            node->code = code;
            (yyval.node) = node;
}
#line 1784 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 424 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *assign_statement = (yyvsp[-1].node);
            std::string code = assign_statement->code;
            node->code = code;
            (yyval.node) = node;
}
#line 1796 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 431 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            std::string code = std::string("^");
            node->code = code;
            (yyval.node) = node;
}
#line 1807 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 437 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            std::string code = std::string("~");
            node->code = code;
            (yyval.node) = node;
}
#line 1818 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 443 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *expression = (yyvsp[-1].node);
            std::string code = expression->code;
            code += std::string(".> ") + expression->temp + std::string("\n");
            node->code = code;
            (yyval.node) = node;
}
#line 1831 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 451 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            std::string name = create_temp();
            std::string assign = build_temp(name, patch::to_string((yyvsp[-1].op_val)));
            std::string code = assign;
            code += std::string(".> ") + name + std::string("\n");
            node->code = assign + code;
            (yyval.node) = node;
}
#line 1845 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 460 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *expression = (yyvsp[-1].node);
            std::string code = expression->code;
            code += std::string(".< ") + expression->temp + std::string("\n");
            node->code = code;
            (yyval.node) = node;
}
#line 1858 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 470 "bison.y" /* yacc.c:1646  */
    {
        std::string var_name = (yyvsp[-2].op_val);

        if (check_if_variable_in_symbol_table(var_name, Integer)) {
          printf("Error: Variable %s already declared\n", var_name.c_str());
          exit(1);
        }

        CodeNode *integerexpression = (yyvsp[0].node);
        CodeNode *node = new CodeNode;
        std::string code = integerexpression->code;
        code += std::string(". ") + var_name + std::string("\n");
        code += std::string("= ") + var_name + std::string(", ") + integerexpression->temp + std::string("\n");
        add_variable_to_symbol_table(var_name, Integer);
        node->code = code;
        (yyval.node) = node;
}
#line 1880 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 487 "bison.y" /* yacc.c:1646  */
    {
                std::string var_name = (yyvsp[0].op_val);
                if (check_if_variable_in_symbol_table(var_name, Integer)) {
                  printf("Error: Variable %s already declared\n", var_name.c_str());
                  exit(1);
                }
                CodeNode *node = new CodeNode;
                std::string code = std::string(". ") + var_name + std::string("\n");
                node->code = code;
                add_variable_to_symbol_table(var_name, Integer);
                (yyval.node) = node;
             }
#line 1897 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 499 "bison.y" /* yacc.c:1646  */
    {
                CodeNode *node = new CodeNode;
                std::string var_name = (yyvsp[-5].op_val);
                if (check_if_variable_in_symbol_table(var_name, Array)) {
                  printf("Error: Array %s already declared\n", var_name.c_str());
                  exit(1);
                }
                add_variable_to_symbol_table(var_name, Array); // Arrays & Integers cannot have same name

                int j = atoi((yyvsp[-1].op_val));
                if (j < 1) {
                  printf("Error: Array size cannot be negative or zero\n");
                  exit(1);
                }
                

                std::string code = std::string(".[] ") + var_name + ", " + patch::to_string(j) + std::string("\n");
                node->code = code;
                (yyval.node) = node;
             }
#line 1922 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 520 "bison.y" /* yacc.c:1646  */
    {
                std::string func_name = (yyvsp[-3].op_val);
                if (!check_if_function_in_symbol_table(func_name)) {
                  printf("Error: Function %s does not exist \n", func_name.c_str());
                  exit(1);
                }

                CodeNode *params = (yyvsp[-1].node);
                std::string code = params->code;
                std::string temp = create_temp();

                code += ". " + temp + "\n";
                code += "call " + func_name + ", " + temp + "\n";


                CodeNode *node = new CodeNode;
                node->code = code;
                node->temp = temp;
                (yyval.node) = node;
              }
#line 1947 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 541 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            (yyval.node) = node;
}
#line 1956 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 545 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *param = (yyvsp[-2].node);
            CodeNode *params = (yyvsp[0].node);
            std::string code = param->code + params->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            (yyval.node) = node;
        }
#line 1969 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 553 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *param = (yyvsp[0].node);
            std::string code = param->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            (yyval.node) = node;
        }
#line 1981 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 561 "bison.y" /* yacc.c:1646  */
    {
            std::string name = create_temp();
            std::string assign = build_temp(name, patch::to_string((yyvsp[0].op_val)));
            std::string code = std::string("param ") + name + std::string("\n");
            CodeNode *node = new CodeNode;
            node->code = assign + code;
            (yyval.node) = node;
}
#line 1994 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 569 "bison.y" /* yacc.c:1646  */
    {
            std::string var_name = (yyvsp[0].op_val);
            variable_exist(var_name, Integer);
            std::string code = std::string("param ") + (yyvsp[0].op_val) + std::string("\n");
            CodeNode *node = new CodeNode;
            node->code = code;
            (yyval.node) = node;
}
#line 2007 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 580 "bison.y" /* yacc.c:1646  */
    {
                CodeNode *node = new CodeNode;
                CodeNode *booleanexpression = (yyvsp[-4].node);
                CodeNode *statements = (yyvsp[-1].node);
                std::string code = booleanexpression->code;

                std::string label_body = create_temp() + std::string("_if_body");
                std::string label_end = create_temp() + std::string("_if_end");

                code += std::string("?:= ") + label_body  + std::string(", ") + booleanexpression->temp + std::string("\n");
                code += std::string(":= ") + label_end + std::string("\n");
                code += std::string(": ") + label_body + std::string("\n");
                code += statements->code;
                code += std::string(": ") + label_end + std::string("\n");
                node->code = code;
                (yyval.node) = node;
}
#line 2029 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 597 "bison.y" /* yacc.c:1646  */
    {
                CodeNode *node = new CodeNode;
                CodeNode *booleanexpression = (yyvsp[-8].node);
                CodeNode *if_statements = (yyvsp[-5].node);
                CodeNode *else_statements = (yyvsp[-1].node);
                std::string code = booleanexpression->code;

                std::string if_body = create_temp() + std::string("_if_body");
                std::string else_body = create_temp() + std::string("_else_body");
                std::string end_end = create_temp() + std::string("_end_end");

                code += std::string("?:= ") + if_body+ std::string(", ") +   booleanexpression->temp + std::string("\n");
                code += std::string(":= ") + else_body + std::string("\n");
                code += std::string(": ") + if_body + std::string("\n");
                code += if_statements->code;
                code += std::string(":= ") + end_end + std::string("\n");
                code += std::string(": ") + else_body + std::string("\n");
                code += else_statements->code;
                code += std::string(": ") + end_end + std::string("\n");
                node->code = code;
                (yyval.node) = node;
            }
#line 2056 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 620 "bison.y" /* yacc.c:1646  */
    {
                CodeNode *node = new CodeNode;
                CodeNode *booleanexpression = (yyvsp[-4].node);
                CodeNode *statements = (yyvsp[-1].node);

                std::string loop_start = create_temp() + std::string("_loop_start");
                std::string loop_body = create_temp() + std::string("_loop_body");
                std::string loop_end = create_temp() + std::string("_loop_end");

                std::string code = std::string(": ") + loop_start + std::string("\n");      
                code += booleanexpression->code;     
                code += std::string("?:= ") + loop_body + std::string(", ") +  booleanexpression->temp + std::string("\n");
                code += std::string(":= ") + loop_end + std::string("\n");
                code += std::string(": ") + loop_body + std::string("\n");
                for (int i = 0; i < statements->code.size(); i++) {
                    if (statements->code[i] == '^') {
                        code += std::string(":= ") + loop_start + std::string("\n");
                    }
                    else if (statements->code[i] == '~') {
                        code += std::string(":= ") + loop_end + std::string("\n");
                    }
                    else {
                      code += statements->code[i];
                    }
                }
                code += std::string(":= ") + loop_start + std::string("\n");
                code += std::string(": ") + loop_end + std::string("\n");
                node->code = code;
                (yyval.node) = node;


}
#line 2093 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 653 "bison.y" /* yacc.c:1646  */
    {
                    CodeNode *node = new CodeNode;
                    Function * f = get_function();
                    if (f->name == "main") {
                      node->code = std::string("\n");
                    }
                    else {

                    node->code = std::string("ret 0\n");
                    }
                    (yyval.node) = node;
                  }
#line 2110 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 665 "bison.y" /* yacc.c:1646  */
    {
                    CodeNode *node = new CodeNode;
                    CodeNode *expression = (yyvsp[0].node);
                    std::string code = expression->code;

                    // Get function and check if it is main or not
                    Function * f = get_function();
                    if (f->name == "main") {
                      printf("Error: Cannot return from main function\n");
                      exit(1);
                    }
                    
                    code += std::string("ret ") + expression->temp + std::string("\n");
                    node->code = code;
                    (yyval.node) = node;
                }
#line 2131 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 682 "bison.y" /* yacc.c:1646  */
    {
                    CodeNode *node = new CodeNode;
                    std::string var_name = (yyvsp[-2].op_val);
                    variable_exist(var_name, Integer);
                    CodeNode *expression = (yyvsp[0].node);
                    std::string code = expression->code;
                    code += std::string("= ") + var_name + std::string(", ") + expression->temp + std::string("\n");
                    node->code = code;
                    (yyval.node) = node;
}
#line 2146 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 692 "bison.y" /* yacc.c:1646  */
    {
                    CodeNode *node = new CodeNode;
                    std::string var_name = (yyvsp[-5].op_val);
                    variable_exist(var_name, Array);
                    CodeNode *expression1 = (yyvsp[-3].node);
                    CodeNode *expression2 = (yyvsp[0].node);
                    std::string code = expression1->code;
                    code += expression2->code;
                    code += std::string("[]= ") + var_name + std::string(", ") + expression1->temp + std::string(", ") + expression2->temp + std::string("\n");
                    node->code = code;
                    (yyval.node) = node;
                }
#line 2163 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 705 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            std::string temp = (yyvsp[0].op_val);
            variable_exist(temp, Integer);
            node->temp = temp;
            node->code = "";
            (yyval.node) = node;
          }
#line 2176 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 713 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *integerexpression = (yyvsp[0].node);
            std::string temp = integerexpression->temp;
            std::string code = integerexpression->code;
            node->temp = temp;
            node->code = code;
            (yyval.node) = node;
          }
#line 2190 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 722 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *booleanexpression = (yyvsp[0].node);
            std::string temp = booleanexpression->temp;
            std::string code = booleanexpression->code;
            node->temp = temp;
            node->code = code;
            (yyval.node) = node;
          }
#line 2204 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 731 "bison.y" /* yacc.c:1646  */
    {
            CodeNode *node = new CodeNode;
            CodeNode *arrayexpression = (yyvsp[0].node);
            std::string temp = arrayexpression->temp;
            std::string code = arrayexpression->code;
            node->temp = temp;
            node->code = code;
            (yyval.node) = node;
          }
#line 2218 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 741 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *integer_expression_actual_number = (yyvsp[0].node);
              std::string temp = integer_expression_actual_number->temp;
              node->temp = temp;
              (yyval.node) = node;
            }
#line 2230 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 748 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *integerexpression = (yyvsp[-1].node);
              std::string temp = integerexpression->temp;
              node->temp = temp;
              node->code = integerexpression->code;
              (yyval.node) = node;
            }
#line 2243 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 756 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "+ " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
            }
#line 2261 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 769 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "- " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
            }
#line 2279 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 782 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "* " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
            }
#line 2297 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 795 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "/ " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
            }
#line 2315 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 808 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "% " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
            }
#line 2333 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 821 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *function_call = (yyvsp[0].node);
              std::string temp = function_call->temp;
              std::string code = function_call->code;
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
            }
#line 2347 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 831 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "== " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
}
#line 2365 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 844 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "!= " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
          }
#line 2383 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 857 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "< " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
          }
#line 2401 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 870 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "> " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
          }
#line 2419 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 883 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "<= " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
          }
#line 2437 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 896 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[-2].node);
              CodeNode *expression2 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += ">= " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
          }
#line 2455 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 909 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = (yyvsp[0].node);
              std::string temp1 = expression1->temp;
              std::string code = expression1->code;
              std::string temp = create_temp_with_code(code);
              code += "! " + temp + ", " + temp1 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
          }
#line 2471 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 921 "bison.y" /* yacc.c:1646  */
    {
              CodeNode *node = new CodeNode;
              CodeNode *integer_expression = (yyvsp[-1].node);
              std::string var_name = (yyvsp[-3].op_val);
              variable_exist(var_name, Array);
              std::string temp1 = integer_expression->temp;
              std::string code = integer_expression->code;
              std::string temp = create_temp_with_code(code);
              code += "=[] " + temp + ", " + var_name + ", " + temp1 + "\n";
              node->code = code;
              node->temp = temp;
              (yyval.node) = node;
}
#line 2489 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 936 "bison.y" /* yacc.c:1646  */
    {
  CodeNode *node = new CodeNode;
  node->temp = (yyvsp[0].op_val);
  (yyval.node) = node;
}
#line 2499 "bison.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 942 "bison.y" /* yacc.c:1646  */
    {
  std::string func_name = (yyvsp[0].op_val);
  if (check_if_function_in_symbol_table(func_name)) {
    printf("Error: Function %s already defined\n", func_name.c_str());
    exit(1);
  }
  add_function_to_symbol_table(func_name);
  (yyval.op_val) = (yyvsp[0].op_val);
}
#line 2513 "bison.tab.c" /* yacc.c:1646  */
    break;


#line 2517 "bison.tab.c" /* yacc.c:1646  */
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
#line 952 "bison.y" /* yacc.c:1906  */



int main(int argc, char** argv){
	if(argc >= 2){
		yyin = fopen(argv[1], "r");
		if(yyin == NULL)
			yyin = stdin;
	}else{
		yyin = stdin;
	}
	yyparse();
     return 0;
}

/* Called by yyparse on error. */
void yyerror(const char *msg)
{
   printf("** Line %d: %s\n", current_line, msg);
   exit(1);
}
