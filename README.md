# basic-c-interpreter
A basic c++ interpreter for the language Z+-.

Consider a very simple programming language named Z+-. The Z+-  programming language has the following features:

Z+- variables can store a string or integer value. 
A single variable can switch between integer and string values during program execution. Assigning a value to a variable creates that variable for future use. A runtime error occurs if a variable is used before it is given a value.
Variables are case sensitive and consist only of upper and lower-case letters.
The following are Z+- reserved words: PRINT, FOR, ENDFOR, PROC, ENDPROC, CALL
You may assume that the Z+- program is syntactically correct.
The PRINT statement displays one particular variable’s value. This is done as:

		PRINT numCookies ;


The right-hand side of a simple assignment statement (i.e., =) is either a variable name (which must have a value), signed integer, or string literal. For example, the following are valid:

A = 12 ;
A = B ;
A = "hello" ;

There are three compound assignment statements: +=, *=, and -=.  The meaning of these operators depends on data type of the left and right hand side of the operator. 

<string var> += <string>   concat right string onto end of left string
<integer var> += <integer> increment left integer with value on right 
<integer var> *= <integer> multiply left integer by value on right 
<integer var> -= <integer> subtract right integer from value on left

A += 34 ;
A *= B ;
A += "hello world" ;

	All other combinations are illegal and cause a runtime error.

Every statement is terminated by a semi-colon.
There is a loop statement – FOR - whose body contains at least one simple statement (i.e., no nested loops), which are on presented on one line. The keyword FOR is followed by an integer constant, which indicates the number of times to execute the loop. Following this number is a sequence of statements defining the loop's body, followed by the word ENDFOR, as done here:

FOR 5 B += A ; A *= 2 ; ENDFOR


Z+-  for loops can be nested and must appear on one line:

FOR 5 B += A ; A *= 2 ; FOR 10 A += B ; ENDFOR A += 2 ; ENDFOR


Z+- programs must have at least one space separating all lexical elements.
Here is an example Z+- program:

A = 1 ;
B = 0 ;
FOR 5 B += A ; A *= 2 ; ENDFOR
A += 1000 ;
PRINT A ;
PRINT B ;
This program's output is:

A=1032
B=31
 
As an example, an equivalent Python program would be:

A = 1
B = 0
for i in range(5):
        B += A
        A *= 2
A += 1000
print("A=" + str(A))
print("B=" + str(B))

Here is a second Z+- program:
A = 10 ;
A += A ;
PRINT A ;
A = "hello" ;
A += A ;
PRINT A ;
A += 123 ;
PRINT A

The output to this second program would yield an error. Your program should display the line number of this error and then stop processing:

A=20
A=hellohello
RUNTIME ERROR: line 7


###INSTALLATION:
clone the repository to a given directory
 Use
 
  >c++ -std=c++11 -o interpreter *.cpp
  
  >interpreter prog1.zpm

to run the file prog1.zpm
