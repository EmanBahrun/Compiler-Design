%{
     #include <stdio.h>
     #include <string>
     #include <vector>
     #include <string.h>
     #include <stdlib.h>
     #include <stdio.h>
     #include <stdlib.h>
     #include <sstream>

     namespace patch
    {
        template < typename T > std::string to_string( const T& n )
        {
            std::ostringstream stm ;
            stm << n ;
            return stm.str() ;
        }
    }


     extern FILE * yyin;
     extern int yylex(void);
     void yyerror(const char * msg);
     extern int current_line;

     char * indentifierToken;
     int numberToken;
     int count_names = 0;
     static int temp_count = 0;

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
     char numbers[5] = {'0', '1', '2', '3', '4',};

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

     bool has_main() {
      bool has_main_b = false;
      for (int i = 0; i < symbol_table.size(); i++) {
        Function * f = & symbol_table[i];
        if (f->name == "main") {
          has_main_b = true;
        }
      }
      return has_main_b;
     }

     void printer(const char* h) {
        return;
     }

     std::string create_temp() {
        std::string temp = "_t" + patch::to_string(temp_count);
        temp_count++;
        return temp;
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
    if (!has_main()) {
      printf("Error: No main function found\n");
      exit(1);
    }
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
                    code += patch::to_string(num_args);
                    num_args++;
                }
                else {
                  code += arguments->code[i];
                }
            }
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
            std::string code = std::string(". ") + var_name + std::string("\n");
            std::string code2 = std::string("= ") + var_name + std::string(", $@\n");
            CodeNode *node = new CodeNode;
            node->code = code + code2;
            $$ = node;
         }
         ;

statements: %empty {
            CodeNode *node = new CodeNode;
            $$ = node;
          }
          | statement statements {
            CodeNode *node = new CodeNode;
            $$ = node;
          }
statement: declaration SEMICOLON
         | function_call SEMICOLON
         | if_statement
         | while_statement
         | return_statement SEMICOLON
         | assign_statement SEMICOLON
         | CONTINUE SEMICOLON {printer("statement -> CONTINUE\n");}
         | BREAK SEMICOLON {printer("statement -> BREAK\n");}
         | PRINT expression SEMICOLON {printer("statement -> PRINT expression\n");}
         | GET IDENTIFIER SEMICOLON {printer("statement -> GET IDENTIFIER\n" );}
         ;
declaration: INTEGERVAR IDENTIFIER ASSIGN integerexpression {printer("declaration -> INTEGER IDENTIFIER\n");}
             | INTEGERVAR IDENTIFIER {printer("declaration -> INTEGER IDENTIFIER\n");}
             | ARRAY IDENTIFIER ASSIGN L_SQUARE_BRACKET ARRAYFILL INTEGER R_SQUARE_BRACKET {printer("declaration -> ARRAY IDENTIFIER ASSIGN L_SQUARE_BRACKET ARRAYFILL INTEGER R_SQUARE_BRACKET\n");}
           ;
function_call: IDENTIFIER L_PAREN params R_PAREN {printer("function_call -> IDENTIFIER L_PAREN params R_PAREN\n");}
             ;
params: %empty {printer("params -> epsilon\n");}
        | param COMMA params {printer("params -> param COMMA params\n");}
        | param {printer("params -> param\n");}
        ;
param: INTEGER {printer("param -> INTEGER\n");}
     | IDENTIFIER {printer("param -> IDENTIFIER\n");}
     ;

     
if_statement: IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {printer("if_statement -> IF L_PAREN booleanexpression R_PAREN RBRACE statements\n");}
            | IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE else_statement {printer("if_statement -> IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE else_statement\n");}
            ;
else_statement: ELSE LBRACE statements RBRACE {printer("else_statement -> ELSE LBRACE statements RBRACE\n");}
              ;
while_statement: WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {printer("while -> WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE\n");}
     ;
return_statement: RETURN {printer("return_statement -> RETURN \n");}
                | RETURN expression {printer("return_statement -> RETURN expression \n");}
                ;
assign_statement: IDENTIFIER ASSIGN expression {printer("assign_statement ->IDENTIFIER ASSIGN expression \n");}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression  {printer("assign_statement -> IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression \n" );}
                ;
expression: IDENTIFIER {printer("expression -> IDENTIFIER\n");}
          | integerexpression {printer("expression -> integerexpression\n");}
          | booleanexpression {printer("expression ->booleanexpression\n");}
          | arrayexpression {printer("expression -> arrayexpression\n");}
          ;
integerexpression: INTEGER {printer("integerexpression -> INTEGER\n" );}
            | expression ADD expression {printer("integerexpression -> expression ADD expression\n");}
            | expression SUB expression {printer("integerexpression -> expression SUB expression\n" );}
            | expression MULT expression {printer("integerexpression -> expression MULT expression\n");}
            | expression DIV expression {printer("integerexpression -> expression DIV expression\n");}
            | expression MOD expression {printer("integerexpression ->  expression MOD expression\n");}
            | L_PAREN expression R_PAREN {printer("integerexpression -> L_PAREN expression R_PAREN\n");}
            | function_call {printer("integerexpression -> function_call\n");}
            ;
booleanexpression: expression EQ expression {printer("booleanexpression -> expression EQ expression\n");}
          | expression NEQ expression {printer("booleanexpression -> expression NEQ expression\n");}
          | expression LT expression {printer("booleanexpression -> expression LT expression\n");}
          | expression GT expression {printer("booleanexpression -> expression GT expression\n");}
          | expression LTE expression {printer("booleanexpression -> expression LTE expression\n");}
          | expression GTE expression {printer("booleanexpression -> expression GTE expression\n");}
          | NOT expression {printer("booleanexpression -> NOT expression\n");}
          ;
arrayexpression: IDENTIFIER L_SQUARE_BRACKET integerexpression R_SQUARE_BRACKET {printer("arrayexpression ->  IDENTIFIER L_SQUARE_BRACKET integerexpression R_SQUARE_BRACKET\n");}
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
