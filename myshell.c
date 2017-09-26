#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

char **split_line(char *buf)
{
    int i = 0;
    char **args = malloc(64 * sizeof(char *));
    char *tok = strtok(buf, " ");

    while (tok != NULL)
    {
        args[i] = tok;     
        tok = strtok(NULL, " ");
        printf("args[%i]: %s\n", i, args[i]);
        i++;
    }
    args[i] = NULL;

    return args;
}

void execute_line(char **args) 
{
    int status;
    pid_t pid;
    pid = fork();
    if (pid == 0) 
    {
        if (execvp(*args, args) < 0) 
        {
            
            perror("sh");
        }     
    } 
    else if (pid < 0) 
    {
        printf("Forking error");
    } 
    else 
    {
        // Parent process
        waitpid(pid, &status, WUNTRACED);
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

        fgets(line, sizeof(line), stdin);

        // Remove trailing '\n' from the usage of fgets()
        char *pos;
        if ((pos = strchr(line, '\n')) != NULL)
            *pos = '\0';
        

        char **args = split_line(line);

        /*
        int i;
        for (i = 0; i < 2; i++)
        {
            printf("%s\n", args[i]);
        }
        */
        execute_line(args);
        
    }
}