                 CS554 Spike4 - LOBO-C TYPE PROPAGATION AND 
		 		CONSTANT FOLDING

  CONTACT INFORMATION

     Author:          Arpit Garg
     Email(s):        iarpitgarg@gmail.com, kiralobo@cs.unm.edu
     Date:            Tue March 27 12:05:15 2018 
                                               
  CONTENT DESCRIPTION                          
                                               
    Spike4 is a standalone program -- written in C, C++, or Java
    -- that reads a legal LOBO-C block from a filename supplied on the
    command line, or from standard input, then prints, to standard
    output, a variety of information about the LOBO-C code. The output
    format for spike4 is called 'BOTLPIF', which stands for 'block-oriented
    type-labeled parenthesized infix form'. See spike4.txt in spikes
    folder in the root directory for a complete description.

  SPECIFICATION ISSUES

    The following discussion is with respect to the spike4.txt
    specification. The following issues were noted during project
    development, presented along with the chosen resolutions:
                                                             
    - ISSUE #1: The program does have some memory leakages majorly because
      of not well defined ownership of the type objects.
    - RESOLUTION: Should be resolved after flyweight design pattern
      is implemented before the next spike.

  IMPLEMENTATION SPECIFICS           

    The enclosed spike4 is a fully-conforming implementation of the
    spike4.txt specification, passing all supplied tests.
    
    - SPECIFIC #1: Error recovery while parsing AST is being done in the
      same way as spike3 but no error recovery is performed if an error
      occurs during type propogation and constant folding, and the program
      exits with status 1

  BUILD AND MAKE SPECIFICS           

    How to build and test?
     - `make` 		- compiles and builds the source code
     - `make test` 	- for automatically checking all the *.s4i test
			  cases with their corresponding outputs in
			  *.s4o files in 'tests' directory without the
			  whitespace differences 
     - `make realclean` - removes the object files and executables

    How to use?
     - ./spike4 <filename> 	- reads the supplied file and returns 
     				  output as standard output
     - cat <filename> | ./spike4 - takes file contents as standard input
				  and returns output as standard output

  ACKNOWLEDGMENTS:

     Professor Ackley designed the spec and provided some test cases.
                                              
  KNOWN BUGS:

     No known bugs. Please email in case any bugs are found.
