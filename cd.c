#include "main.h"

/**
 * tokenize_input - Tokenizes a user input string into an array of arguments.
 *
 * This function takes a user input string and tokenizes it into separate arguments.
 * The input string is modified in place, and the resulting arguments are stored
 * in the provided array 'args'. The last element of the 'args' array is always set
 * to NULL, following the conventions required for execvp.
 * input: 
 * args:
 *
 * Return:
 */

void tokenize_input(char *input, char *args[]) 
{
	int num_args = 0;
	char *token = input;
	
	while (*token != '\0') 
	{
		while (*token == ' ' || *token == '\t' || *token == '\n') 
		{
			*token = '\0';
			token++;
		}
		
		args[num_args++] = token;
		
		while (*token != '\0' && *token != ' ' && *token != '\t' && *token != '\n') 
			token++;
	}
	
	args[num_args] = NULL;
}

/**
 * execute_command - Executes a command in the child process 
 * args: An array of strings where the first element is the command
 * and the subsequent elements are its arguments. The last
 * element should be NULL as required by execvp().
 *
 * Return:
 * - Returns the exit status of the child process if the command
 *   was executed successfully.
 * - Returns -1 if fork() fails.
 */

int execute_command(char *args[]) 
{
	pid_t pid = fork();
	
	if (pid == 0) 
	{
		execvp(args[0], args);
		
		perror("Command not found");
		
		exit(1);
	} 
	
	else if (pid > 0) 
	{
		int status;
		wait(&status);
		
		return (WEXITSTATUS(status));
	} 
	
	else 
	{
		perror("Fork failed");
		return (-1);
	}
}

/**
 * change_directory - 
 * new_dir:
 *
 * Return:
 */

void change_directory(char *new_dir) 
{
	char current_dir[MAX_INPUT_LENGTH];
	
	getcwd(current_dir, sizeof(current_dir));
	
	if (chdir(new_dir) == 0) 
		setenv("PWD", getcwd(NULL, 0), 1);
	
	else
		perror("cd failed");
}

/**
 * main - 
 * input:
 * args:
 *
 * Return:
 */

int main(void) 
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];
	
	while (1) 
	{
		printf("SimpleShell> ");
		
		fgets(input, MAX_INPUT_LENGTH, stdin);
		
		input[strlen(input) - 1] = '\0';
		
		if (strcmp(input, "exit") == 0)
			break;
		
		tokenize_input(input, args);
		
		if (strcmp(args[0], "cd") == 0) 
		{
			if (args[1] == NULL) 
			{
				change_directory(getenv("HOME"));
			
			else if (strcmp(args[1], "-") == 0) 
			{
				char *previous_dir = getenv("OLDPWD");
				
				if (previous_dir != NULL) 
					change_directory(previous_dir);
				
			}
			
			else 
				printf("OLDPWD not set\n"); 
			}
			
			else 
				change_directory(args[1]);
		} 
		
		else 
		{
			int result = execute_command(args);
			
			if (result == -1) 
				printf("Command not found\n");
		}
	}
	
	return (0);
}
