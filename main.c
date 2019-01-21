#include<stdlib.h>
#include<stdio.h> //for getline()
#include <sys/types.h> //for ssize_t

//argc is the number of command line arguments passed by the user
//including the name of this program itself. argv contains the actual arguments
int main(int argc, char **argv)
{

    shell_loop(); //this will keep looping

    //for portability to non POSIX systems use this macro, on POSIX systems value of this macro is 0
    //this macro is defined in stdlib.h
    return EXIT_SUCCESS; 

}

void shell_loop(void)
{
    //read the command, split it into program and argument, execute the program with arguments
    char *line;
    char **args;
    int status;

    //do while loop is used to get the value of the status variable 
    do
    {

        printf("> ");
        line = read_line();
        args = split_line(line);
        status = execute(args);

        free(line);
        free(args);

    }while(status);

}

char *read_line(void)
{

    char *line = NULL;
    ssize_t bufsize = 0; //ssize_t is signed size_t, to be able to hold -1 also.

    //getline takes the address of the buffer, address of the variable that holds the size of the buffer
    getline(&line, &bufsize, stdin);
    return line;

}