/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20200330

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0


#include "wml.h"

#if defined(__STDC__)
#include <string.h>		/* for strcpy() */
#endif

#ifndef XmConst
#if defined(__STDC__) || !defined( NO_CONST )
#define XmConst const
#else
#define XmConst
#endif /* __STDC__ */
#endif /* XmConst */

#if !defined(__STDC__)
/*
 * Undefine NULL, since it is defined in stdio
 */
#undef NULL
#endif


#if ! defined(YYSTYPE) && ! defined(YYSTYPE_IS_DECLARED)
/* Default: YYSTYPE is the semantic value type. */
typedef int YYSTYPE;
# define YYSTYPE_IS_DECLARED 1
#endif

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

#if !(defined(yylex) || defined(YYSTATE))
int YYLEX_DECL();
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define CLASS 1
#define RESOURCE 2
#define DATATYPE 3
#define CONTROLLIST 4
#define ENUMERATIONSET 5
#define ENUMERATIONVALUE 6
#define CHARACTERSET 7
#define CHILD 50
#define DOCNAME 8
#define CONVFUNC 9
#define ALIAS 10
#define TYPE 11
#define RESOURCELITERAL 12
#define RELATED 13
#define INTERNALLITERAL 14
#define XRMRESOURCE 15
#define EXCLUDE 16
#define RESOURCES 17
#define SUPERCLASS 18
#define CONTROLS 19
#define WIDGETCLASS 20
#define DIALOGCLASS 21
#define DEFAULT 22
#define ENUMLITERAL 23
#define XMSTRINGCHARSETNAME 24
#define DIRECTION 25
#define PARSEDIRECTION 26
#define CHARACTERSIZE 27
#define CTRLMAPSRESOURCE 28
#define CHILDREN 51
#define PARENTCLASS 52
#define METACLASS 29
#define WIDGET 30
#define GADGET 31
#define ARGUMENT 32
#define REASON 33
#define CONSTRAINT 34
#define SUBRESOURCE 35
#define ATTRTRUE 36
#define ATTRFALSE 37
#define LEFTTORIGHT 38
#define RIGHTTOLEFT 39
#define ONEBYTE 40
#define TWOBYTE 41
#define MIXED1_2BYTE 42
#define COLON 43
#define SEMICOLON 44
#define EQUALS 45
#define LBRACE 46
#define RBRACE 47
#define STRING 48
#define ERRORTOKEN 49
#define YYERRCODE 256
typedef int YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    1,    1,    1,    1,    1,    1,    1,    1,
   10,    1,    2,   11,   11,   13,   11,    3,   14,   14,
   16,   14,    4,   17,   17,   19,   17,    5,   20,   20,
   22,   20,    6,   23,   23,   25,   23,    7,   26,   26,
   28,   26,    8,   29,   29,   31,   29,    9,   32,   32,
   34,   32,   38,   12,   36,   36,   36,   37,   37,   37,
   40,   37,   39,   39,   43,   41,   46,   41,   41,   41,
   41,   50,   41,   42,   42,   42,   42,   42,   42,   42,
   44,   45,   45,   47,   51,   51,   51,   53,   51,   52,
   52,   56,   54,   57,   54,   55,   55,   55,   59,   55,
   58,   58,   62,   60,   64,   60,   65,   60,   61,   61,
   63,   48,   66,   66,   66,   68,   66,   67,   67,   71,
   69,   72,   69,   70,   70,   73,   70,   49,   74,   74,
   74,   76,   74,   75,   75,   78,   77,   79,   77,   82,
   15,   80,   80,   80,   80,   81,   81,   81,   84,   81,
   83,   83,   87,   85,   89,   85,   90,   85,   86,   86,
   86,   86,   86,   86,   86,   86,   88,   18,   92,   21,
   91,   91,   91,   94,   91,   93,   93,   97,   95,   98,
   95,   96,   96,   96,  100,   24,   99,   99,   99,  102,
   99,  101,  101,  105,  103,  106,  103,  104,  104,  107,
  104,  110,   27,  108,  109,  109,  109,  112,  109,  111,
  111,  114,  113,  115,  113,  117,   30,  116,  116,  116,
  119,  116,  118,  118,  122,  120,  123,  120,  121,  125,
   33,  124,  124,  124,  127,  124,  126,  126,  130,  128,
  133,  128,  134,  128,  129,  129,  129,  131,  131,  131,
  132,  132,  132,  132,  132,   35,
};
static const YYINT yylen[] = {                            2,
    0,    2,    1,    1,    1,    1,    1,    1,    1,    1,
    0,    3,    2,    2,    3,    0,    3,    2,    2,    3,
    0,    3,    2,    2,    3,    0,    3,    2,    2,    3,
    0,    3,    2,    2,    3,    0,    3,    2,    2,    3,
    0,    3,    2,    2,    3,    0,    3,    2,    2,    3,
    0,    3,    0,    5,    1,    1,    1,    0,    2,    3,
    0,    3,    1,    2,    0,    5,    0,    5,    2,    2,
    2,    0,    3,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    2,    0,    2,    3,    0,    3,    1,
    2,    0,    4,    0,    3,    0,    2,    3,    0,    3,
    1,    2,    0,    5,    0,    5,    0,    3,    1,    1,
    1,    2,    0,    2,    3,    0,    3,    1,    2,    0,
    4,    0,    3,    0,    2,    0,    3,    2,    0,    2,
    3,    0,    3,    1,    2,    0,    3,    0,    3,    0,
    5,    1,    1,    1,    1,    0,    2,    3,    0,    3,
    1,    2,    0,    5,    0,    5,    0,    3,    1,    1,
    1,    1,    1,    1,    1,    1,    1,    3,    0,    3,
    0,    2,    3,    0,    3,    1,    2,    0,    5,    0,
    3,    1,    1,    1,    0,    3,    0,    2,    3,    0,
    3,    1,    2,    0,    4,    0,    3,    0,    2,    0,
    3,    0,    5,    1,    0,    2,    3,    0,    3,    1,
    2,    0,    3,    0,    3,    0,    4,    0,    2,    3,
    0,    3,    1,    2,    0,    5,    0,    3,    1,    0,
    3,    0,    2,    3,    0,    3,    1,    2,    0,    5,
    0,    5,    0,    3,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,    1,
};
static const YYINT yydefred[] = {                         1,
    0,   11,    0,    0,    0,    0,    0,    0,    0,    0,
    2,    3,    4,    5,    6,    7,    8,    9,   10,    0,
   16,  256,    0,    0,    0,   21,    0,    0,    0,   31,
    0,    0,  169,   36,    0,    0,  185,   41,    0,    0,
    0,   46,    0,    0,    0,   51,    0,    0,  230,   26,
    0,    0,    0,   12,    0,    0,   14,    0,    0,    0,
   19,    0,    0,    0,   29,    0,    0,    0,   34,    0,
    0,    0,   39,    0,    0,    0,   44,  216,    0,    0,
   49,    0,    0,    0,   24,    0,   17,   15,   55,   56,
   57,   53,   22,   20,  142,  143,  144,  145,  140,   32,
   30,  174,    0,  170,   37,   35,  190,    0,  186,   42,
   40,  204,  202,   47,   45,    0,   52,   50,  235,    0,
  231,   27,   25,  168,    0,    0,    0,  180,  183,  182,
  184,  172,    0,  176,    0,    0,  196,  188,  194,    0,
  192,    0,  221,    0,  217,    0,  243,  246,  245,  247,
  248,  249,  250,  233,    0,  237,    0,    0,   61,    0,
   54,  149,    0,  141,  175,    0,  173,  177,    0,  191,
    0,    0,  189,  193,  208,    0,  203,    0,  227,  229,
  219,    0,  223,    0,  236,    0,  234,  238,    0,    0,
    0,   72,   77,   78,   76,    0,   74,    0,   79,   81,
   80,    0,   75,   59,    0,   63,    0,    0,    0,    0,
    0,    0,  157,  161,  164,  166,  159,  160,  163,  162,
  167,  165,  147,    0,  151,    0,    0,  181,  178,  197,
  200,    0,    0,    0,  214,  206,  212,    0,  210,  222,
    0,  220,  224,    0,  244,  239,  251,  252,  253,  254,
  255,  241,   62,    0,   88,    0,   84,  116,    0,  112,
  132,    0,  128,   60,   64,    0,    0,   69,   70,   71,
  150,    0,  148,  152,    0,    0,    0,    0,  199,  195,
  209,    0,    0,  207,  211,  228,  225,    0,    0,   73,
    0,   94,   86,   92,    0,   90,    0,  122,  114,  120,
    0,  118,    0,  138,  130,  136,    0,  134,   65,   82,
   83,   67,  158,  153,  155,  179,  201,  215,  213,    0,
  240,  242,   89,    0,    0,   87,   91,  117,    0,    0,
  115,  119,  133,    0,    0,  131,  135,    0,    0,    0,
    0,  226,   95,   99,    0,    0,  123,  126,    0,    0,
  139,  137,   66,   68,  154,  156,    0,  107,  109,  111,
  110,   97,    0,  101,    0,    0,   93,    0,  125,  121,
  100,    0,   98,  102,    0,    0,  127,  108,  103,  105,
    0,    0,  104,  106,
};
static const YYINT yydgoto[] = {                          1,
   11,   12,   13,   14,   15,   16,   17,   18,   19,   20,
   23,   24,   55,   27,   28,   59,   51,   52,   83,   31,
   32,   63,   35,   36,   67,   39,   40,   71,   43,   44,
   75,   47,   48,   79,   25,   92,  161,  125,  205,  191,
  206,  207,  338,  208,  312,  339,  209,  210,  211,  254,
  257,  295,  291,  296,  346,  325,  324,  363,  357,  364,
  365,  381,  366,  382,  372,  260,  301,  297,  302,  350,
  330,  329,  368,  263,  307,  303,  308,  335,  334,   99,
  164,  126,  224,  212,  225,  226,  340,  227,  341,  272,
  104,   66,  133,  127,  134,  135,  277,  166,  109,   70,
  140,  136,  141,  233,  172,  171,  278,  113,  177,  142,
  238,  234,  239,  283,  282,  145,  116,  182,  178,  183,
  184,  320,  241,  121,   82,  155,  146,  156,  157,  288,
  158,  252,  289,  186,
};
static const YYINT yysindex[] = {                         0,
  116,    0,  -24,   -3,   12,   65,   81,   87,   93,   95,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -18,
    0,    0,  -20,  -11,   -1,    0,  -20,    2,   59,    0,
  -20,  108,    0,    0,  -20,  109,    0,    0,  -20,  114,
   60,    0,  -20,  121,  126,    0,  -20,  156,    0,    0,
  -20,  175,  143,    0,  184,  185,    0,  193,  196,  202,
    0,  227,  205,  212,    0,  -17,  213,  222,    0,   -9,
  236,  238,    0,  187,  239,  240,    0,    0,  241,  242,
    0,   -8,  243,  244,    0,  233,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  123,    0,    0,    0,    0,   67,    0,    0,
    0,    0,    0,    0,    0,   -6,    0,    0,    0,  191,
    0,    0,    0,    0,   -5,   -2,  186,    0,    0,    0,
    0,    0,  189,    0,  192,  245,    0,    0,    0,   78,
    0,   13,    0,    9,    0,  246,    0,    0,    0,    0,
    0,    0,    0,    0,  217,    0,  249,  250,    0,  159,
    0,    0,  134,    0,    0,  252,    0,    0,  251,    0,
  254,   16,    0,    0,    0,   80,    0,  253,    0,    0,
    0,   11,    0,  256,    0,  258,    0,    0,  257,  237,
  259,    0,    0,    0,    0,   17,    0,   18,    0,    0,
    0,   53,    0,    0,  174,    0,  262,  263,  268,  269,
  270,  271,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  149,    0,  272,  274,    0,    0,    0,
    0,  273,  280,  278,    0,    0,    0,   86,    0,    0,
  282,    0,    0,  267,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  283,    0,  103,    0,    0,  127,    0,
    0,  137,    0,    0,    0,  281,  176,    0,    0,    0,
    0,  284,    0,    0,  285,  176,  287,  288,    0,    0,
    0,  295,  296,    0,    0,    0,    0,  297,  300,    0,
  298,    0,    0,    0,  142,    0,  301,    0,    0,    0,
  151,    0,  303,    0,    0,    0,  160,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  308,
    0,    0,    0,  309,   54,    0,    0,    0,  310,   55,
    0,    0,    0,  311,  312,    0,    0,  313,  314,  316,
  318,    0,    0,    0,   14,  319,    0,    0,  317,  321,
    0,    0,    0,    0,    0,    0,  320,    0,    0,    0,
    0,    0,  198,    0,  302,  323,    0,  322,    0,    0,
    0,  326,    0,    0,  325,  176,    0,    0,    0,    0,
  327,  330,    0,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    7,    0,    0,    0,   15,    0,    0,    0,
   48,    0,    0,    0,   66,    0,    0,    0,   74,    0,
    0,    0,   82,    0,    0,    0,   90,    0,    0,    0,
  105,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  331,    0,    0,    0,  332,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  333,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  334,    0,    0,    0,    0,
    0,    0,    0,    0,  336,  337,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  338,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  340,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,  175,    0,  341,    0,    0,
    0,  342,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  343,    0,    0,    0,    0,  344,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  266,    0,    0,  289,    0,    0,  315,    0,    0,
  358,    0,    0,  255,    0,    0,  293,    0,    0,  348,
    0,    0,  345,    0,   -4,    0,    0,    0,    0,    0,
  190,    0,    0,    0, -146,    0,    0,    0,    0,    0,
    0,    0,    0,   99,    0,    0,    0,    0,    0,   33,
    0,    0,    0,    0,    0,    0,    0,    0,   96,    0,
    0,    0,    0,    0,    0,    0,   92,    0,    0,    0,
    0,    0,    0,    0,  177,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  275,    0,    0,    0,    0,    0,
    0,    0,  260,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  164,    0,    0,    0,    0,    0,    0,  221,
    0,    0,    0,    0,    0,    0,    0,  264,    0,    0,
    0,    0,    0,    0,
};
#define YYTABLESIZE 473
static const YYINT yytable[] = {                         29,
   33,   37,   41,   45,   49,   53,   13,   13,   13,   13,
   13,   13,   13,   13,   18,   18,   18,   18,   18,   18,
   18,   18,   29,   22,  359,   54,   33,   22,  103,  360,
   37,  180,   57,  180,   41,  361,  108,  120,   45,  144,
  160,   58,   49,  163,   22,   61,   53,   28,   28,   28,
   28,   28,   28,   28,   28,  181,   13,  242,  176,   22,
  362,  232,  256,  259,   18,   33,   33,   33,   33,   33,
   33,   33,   33,   38,   38,   38,   38,   38,   38,   38,
   38,   43,   43,   43,   43,   43,   43,   43,   43,   48,
   48,   48,   48,   48,   48,   48,   48,   28,  262,  345,
  349,   62,   74,  139,   23,   23,   23,   23,   23,   23,
   23,   23,   22,  138,   22,   33,    3,    4,    5,    6,
    7,    8,    9,   38,  173,   22,  236,   22,   22,  315,
  129,   43,  284,   22,   22,  139,  130,  131,  214,   48,
   22,  215,   22,  216,  217,  218,  219,  220,  221,  293,
   22,   65,   69,  214,   23,  222,  215,   73,  216,  217,
  218,  219,  220,  221,   77,   10,  193,  194,   78,  132,
  222,  237,  195,  299,   22,  196,  197,  198,  199,  200,
  223,  193,  194,  305,   22,   86,  201,  195,  326,   22,
  196,  197,  198,  199,  200,  273,  129,  331,   22,   81,
  148,  201,  130,  131,  149,  204,  336,   22,  359,  202,
  203,  310,  311,  360,  150,  151,  152,  153,   85,  361,
  264,   89,   90,   91,  202,  203,  148,   87,   88,  380,
  149,   21,  165,  237,  112,  167,  169,  154,  102,   93,
  150,  151,  152,  153,  373,   94,  107,  119,  100,  143,
  159,  294,   26,  162,  300,  101,  105,  306,   95,   96,
   97,   98,   13,  187,  179,  106,  179,   30,  175,  358,
   18,  231,  255,  258,  247,  248,  249,  250,  251,  110,
  124,  111,  114,  115,  117,  118,  122,  123,   56,   68,
  294,  170,  185,  189,  190,  228,  300,  230,  229,  240,
  244,  245,  306,   28,  246,  253,  266,  267,  261,  344,
  348,  268,  269,  270,  287,   60,  275,  271,  276,  279,
   34,   33,  137,  280,  281,  286,  290,  313,  309,   38,
  316,   72,  314,  137,  317,  235,   38,   43,  318,  319,
  321,  235,   42,  322,  323,   48,  375,  328,   46,  333,
   50,  342,  343,  347,  351,  352,  353,  354,  292,  355,
   23,  356,  367,  369,  370,   84,  371,  376,  377,  378,
  383,    2,  379,  384,  171,  187,  232,  218,  128,   58,
  146,  205,  298,  198,  113,  129,   96,  124,   64,  213,
   76,   80,  304,  327,  265,  374,  332,  292,  337,  174,
  274,  285,  243,    0,  213,    0,  298,  168,    0,    0,
    0,    0,    0,    0,  192,  304,    0,    0,  188,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  192,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  128,    0,  147,    0,    0,    0,
    0,    0,    0,  358,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,  147,
};
static const YYINT yycheck[] = {                          4,
    5,    6,    7,    8,    9,   10,    0,    1,    2,    3,
    4,    5,    6,    7,    0,    1,    2,    3,    4,    5,
    6,    7,   27,   48,   11,   44,   31,   48,   46,   16,
   35,   23,   44,   23,   39,   22,   46,   46,   43,   46,
   46,   43,   47,   46,   48,   44,   51,    0,    1,    2,
    3,    4,    5,    6,    7,   47,   50,   47,   46,   48,
   47,   46,   46,   46,   50,    0,    1,    2,    3,    4,
    5,    6,    7,    0,    1,    2,    3,    4,    5,    6,
    7,    0,    1,    2,    3,    4,    5,    6,    7,    0,
    1,    2,    3,    4,    5,    6,    7,   50,   46,   46,
   46,   43,   43,  108,    0,    1,    2,    3,    4,    5,
    6,    7,   48,   47,   48,   50,    1,    2,    3,    4,
    5,    6,    7,   50,   47,   48,   47,   48,   48,  276,
    8,   50,   47,   48,   48,  140,   14,   15,    5,   50,
   48,    8,   48,   10,   11,   12,   13,   14,   15,   47,
   48,   44,   44,    5,   50,   22,    8,   44,   10,   11,
   12,   13,   14,   15,   44,   50,    8,    9,   43,   47,
   22,  176,   14,   47,   48,   17,   18,   19,   20,   21,
   47,    8,    9,   47,   48,   43,   28,   14,   47,   48,
   17,   18,   19,   20,   21,   47,    8,   47,   48,   44,
   10,   28,   14,   15,   14,   47,   47,   48,   11,   51,
   52,   36,   37,   16,   24,   25,   26,   27,   44,   22,
   47,   29,   30,   31,   51,   52,   10,   44,   44,  376,
   14,  256,   47,  238,   48,   47,   45,   47,  256,   44,
   24,   25,   26,   27,   47,   44,  256,  256,   44,  256,
  256,  256,  256,  256,  259,   44,   44,  262,   32,   33,
   34,   35,  256,   47,  256,   44,  256,  256,  256,  256,
  256,  256,  256,  256,   38,   39,   40,   41,   42,   44,
   48,   44,   44,   44,   44,   44,   44,   44,   23,   35,
  295,   47,   47,   45,   45,   44,  301,   44,   48,   47,
   45,   44,  307,  256,   48,   47,   45,   45,  256,  256,
  256,   44,   44,   44,   48,   27,   45,   47,   45,   47,
  256,  256,  256,   44,   47,   44,   44,   44,   48,  256,
   44,   39,   48,  256,   47,  256,  256,  256,   44,   44,
   44,  256,  256,   44,   47,  256,   45,   47,  256,   47,
  256,   44,   44,   44,   44,   44,   44,   44,  256,   44,
  256,   44,   44,   47,   44,   51,   47,   45,   47,   44,
   44,  256,   48,   44,   44,   44,   44,   44,  256,   44,
   44,   44,  256,   44,   44,   44,   44,   44,   31,  256,
   43,   47,  256,  295,  205,  363,  301,  256,  307,  140,
  224,  238,  182,   -1,  256,   -1,  256,  133,   -1,   -1,
   -1,   -1,   -1,   -1,  256,  256,   -1,   -1,  155,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  256,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  256,   -1,  256,   -1,   -1,   -1,
   -1,   -1,   -1,  256,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  256,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 256
#define YYUNDFTOKEN 393
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file","CLASS","RESOURCE","DATATYPE","CONTROLLIST","ENUMERATIONSET",
"ENUMERATIONVALUE","CHARACTERSET","DOCNAME","CONVFUNC","ALIAS","TYPE",
"RESOURCELITERAL","RELATED","INTERNALLITERAL","XRMRESOURCE","EXCLUDE",
"RESOURCES","SUPERCLASS","CONTROLS","WIDGETCLASS","DIALOGCLASS","DEFAULT",
"ENUMLITERAL","XMSTRINGCHARSETNAME","DIRECTION","PARSEDIRECTION",
"CHARACTERSIZE","CTRLMAPSRESOURCE","METACLASS","WIDGET","GADGET","ARGUMENT",
"REASON","CONSTRAINT","SUBRESOURCE","ATTRTRUE","ATTRFALSE","LEFTTORIGHT",
"RIGHTTOLEFT","ONEBYTE","TWOBYTE","MIXED1_2BYTE","COLON","SEMICOLON","EQUALS",
"LBRACE","RBRACE","STRING","ERRORTOKEN","CHILD","CHILDREN","PARENTCLASS",0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : statement_block_list",
"statement_block_list :",
"statement_block_list : statement_block_list statement_block",
"statement_block : class_statement_block",
"statement_block : resource_statement_block",
"statement_block : child_statement_block",
"statement_block : datatype_statement_block",
"statement_block : ctrlist_statement_block",
"statement_block : enumset_statement_block",
"statement_block : enumval_statement_block",
"statement_block : charset_statement_block",
"$$1 :",
"statement_block : error $$1 SEMICOLON",
"class_statement_block : CLASS class_statement_list",
"class_statement_list : class_statement SEMICOLON",
"class_statement_list : class_statement_list class_statement SEMICOLON",
"$$2 :",
"class_statement_list : error $$2 SEMICOLON",
"resource_statement_block : RESOURCE resource_statement_list",
"resource_statement_list : resource_statement SEMICOLON",
"resource_statement_list : resource_statement_list resource_statement SEMICOLON",
"$$3 :",
"resource_statement_list : error $$3 SEMICOLON",
"child_statement_block : CHILD child_statement_list",
"child_statement_list : child_statement SEMICOLON",
"child_statement_list : child_statement_list child_statement SEMICOLON",
"$$4 :",
"child_statement_list : error $$4 SEMICOLON",
"datatype_statement_block : DATATYPE datatype_statement_list",
"datatype_statement_list : datatype_statement SEMICOLON",
"datatype_statement_list : datatype_statement_list datatype_statement SEMICOLON",
"$$5 :",
"datatype_statement_list : error $$5 SEMICOLON",
"ctrlist_statement_block : CONTROLLIST ctrlist_statement_list",
"ctrlist_statement_list : ctrlist_statement SEMICOLON",
"ctrlist_statement_list : ctrlist_statement_list ctrlist_statement SEMICOLON",
"$$6 :",
"ctrlist_statement_list : error $$6 SEMICOLON",
"enumset_statement_block : ENUMERATIONSET enumset_statement_list",
"enumset_statement_list : enumset_statement SEMICOLON",
"enumset_statement_list : enumset_statement_list enumset_statement SEMICOLON",
"$$7 :",
"enumset_statement_list : error $$7 SEMICOLON",
"enumval_statement_block : ENUMERATIONVALUE enumval_statement_list",
"enumval_statement_list : enumval_statement SEMICOLON",
"enumval_statement_list : enumval_statement_list enumval_statement SEMICOLON",
"$$8 :",
"enumval_statement_list : error $$8 SEMICOLON",
"charset_statement_block : CHARACTERSET charset_statement_list",
"charset_statement_list : charset_statement SEMICOLON",
"charset_statement_list : charset_statement_list charset_statement SEMICOLON",
"$$9 :",
"charset_statement_list : error $$9 SEMICOLON",
"$$10 :",
"class_statement : name COLON class_type $$10 class_definition",
"class_type : METACLASS",
"class_type : WIDGET",
"class_type : GADGET",
"class_definition :",
"class_definition : LBRACE RBRACE",
"class_definition : LBRACE class_attribute_list RBRACE",
"$$11 :",
"class_definition : error $$11 RBRACE",
"class_attribute_list : class_attribute",
"class_attribute_list : class_attribute_list class_attribute",
"$$12 :",
"class_attribute : class_attribute_name EQUALS STRING $$12 SEMICOLON",
"$$13 :",
"class_attribute : boolean_class_attribute_name EQUALS boolean_attribute_value $$13 SEMICOLON",
"class_attribute : class_resources SEMICOLON",
"class_attribute : class_controls SEMICOLON",
"class_attribute : class_children SEMICOLON",
"$$14 :",
"class_attribute : error $$14 SEMICOLON",
"class_attribute_name : SUPERCLASS",
"class_attribute_name : PARENTCLASS",
"class_attribute_name : INTERNALLITERAL",
"class_attribute_name : DOCNAME",
"class_attribute_name : CONVFUNC",
"class_attribute_name : WIDGETCLASS",
"class_attribute_name : CTRLMAPSRESOURCE",
"boolean_class_attribute_name : DIALOGCLASS",
"boolean_attribute_value : ATTRTRUE",
"boolean_attribute_value : ATTRFALSE",
"class_resources : RESOURCES class_resources_block",
"class_resources_block :",
"class_resources_block : LBRACE RBRACE",
"class_resources_block : LBRACE class_resource_list RBRACE",
"$$15 :",
"class_resources_block : error $$15 RBRACE",
"class_resource_list : class_resource_element",
"class_resource_list : class_resource_list class_resource_element",
"$$16 :",
"class_resource_element : name $$16 class_resource_attributes SEMICOLON",
"$$17 :",
"class_resource_element : error $$17 SEMICOLON",
"class_resource_attributes :",
"class_resource_attributes : LBRACE RBRACE",
"class_resource_attributes : LBRACE class_resource_attribute_list RBRACE",
"$$18 :",
"class_resource_attributes : error $$18 RBRACE",
"class_resource_attribute_list : class_resource_attribute_element",
"class_resource_attribute_list : class_resource_attribute_list class_resource_attribute_element",
"$$19 :",
"class_resource_attribute_element : class_resource_attribute_name EQUALS STRING $$19 SEMICOLON",
"$$20 :",
"class_resource_attribute_element : boolean_class_resource_attribute_name EQUALS boolean_attribute_value $$20 SEMICOLON",
"$$21 :",
"class_resource_attribute_element : error $$21 SEMICOLON",
"class_resource_attribute_name : TYPE",
"class_resource_attribute_name : DEFAULT",
"boolean_class_resource_attribute_name : EXCLUDE",
"class_controls : CONTROLS class_controls_block",
"class_controls_block :",
"class_controls_block : LBRACE RBRACE",
"class_controls_block : LBRACE class_controls_list RBRACE",
"$$22 :",
"class_controls_block : error $$22 RBRACE",
"class_controls_list : class_controls_element",
"class_controls_list : class_controls_list class_controls_element",
"$$23 :",
"class_controls_element : name $$23 class_controls_attributes SEMICOLON",
"$$24 :",
"class_controls_element : error $$24 SEMICOLON",
"class_controls_attributes :",
"class_controls_attributes : LBRACE RBRACE",
"$$25 :",
"class_controls_attributes : error $$25 RBRACE",
"class_children : CHILDREN class_children_block",
"class_children_block :",
"class_children_block : LBRACE RBRACE",
"class_children_block : LBRACE class_children_list RBRACE",
"$$26 :",
"class_children_block : error $$26 RBRACE",
"class_children_list : class_children_element",
"class_children_list : class_children_list class_children_element",
"$$27 :",
"class_children_element : name $$27 SEMICOLON",
"$$28 :",
"class_children_element : error $$28 SEMICOLON",
"$$29 :",
"resource_statement : name COLON resource_type $$29 resource_definition",
"resource_type : ARGUMENT",
"resource_type : REASON",
"resource_type : CONSTRAINT",
"resource_type : SUBRESOURCE",
"resource_definition :",
"resource_definition : LBRACE RBRACE",
"resource_definition : LBRACE resource_attribute_list RBRACE",
"$$30 :",
"resource_definition : error $$30 RBRACE",
"resource_attribute_list : resource_attribute",
"resource_attribute_list : resource_attribute_list resource_attribute",
"$$31 :",
"resource_attribute : resource_attribute_name EQUALS STRING $$31 SEMICOLON",
"$$32 :",
"resource_attribute : boolean_resource_resource_attribute_name EQUALS boolean_attribute_value $$32 SEMICOLON",
"$$33 :",
"resource_attribute : error $$33 SEMICOLON",
"resource_attribute_name : TYPE",
"resource_attribute_name : RESOURCELITERAL",
"resource_attribute_name : ENUMERATIONSET",
"resource_attribute_name : INTERNALLITERAL",
"resource_attribute_name : RELATED",
"resource_attribute_name : DOCNAME",
"resource_attribute_name : DEFAULT",
"resource_attribute_name : ALIAS",
"boolean_resource_resource_attribute_name : XRMRESOURCE",
"child_statement : name COLON STRING",
"$$34 :",
"datatype_statement : name $$34 datatype_definition",
"datatype_definition :",
"datatype_definition : LBRACE RBRACE",
"datatype_definition : LBRACE datatype_attribute_list RBRACE",
"$$35 :",
"datatype_definition : error $$35 RBRACE",
"datatype_attribute_list : datatype_attribute",
"datatype_attribute_list : datatype_attribute_list datatype_attribute",
"$$36 :",
"datatype_attribute : datatype_attribute_name EQUALS STRING $$36 SEMICOLON",
"$$37 :",
"datatype_attribute : error $$37 SEMICOLON",
"datatype_attribute_name : INTERNALLITERAL",
"datatype_attribute_name : DOCNAME",
"datatype_attribute_name : XRMRESOURCE",
"$$38 :",
"ctrlist_statement : name $$38 ctrlist_definition",
"ctrlist_definition :",
"ctrlist_definition : LBRACE RBRACE",
"ctrlist_definition : LBRACE ctrlist_controls_list RBRACE",
"$$39 :",
"ctrlist_definition : error $$39 RBRACE",
"ctrlist_controls_list : ctrlist_control",
"ctrlist_controls_list : ctrlist_controls_list ctrlist_control",
"$$40 :",
"ctrlist_control : name $$40 ctrlist_controls_attributes SEMICOLON",
"$$41 :",
"ctrlist_control : error $$41 SEMICOLON",
"ctrlist_controls_attributes :",
"ctrlist_controls_attributes : LBRACE RBRACE",
"$$42 :",
"ctrlist_controls_attributes : error $$42 RBRACE",
"$$43 :",
"enumset_statement : name COLON enumset_data_type $$43 enumset_definition",
"enumset_data_type : STRING",
"enumset_definition :",
"enumset_definition : LBRACE RBRACE",
"enumset_definition : LBRACE enumset_value_list RBRACE",
"$$44 :",
"enumset_definition : error $$44 RBRACE",
"enumset_value_list : enumset_value",
"enumset_value_list : enumset_value_list enumset_value",
"$$45 :",
"enumset_value : name $$45 SEMICOLON",
"$$46 :",
"enumset_value : error $$46 SEMICOLON",
"$$47 :",
"enumval_statement : name COLON $$47 enumvalue_definition",
"enumvalue_definition :",
"enumvalue_definition : LBRACE RBRACE",
"enumvalue_definition : LBRACE enumvalue_attributes_list RBRACE",
"$$48 :",
"enumvalue_definition : error $$48 RBRACE",
"enumvalue_attributes_list : enumvalue_attribute",
"enumvalue_attributes_list : enumvalue_attributes_list enumvalue_attribute",
"$$49 :",
"enumvalue_attribute : enumvalue_attribute_name EQUALS STRING $$49 SEMICOLON",
"$$50 :",
"enumvalue_attribute : error $$50 SEMICOLON",
"enumvalue_attribute_name : ENUMLITERAL",
"$$51 :",
"charset_statement : name $$51 charset_definition",
"charset_definition :",
"charset_definition : LBRACE RBRACE",
"charset_definition : LBRACE charset_attribute_list RBRACE",
"$$52 :",
"charset_definition : error $$52 RBRACE",
"charset_attribute_list : charset_attribute",
"charset_attribute_list : charset_attribute_list charset_attribute",
"$$53 :",
"charset_attribute : charset_attribute_name EQUALS STRING $$53 SEMICOLON",
"$$54 :",
"charset_attribute : predefined_charset_attribute_name EQUALS predefined_charset_attribute_value $$54 SEMICOLON",
"$$55 :",
"charset_attribute : error $$55 SEMICOLON",
"charset_attribute_name : INTERNALLITERAL",
"charset_attribute_name : ALIAS",
"charset_attribute_name : XMSTRINGCHARSETNAME",
"predefined_charset_attribute_name : DIRECTION",
"predefined_charset_attribute_name : PARSEDIRECTION",
"predefined_charset_attribute_name : CHARACTERSIZE",
"predefined_charset_attribute_value : LEFTTORIGHT",
"predefined_charset_attribute_value : RIGHTTOLEFT",
"predefined_charset_attribute_value : ONEBYTE",
"predefined_charset_attribute_value : TWOBYTE",
"predefined_charset_attribute_value : MIXED1_2BYTE",
"name : STRING",

};
#endif

#if YYDEBUG
int      yydebug;
#endif

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;
int      yynerrs;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;

/*
 * Dummmy error routine, since we output our own.
 */
int yyerror (s)
char *s;
{
	return 0;
}


#include "wmllex.c"


#if YYDEBUG
#include <stdio.h>	/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yym = 0;
    yyn = 0;
    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        yychar = YYLEX;
        if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if (((yyn = yysindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if (((yyn = yyrindex[yystate]) != 0) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag != 0) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab; /* redundant goto avoids 'unused label' warning */
yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if (((yyn = yysindex[*yystack.s_mark]) != 0) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym > 0)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);

    switch (yyn)
    {
case 11:
	{ LexIssueError(0); }
break;
case 16:
	{ LexIssueError(SEMICOLON); }
break;
case 21:
	{ LexIssueError(SEMICOLON); }
break;
case 26:
	{ LexIssueError(SEMICOLON); }
break;
case 31:
	{ LexIssueError(SEMICOLON); }
break;
case 36:
	{ LexIssueError(SEMICOLON); }
break;
case 41:
	{ LexIssueError(SEMICOLON); }
break;
case 46:
	{ LexIssueError(SEMICOLON); }
break;
case 51:
	{ LexIssueError(SEMICOLON); }
break;
case 53:
	{ wmlCreateClass (yynameval, yytknval1); }
break;
case 55:
	{ yytknval1 = METACLASS; }
break;
case 56:
	{ yytknval1 = WIDGET; }
break;
case 57:
	{ yytknval1 = GADGET; }
break;
case 61:
	{ LexIssueError(RBRACE); }
break;
case 65:
	{ wmlAddClassAttribute (yytknval1, yystringval); }
break;
case 67:
	{ wmlAddClassAttribute (yytknval1, yytknval2); }
break;
case 72:
	{ LexIssueError(SEMICOLON); }
break;
case 74:
	{ yytknval1 = SUPERCLASS; }
break;
case 75:
	{ yytknval1 = PARENTCLASS; }
break;
case 76:
	{ yytknval1 = INTERNALLITERAL; }
break;
case 77:
	{ yytknval1 = DOCNAME; }
break;
case 78:
	{ yytknval1 = CONVFUNC; }
break;
case 79:
	{ yytknval1 = WIDGETCLASS; }
break;
case 80:
	{ yytknval1 = CTRLMAPSRESOURCE; }
break;
case 81:
	{ yytknval1 = DIALOGCLASS; }
break;
case 82:
	{ yytknval2 = ATTRTRUE; }
break;
case 83:
	{ yytknval2 = ATTRFALSE; }
break;
case 88:
	{ LexIssueError(RBRACE); }
break;
case 92:
	{ wmlAddClassResource (yynameval); }
break;
case 94:
	{ LexIssueError(SEMICOLON); }
break;
case 99:
	{ LexIssueError(RBRACE); }
break;
case 103:
	{ wmlAddClassResourceAttribute (yytknval1, yystringval); }
break;
case 105:
	{ wmlAddClassResourceAttribute (yytknval1, yytknval2); }
break;
case 107:
	{ LexIssueError(SEMICOLON); }
break;
case 109:
	{ yytknval1 = TYPE; }
break;
case 110:
	{ yytknval1 = DEFAULT; }
break;
case 111:
	{ yytknval1 = EXCLUDE; }
break;
case 116:
	{ LexIssueError(RBRACE); }
break;
case 120:
	{ wmlAddClassControl (yynameval); }
break;
case 122:
	{ LexIssueError(SEMICOLON); }
break;
case 126:
	{ LexIssueError(RBRACE); }
break;
case 132:
	{ LexIssueError(RBRACE); }
break;
case 136:
	{ wmlAddClassChild (yynameval); }
break;
case 138:
	{ LexIssueError(SEMICOLON); }
break;
case 140:
	{ wmlCreateResource (yynameval, yytknval1); }
break;
case 142:
	{ yytknval1 = ARGUMENT; }
break;
case 143:
	{ yytknval1 = REASON; }
break;
case 144:
	{ yytknval1 = CONSTRAINT; }
break;
case 145:
	{ yytknval1 = SUBRESOURCE; }
break;
case 149:
	{ LexIssueError(RBRACE); }
break;
case 153:
	{ wmlAddResourceAttribute (yytknval1, yystringval); }
break;
case 155:
	{ wmlAddResourceAttribute (yytknval1, yytknval2); }
break;
case 157:
	{ LexIssueError(SEMICOLON); }
break;
case 159:
	{ yytknval1 = TYPE; }
break;
case 160:
	{ yytknval1 = RESOURCELITERAL; }
break;
case 161:
	{ yytknval1 = ENUMERATIONSET; }
break;
case 162:
	{ yytknval1 = INTERNALLITERAL; }
break;
case 163:
	{ yytknval1 = RELATED; }
break;
case 164:
	{ yytknval1 = DOCNAME; }
break;
case 165:
	{ yytknval1 = DEFAULT; }
break;
case 166:
	{ yytknval1 = ALIAS; }
break;
case 167:
	{ yytknval1 = XRMRESOURCE; }
break;
case 168:
	{ wmlCreateChild(yynameval, yystringval); }
break;
case 169:
	{ wmlCreateDatatype (yystringval); }
break;
case 174:
	{ LexIssueError(RBRACE); }
break;
case 178:
	{ wmlAddDatatypeAttribute (yytknval1, yystringval); }
break;
case 180:
	{ LexIssueError(SEMICOLON); }
break;
case 182:
	{ yytknval1 = INTERNALLITERAL; }
break;
case 183:
	{ yytknval1 = DOCNAME; }
break;
case 184:
	{ yytknval1 = XRMRESOURCE; }
break;
case 185:
	{ wmlCreateOrAppendCtrlList (yynameval); }
break;
case 190:
	{ LexIssueError(RBRACE); }
break;
case 194:
	{ wmlAddCtrlListControl (yynameval); }
break;
case 196:
	{ LexIssueError(SEMICOLON); }
break;
case 200:
	{ LexIssueError(RBRACE); }
break;
case 202:
	{ wmlCreateEnumSet (yynameval, yystringval); }
break;
case 208:
	{ LexIssueError(RBRACE); }
break;
case 212:
	{ wmlAddEnumSetValue (yynameval); }
break;
case 214:
	{ LexIssueError(SEMICOLON); }
break;
case 216:
	{ wmlCreateEnumValue (yynameval); }
break;
case 221:
	{ LexIssueError(RBRACE); }
break;
case 225:
	{ wmlAddEnumValueAttribute (yytknval1, yystringval); }
break;
case 227:
	{ LexIssueError(SEMICOLON); }
break;
case 229:
	{ yytknval1 = ENUMLITERAL; }
break;
case 230:
	{ wmlCreateCharset (yystringval); }
break;
case 235:
	{ LexIssueError(RBRACE); }
break;
case 239:
	{ wmlAddCharsetAttribute (yytknval1, yystringval); }
break;
case 241:
	{ wmlAddCharsetAttribute (yytknval1, yytknval2); }
break;
case 243:
	{ LexIssueError(SEMICOLON); }
break;
case 245:
	{ yytknval1 = INTERNALLITERAL; }
break;
case 246:
	{ yytknval1 = ALIAS; }
break;
case 247:
	{ yytknval1 = XMSTRINGCHARSETNAME; }
break;
case 248:
	{ yytknval1 = DIRECTION; }
break;
case 249:
	{ yytknval1 = PARSEDIRECTION; }
break;
case 250:
	{ yytknval1 = CHARACTERSIZE; }
break;
case 251:
	{ yytknval2 = LEFTTORIGHT; }
break;
case 252:
	{ yytknval2 = RIGHTTOLEFT; }
break;
case 253:
	{ yytknval2 = ONEBYTE; }
break;
case 254:
	{ yytknval2 = TWOBYTE; }
break;
case 255:
	{ yytknval2 = MIXED1_2BYTE; }
break;
case 256:
	{ strcpy (yynameval, (XmConst char *)yystringval); }
break;
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            yychar = YYLEX;
            if (yychar < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                if ((yys = yyname[YYTRANSLATE(yychar)]) == NULL) yys = yyname[YYUNDFTOKEN];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if (((yyn = yygindex[yym]) != 0) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == (YYINT) yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
