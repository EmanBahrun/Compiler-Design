%{
    #include <stdio.h>
%}
%token INTEGER IDENTIFIER FUNCTION ARRAY ARRAYFILL IF ELESE WHILE CONTINUE BREAK GET PRINT NOT TRUE FALSE RETURN SEMICOLON COLON COMMA L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN LBRACE RBRACE ADD SUB MULT DIV MOD EQ NEQ LT GT LTE GTE INTEGERVAR ELSE
%start prog_start

%%
prog_start: %empty {printf("prog_start -> epsilon\n");}
          | functions {printf("prog_start -> functions\n");}
          ;

functions: function {printf("functions -> function\n");}
         | function functions {printf("functions -> functions\n");}
         ;
function:  FUNCTION IDENTIFIER L_PAREN arguments R_PAREN LBRACE statements RBRACE 
           {printf("function->FUNCTION IDENTIFIER L_PAREN arguments R_PAREN LBRACE statements RBRACE\n");};
arguments: %empty 
           {printf("arguments -> epsilon\n");}
         | argument COMMA arguments {printf("arguments -> argument COMMA arguments\n");}
         | argument {printf("arguments -> argument\n");}
         ;
argument: INTEGERVAR IDENTIFIER {printf("argument->INTEGERVAR IDENTIFIER\n");}
        ;


statements: %empty {printf("statements -> epsilon\n" );}
          | statement SEMICOLON statements {printf("statements -> statement SEMICOLON statements\n");}
statement: declaration
         | function_call
         | if_statement
         | while_statement
         | return_statement
         | assign_statement
         | CONTINUE SEMICOLON {printf("statement -> CONTINUE SEMICOLON\n");}
         | BREAK SEMICOLON {printf("statement -> BREAK SEMICOLON\n");}
         | PRINT expression SEMICOLON {printf("statement -> PRINT expression SEMICOLON\n");}
         | GET IDENTIFIER SEMICOLON {printf("statement -> GET IDENTIFIER SEMICOLON\n" );}
         ;
if_statement: IF L_PAREN booleanexpression R_PAREN LBRACE statements LBRACE {printf("if_statement -> IF L_PAREN booleanexpression R_PAREN LBRACE statements\n");}
            | IF L_PAREN booleanexpression R_PAREN LBRACE statements LBRACE else_statement {printf("if_statement -> IF L_PAREN booleanexpression R_PAREN LBRACE statements LBRACE else_statement\n");}
            ;
else_statement: ELSE LBRACE statements RBRACE {printf("else_statement -> ELSE LBRACE statements RBRACE\n");}
              | ELSE if_statement {printf("else_statement -> ELSE if_statement\n");}
              ;
while_statement: WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {printf("while -> WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE\n");}
     ;
return_statement: RETURN SEMICOLON {printf("return_statement -> RETURN SEMICOLON\n");}
                | RETURN expression SEMICOLON {printf("return_statement -> RETURN expression SEMICOLON\n");}
                ;
assign_statement: IDENTIFIER ASSIGN expression SEMICOLON {printf("assign_statement ->IDENTIFIER ASSIGN expression SEMICOLON\n");}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression SEMICOLON {printf("assign_statement -> IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression SEMICOLON\n" );}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN ARRAYFILL INTEGER SEMICOLON {printf("assign_statement -> IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN ARRAYFILL INTEGER SEMICOLON\n");}
                ;
expression: IDENTIFIER {printf("expression -> IDENTIFIER\n");}
          | INTEGER {printf("expression -> INTEGER\n" );}
          | integerexpression {printf("expression -> integerexpression\n");}
          | booleanexpression {printf("expression ->booleanexpression\n");}
          | arrayexpression {printf("expression -> arrayexpression\n");}
          ;
integerexpression: expression ADD expression {printf("integerexpression -> expression ADD expression\n");}
            | expression SUB expression {printf("integerexpression -> expression SUB expression\n" );}
            | expression MULT expression {printf("integerexpression -> expression MULT expression\n");}
            | expression DIV expression {printf("integerexpression -> expression DIV expression\n");}
            | expression MOD expression {printf("integerexpression ->  expression MOD expression\n");}
            | L_PAREN expression R_PAREN {printf("integerexpression -> L_PAREN expression R_PAREN\n");}
            ;
booleanexpression: expression EQ expression {printf("booleanexpression -> expression EQ expression\n");}
          | expression NEQ expression {printf("booleanexpression -> expression NEQ expression\n");}
          | expression LT expression {printf("booleanexpression -> expression LT expression\n");}
          | expression GT expression {printf("booleanexpression -> expression GT expression\n");}
          | expression LTE expression {printf("booleanexpression -> expression LTE expression\n");}
          | expression GTE expression {printf("booleanexpression -> expression GTE expression\n");}
          | NOT expression {printf("booleanexpression -> NOT expression\n");}
          ;
arrayexpression: IDENTIFIER L_SQUARE_BRACKET integerexpression R_SQUARE_BRACKET {printf("arrayexpression ->  IDENTIFIER L_SQUARE_BRACKET integerexpression R_SQUARE_BRACKET\n");}
               ;
declaration: INTEGER IDENTIFIER SEMICOLON {printf("declaration -> INTEGER IDENTIFIER SEMICOLON\n");}
           ;
function_call: IDENTIFIER L_PAREN params R_PAREN {printf("function_call -> IDENTIFIER L_PAREN params R_PAREN\n");}
             ;
params: %empty {printf("params -> epsilon\n");}
        | param COMMA params {printf("params -> param COMMA params\n");}
        ;
param: INTEGER {printf("param -> INTEGER\n");}
     | IDENTIFIER {printf("param -> IDENTIFIER\n");}
     ;

%%


int main(int argc, char** argv) {
    FILE* yyin = stdin;
    if (argc >= 2) {
        printf("Opening %s...\n", argv[1]);
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Error: could not open file %s.\n", argv[1]);
        }
        else {
            printf("File opened successfully.\n");
        }
    }
    else {
        printf("No input file provided, reading from standard input...\n");
    }
    yyparse();
    return 0;
}