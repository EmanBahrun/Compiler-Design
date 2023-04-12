%{
    // C code here.
    #include <stdio.h>
%}

DIGIT [0-9]
ALPHA [a-zA-Z]
%%

{DIGIT}+ { printf("NUMBER: %s\n", yytext); }
{ALPHA}+ { printf("WORD: %s\n", yytext); }

%%


int main(void) {
    printf("Ctrl+D to quit\n");
    yylex();
}