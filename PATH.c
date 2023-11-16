#include "main.h"

/**
 * get_command_path - Searches for the full path of a command in the 
 * directories specified by the PATH environment variable.
 *
 * This function takes a command name as input and searches for it in 
 * the directories specified by the PATH environment variable.
 * If the command is found and is executable, it returns the full path 
 * of the command. If the command is not found or is not
 * executable in any of the specified directories, it returns NULL.
 *
 * command: The name of the command to search for.
 *
 * Return:
 * - On success, a dynamically allocated string containing the 
 *   full path of the command (which should be freed by the caller).
 * - On failure (command not found or not executable), NULL.
 */

char *get_command_path(char *command) 
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");
	
	while (token != NULL) 
	{
		char *command_path = malloc(strlen(token) + strlen(command) + 2);
		
		sprintf(command_path, "%s/%s", token, command);
		
		if (access(command_path, X_OK) == 0) 
		{
			free(path_copy);
			return (command_path);
		}
		
		free(command_path);
		token = strtok(NULL, ":");
	}
	
	free(path_copy);
	return (NULL);
}

/**
 * execute_command - Executes a command in a child process.
 *
 * This function creates a child process using fork() and attempts
 * to execute the command specified in the args array. If the 
 * command is found and executed successfully,the parent process
 * waits for the child process to complete and retrieves its exit 
 * status.If the command execution fails, an error message is printed.
 *
 * args: An array of strings where the first element is the command 
 * and the subsequent elements are its arguments. The last element 
 * should be NULL as required by execvp().
 *
 * Return:
 * - Returns the exit status of the child process if the command was 
 *   executed successfully.
 * - Returns -1 if fork() fails.
 */
int execute_command(char *args[]) 
{
	char *command_path = get_command_path(args[0]);
	
	if (command_path == NULL) 
	{
		printf("Command '%s' not found\n", args[0]);
		return (-1);
	}
	
	pid_t pid = fork();
	
	if (pid == 0) 
	{
		execv(command_path, args);
		perror("Execution failed");
		free(command_path);
		exit(1);
	} 
	
	else if (pid > 0) 
	{
		int status;
		
		wait(&status);
		free(command_path);
		
		return (WEXITSTATUS(status));
	} 
	
	else 
	{
		perror("Fork failed");
		free(command_path);
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
		
		if (args[0] != NULL && access(args[0], X_OK) == 0) 
		{
			int result = execute_command(args);
			
			if (result == -1) 
				printf("Failed to execute command\n");
		} 
		
		else 
			printf("Command '%s' not found\n", args[0]);
	}
	
	return (0);
}
