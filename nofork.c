#include "main.h"

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
