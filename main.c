#include <stdlib.h> //malloc(), reallaoc(), free(), exit(), execvp(), EXIT_SUCCESS, EXIT_FAILURE
#include <stdio.h> //for getline(), fprintf(), stderr(), getchar(), perror()
#include <sys/types.h> //for ssize_t
#include <string.h> //for strtok(), strcmp()
#include <unistd.h> //for fork(), chdir(), pid_t
#include <sys/wait.h> //for waitpid() and other wait macros
#define TOKEN_BUFSIZE 64
#define TOKEN_DELIM " \t\r\n\a"


//list of built-in commands
char *builtin_commands[] = {"cd", "help", "exit"};

//forward declarations of builtin functions
int shell_cd(char **);
int shell_help(char **);
int shell_exit(char **);

//array of function pointers, these functions take char ** as argument and return an int
int (*builtin_functions[])(char**) = { &shell_cd, &shell_help, &shell_exit };

int shell_num_builtins()
{
  return sizeof(builtin_commands) / sizeof(char *);
}

int shell_cd(char **args)
{
    if (args[1] == NULL)
    {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
    }

    else
    {
        if(chdir(args[1]) != 0) 
        {
            perror("shell error");
        }
    }

    return 1;
}

int shell_help(char **args)
{
    int i;
    printf("Simple Shell\n");
    printf("Enter program names and arguments, and hit enter.\n");
    printf("The following are built in:\n");

    for (i = 0; i < shell_num_builtins(); i++) 
    {
        printf("  %s\n", builtin_commands[i]);
    }

    return 1;
}

int shell_exit(char **args)
{
    //signal for the command loop to terminate
    return 0;
}

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

int shell_launch(char **args)
{

    pid_t pid, wpid;
    int status;

    pid = fork();
    if(pid == 0)
    {
        if(execvp(args[0], args) == -1)
        {
            perror("shell error");
        }
        exit(EXIT_FAILURE);
    }

    if(pid <= 0)
    {
        perror("shell fork error");
    }

    else
    {   
        do 
        {
            //block the parent process until the child is terminated or stopped
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status)); 
        //keep blocking until either the child is terminated normally or terminated by a signal, 
        //if none happens, i.e, child hasn't terminated either way, then continue blocking it
    }

    //this is a signal to the calling function that we should prompt for input again
    return 1;       
}


int shell_execute(char **args)
{
    int i;
    if (args[0] == NULL) 
    {
        // An empty command was entered.
        return 1;
    }

    for(i=0; i<shell_num_builtins(); i++)
    {
        if(strcmp(args[0], builtin_commands[i]) == 0)
        {
            return (*builtin_functions[i])(args);
        }   
    }

    return shell_launch(args);
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
        status = shell_execute(args);

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