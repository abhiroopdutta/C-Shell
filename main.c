#include<stdlib.h>
#include<stdio.h> //for getline()
#include <sys/types.h> //for ssize_t
#include <string.h>
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"


char *shell_read_line(void)
{
    char *line = NULL;
    ssize_t bufsize = 0; //ssize_t is signed size_t, to be able to hold -1 also.

    //getline takes the address of the buffer, address of the variable that holds the size of the buffer
    getline(&line, &bufsize, stdin);
    return line;
}

char **shell_split_line(char *line)
{
    int bufsize = TOKEN_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens)
    {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIM);

    while(token!= NULL)
    {
        tokens[position] = token;
        position++;

        if(position >= bufsize)
        {
            bufsize += TOKEN_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));

            if(!tokens)
            {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
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
        line = shell_read_line();
        args = shell_split_line(line);
        // status = shell_execute(args);

        free(line);
        free(args);

    }while(status);

}

//argc is the number of command line arguments passed by the user
//including the name of this program itself. argv contains the actual arguments
int main(int argc, char **argv)
{

    shell_loop(); //this will keep looping

    //for portability to non POSIX systems use this macro, on POSIX systems value of this macro is 0
    //this macro is defined in stdlib.h
    return EXIT_SUCCESS; 

}