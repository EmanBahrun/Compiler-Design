%{
    // C code here.
    #include <stdio.h>
    int character_count = 0;
    int line_count = 0;
%}
%option yylineno


INTEGER [0-9]
IDENTIFIER [a-zA-Z][a-zA-Z_0-9]+
COMMENT #.*\n
ARRAYLENGTH \.\.\.[1-9][0-9]+
%%

"function"	{ printf("FUNCTION\n");character_count+= yyleng;}
"Array"	{ printf("ARRAY\n");character_count+= yyleng;}
"Integer"	{ printf("INTEGERVAR\n");character_count+= yyleng;}
"if"	{ printf("IF\n")character_count+= yyleng;}
"else"	{ printf("ELSE\n");character_count+= yyleng;}
"while"	{ printf("WHILE\n");character_count+= yyleng;}
"continue"	{ printf("CONTINUE\n");character_count+= yyleng;}
"break"	{ printf("BREAK\n");character_count+= yyleng;}
"get"	{ printf("GET\n");character_count+= yyleng;}
"print"	{ printf("PRINT\n");character_count+= yyleng;}
"not"	{ printf("NOT\n");character_count+= yyleng;}
"true"	{ printf("TRUE\n");character_count+= yyleng;}
"false"	{ printf("FALSE\n");character_count+= yyleng;}
"return"	{ printf("RETURN\n");character_count+= yyleng;}




"+"	{ printf("PLUS\n");character_count+= yyleng;}
"-"	{ printf("SUB\n");character_count+= yyleng;}
"*"	{ printf("MULT\n");character_count+= yyleng;}
"/"	{ printf("DIV\n");character_count+= yyleng;}
"%"	{ printf("MOD\n");}character_count+= yyleng;

"=="	{ printf("EQ\n");character_count+= yyleng;}
"!="	{ printf("NEQ\n");character_count+= yyleng;}
"<"	    { printf("LT\n");character_count+= yyleng;}
">"	    { printf("GT\n");character_count+= yyleng;}
"<="	{ printf("LTE\n");character_count+= yyleng;}
">="	{ printf("GTE\n");character_count+= yyleng;}


";"	{ printf("SEMICOLON\n");character_count+= yyleng;}
":"	{ printf("COLON\n");character_count+= yyleng;}
","	{ printf("COMMA\n");character_count+= yyleng;}
"("	{ printf("L_PAREN\n");character_count+= yyleng;}
")"	{ printf("R_PAREN\n");character_count+= yyleng;}
"["	{ printf("L_SQUARE_BRACKET\n");character_count+= yyleng;}
"]"	{ printf("R_SQUARE_BRACKET\n");character_count+= yyleng;}
"="	{ printf("ASSIGN\n");character_count+= yyleng;}
"{"	{ printf("LBRACE\n");character_count+= yyleng;}
"}"	{ printf("RBRACE\n");character_count+= yyleng;}
"..." { printf("ARRAYFILL\n");character_count+= yyleng;}
"\n" {character_count = 0; line_count = 0}

{INTEGER}+ { printf("INTEGER: %s\n", yytext); }
{IDENTIFIER}+ { printf("IDENTIFIER: %s\n", yytext); }
{COMMENT}+ {}
{ARRAYLENGTH}+ { printf("ARRAYLENGTH: %s\n", yytext + 3); }
" "  {character_count+= yyleng;}

.    { printf("**ERROR. Unidentified token '%s' at line %d, column %d \n", yytext, yylineno, character_count);}
%%


int main(void) {
    printf("Ctrl+D to quit\n");
    yylex();
}