#include "main.h"

/**
 * execute_command - creates a child process and
 * executes command within that process. 
 *
 * args: An array of strings where the first element 
 * is the command and the subsequent elements are its 
 * arguments. The last element should be NULL as required 
 * by execvp().
 *
 * Return:
 * - The exit status of the child process if the command was 
 *   executed successfully.
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
 * main - The main function of the simple shell program.
 * It handles user's input, executes command, and
 * manages processes.
 *
 * input: A character array to store the user's input 
 * and tokenize the input in the simple shell
 *
 * args: the array of strings where the tokenized
 * input will be stored
 *
 * num_args: Used to Keep track of the number of arguments
 * provided by the user.
 *
 * Return: 0
 */

int main(void) 
{
	char input[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];
	int num_args;
	
	while (1) 
	{
		printf("SimpleShell> ");
		
		fgets(input, MAX_INPUT_LENGTH, stdin);
		
		input[strlen(input) - 1] = '\0';
		
		if (strcmp(input, "exit") == 0)
			break;
		
		char *token = strtok(input, " ");
		num_args = 0;
		
		while (token != NULL) 
		{
			args[num_args++] = token;
			token = strtok(NULL, " ");
		}
		
		args[num_args] = NULL;
		
		int result = execute_command(args);
		
		if (result == -1)
			printf("Command not found\n");
	}
	
	return (0);
}