%{
    #include <stdio.h>
    extern FILE* yyin;
    void yyerror(char const *msg);
    #define YYERROR_VERBOSE 1
    extern int yylineno;
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
         | %empty {printf("prog_start -> epsilon\n");}
        ;

statements: %empty {printf("statements -> epsilon\n" );}
          | statement statements {printf("statements -> statement SEMICOLON statements\n");}
statement: declaration SEMICOLON
         | function_call SEMICOLON
         | if_statement
         | while_statement
         | return_statement SEMICOLON
         | assign_statement SEMICOLON
         | CONTINUE SEMICOLON {printf("statement -> CONTINUE\n");}
         | BREAK SEMICOLON {printf("statement -> BREAK\n");}
         | PRINT expression SEMICOLON {printf("statement -> PRINT expression\n");}
         | GET IDENTIFIER SEMICOLON {printf("statement -> GET IDENTIFIER\n" );}
         ;
declaration: INTEGERVAR IDENTIFIER ASSIGN integerexpression {printf("declaration -> INTEGER IDENTIFIER\n");}
             | INTEGERVAR IDENTIFIER {printf("declaration -> INTEGER IDENTIFIER\n");}
             | ARRAY IDENTIFIER ASSIGN L_SQUARE_BRACKET ARRAYFILL R_SQUARE_BRACKET {printf("declaration -> ARRAY IDENTIFIER ASSIGN L_SQUARE_BRACKET ARRAYFILL R_SQUARE_BRACKET\n");}
           ;
function_call: IDENTIFIER L_PAREN params R_PAREN {printf("function_call -> IDENTIFIER L_PAREN params R_PAREN\n");}
             ;
params: %empty {printf("params -> epsilon\n");}
        | param COMMA params {printf("params -> param COMMA params\n");}
        | param {printf("params -> param\n");}
        ;
param: INTEGER {printf("param -> INTEGER\n");}
     | IDENTIFIER {printf("param -> IDENTIFIER\n");}
     ;

     
if_statement: IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {printf("if_statement -> IF L_PAREN booleanexpression R_PAREN RBRACE statements\n");}
            | IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE else_statement {printf("if_statement -> IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE else_statement\n");}
            ;
else_statement: ELSE LBRACE statements RBRACE {printf("else_statement -> ELSE LBRACE statements RBRACE\n");}
              ;
while_statement: WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {printf("while -> WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE\n");}
     ;
return_statement: RETURN {printf("return_statement -> RETURN \n");}
                | RETURN expression {printf("return_statement -> RETURN expression \n");}
                ;
assign_statement: IDENTIFIER ASSIGN expression {printf("assign_statement ->IDENTIFIER ASSIGN expression \n");}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression  {printf("assign_statement -> IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression \n" );}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN ARRAYFILL INTEGER  {printf("assign_statement -> IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN ARRAYFILL INTEGER \n");}
                ;
expression: IDENTIFIER {printf("expression -> IDENTIFIER\n");}
          | integerexpression {printf("expression -> integerexpression\n");}
          | booleanexpression {printf("expression ->booleanexpression\n");}
          | arrayexpression {printf("expression -> arrayexpression\n");}
          ;
integerexpression: INTEGER {printf("integerexpression -> INTEGER\n" );}
            | expression ADD expression {printf("integerexpression -> expression ADD expression\n");}
            | expression SUB expression {printf("integerexpression -> expression SUB expression\n" );}
            | expression MULT expression {printf("integerexpression -> expression MULT expression\n");}
            | expression DIV expression {printf("integerexpression -> expression DIV expression\n");}
            | expression MOD expression {printf("integerexpression ->  expression MOD expression\n");}
            | L_PAREN expression R_PAREN {printf("integerexpression -> L_PAREN expression R_PAREN\n");}
            | function_call {printf("integerexpression -> function_call\n");}
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

%%


void main(int argc, char** argv){
	if(argc >= 2){
		yyin = fopen(argv[1], "r");
		if(yyin == NULL)
			yyin = stdin;
	}else{
		yyin = stdin;
	}
	yyparse();
}

/* Called by yyparse on error. */
void
yyerror (char const *s)
{
	  fprintf (stderr, "Error: %s at line: %d \n", s, yylineno);
}
