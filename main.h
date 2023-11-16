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

char *custom_getline();
void print_aliases(void);
void print_alias(char *name);
void define_alias(char *name, char *value);
void execute_commands_from_file(const char *filename);
void main(int argc, char *argv[]);
char *get_command_path(char *command);
int execute_command(char *args[]);
void tokenize_input(char *input, char *args[]);
void change_directory(char *new_dir);
