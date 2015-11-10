----------------
Faults:
----------------
When compiling with the '-ansi' flag, if no errors were detected I received
'clang error: argument unused during compilation: -ansi', which
halted compilation. The only way I found around this was to remove -ansi
from the makefile (after fixing all the bugs it detected). 

In summary:
the program works, and all errors detected by -ansi were fixed, but I
could not include -ansi and have the program executable at the same time.
I hope this doesn't necessitate a 0 on the assignment.
----------------
Running:
----------------
Type 'make' on the command line, then './a.out'. Enter the name of the
file you would like to import (provided it is in your current directory), and
hit enter. The various permutations of the list should print.
