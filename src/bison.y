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

     bool check_if_function_in_symbol_table(std::string& value) {
        for (int i = 0; i < symbol_table.size(); i++) {
          Function * f = & symbol_table[i];
          if (f->name == value) {
            return true;
          }
        }
        return false;
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

     bool check_if_variable_in_symbol_table(std::string & temp) {
        Function * f = get_function();
        for (int i = 0; i < f -> declarations.size(); i++) {
          Symbol * s = & f -> declarations[i];
          if (s -> name == temp) {
            return true;
          }
        }
        return false;
     }

     void variable_exist(std::string & temp) {
        if (!check_if_variable_in_symbol_table(temp)) {
          printf("***Error. Variable %s does not exist\n", temp.c_str());
          exit(1);
        }
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
        std::string temp = "_temporary" + patch::to_string(temp_count);
        temp_count++;
        add_variable_to_symbol_table(temp, Integer);
        return temp;
     }
     std::string create_temp_with_code(std::string& code) {
        std::string temp = create_temp();
        std::string create = ". " + temp + "\n";
        code += create;
        return temp;
     }
     std::string build_temp(std::string temp, std::string value) {
        std::string create = ". " + temp + "\n";
        std::string assign = "= " + temp + ", " + value + "\n";
        return create + assign;
     }

     struct CodeNode {
       std::string code; // generated code as a string.
       std::string name;
       std::string temp;
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
%type  <op_val> function_indentifier
%type  <node>   functions
%type  <node>   function
%type  <node>   declaration
%type  <node>   statements
%type  <node>   statement
%type  <node>   argument
%type  <node>   arguments
%type  <node>   expression
%type <node>   param
%type <node>   params
%type <node> function_call
%type <node> integerexpression
%type <node> integer_expression_actual_number
%type <node> booleanexpression
%type <node> arrayexpression
%type <node> return_statement
%type <node> assign_statement

%%
prog_start: 
functions {
    CodeNode *node = $1;
    std::string code = node->code;
    if (!has_main()) {
      printf("Error: No main function found\n");
      exit(1);
    }
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
            if (check_if_variable_in_symbol_table(var_name)) {
              printf("Error: Arguments have same variable name: %s\n", var_name.c_str());
              exit(1);
            }
            // @ is a special token that we will use in functin above.
            std::string code = std::string(". ") + var_name + std::string("\n");
            std::string code2 = std::string("= ") + var_name + std::string(", $@\n");
            add_variable_to_symbol_table(var_name, Integer);
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
            CodeNode *statement = $1;
            CodeNode *statements = $2;
            std::string code = statement->code + statements->code;
            node->code = code;
            $$ = node;
          }
statement: declaration SEMICOLON {
            CodeNode *node = new CodeNode;
            CodeNode *declaration = $1;
            std::string code = declaration->code;
            node->code = code;
            $$ = node;
}
         | function_call SEMICOLON {
            CodeNode *node = new CodeNode;
            CodeNode *function_call = $1;
            std::string code = function_call->code;
            node->code = code;
            $$ = node;
         }
         | if_statement {
            CodeNode *node = new CodeNode;
            $$ = node;
}
         | while_statement {
            CodeNode *node = new CodeNode;
            $$ = node;
}
         | return_statement SEMICOLON {
            CodeNode *node = new CodeNode;
            CodeNode *return_statement = $1;
            std::string code = return_statement->code;
            node->code = code;
            $$ = node;
}
         | assign_statement SEMICOLON {
            CodeNode *node = new CodeNode;
            CodeNode *assign_statement = $1;
            std::string code = assign_statement->code;
            node->code = code;
            $$ = node;
}
         | CONTINUE SEMICOLON {
            CodeNode *node = new CodeNode;
            $$ = node;
}
         | BREAK SEMICOLON {
            CodeNode *node = new CodeNode;
            $$ = node;
}
         | PRINT expression SEMICOLON {
            CodeNode *node = new CodeNode;
            CodeNode *expression = $2;
            std::string code = expression->code;
            code += std::string(".> ") + expression->temp + std::string("\n");
            node->code = code;
            $$ = node;
}
         | GET expression SEMICOLON {
            CodeNode *node = new CodeNode;
            CodeNode *expression = $2;
            std::string code = expression->code;
            code += std::string(".< ") + expression->temp + std::string("\n");
            node->code = code;
            $$ = node;
}
         ;
declaration: INTEGERVAR IDENTIFIER ASSIGN expression {
        std::string var_name = $2;

        if (check_if_variable_in_symbol_table(var_name)) {
          printf("Error: Variable %s already declared\n", var_name.c_str());
          exit(1);
        }

        CodeNode *integerexpression = $4;
        CodeNode *node = new CodeNode;
        std::string code = integerexpression->code;
        code += std::string(". ") + var_name + std::string("\n");
        code += std::string("= ") + var_name + std::string(", ") + integerexpression->temp + std::string("\n");
        add_variable_to_symbol_table(var_name, Integer);
        node->code = code;
        $$ = node;
}
             | INTEGERVAR IDENTIFIER {
                std::string var_name = $2;
                if (check_if_variable_in_symbol_table(var_name)) {
                  printf("Error: Variable %s already declared\n", var_name.c_str());
                  exit(1);
                }
                CodeNode *node = new CodeNode;
                std::string code = std::string(". ") + var_name + std::string("\n");
                node->code = code;
                add_variable_to_symbol_table(var_name, Integer);
                $$ = node;
             }
             | ARRAY IDENTIFIER ASSIGN L_SQUARE_BRACKET ARRAYFILL INTEGER R_SQUARE_BRACKET {
                CodeNode *node = new CodeNode;
                std::string var_name = $2;
                if (check_if_variable_in_symbol_table(var_name)) {
                  printf("Error: Array %s already declared\n", var_name.c_str());
                  exit(1);
                }
                add_variable_to_symbol_table(var_name, Integer); // Arrays & Integers cannot have same name
                std::string code = std::string(".[] ") + var_name + ", " + patch::to_string($6) + std::string("\n");
                node->code = code;
                $$ = node;
             }
           ;
function_call: IDENTIFIER L_PAREN params R_PAREN {
                std::string func_name = $1;
                if (!check_if_function_in_symbol_table(func_name)) {
                  printf("Error: Function %s does not exist \n", func_name.c_str());
                  exit(1);
                }

                CodeNode *params = $3;
                std::string code = params->code;
                std::string temp = create_temp();

                code += ". " + temp + "\n";
                code += "call " + func_name + ", " + temp + "\n";


                CodeNode *node = new CodeNode;
                node->code = code;
                node->temp = temp;
                $$ = node;
              }
             ;
params: %empty {
            CodeNode *node = new CodeNode;
            $$ = node;
}
        | param COMMA params {
            CodeNode *param = $1;
            CodeNode *params = $3;
            std::string code = param->code + params->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            $$ = node;
        }
        | param {
            CodeNode *param = $1;
            std::string code = param->code;
            CodeNode *node = new CodeNode;
            node->code = code;
            // printf(node->code.c_str());
            $$ = node;
        }
        ;
param: INTEGER {
            std::string name = create_temp();
            std::string assign = build_temp(name, patch::to_string($1));
            std::string code = std::string("param ") + name + std::string("\n");
            CodeNode *node = new CodeNode;
            node->code = assign + code;
            $$ = node;
}
     | IDENTIFIER {
            std::string var_name = $1;
            variable_exist(var_name);
            std::string code = std::string("param ") + $1 + std::string("\n");
            CodeNode *node = new CodeNode;
            node->code = code;
            $$ = node;
}
     ;

     
if_statement: IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {printer("if_statement -> IF L_PAREN booleanexpression R_PAREN RBRACE statements\n");}
            | IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE else_statement {printer("if_statement -> IF L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE else_statement\n");}
            ;
else_statement: ELSE LBRACE statements RBRACE {printer("else_statement -> ELSE LBRACE statements RBRACE\n");}
              ;
while_statement: WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE {printer("while -> WHILE L_PAREN booleanexpression R_PAREN LBRACE statements RBRACE\n");}
     ;
return_statement: RETURN {
                    CodeNode *node = new CodeNode;
                    Function * f = get_function();
                    if (f->name == "main") {
                      node->code = std::string("\n");
                    }
                    else {

                    node->code = std::string("ret 0\n");
                    }
                    $$ = node;
                  }
                | RETURN expression {
                    CodeNode *node = new CodeNode;
                    CodeNode *expression = $2;
                    std::string code = expression->code;

                    // Get function and check if it is main or not
                    Function * f = get_function();
                    if (f->name == "main") {
                      printf("Error: Cannot return from main function\n");
                      exit(1);
                    }
                    
                    code += std::string("ret ") + expression->temp + std::string("\n");
                    node->code = code;
                    $$ = node;
                }
                ;
assign_statement: IDENTIFIER ASSIGN expression {
                    CodeNode *node = new CodeNode;
                    std::string var_name = $1;
                    variable_exist(var_name);
                    CodeNode *expression = $3;
                    std::string code = expression->code;
                    code += std::string("= ") + var_name + std::string(", ") + expression->temp + std::string("\n");
                    node->code = code;
                    $$ = node;
}
                | IDENTIFIER L_SQUARE_BRACKET expression R_SQUARE_BRACKET ASSIGN expression  {
                    CodeNode *node = new CodeNode;
                    std::string var_name = $1;
                    variable_exist(var_name);
                    CodeNode *expression1 = $3;
                    CodeNode *expression2 = $6;
                    std::string code = expression1->code;
                    code += expression2->code;
                    code += std::string("[]= ") + var_name + std::string(", ") + expression1->temp + std::string(", ") + expression2->temp + std::string("\n");
                    node->code = code;
                    $$ = node;
                }
                ;
expression: IDENTIFIER {
            CodeNode *node = new CodeNode;
            std::string temp = $1;
            variable_exist(temp);
            node->temp = temp;
            node->code = "";
            $$ = node;
          }
          | integerexpression {
            CodeNode *node = new CodeNode;
            CodeNode *integerexpression = $1;
            std::string temp = integerexpression->temp;
            std::string code = integerexpression->code;
            node->temp = temp;
            node->code = code;
            $$ = node;
          }
          | booleanexpression {
            CodeNode *node = new CodeNode;
            CodeNode *booleanexpression = $1;
            std::string temp = booleanexpression->temp;
            std::string code = booleanexpression->code;
            node->temp = temp;
            node->code = code;
            $$ = node;
          }
          | arrayexpression {
            CodeNode *node = new CodeNode;
            CodeNode *arrayexpression = $1;
            std::string temp = arrayexpression->temp;
            std::string code = arrayexpression->code;
            node->temp = temp;
            node->code = code;
            $$ = node;
          }
          ;
integerexpression: integer_expression_actual_number {
              CodeNode *node = new CodeNode;
              CodeNode *integer_expression_actual_number = $1;
              std::string temp = integer_expression_actual_number->temp;
              node->temp = temp;
              $$ = node;
            }
            | L_PAREN integerexpression R_PAREN {
              CodeNode *node = new CodeNode;
              CodeNode *integerexpression = $2;
              std::string temp = integerexpression->temp;
              node->temp = temp;
              node->code = integerexpression->code;
              $$ = node;
            }
            | expression ADD expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "+ " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
            }
            | expression SUB expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "- " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
            }
            | expression MULT expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "* " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
            }
            | expression DIV expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "/ " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
            }
            | expression MOD expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "% " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
            }
            | function_call {
              CodeNode *node = new CodeNode;
              CodeNode *function_call = $1;
              std::string temp = function_call->temp;
              std::string code = function_call->code;
              node->code = code;
              node->temp = temp;
              $$ = node;
            }
            ;
booleanexpression: expression EQ expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "== " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
}
          | expression NEQ expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "!= " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
          }
          | expression LT expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "< " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
          }
          | expression GT expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "> " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
          }
          | expression LTE expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += "<= " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
          }
          | expression GTE expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $1;
              CodeNode *expression2 = $3;
              std::string temp1 = expression1->temp;
              std::string temp2 = expression2->temp;
              std::string code = expression1->code + expression2->code;
              std::string temp = create_temp_with_code(code);
              code += ">= " + temp + ", " + temp1 + ", " + temp2 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
          }
          | NOT expression {
              CodeNode *node = new CodeNode;
              CodeNode *expression1 = $2;
              std::string temp1 = expression1->temp;
              std::string code = expression1->code;
              std::string temp = create_temp_with_code(code);
              code += "! " + temp + ", " + temp1 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
          }
          ;
arrayexpression: IDENTIFIER L_SQUARE_BRACKET integerexpression R_SQUARE_BRACKET {
              CodeNode *node = new CodeNode;
              CodeNode *integer_expression = $3;
              std::string var_name = $1;
              variable_exist(var_name);
              std::string temp1 = integer_expression->temp;
              std::string code = integer_expression->code;
              std::string temp = create_temp_with_code(code);
              code += "=[] " + temp + ", " + var_name + ", " + temp1 + "\n";
              node->code = code;
              node->temp = temp;
              $$ = node;
}
               ;

integer_expression_actual_number: INTEGER {
  CodeNode *node = new CodeNode;
  node->temp = $1;
  $$ = node;
}

function_indentifier: IDENTIFIER {
  std::string func_name = $1;
  if (check_if_function_in_symbol_table(func_name)) {
    printf("Error: Function %s already defined\n", func_name.c_str());
    exit(1);
  }
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
