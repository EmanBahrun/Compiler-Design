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


Precedence
> Operators are listed top to bottom, in descending precendence.

<table border="1">
<tbody><tr>
<th style="text-align: left">Precedence</th>
<th style="text-align: left">Operator</th>
<th style="text-align: left">Description</th>
<th style="text-align: left">Associativity</th>
</tr>
<tr>
<th >0</th>
<td><code>()</code></td>
<td>Function calls</td>
<td>Left-to-right</td>
</tr>
</tr>
<tr>
<th >1</th>
<td><code>[]</code></td>
<td>Array subscripting</td>
<td>Left-to-right</td>
</tr>
<tr>
<th>2</th>
<td><code>-</code></td>
<td>Unary minus</td>
<td>Right-to-left</td>
</tr>
<tr>
<th rowspan="3">3</th>
<td><code>*</code></td>
<td>Multiplication</td>
<td style="vertical-align: top" rowspan="12">Left-to-right</td>
</tr>
<tr>
<td><code>/</code></td>
<td>Division</td>
</tr>
<tr>
<td><code>%</code></td>
<td> Remainder</td>
</tr>
<tr>
<th rowspan="2">4</th>
<td><code>+</code></td>
<td>Addition</td>
</tr>
<tr>
<td><code>-</code></td>
<td>Subtraction</td>
</tr>

<tr>
<th rowspan="6">5</th>
<td><code>&lt;</code></td>
<td>For relational operators  < </td>
</tr>
<tr>
<td><code>&lt;=</code></td>
<td>For relational operators <= </td>
</tr>
<tr>
<td><code>&gt;</code></td>
<td>For relational operators > </td>
</tr>
<tr>
<td><code>&gt;=</code></td>
<td>For relational operators >= </td>
</tr>
<tr>
<td><code>==</code></td>
<td>For relational operator == </td>
</tr>
<tr>
<td><code><></code></td>
<td>For relational operator != </td>
</tr>
<tr>
<tr>
<th>6</th>
<td><code>not</code></td>
<td>Logical not</td>
<td>Right-to-left</td>
</tr>
<tr>
<tr>
<tr>
<th >7</th>
<td><code>:=</code></td>
<td>Assignment </td>
<td>Right-to-left</td>
</tr>
</tbody></table>

