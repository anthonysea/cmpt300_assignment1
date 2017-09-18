#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main()
{
    char line[1024];
    
    while (1)
    {
        // Print shell prompt with the current time and date
        char date_and_time[20];
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        strftime(date_and_time, sizeof(date_and_time), "%x - %I:%M%p", tm);
        printf("%s# ", date_and_time);

        fgets(line, sizeof(line), stdin);

        break;
    }
}