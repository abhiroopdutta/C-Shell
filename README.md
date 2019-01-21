# C-Shell

A shell does three things in its lifetime - 
    1.initialize - read and execute its configuration files
    2.interpret - read commands from stdin and execute them
    3.terminate - execute shutdown command, frees up memory and terminate 

Our shell won't have any config files, no shutdown commands, so only looping
to interpret instructions

During the loop, the shell again does three things - 
    Read: Read the command from standard input.
    Parse: Separate the command string into a program and arguments.
    Execute: Run the parsed command
