<<<<<<< HEAD
#include "main.h"

/**
 * tokenize_input - Scans  the input string, identifies the start 
 * of each argument, and replaces spaces with null terminators 
 * to create separate strings for each argument
 *
 * input: A character array to store user input in the simple 
 * shell.
 *
 * args: An array of strings representing command-line 
 * arguments in the simple shell.
 *
 * Return: NULL
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
		{
			token++;
		}
	}
	
	args[num_args] = NULL;
}

/**
 * execute_command - Executes a command in a child process
 *
 * args:  An array of strings where the first element is the 
 * command and the subsequent elements are its arguments. 
 * The last element should be NULL as required by execvp().
 *
 * Return:
 * - Returns the exit status of the child process if the
 *   command was executed successfully.
 * - Returns -1 if fork() fails
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
 * Return: 0
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
		
		int result = execute_command(args);
		
		if (result == -1)
			printf("Command not found\n");
	}
	
	return (0);
}
=======
#include "main.h"

/**
 * tokenize_input - Scans  the input string, identifies the start 
 * of each argument, and replaces spaces with null terminators 
 * to create separate strings for each argument
 *
 * input: A character array to store user input in the simple 
 * shell.
 *
 * args: An array of strings representing command-line 
 * arguments in the simple shell.
 *
 * num_args: An integer variable that represents the count
 * of arguments in an array.
 * token: A pointer to a character
 * Return: NULL
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
		{
			token++;
		}
	}
	
	args[num_args] = NULL;
}

/**
 * execute_command - Executes a command in a child process
 *
 * args:  An array of strings where the first element is the 
 * command and the subsequent elements are its arguments. 
 * The last element should be NULL as required by execvp().
 *
 * Return:
 * - Returns the exit status of the child process if the
 *   command was executed successfully.
 * - Returns -1 if fork() fails
 */

void execute_command(char *args[]) 
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
 * args: The array of strings where the tokenized
 * input will be stored
 *
 * Return: 0
 */

int main() 
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
		
		int result = execute_command(args);
		
		if (result == -1)
			printf("Command not found\n");
	}
	
	return (0);
}
>>>>>>> d0f104afcf004db34f66eeb0cb8369d55bf6e01b
