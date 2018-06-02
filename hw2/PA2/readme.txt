1. Name: readme
2. Description: describe PA2.tgz and its contents
3. Contents:
    (1) testcase          | directory
    (2) sample_output     | directory
	(3) MiniSat_v1.14_linux
    (3) readme
	
4. Detailed Contents:
    (1) testcase 
        Includes three testcases. 
		Each testcase includes A and B(e.g., c17_A.bench and c17_B.bench).
		The inputs and outputs of A and B are identical, while the interal gate may be different.
		The internal gate order must follow in topological order.
		
		
    (2) sample_output
        Includes three sample_output(eg., c17.dimacs) of each testcase.
        The answer of each testcase:
		example: SAT
		c17    : SAT
		c432   : UNSAT
	
	(3) MiniSat_v1.14_linux
		Minisat binary. 
		Please type "chmod 777 MiniSat_v1.14_linux" before you use it.
