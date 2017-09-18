#include <stdio.h>
#include <string.h>

int main() 
{
    char buff[50];
    int i;
    char *p;
    char *array[10];
    int x;

    // for (x = 0; x < 3; x++);
    while (1)
    {
        printf("Type a command: ");
        fgets(buff, 200, stdin);
        // Breaks the string into tokens and stores a pointer to each token into "array[]"
        i = 0;
        p = strtok(buff, " ");
        while (p != NULL)
        {
            array[i++] = p;
            p = strtok(NULL, " ");
        }

        // Iterates through "array[]" an ddisplays each token on screen
        for (i = 0; i < 3; ++i)
        {
            printf("%s\n", array[i]);
        }

        break;
    }

    return 0;
}