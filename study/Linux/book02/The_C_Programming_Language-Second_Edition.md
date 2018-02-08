

# 2 - Types, Operators and Expressions

Variables and constants are the basic data objects manipulated in a program. Declarations list
the variables to be used, and state what type they have and perhaps what their initial values
are. Operators specify what is to be done to them. Expressions combine variables and
constants to produce new values. The type of an object determines the set of values it can
have and what operations can be performed on it. These building blocks are the topics of this
chapter.
The ANSI standard has made many small changes and additions to basic types and
expressions. There are now signed and unsigned forms of all integer types, and notations for
unsigned constants and hexadecimal character constants. Floating-point operations may be
done in single precision; there is also a long double type for extended precision. String
constants may be concatenated at compile time. Enumerations have become part of the
language, formalizing a feature of long standing. Objects may be declared const , which
prevents them from being changed. The rules for automatic coercions among arithmetic types
have been augmented to handle the richer set of types.

## 2.1 Variable Names

Although we didn't say so in Chapter 1, there are some restrictions on the names of variables
and symbolic constants. Names are made up of letters and digits; the first character must be a
letter. The underscore `` _ '' counts as a letter; it is sometimes useful for improving the
readability of long variable names. Don't begin variable names with underscore, however,
since library routines often use such names. Upper and lower case letters are distinct, so x and
X are two different names. Traditional C practice is to use lower case for variable names, and
all upper case for symbolic constants.
At least the first 31 characters of an internal name are significant. For function names and
external variables, the number may be less than 31, because external names may be used by
assemblers and loaders over which the language has no control. For external names, the
standard guarantees uniqueness only for 6 characters and a single case. Keywords like if ,
else , int , float , etc., are reserved: you can't use them as variable names. They must be in
lower case.
It's wise to choose variable names that are related to the purpose of the variable, and that are
unlikely to get mixed up typographically. We tend to use short names for local variables,
especially loop indices, and longer names for external variables.



## 2.2 Data Types and Sizes

There are only a few basic data types in C:
| char | a single byte, capable of holding one character in the local character set |
| int | an integer, typically reflecting the natural size of integers on the host machine |





# 4 - Functions and Program Structure

## 4.5 Header Files
>Let is now consider dividing(分离) the calculator program into several source files, as it might be is each of the components（组件） were substantially（实质上） bigger. The main function would go in one file,  which we will call `main.c`; `push`, `pop`, and their variables go into a second file, `stack.c`; `getop` goes into a third, `getop.c`. Finally, `getch` and `ungetch` go into a fourth file, `getch.c`; we separate（分离） them from the others because they would come from a separately-compiled library（分别编译的库） in a realistic program（实际的程序中）.

>There is one more thing to worry about - the definitions and declarations shared among files. As much as possible, we want to centralize this, so that there is only one copy to get and keep right as the program evolves. Accordingly, we will place this common material in a header file, `calc.h`, which will be included as necessary. (The `#include` line is described in Section 4.11.) The resulting program then looks like this:

*calc.h*
```c
#define NUMBER '0'
void push(double);
double pop(void);
int getop(char []);
int getch()
```
*main.c*
```c
#include <stdio.h>
#include <stdlib.h>
#include "calc.h"
#define MAXOP 100
main() {
  ...
}
```
*getop.c*
```c
#include <stdio.h>
#include <ctype.h>
#include "calc.h"
getop() {
  ...
}
```
*stack.c*
```c
#include <stdio.h>
#include "calc.h"
#define MAXVAL 100
int sp =0;
double val[MAXVAL];
void push(double) {
  ...
}
double pop(void) {
  ...
}
```
*getch.c*
```c
#include <stdio.h>
# define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch(void) {
  ...
}
void ungetch(int) {
  ...
}
```

# 4.11 The C Preprocessor
>C provides certain language facilities by means of a preprocessor, which is conceptionally a separate first step in compilation. The two most frequently used features are `#include`, to include the contents of a file during compilation, and `#define`, to replace a token by an arbitrary(任意的) sequence of characters. Other features described in this section include conditional compilation and macros with arguments.


















