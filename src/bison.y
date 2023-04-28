%{

%}
%token INTEGER SEMICOLON IDENTIFIER FUNCTION ARRAY ARRAYFILL IF ELESE WHILE CONTINUE BREAK GET PRINT NOT TRUE FALSE RETURN SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN LBRACE RBRACE  ADD SUB MULT DIV MOD EQ NEQ LT GT LTE GTE INTEGERVAR
%start prog_start

%%
# Starting symbol
prog_start: %empty {printf("prog_start -> epsilon\n");}
          | functions {printf("prog_start -> functions\n")}
          ;

functions: function {printf("functions -> function\n")}
         | function functions {printf("functions -> functions\n")}
         ;
function:  FUNCTION IDENTIFIER L_PAREN arguments R_PAREN LBRACE statements RBRACE {printf("\n");};
arguments: %empty {printf("arguments -> epsilon\n");}
         | argument COMMA arguments {printf("arguments -> argument COMMA arguments\n")}
         | argument {printf("arguments -> argument\n")}
         ;
argument: INTEGERVAR IDENTIFIER {}
        ;


# Statements stuff
statements: %empty {}
          | statement SEMICOLON statements {}
statement: declaration
         | function_call
         | if_statement
         | while_statement
         | return_statement
         | assign_statement
         | CONTINUE SEMICOLON {}
         | BREAK SEMICOLON {}
         | PRINT expression SEMICOLON {}
         | GET IDENTIFIER SEMICOLON {}
         ;
if_statement: IF L_PAREN booleanexpression R_PAREN LBRACE statements LBRACE {}
            | IF L_PAREN booleanexpression R_PAREN LBRACE statements LBRACE else_statement {}
            ;
while: WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {}
     ;
return_statement: RETURN SEMICOLON {}
                | RETURN expression SEMICOLON {}
                ;
assign_statement: IDENTIFIER ASSIGN expression SEMICOLON {}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression SEMICOLON {}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN ARRAYFILL INTEGER SEMICOLON {}
                ;
expression: IDENTIFIER {}
          | INTEGER {}
          | integerexpression {}
          | booleanexpression {}
          | arrayexpression {}
          ;
integerexpression: IDENTIFIER {}
            | INTEGER {}
            | expression ADD expression {}
            | expression SUB expression {}
            | expression MULT expression {}
            | expression DIV expression {}
            | expression MOD expression {}
            | L_PAREN expression R_PAREN {}
            ;
booleanexpression: IDENTIFIER {}
          | INTEGER {}
          | expression EQ expression {}
          | expression NEQ expression {}
          | expression LT expression {}
          | expression GT expression {}
          | expression LTE expression {}
          | expression GTE expression {}
          | expression AND expression {}
          | expression OR expression {}
          | NOT expression {}
          | L_PAREN expression R_PAREN {}
          ;
arrayexpression: IDENTIFIER L_SQUARE_BRACKET integerexpression R_SQUARE_BRACKET {}
               ;
declaration: INTEGER IDENTIFIER SEMICOLON {printf("declaration -> INTEGER IDENTIFIER SEMICOLON\n");}
           ;
function_call: IDENTIFIER L_PAREN params R_PAREN {}
             ;
params: %empty {}
        | param COMMA params {}
        ;
param: INTEGER {}
     | IDENTIFIER {}
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