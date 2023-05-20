%{
    // C code here.
    #include <stdio.h>
    #include "y.tab.h"
    int character_count = 0;
%}
%option yylineno


INTEGER [0-9]
IDENTIFIER [a-zA-Z][a-zA-Z_0-9]+
BADIDENTIFIERONE [0-9][a-zA-Z][a-zA-Z_0-9]+
COMMENT #.*\n
ARRAYLENGTH \.\.\.[1-9][0-9]+
%%

"function"	{ character_count+= yyleng; return FUNCTION;}
"Array"	{ character_count+= yyleng; return ARRAY;}
"Integer"	{ character_count+= yyleng; return INTEGERVAR;}
"if"	{ character_count+= yyleng; return IF;}
"else"	{ character_count+= yyleng; return ELSE;}
"while"	{ character_count+= yyleng; return WHILE;}
"continue"	{ character_count+= yyleng; return CONTINUE;}
"break"	{ character_count+= yyleng; return BREAK;}
"get"	{ character_count+= yyleng; return GET;}
"print"	{ character_count+= yyleng; return PRINT;}
"not"	{ character_count+= yyleng; return NOT;}
"true"	{ character_count+= yyleng; return TRUE;}
"false"	{ character_count+= yyleng; return FALSE;}
"return"	{ character_count+= yyleng; return RETURN;}
"+"	{ character_count+= yyleng; return ADD;}
"-"	{ character_count+= yyleng; return SUB;}
"*"	{ character_count+= yyleng; return MULT;}
"/"	{ character_count+= yyleng; return DIV;}
"%"	{ character_count+= yyleng; return MOD;}
"=="	{ character_count+= yyleng; return EQ;}
"!="	{ character_count+= yyleng; return NEQ;}
"<"	    { character_count+= yyleng; return LT;}
">"	    { character_count+= yyleng; return GT;}
"<="	{ character_count+= yyleng; return LTE;}
">="	{ character_count+= yyleng; return GTE;}
";"	{ character_count+= yyleng; return SEMICOLON;}
":"	{ character_count+= yyleng; return COLON;}
","	{ character_count+= yyleng; return COMMA;}
"("	{ character_count+= yyleng; return L_PAREN;}
")"	{ character_count+= yyleng; return R_PAREN;}
"["	{ character_count+= yyleng; return L_SQUARE_BRACKET;}
"]"	{ character_count+= yyleng; return R_SQUARE_BRACKET;}
"="	{ character_count+= yyleng; return ASSIGN;}
"{"	{ character_count+= yyleng; return LBRACE;}
"}"	{ character_count+= yyleng; return RBRACE;}
"\n" {character_count = 0;}

{INTEGER}+ { return INTEGER; }
{BADIDENTIFIERONE} { printf("**ERROR. Cannot start with numbers for indentifier '%s' at line %d, column %d \n", yytext, yylineno, character_count); exit(0);}
{IDENTIFIER}+ { return IDENTIFIER; }
{COMMENT}+ {}
{ARRAYLENGTH}+ { return ARRAYFILL; }
" "  {character_count+= yyleng;}
.    { printf("**ERROR. Unidentified token '%s' at line %d, column %d \n", yytext, yylineno, character_count); exit(0);}
%%