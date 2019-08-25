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

System calls - 

1.fprintf()
2.exit()
3.execvp()
This particular variant expects a program name and an array (also called a vector, hence the ‘v’) of string arguments (the first one has to be the program name). The ‘p’ means that instead of providing the full file path of the program to run, we’re going to give its name, and let the operating system search for the program in the path


https://stackoverflow.com/questions/5744393/why-is-the-first-argument-of-getline-a-pointer-to-pointer-char-instead-of-c/36098042

https://stackoverflow.com/questions/4051347/in-c-can-i-initialize-a-string-in-a-pointer-declaration-the-same-way-i-can-init/4051454
