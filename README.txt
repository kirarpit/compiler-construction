                 CS554 Spike1 - Lexical Analysis

  CONTACT INFORMATION
     Author:          Arpit Garg
     Email(s):        iarpitgarg@gmail.com, kiralobo@cs.unm.edu
     Date:            Fri Feb  9 02:17:38 2018 
                                               
  CONTENT DESCRIPTION                          
                                               
     Spike1 performs lexical analysis and token location for grammars.
     See spike1.txt in the root directory for a complete description.

  SPECIFICATION ISSUES

    The following discussion is with respect to the spike1.txt
    specification. The following issues were noted during project
    development, presented along with the chosen resolutions:
                                                             
    - ISSUE #1: Garbage values in the input apart from the case when 
      they are in a comment (Checkout (s1.4.2) in spike1.txt for more
      info on Comment Processing) might cause the program to exit
      with a non-zero status.
    - RESOLUTION #1: Don't input garbage values. XD

  IMPLEMENTATION SPECIFICS           
                                     
    The enclosed spike1 is a fully-conforming implementation of the
    spike1.txt (version 11) specification, passing all supplied tests.
    
    How to build and test?
     - `make` 		- compiles and builds the source code
     - `make test` 	- for automatically checking all the *.lexi test
			  cases with their corresponding outputs in
			  *.lexo files in 'tests' directory under 
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
