all:
	flex lexer.l
	bison -v -d --file-prefix=y bison.y
	gcc -o parser lex.yy.c y.tab.c -lfl
	
