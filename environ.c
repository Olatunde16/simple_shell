#include "main.h"

extern char **environ;

/**
* main -
* env:
*
* Return: 0
*/

int main(void) 
{
    char **env = environ;
    while (*env != NULL) 
    {
        printf("%s\n", *env);
        env++;
    }

    return (0);
}
