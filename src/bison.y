%{

%}
%token INTEGER SEMICOLON IDENTIFER ...
%start prog_start

%%
prog_start: %empty {printf("prog_start -> epsilon\n");}
          | functions {printf("prog_start -> functions\n")}
          ;
functions: function {printf("functions -> function\n")}
         | function functions {printf("functions -> functions\n")}
         ;
function:  INTEGER IDENTIFER LPR arguments RPR LBR statements RBR
           {printf("\n");}
arguments: %empty {printf("arguments -> epsilon\n");}
         | argument COMMA arguments {printf("arguments -> argument COMMA arguments\n")}
         ;
argument: INT INDENTIFIER {}
        ;
statements: %empty {}
          | statement SEMICOLON statements {}
statement: declaration
         | function_call
         ;
declaration: INTEGER IDENTIFER
           ;
function_call: IDENTIFER LPR params RPR {}
             ;
statement: declaration {}

    
%%


void main(int argc, char** argv) {
    if (argc >=2 ) {
        yyin = fopen(argv[1], "r);
        if (yyin == NULL) {
            yyin = stdin;
        }
    }
    else {
        yyin = stdin;
    }
    yyparse();
}