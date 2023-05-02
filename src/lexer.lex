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

"function"	{ return FUNCTION;}
"Array"	{ return ARRAY;}
"Integer"	{ return INTEGERVAR;}
"if"	{ return IF;}
"else"	{ return ELSE;}
"while"	{ return WHILE;}
"continue"	{ return CONTINUE;}
"break"	{ return BREAK;}
"get"	{ return GET;}
"print"	{ return PRINT;}
"not"	{ return NOT;}
"true"	{ return TRUE;}
"false"	{ return FALSE;}
"return"	{ return RETURN;}
"+"	{ return ADD;}
"-"	{ return SUB;}
"*"	{ return MULT;}
"/"	{ return DIV;}
"%"	{ return MOD;}
"=="	{ return EQ;}
"!="	{ return NEQ;}
"<"	    { return LT;}
">"	    { return GT;}
"<="	{ return LTE;}
">="	{ return GTE;}
";"	{ return SEMICOLON;}
":"	{ return COLON;}
","	{ return COMMA;}
"("	{ return L_PAREN;}
")"	{ return R_PAREN;}
"["	{ return L_SQUARE_BRACKET;}
"]"	{ return R_SQUARE_BRACKET;}
"="	{ return ASSIGN;}
"{"	{ return LBRACE;}
"}"	{ return RBRACE;}
"\n" {character_count = 0; }

{INTEGER}+ { return INTEGER; }
{BADIDENTIFIERONE} { printf("**ERROR. Cannot start with numbers for indentifier '%s' at line %d, column %d \n", yytext, yylineno, character_count);}
{IDENTIFIER}+ { return IDENTIFIER; }
{COMMENT}+ {}
{ARRAYLENGTH}+ { return ARRAYFILL; }
" "  {}
.    { printf("**ERROR. Unidentified token '%s' at line %d, column %d \n", yytext, yylineno, character_count);}
%%