%{
    // C code here.
    #include <stdio.h>
%}


INTEGER [0-9]
IDENTIFIER [a-zA-Z][a-zA-Z_0-9]+
%%


"function"	{ printf("FUNCTION: %s\n", yytext);}
"beginparams"	{ printf("BEGIN_PARAMS: %s\n", yytext);}
"endparams"	{ printf("END_PARAMS: %s\n", yytext);}
"beginlocals"	{ printf("BEGIN_LOCALS: %s\n", yytext);}
"endlocals"	{ printf("END_LOCALS: %s\n", yytext);}
"beginbody"	{ printf("BEGIN_BODY: %s\n", yytext);}
"endbody"	{ printf("END_BODY: %s\n", yytext);}
"Array"	{ printf("ARRAY: %s\n", yytext);}
"of"	{ printf("OF: %s\n", yytext);}
"if"	{ printf("IF: %s\n", yytext);}
"then"	{ printf("THEN: %s\n", yytext);}
"endif"	{ printf("ENDIF: %s\n", yytext);}
"else"	{ printf("ELSE: %s\n", yytext);}
"while"	{ printf("WHILE: %s\n", yytext);}
"do"	{ printf("DO: %s\n", yytext);}
"beginloop"	{ printf("BEGINLOOP: %s\n", yytext);}
"endloop"	{ printf("ENDLOOP: %s\n", yytext);}
"continue"	{ printf("CONTINUE: %s\n", yytext);}
"break"	{ printf("BREAK: %s\n", yytext);}
"read"	{ printf("READ: %s\n", yytext);}
"write"	{ printf("WRITE: %s\n", yytext);}
"not"	{ printf("NOT: %s\n", yytext);}
"true"	{ printf("TRUE: %s\n", yytext);}
"false"	{ printf("FALSE: %s\n", yytext);}
"return"	{ printf("RETURN: %s\n", yytext);}




"+"	{ printf("PLUS\n");}
"-"	{ printf("SUB\n");}
"*"	{ printf("MULT\n");}
"/"	{ printf("DIV\n");}
"%"	{ printf("MOD\n");}

"=="	{ printf("EQ: %s\n", yytext);}
"!="	{ printf("NEQ: %s\n", yytext);}
"<"	    { printf("LT: %s\n", yytext);}
">"	    { printf("GT: %s\n", yytext);}
"<="	{ printf("LTE: %s\n", yytext);}
">="	{ printf("GTE: %s\n", yytext);}


";"	{ printf("SEMICOLON: %s\n", yytext);}
":"	{ printf("COLON: %s\n", yytext);}
","	{ printf("COMMA: %s\n", yytext);}
"("	{ printf("L_PAREN: %s\n", yytext);}
")"	{ printf("R_PAREN: %s\n", yytext);}
"["	{ printf("L_SQUARE_BRACKET: %s\n", yytext);}
"]"	{ printf("R_SQUARE_BRACKET: %s\n", yytext);}
"="	{ printf("ASSIGN: %s\n", yytext);}
"{"	{ printf("LBRACE: %s\n", yytext);}
"}"	{ printf("RBRACE: %s\n", yytext);}



{INTEGER}+ { printf("INTEGER: %s\n", yytext); }
{IDENTIFIER}+ { printf("IDENTIFIER: %s\n", yytext); }

.    { printf("**ERROR. Unidentified token '%s'",yytext);}
%%


int main(void) {
    printf("Ctrl+D to quit\n");
    yylex();
}