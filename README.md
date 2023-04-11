# Master Script
> The perfect programming language built at UCR by three geniuses.
> Extension: .mas
> Compiler Name: Master Compiler


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


|   Reserved Words      |    Token Name    |
| --------------------- | ---------------- |
| int                   | INT              |
| function              | FUNCTION         |
| beginparams           | BEGIN_PARAMS     |
| endparams             | END_PARAMS       |
| beginlocals           | BEGIN_LOCALS     |
| endlocals             | END_LOCALS       |
| beginbody             | BEGIN_BODY       | 
| endbody               | END_BODY         |
| array                 | ARRAY            |
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


