                 CS554 Spike2 - LOBO-C EXPRESSION TREES

  CONTACT INFORMATION
     Author:          Arpit Garg
     Email(s):        iarpitgarg@gmail.com, kiralobo@cs.unm.edu
     Date:            Sun Feb  18 21:46:01 2018 
                                               
  CONTENT DESCRIPTION                          
                                               
     Spike2 performs lexical analysis and grammar parsing on tokens.
     See spike2.txt in the root directory for a complete description.

  SPECIFICATION ISSUES

    The following discussion is with respect to the spike2.txt
    specification. The following issues were noted during project
    development, presented along with the chosen resolutions:
                                                             
    - ISSUE #1: Output in the test cases when errors are encountered is
      inconsistent. Possibly because of a bug where semicolon in not
      being checked before printing the parsed tree.
    - RESOLUTION #1: Since, the spike specification doesn't talk about
      the output when errors are encountered, I've taken the liberty
      to be consistent with the inconsistency and reproduce the bug.

    - ISSUE #2: In ASGN_EXPR, when COND_EXPR is successfully parsed
      and "=" token is found next, the parse COND_EXPR is assumed to
      be POSTFIX_EXPR instead. So, some inputs like "-1=1;" would be
      parsed as if they are legal. Although, they would result into 
      legal counterparts i.e. ((-1)=1) in above example.
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
