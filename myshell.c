#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char **split_line(char *buf)
{
    int i = 0;
    char **args = malloc(64 * sizeof(char *));
    char *tok = strtok(buf, " ");

    while (tok != NULL)
    {
        args[i++] = tok;
        tok = strtok(NULL, " ");
    }

    return args;
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

        char **args = split_line(line);

        int i;
        for (i = 0; i < 2; i++)
        {
            printf("%s\n", args[i]);
        }
    
        
        break;
    }
}