%option yylineno
%option noyywrap
%{
    #include <string.h>
    #include "bison.tab.h"

    int current_character = 0;
    int current_line = 1;
    extern char *indentifierToken;
    extern int numberToken;
%}


INTEGER [0-9]
IDENTIFIER [a-zA-Z][a-zA-Z_0-9]+
BADIDENTIFIERONE [0-9][a-zA-Z][a-zA-Z_0-9]+
COMMENT #.*\n
ARRAYLENGTH \.\.\.
%%

"function"	{ current_character += yyleng; return FUNCTION;}
"Array"	{ current_character += yyleng; return ARRAY;}
"Integer"	{ current_character += yyleng; return INTEGERVAR;}
"if"	{ current_character += yyleng; return IF;}
"else"	{ current_character += yyleng; return ELSE;}
"while"	{ current_character += yyleng; return WHILE;}
"continue"	{ current_character += yyleng; return CONTINUE;}
"break"	{ current_character += yyleng; return BREAK;}
"get"	{ current_character += yyleng; return GET;}
"print"	{ current_character += yyleng; return PRINT;}
"not"	{ current_character += yyleng; return NOT;}
"true"	{ current_character += yyleng; return TRUE;}
"false"	{ current_character += yyleng; return FALSE;}
"return"	{ current_character += yyleng; return RETURN;}
"+"	{ current_character += yyleng; return ADD;}
"-"	{ current_character += yyleng; return SUB;}
"*"	{ current_character += yyleng; return MULT;}
"/"	{ current_character += yyleng; return DIV;}
"%"	{ current_character += yyleng; return MOD;}
"=="	{ current_character += yyleng; return EQ;}
"!="	{ current_character += yyleng; return NEQ;}
"<"	    { current_character += yyleng; return LT;}
">"	    { current_character += yyleng; return GT;}
"<="	{ current_character += yyleng; return LTE;}
">="	{ current_character += yyleng; return GTE;}
";"	{ current_character += yyleng; return SEMICOLON;}
":"	{ current_character += yyleng; return COLON;}
","	{ current_character += yyleng; return COMMA;}
"("	{ current_character += yyleng; return L_PAREN;}
")"	{ current_character += yyleng; return R_PAREN;}
"["	{ current_character += yyleng; return L_SQUARE_BRACKET;}
"]"	{ current_character += yyleng; return R_SQUARE_BRACKET;}
"="	{ current_character += yyleng; return ASSIGN;}
"{"	{ current_character += yyleng; return LBRACE;}
"}"	{ current_character += yyleng; return RBRACE;}
"\n" {current_character = 0; current_line++;}

{INTEGER}+ { 
    current_character += yyleng;
    char * token = new char[yyleng];
    strcpy(token, yytext);
    yylval.op_val = token;
    numberToken = atoi(yytext);
    return INTEGER; 
}
{BADIDENTIFIERONE} { printf("**ERROR. Cannot start with numbers for indentifier '%s' at line %d, column %d \n", yytext, yylineno, current_character); exit(0);}
{IDENTIFIER}+ { 
    current_character += yyleng; 
    char * token = new char[yyleng];
    strcpy(token, yytext);
    yylval.op_val = token;
    indentifierToken = yytext; 
    return IDENTIFIER; 
}
{COMMENT}+ { current_character += yyleng; }
{ARRAYLENGTH}+ { current_character += yyleng; return ARRAYFILL; }
" "  {current_character += yyleng;}
.    { printf("**ERROR. Unidentified token '%s' at line %d, column %d \n", yytext, yylineno, current_character); exit(0);}
%%