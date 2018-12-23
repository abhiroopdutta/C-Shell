#include<stdlib.h>

/* A shell does three things in its lifetime - 
    1.initialize - read and execute its configuration files
    2.interpret - read commands from stdin and execute them
    3.terminate - execute shutdown command, frees up memory and terminate 

our shell won't have any config files, no shutdown commands, so only looping
to interpret instructions
*/

//argc is the number of command line arguments passed by the user
//including the name of this program itself. argv contains the actual arguments

int main(int argc, char **argv)
{

    shell_loop(); //this will keep looping

    //for portability to non POSIX systems use this macro, on POSIX systems value of this macro is 0
    //this macro is defined in stdlib.h
    return EXIT_SUCCESS; 

}