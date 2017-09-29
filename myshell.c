#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

// Split string into array of char pointers
char **split_line(char *buf)
{
    int i = 0;
    char **args = malloc(64 * sizeof(char *));
    char *tok = strtok(buf, " ");

    while (tok != NULL)
    {
        args[i] = tok;     
        tok = strtok(NULL, " ");
        // printf("args[%i]: %s\n", i, args[i]); // Debugging output
        i++;
    }
    args[i] = NULL;

    return args;
}

// Execute command 
void execute_line(char **args) 
{
    int status;
    pid_t pid;

    // exit builtin command
    if (strcmp(args[0], "exit") == 0) 
    {
        exit(1);
    }
    // cd builtin command
    else if (strcmp(args[0], "cd") == 0)
    {
        if (chdir(args[1]) < 0) {
            perror("sh");
        }
    } 
    else 
    {
        pid = fork();
        if (pid == 0) // Child process
        {
            if (execvp(*args, args) < 0) 
            {     
                perror("sh");
            }     
        } 
        else if (pid < 0) // Error forking
        {
            printf("Forking error");
        } 
        else 
        {
            // Parent process
            waitpid(pid, &status, WUNTRACED);
        }
    }

    
        
}


int main()
{
    char line[1024];
    char **args;
    
    while (1)
    {
        // Print shell prompt with the current time and date
        char date_and_time[20];
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(date_and_time, sizeof(date_and_time), "%x - %I:%M%p", tm);
        printf("%s# ", date_and_time);

        // Get input from user
        fgets(line, sizeof(line), stdin);

        // Remove trailing '\n' from input
        char *pos;
        if ((pos = strchr(line, '\n')) != NULL)
            *pos = '\0';
        
        // Tokenize the input
        char **args = split_line(line);

        // Execute command with arguments
        execute_line(args);
        
    }
}