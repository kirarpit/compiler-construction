                 CS554 Spike5 - LOBO-C MIPS CODE GENERATION

  CONTACT INFORMATION

     Author:          Arpit Garg
     Email(s):        iarpitgarg@gmail.com, kiralobo@cs.unm.edu
     Date:            Fri April 20 16:55:15 2018 
                                               
  CONTENT DESCRIPTION                          
                                               
    Spike5 is a standalone program -- written in C++ -- that reads
    a legal LOBO-C block from a filename supplied on the command 
    line, or from standard input, then prints, to standard output, 
    MIPS assembly code. Spike5 will be tested using the 'tlc' testing
    framework which can be found under spike5 folder. See spike5.txt in
    spikes folder in the root directory for a complete description.

  SPECIFICATION ISSUES

    The following discussion is with respect to the spike5.txt
    specification. The following issues were noted during project
    development, presented along with the chosen resolutions:
                                                             
    - ISSUE #1: The spec doesn't say much about comma operator type
    rules and usage.
    - RESOLUTION: Comma operator, doesn't preserve the lvalue and is
    neither assignable according to the implementation. Check 
    'tests/t10.loboc' for more info.

  IMPLEMENTATION SPECIFICS           

    The enclosed spike5 is a fully-conforming implementation of the
    spike5.txt specification, passing all supplied tests.
    
    - SPECIFIC #1: In case any errors apart from runtime errors are 
    encountered, the assembly code is not printed, instead Spike4 output
    with error messages are shown to help understand the errors.

  BUILD AND MAKE SPECIFICS           

    How to build and test?
     - `make` 		- compiles and builds the source code
     - `make realclean` - removes the object files and executables

    How to use?
     - ./spike5 <filename> 	- reads the supplied file and returns 
     				  output as standard output
     - cat <filename> | ./spike5 - takes file contents as standard input
				  and returns output as standard output

  ACKNOWLEDGMENTS:

     Professor Ackley designed the spec and provided some test cases.
                                              
  KNOWN BUGS:

     - Might encounter Segment fault in case when type propagation fails 
     and the compiler tries to find more errors.
     - ISEQ4 pointer dereference might not output correct assembly code in
     case there multiple types involved.
