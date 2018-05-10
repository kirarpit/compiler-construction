              CS554 Spike5 - LOBO-C MIPS CODE GENERATION

  CONTACT INFORMATION

     Author:          Arpit Garg
     Email(s):        iarpitgarg@gmail.com, kiralobo@cs.unm.edu
     Date:            Wed May 09 20:512:45 2018 
                                               
  CONTENT DESCRIPTION                          
                                               
    Spike5 is a standalone program -- written in C++ -- that reads
    a legal LOBO-C block from a filename supplied on the command 
    line, or from standard input, then prints, to standard output, 
    MIPS assembly code. Spike5 -- except the extended feature(ISEQ5)
    -- will be tested using the 'tlc' testing framework which can
    be found under spike5 folder. See spike5*.txt in spikes folder 
    in the root directory for a complete description.

  SPECIFICATION ISSUES

    The following discussion is with respect to the spike5.txt
    specification. The following issues were noted during project
    development, presented along with the chosen resolutions:
                                                             
    - ISSUE #1: The spec doesn't say much about comma operator type
    rules and usage.
    - RESOLUTION: Comma operator, doesn't preserve the lvalue and is
    neither assignable according to the implementation. Check 
    'tests/e10.loboc' for more info.

  IMPLEMENTATION SPECIFICS           

    The enclosed spike5 is a fully-conforming implementation of the
    spike5.txt specification, passing all supplied tests.
    
    - SPECIFIC #1: In case any errors apart from runtime errors are 
    encountered, the assembly code is not printed, instead 
    spike4-output with error messages are shown to help understand 
    the errors.

    - SPECIFIC #2: Pointer increment doesn't always increment the
    pointer by 1 but by the size of the type it's pointing at. Same 
    is the case with pointer decrement. Check 'tests/is5_pointer.loboc'
    for more info.

  ISEQ5 IMPLEMENTATION SPECIFICS           

    ISEQ5 is an extended feature using which, the program accepts input
    and can produce output too. This is made possible with the help of 
    a special keyword "loboc". Check spike5 grammar.txt for the 
    complete usage. 

    - SPECIFIC #1: ISEQ5 is backward compatible. Hence, no separate
    mechanism is required to run spike5. To test ISEQ5, the programmer
    has to take the generated assembly code and run it through spim
    without using the TLC. Check 'Build, Make & Test' section in the
    README file for more info.

    - SPECIFIC #2: Although the defined grammar for IO_EXPR allows a
    wide variety of the usage of the keyword "loboc", not everything
    is valid and the program might return an error. Semantic analysis 
    narrows down the usage. Check is5*.loboc under tests folder for 
    some valid usages.

    - SPECIFIC #3: When a bool type variable input is taken from the 
    user, the input is converted to either 0 or 1. In the case of a
    non-zero input, the input is converted to 1, otherwise it stays 0.

  BUILD, MAKE & TEST SPECIFICS           

    How to build and test?
     - `make` 		- compiles and builds the source code
     - `make realclean` - removes the object files and the executable

    How to use?
     - ./spike5 <filename>   - reads the supplied loboc code and
     			      returns assembly code as standard output

     - spim -file <filename> - reads assembly code and runs it on a
     			      simulation of MIPS architecture

    Example:
    $> ./spike5 tests/is5_bool.loboc > assemblyCode.s
    $> spim -file assemblyCode.s

  ACKNOWLEDGMENTS:

     Professor Ackley designed the spec and provided some test cases.
                                              
  KNOWN BUGS:

     No known bugs. Please email in case any bugs are found.
