%{
    // C code here.
    #include <stdio.h>
    int character_count = 0;
%}
%option yylineno


INTEGER [0-9]
IDENTIFIER [a-zA-Z][a-zA-Z_0-9]+
COMMENT #.*\n
ARRAYLENGTH \.\.\.[1-9][0-9]+
%%

"function"	{ printf("FUNCTION\n");}
"Array"	{ printf("ARRAY\n");}
"Integer"	{ printf("INTEGERVAR\n");}
"if"	{ printf("IF\n");}
"else"	{ printf("ELSE\n");}
"while"	{ printf("WHILE\n");}
"continue"	{ printf("CONTINUE\n");}
"break"	{ printf("BREAK\n");}
"get"	{ printf("GET\n");}
"print"	{ printf("PRINT\n");}
"not"	{ printf("NOT\n");}
"true"	{ printf("TRUE\n");}
"false"	{ printf("FALSE\n");}
"return"	{ printf("RETURN\n");}




"+"	{ printf("PLUS\n");}
"-"	{ printf("SUB\n");}
"*"	{ printf("MULT\n");}
"/"	{ printf("DIV\n");}
"%"	{ printf("MOD\n");}

"=="	{ printf("EQ\n");}
"!="	{ printf("NEQ\n");}
"<"	    { printf("LT\n");}
">"	    { printf("GT\n");}
"<="	{ printf("LTE\n");}
">="	{ printf("GTE\n");}


";"	{ printf("SEMICOLON\n");}
":"	{ printf("COLON\n");}
","	{ printf("COMMA\n");}
"("	{ printf("L_PAREN\n");}
")"	{ printf("R_PAREN\n");}
"["	{ printf("L_SQUARE_BRACKET\n");}
"]"	{ printf("R_SQUARE_BRACKET\n");}
"="	{ printf("ASSIGN\n");}
"{"	{ printf("LBRACE\n");}
"}"	{ printf("RBRACE\n");}
"..." { printf("ARRAYFILL\n");}
"\n" {}

{INTEGER}+ { printf("INTEGER: %s\n", yytext); }
{IDENTIFIER}+ { printf("IDENTIFIER: %s\n", yytext); }
{COMMENT}+ {}
{ARRAYLENGTH}+ { printf("ARRAYLENGTH: %s\n", yytext + 3); }
" " {}

.    { printf("**ERROR. Unidentified token '%s' at line %d, column %d \n", yytext, yylineno, character_count);}
%%


int main(void) {
    printf("Ctrl+D to quit\n");
    yylex();
}