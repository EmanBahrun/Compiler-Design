echo "" > lex_output.txt
for i in examples/*.mas; do echo $i; ./src/a.out < $i; echo; done > lex_output.txt


echo "" > bison_output.txt
for i in examples/*.mas; do echo $i; ./src/parser $i; echo; done > bison_output.txt