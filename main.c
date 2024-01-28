#include "main.h"

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
		printf("Simple-Shell (PID: %d)> ", getpid());
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
		pid_t pid = fork();
		
		if (pid == 0) 
		{
			execvp(args[0], args);
			perror("Command not found");
			exit(1);
		} 
		
		else if (pid > 0) 
			wait(NULL);
		
		else 
			perror("Fork failed");
	}
	
	return (0);
}
