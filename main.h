#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define MAX_ALIASES 64
#define MAX_ALIAS_NAME 64
#define MAX_ALIAS_VALUE 256

typedef struct 
{
    char name[MAX_ALIAS_NAME];
    char value[MAX_ALIAS_VALUE];
} Alias;

Alias aliases[MAX_ALIASES];
int num_aliases = 0;

void execute_command(char *args[]);
