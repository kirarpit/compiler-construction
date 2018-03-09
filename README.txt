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

    The following discussion is with respect to the spike3.txt
    specification. The following issues were noted during project
    development, presented along with the chosen resolutions:
                                                             
    - ISSUE #1: In the provided test cases outputs, blank line at the
      end of the file seems to be missing.
    - RESOLUTION: This behaviour is not replicated and a blank line is
      added at the end of the given test cases output files. Refer
      (s3.4.6.2.3.5) for further information.

    - ISSUE #2: If extra closing curly bracket is encountered, then
      BLOCK parsing returns and no error recovery is performed. Program
      then exits with +1 error count. (See t15.blk* for more info)

  IMPLEMENTATION SPECIFICS           

    The enclosed spike3 is a fully-conforming implementation of the
    spike3.txt specification, passing all supplied tests.
    
    - SPECIFIC #1: In case an error is encountered while parsing 
      DEFS, the whole definition would be ignored as if it wasn't there
      to start with. It would not appear in VDI at all or anywhere else.

    - SPECIFIC #2: In case an error is encountered while parsing 
      STATEMENTS, the whole statement in which error is found would be
      ignored in BOFPIF output but any varaibles that occur before the
      error would still be parsed for variable declaration.
    
    - SPECIFIC #3: If more than 9 errors are encountered, the program
      gives up faith in machines and exits right away without any 
      sanity checks.

    - SPECIFIC #4: Block is printed before checking whether the next token
      is EOF or not.

  BUILD AND MAKE SPECIFICS           

    How to build and test?
     - `make` 		- compiles and builds the source code
     - `make test` 	- for automatically checking all the *.expi test
			  cases with their corresponding outputs in
			  *.expo files in 'tests' directory under 
			  'root' directory
     - `make realclean` - removes the object files and executables

    How to use?
     - ./spike3 <filename> 	- reads file contents and returns output
				  as standard output
     - cat <filename> | ./spike3 - takes file contents as standard input
				  and returns output as standard output

  ACKNOWLEDGMENTS:

     Professor Ackley designed the spec and provided some test cases.
                                              
  KNOWN BUGS:

     No known bugs. Please email in case any bugs are found.
