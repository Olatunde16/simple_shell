<<<<<<< HEAD
#include "main.h"

/**
 * execute_command - Executes a command in a child process.
 *
 * This function takes an array of command arguments ('args') and forks a
 * child process to execute the specified command using execvp. It waits for
 * the child process to complete and prints the exit status.
 *
 * args: An array of strings representing the command and its arguments.
 * Return: NULL
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
		
		if (WIFEXITED(status)) 
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
	} 
	
	else 
		perror("Fork failed");
}

/**
 * execute_commands_from_file - Executes commands from a file.
 *
 * This function takes a filename as input, opens the file, and reads lines
 * containing commands. It tokenizes each line into arguments and executes
 * the command using execute_command function.
 *
 * filename: The name of the file containing commands.
 * 
 * Return: NULL
 */

void execute_commands_from_file(const char *filename) 
{
	FILE *file = fopen(filename, "r");
	
	if (file == NULL) 
	{
		perror("Error opening file");
		return;
	}
	
	char line[MAX_INPUT_LENGTH];
	
	while (fgets(line, sizeof(line), file) != NULL) 
	{
		line[strlen(line) - 1] = '\0';
		
		char *args[MAX_ARGS];
		int num_args = 0;
		char *token = strtok(line, " ");
		
		while (token != NULL) 
		{
			args[num_args++] = token;
			token = strtok(NULL, " ");
		}
		
		args[num_args] = NULL;

		if (strcmp(args[0], "setenv") == 0
		{
			if (num_args == 3) 
			{
				if (setenv(args[1], args[2], 1) != 0)
					fprintf(stderr, "Error setting environment variable: %s\n", args[1]);
			} 
			
			else
				fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		} 
		
		else if (strcmp(args[0], "unsetenv") == 0) 
		{
			if (num_args == 2) 
				if (unsetenv(args[1]) != 0) 
					fprintf(stderr, "Error unsetting environment variable: %s\n", args[1]);
		} 
		
		else
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
	
	else
		execute_command(args);
	
	fclose(file);
}

/**
* main - The main function of the simple shell.
* 
* This function is the entry point of the simple shell. If a filename is
* provided as a command-line argument, it reads and executes commands from
* that file. Otherwise, it displays a prompt, waits for user input, and
* executes commands entered by the user. 
* It handles the end of file (Ctrl+D).
* 
* argc: A parameter for handling command-line arguments
* argv: A parameter for handling command-line arguments
* Return: 0
*/

int main(int argc, char *argv[]) 
{
	if (argc == 2) 
		execute_commands_from_file(argv[1]);
	
	else if (argc > 2) 
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return (1);
	} 
	
	else 
	{
		char input[MAX_INPUT_LENGTH];
		
		while (1) 
		{
			printf("simple_shell> ");
			
			if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) 
			{
				printf("\nExiting...\n");
				break;
			}
			
			input[strlen(input) - 1] = '\0';
			
			if (input[0] == '#' || input[0] == '\0')
				continue;

			if (input[0] == ';' || input[0] == '\0')
				continue;

			if (input[0] == '*' || input[0] == '\0')
				continue;
			
			char *args[MAX_ARGS];
			int num_args = 0;
			char *token = strtok(input, " ");
			
			while (token != NULL) 
			{
				args[num_args++] = token;
				token = strtok(NULL, " ");
			}
			
			args[num_args] = NULL;
			
			if (strcmp(args[0], "setenv") == 0) 
			{
				if (num_args == 3) 
				{
					if (setenv(args[1], args[2], 1) != 0)
						fprintf(stderr, "Error setting environment variable: %s\n", args[1]);
				} 
				
				else 
					fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			} 
			
			else if (strcmp(args[0], "unsetenv") == 0) 
			{
				if (num_args == 2) 
				{
					if (unsetenv(args[1]) != 0)
						fprintf(stderr, "Error unsetting environment variable: %s\n", args[1]);
				} 
				
				else 
					fprintf(stderr, "Usage: unsetenv VARIABLE\n");
				else
					execute_command(args);
			}
		}
	
	return (0);
}
=======
#include "main.h"

/**
 * execute_command - Executes a command in a child process.
 *
 * This function takes an array of command arguments ('args') and forks a
 * child process to execute the specified command using execvp. It waits for
 * the child process to complete and prints the exit status.
 *
 * args: An array of strings representing the command and its arguments.
 * Return: NULL
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
		
		if (WIFEXITED(status)) 
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
	} 
	
	else 
		perror("Fork failed");
}

/**
 * execute_commands_from_file - Executes commands from a file.
 *
 * This function takes a filename as input, opens the file, and reads lines
 * containing commands. It tokenizes each line into arguments and executes
 * the command using execute_command function.
 *
 * filename: The name of the file containing commands.
 * 
 * Return: NULL
 */

void execute_commands_from_file(const char *filename) 
{
	FILE *file = fopen(filename, "r");
	
	if (file == NULL) 
	{
		perror("Error opening file");
		return;
	}
	
	char line[MAX_INPUT_LENGTH];
	
	while (fgets(line, sizeof(line), file) != NULL) 
	{
		line[strlen(line) - 1] = '\0';
		
		char *args[MAX_ARGS];
		int num_args = 0;
		char *token = strtok(line, " ");
		
		while (token != NULL) 
		{
			args[num_args++] = token;
			token = strtok(NULL, " ");
		}
		
		args[num_args] = NULL;

		if (strcmp(args[0], "setenv") == 0
		{
			if (num_args == 3) 
			{
				if (setenv(args[1], args[2], 1) != 0)
					fprintf(stderr, "Error setting environment variable: %s\n", args[1]);
			} 
			
			else
				fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		} 
		
		else if (strcmp(args[0], "unsetenv") == 0) 
		{
			if (num_args == 2) 
				if (unsetenv(args[1]) != 0) 
					fprintf(stderr, "Error unsetting environment variable: %s\n", args[1]);
		} 
		
		else
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
	}
	
	else
		execute_command(args);
	
	fclose(file);
}

/**
* main - The main function of the simple shell.
* 
* This function is the entry point of the simple shell. If a filename is
* provided as a command-line argument, it reads and executes commands from
* that file. Otherwise, it displays a prompt, waits for user input, and
* executes commands entered by the user. 
* It handles the end of file (Ctrl+D).
* 
* argc: A parameter for handling command-line arguments
* argv: A parameter for handling command-line arguments
* 
* num_args: Used to Keep track of the number of arguments
* provided by the user.
* token: A pointer to a character or string
* Return: 0
*/

void main2(int argc, char *argv[]) 
{
	if (argc == 2) 
		execute_commands_from_file(argv[1]);
	
	else if (argc > 2) 
	{
		printf("Usage: %s [filename]\n", argv[0]);
		return (1);
	} 
	
	else 
	{
		char input[MAX_INPUT_LENGTH];
		
		while (1) 
		{
			printf("simple_shell> ");
			
			if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) 
			{
				printf("\nExiting...\n");
				break;
			}
			
			input[strlen(input) - 1] = '\0';
			
			if (input[0] == '#' || input[0] == '\0')
				continue;

			if (input[0] == ';' || input[0] == '\0')
				continue;

			if (input[0] == '*' || input[0] == '\0')
				continue;
			
			char *args[MAX_ARGS];
			int num_args = 0;
			char *token = strtok(input, " ");
			
			while (token != NULL) 
			{
				args[num_args++] = token;
				token = strtok(NULL, " ");
			}
			
			args[num_args] = NULL;
			
			if (strcmp(args[0], "setenv") == 0) 
			{
				if (num_args == 3) 
				{
					if (setenv(args[1], args[2], 1) != 0)
						fprintf(stderr, "Error setting environment variable: %s\n", args[1]);
				} 
				
				else 
					fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
			} 
			
			else if (strcmp(args[0], "unsetenv") == 0) 
			{
				if (num_args == 2) 
				{
					if (unsetenv(args[1]) != 0)
						fprintf(stderr, "Error unsetting environment variable: %s\n", args[1]);
				} 
				
				else 
					fprintf(stderr, "Usage: unsetenv VARIABLE\n");
				else
					execute_command(args);
			}
		}
	
	return (0);
}
>>>>>>> 4354e1ec2c411b6fa34f51e73978ba19b8c61d16
