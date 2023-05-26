#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>


/*constants*/
#define EXTERNAL_COMMAND 1
#define INTERNAL_COMMAND 2
#define PATH_COMMAND 3
#define INVALID_COMMAND -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - a struct that maps a command name to a function 
 *
 *@command_name: name of the command
 *@func: the function that executes the command
 */

typedef struct map
{
	char *command_name;
	void (*func)(char **command);
} function_map;

extern char **environ;
extern char *line;
extern char **commands;
extern char *shell_name;
extern int status;

#define (x) (void)(x)

int _putchar(char c);
int _env(int ac, char **av, char **env);
char *_getenv(const char *memb_name);
char *mem_set(char *c, char b, unsigned int x);
int main(int argc __attribute__((unused)), char* argv[]);
void exit(char **code_x args);
void printstr(char *str);
void _rmline(char *str);
void _strcpy(char *here, char *there);
int _strlen(char *str, int len);
