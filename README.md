## Master Script
# Master Script Language Description
> The perfect programming language built at UCR by three geniuses. <br>
> Extension: .mas <br>
> Compiler Name: MASCOM

> The Master Script language provides the following program constructs.
```
1.  Integer scalar variables.
2.  One-dimensional arrays of integers.  
3.  Assignment statements.
4.  While and Do-While loops.
5.  Continue statement.
6.  Break statement.
7.  If-then-else statements.
8.  Read and write statements.
9.  Comments.
10. Functions.

```
Here are some additional details of the Master Script language:

> A comment is introduced by "#" and extends to the end of the current line.
Master Script is case sensitive. All reserved words are lower case except for Integer and Array.
A valid identifier must begin with a letter, may be followed by additional letters, digits, or underscores, and cannot end in an underscore.
Whitespace in Master Script programs can occur due to regular blank spaces, tabs, or newlines.





Example Code: 
> The following illustrates the main function similiar to C++. This code block shows Math (i.e adding, substracting, multiplying, dividing, and mod), instantiation of an Integer and an Array and how to have comments.
```
Integer main() {
    # This is a comment
    Integer variable = 1;
    Array<Integer> arr = [];

    variable = 2;
    variable = 2 + 2;
    variable = 2 - 2;
    variable = 2 * 2;
    variable = 2 / 2;
    variable = 2 % 2;

    return variable;
}
```

Integer Scalar Variables
> The following is an example of the usage of Integer scalar varriables

```
# Correct
Integer one = 1;
Integer two = 2;

one = 4;
two = 8;

# Incorrect
Integer Integer = 1;
Integer = = 1;
one = 2.2;
two = 3.3;
```


One-demensional Arrays of integers
> The following is an example of the usage of One-demensional Arrays of integers

```
Array<Integer> arr = [1, 2, 3];
# Creates an array of size 10.
Array<Integer> arr2 = [...10];

arr[1] = 3;
arr2[9] = 1;
```


Assignment Statements
> The following is an example of assignment statements
```
Integer one = 1;
one = 4;

Array<Integer> arr = [1, 2, 3];
arr[1] = 3;

```

Arithmetic Operators (e.g., +, -, *, /)
> The following is an example of arithmetic operators
```
Integer variable = 1;
# variable is equal to 1;
variable = 2;
# variable is equal to 2;
variable = 2 + 2;
# variable is equal to 4;
variable = variable - 2;
# variable is equal to 2;
variable = 2 * 2;
# variable is equal to 4;
variable = variable / 2;
# variable is equal to 2;
variable = variable % 2;
# variable is equal to 0;
```


Relationship Operators (e.g., +, -, *, /)
> The following is an example of arithmetic operators
```
Integer variable = 1;
# variable is equal to 1;
variable = 2;
# variable is equal to 2;
variable = 2 + 2;
# variable is equal to 4;
variable = variable - 2;
# variable is equal to 2;
variable = 2 * 2;
# variable is equal to 4;
variable = variable / 2;
# variable is equal to 2;
variable = variable % 2;
# variable is equal to 0;
```
List of Tokens
> The following table describes the different kinds of tokens that may be outputted by your lexical analyzer. Comments and whitespace should be ignored by your > lexical analyzer (you should not output any tokens for these).

|   Reserved Words      |    Token Name    |
| --------------------- | ---------------- |
| Integer               | INT              |
| function              | FUNCTION         |
| beginparams           | BEGIN_PARAMS     |
| endparams             | END_PARAMS       |
| beginlocals           | BEGIN_LOCALS     |
| endlocals             | END_LOCALS       |
| beginbody             | BEGIN_BODY       | 
| endbody               | END_BODY         |
| Array                 | ARRAY            |
| of                    | OF               |
| if                    | IF               |
| then                  | THEN             |
| endif                 | ENDIF            |
| else                  | ELSE             |
| while                 | WHILE            |
| do                    | DO               |
| beginloop             | BEGINLOOP        |
| endloop               | ENDLOOP          |
| continue              | CONTINUE         |
| break                 | BREAK            |
| read                  | READ             |
| write                 | WRITE            |
| not                   | NOT              |
| true	                | TRUE             |
| false                 | FALSE            |
| return                | RETURN           |



|   Arithmetic Opeators   |    Token Name    |
| ----------------------- | ---------------- |
|            +            |      ADD         |
|            -            |      SUB         |
|            *            |      MULT        |
|            /            |      DIV         |
|            %            |      MOD         |


|Comparison Operators      |    Token Name       |
| ------------------------ | ------------------- |
|==	                       |       EQ            | 
|!=	                       |      NEQ            |  
|<	                       |      LT             |
|>	                       |      GT             |
|<=	                       |     LTE             |
|>=	                       |     GTE             |


|Other Special Symbols      |    Token Name       |
| ------------------------  | ------------------- |
|;	                        |     SEMICOLON       | 
|:	                        |    COLON            | 
|,	                        |    COMMA            | 
|(	                        |    L_PAREN          | 
|)	                        |    R_PAREN          |
|\[                         |   L_SQUARE_BRACKET  |
|]	                        |    R_SQUARE_BRACKET |
|=	                        |   ASSIGN            | 
|{	                        |   LBRACE            |
|}	                        |   RBRACE            |

|Identifiers and Numbers                                                |    Token Name                                   |
| --------------------------------------------------------------------  | ----------------------------------------------- |
|identifier (e.g., "aardvark", "BIG_PENGUIN", "fLaMInGo_17", "ot73r")	|IDENT XXXX [where XXXX is the identifier itself] |
|number (e.g., "17", "101", "90210", "0", "8675309")	                |NUMBER XXXX [where XXXX is the number itself]    |  
