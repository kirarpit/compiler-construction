### ABOUT
The following discussion is with respect to the spike5*.txt
specification under the folder spikes. 

### SPECIFICATION ISSUES

The following issues were noted during project
development, presented along with the chosen resolutions:
                                               
- **ISSUE #1**: The spec doesn't say much about comma operator type
rules and usage.
- **RESOLUTION**: Comma operator, doesn't preserve the lvalue and is
neither assignable according to the implementation. Check 
'tests/e10.loboc' for more info.

### IMPLEMENTATION SPECIFICS           

The enclosed loboc program is a fully-conforming implementation 
of the spike5*.txt specification, passing all supplied tests.

- **SPECIFIC #1**: In case any errors apart from runtime errors are 
encountered, the assembly code is not printed, instead 
spike4-output with error messages are shown to help understand 
the errors.

- **SPECIFIC #2**: Pointer increment doesn't always increment the
pointer by 1 but by the size of the type it's pointing at. Same 
thing happens in the case of pointer decrement. Check 
'tests/is5_pointer.loboc' for more info.

### ISEQ5 IMPLEMENTATION SPECIFICS           

ISEQ5 is an extended feature using which the program can now 
accept input and produce output. This is made possible with the 
help of a special keyword "loboc". Below are the main use cases 
along with the description. Check grammar.txt under spike5 
folder for the complete usage. 

| Command     | Description                                        |
|-------------|----------------------------------------------------|
| loboc >> a; | Takes the input and stores it in the variable 'a'. |
| loboc << a; | Prints the value of a.                             |

Some key points to note here:-
- The type of the variable 'a' has to be either signed, unsigned
or bool.
- Variable 'a' could be an element of an array as well.

- **SPECIFIC #1**: ISEQ5 is backwards-compatible. Hence, no separate
mechanism is required to build it. To test ISEQ5, the programmer
first has to run ./loboc compiler to generate the assembly code 
and then run this assembly code through spim without using the 
TLC. Consider the following example for a better understanding.

  ```
  $> make
  $> ./loboc tests/is5_bool.loboc > is5_bool.s
  $> spim -file is5_bool.s
  ```

- **SPECIFIC #2**: Although the defined grammar for IO_EXPR allows a
wide variety of usage of the keyword "loboc", not everything
is valid and the program might return an error to help programmer
understand the limitations. Semantic check narrows down the usage
as well. Check is5*.loboc under tests folder for some valid test 
cases.

- **SPECIFIC #3**: When input for a bool type variable is taken from 
the user, the input is converted to either 0 or 1. In the case of
a non-zero input, the input is converted to 1, otherwise it stays 
as it is i.e. 0. Check is5_bool.loboc under tests folder and run 
it for a demonstration.

- **SPECIFIC #4**: Unsigned integer can take signed input but it will
still be treated as unsigned integer throughout the program except
when it's printed because MIPS doesn't support a system call to 
print an unsigned integer. Therefore, all integers are printed as
signed integers. Check 'is5_signed_unsigned.loboc' under tests 
folder for more info.

- **SPECIFIC #5**: For better console readability, a new line is
printed every time the program produces any output.

