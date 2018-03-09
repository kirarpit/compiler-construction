                 CS554 Spike2 - LOBO-C TYPES AND BLOCKS

  CONTACT INFORMATION
     Author:          Arpit Garg
     Email(s):        iarpitgarg@gmail.com, kiralobo@cs.unm.edu
     Date:            Fri March 9 12:42:11 2018 
                                               
  CONTENT DESCRIPTION                          
                                               
     Spike3 parses the standard input or takes a file name as an
     argument and outputs information about variable declarations
     followed by BOFPIF. See spike3.txt in the root directory for a
     complete description.

  SPECIFICATION ISSUES

    The following discussion is with respect to the spike2.txt
    specification. The following issues were noted during project
    development, presented along with the chosen resolutions:
                                                             
    - ISSUE #1: In case an error is encountered while parsing 
      STATEMENTS, the whole statement in which error is found would be
      ignored in BOFPIF output but any varaibles that occur before the
      error would still be parsed for variable declaration.
      the expression Output in the test cases when errors are encountered is
      inconsistent. Possibly because of a bug where semicolon in not
      being checked before printing the parsed tree.
    - RESOLUTION #1: Since, the spike specification doesn't talk about
      the output when errors are encountered, I've taken the liberty
      to be consistent with the inconsistency and reproduce the bug.

    - ISSUE #2: In ASGN_EXPR, when COND_EXPR is successfully parsed
      and "=" token is found next, the parse COND_EXPR is assumed to
      be POSTFIX_EXPR instead. So, some inputs like "-1=1;" would be
      parsed as if they are legal. Although, they would result into 
      their legal counterparts i.e. ((-1)=1) in above example.
    - RESOLUTION #2: Kind of a hack, fixed it for now.

  IMPLEMENTATION SPECIFICS           
                                     
    The enclosed spike1 is a fully-conforming implementation of the
    spike1.txt (version 11) specification, passing all supplied tests.
    
    How to build and test?
     - `make` 		- compiles and builds the source code
     - `make test` 	- for automatically checking all the *.expi test
			  cases with their corresponding outputs in
			  *.expo files in 'tests' directory under 
			  'root' directory
     - `make realclean` - removes the object files and executables

    How to use?
     - ./spike1 <filename> 	- reads file contents and returns output
				  as standard output
     - cat <filename> | ./spike - takes file contents as standard input
				  and returns output as standard output

  ACKNOWLEDGMENTS:

     Professor Ackley designed the spec and provided some test cases.
                                              
  KNOWN BUGS:

     No known bugs. Please email in case any bugs are found.
