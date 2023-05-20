%{
     #include<stdio.h>
     #include<string>
     #include<vector>
     #include<string.h>
     #include<stdlib.h>

     extern FILE * yyin;
     extern int yylex(void);
     void yyerror(const char * msg);
     extern int current_line;

     char * indentifierToken;
     int numberToken;
     int count_names = 0;

     enum Type {
       Integer,
       Array
     };

     struct Symbol {
       std::string name;
       Type type;
     };

     struct Function {
       std::string name;
       std::vector < Symbol > declarations;
     };

     std::vector < Function > symbol_table;

     // remember that Bison is a bottom up parser: that it parses leaf nodes first before
     // parsing the parent nodes. So control flow begins at the leaf grammar nodes
     // and propagates up to the parents.
     Function * get_function() {
       int last = symbol_table.size() - 1;
       if (last < 0) {
         printf("***Error. Attempt to call get_function with an empty symbol table\n");
         printf("Create a 'Function' object using 'add_function_to_symbol_table' before\n");
         printf("calling 'find' or 'add_variable_to_symbol_table'");
         exit(1);
       }
       return & symbol_table[last];
     }

     // find a particular variable using the symbol table.
     // grab the most recent function, and linear search to
     // find the symbol you are looking for.
     // you may want to extend "find" to handle different types of "Integer" vs "Array"
     bool find(std::string & value) {
       Function * f = get_function();
       for (int i = 0; i < f -> declarations.size(); i++) {
         Symbol * s = & f -> declarations[i];
         if (s -> name == value) {
           return true;
         }
       }
       return false;
     }

     // when you see a function declaration inside the grammar, add
     // the function name to the symbol table
     void add_function_to_symbol_table(std::string & value) {
       Function f;
       f.name = value;
       symbol_table.push_back(f);
     }

     // when you see a symbol declaration inside the grammar, add
     // the symbol name as well as some type information to the symbol table
     void add_variable_to_symbol_table(std::string & value, Type t) {
       Symbol s;
       s.name = value;
       s.type = t;
       Function * f = get_function();
       f -> declarations.push_back(s);
     }

     // a function to print out the symbol table to the screen
     // largely for debugging purposes.
     void print_symbol_table(void) {
       printf("symbol table:\n");
       printf("--------------------\n");
       for (int i = 0; i < symbol_table.size(); i++) {
         printf("function: %s\n", symbol_table[i].name.c_str());
         for (int j = 0; j < symbol_table[i].declarations.size(); j++) {
           printf("  locals: %s\n", symbol_table[i].declarations[j].name.c_str());
         }
       }
       printf("--------------------\n");
     }

     struct CodeNode {
       std::string code; // generated code as a string.
       std::string name;
     };
%}


%union {
  char *op_val;
  struct CodeNode *node;
}

%define parse.error verbose
%start prog_start

%token FUNCTION ARRAY INTEGERVAR ARRAYFILL RETURN SEMICOLON COMMA
%token IF ELSE WHILE TRUE FALSE CONTINUE BREAK 
%token GET PRINT
%token NOT COLON L_PAREN R_PAREN L_SQUARE_BRACKET R_SQUARE_BRACKET ASSIGN LBRACE RBRACE 
%token ADD SUB MULT DIV MOD EQ NEQ LT GT LTE GTE 
%token <op_val> INTEGER 
%token <op_val> IDENTIFIER
%type  <op_val> symbol
%type  <op_val> function_indentifier
%type  <node>   functions
%type  <node>   function
%type  <node>   declarations
%type  <node>   declaration
%type  <node>   statements
%type  <node>   statement
%type  <node>   argument
%type  <node>   arguments
%type  <node>   expression


%%
prog_start: 
functions {
    CodeNode *node = $1;
    std::string code = node->code;
    printf("Generated code:\n");
    printf("%s\n", code.c_str());
};

functions: %empty
{ 
    CodeNode *node = new CodeNode;
    $$ = node;
}
| 
function functions {
    CodeNode *func  = $1;
    CodeNode *funcs = $2;
    std::string code = func->code + funcs->code;

    CodeNode *node = new CodeNode;
    node->code = code;
    $$ = node;
}
         ;
function:  FUNCTION function_indentifier L_PAREN arguments R_PAREN LBRACE statements RBRACE 
           {
            std::string func_name = $2;
            CodeNode *arguments = $4;
            CodeNode *statements = $7;
            std::string code = std::string("func ") + func_name + std::string("\n");
            int num_args = 0;
            for (int i = 0; i < arguments->code.size(); i++) {
                if (arguments->code[i] == '@') {
                    code += num_args;
                    num_args++;
                }
                else {
                  code += arguments->code[i];
                }
            }
            code += arguments->code;
            code += statements->code;
            code += std::string("endfunc\n");

            CodeNode *node = new CodeNode;
            node->code = code;
            $$ = node;
           };
arguments: %empty 
           { CodeNode *node = new CodeNode; $$ = node;}
         | argument COMMA arguments {
            CodeNode *arg = $1;
            CodeNode *args = $3;
            std::string code = arg->code + args->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            $$ = node;
         }
         | argument {
            CodeNode *arg = $1;
            std::string code = arg->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            $$ = node;
         }
         ;
argument: INTEGERVAR IDENTIFIER {
            std::string var_name = $2;
            // @ is a special token that we will use in functin above.
            std::string code = var_name + std::string(" $@") + var_name + std::string("\n");
            CodeNode *node = new CodeNode;
            node->code = code;
            $$ = node;
         }
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
             | ARRAY IDENTIFIER ASSIGN L_SQUARE_BRACKET ARRAYFILL INTEGER R_SQUARE_BRACKET {printf("declaration -> ARRAY IDENTIFIER ASSIGN L_SQUARE_BRACKET ARRAYFILL INTEGER R_SQUARE_BRACKET\n");}
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


symbol: 
IDENTIFIER 
{
  $$ = $1; 
}
| INTEGER 
{
  $$ = $1; 
}

function_indentifier: IDENTIFIER {
  std::string func_name = $1;
  add_function_to_symbol_table(func_name);
  $$ = $1;
}

%%


int main(int argc, char** argv){
	if(argc >= 2){
		yyin = fopen(argv[1], "r");
		if(yyin == NULL)
			yyin = stdin;
	}else{
		yyin = stdin;
	}
	yyparse();
     return 0;
}

/* Called by yyparse on error. */
void yyerror(const char *msg)
{
   printf("** Line %d: %s\n", current_line, msg);
   exit(1);
}
