#include "main.h"
#include <stargs.h>

/**
* main - parameter with return value
* @argc: stores number of command-line arguments passed
* @argv: an array of pointers listing all the arguments
*
* Return: Always 0
*/

int main(int argc, char* argv[])
{
    printf("The program name is: %s", argv[0]);

    if (argc == 1)
        printf("\n No extra Command-Line argument was passed "
               "other than the program name");

    if (argc >= 2) {
        printf("\n Number Of Arguments Passed: %d", argc);
        printf("\n----The following are the Command-Line "
               "arguments passed----");

        for (int i = 0; i < argc; i++)
            printf("\n argv[%d]: %s", i, argv[i]);
}

/*
* exit - exits the shell
* @code_x: command entered
*
* Return: void
*/

void exit(char **code_x)
{
	int token_fornum = 0, args;

	for (; code_x[token_fornum] != NULL; token_fornum++)
		;
	if (token_fornum == 1)
	{
		free(code_x);
		free(line);
		free(commands);
		exit(status);
	}
	else if (token_fornum == 2)
	{
		args = _atoi(code_x[1]);
		if (args == -1)
		{
			print(shell_name, STDERR_FILENO);
			print(": 1: exit: Number not found: ", STDERR_FILENO);
			print(code_x[1], STDERR_FILENO);
			print("\n", STDERR_FILENO);
			status = 2;
		}
		else
		{
			free(line);
			free(code_x);
			free(commands);
			exit(args);
		}
	}
	else
		print("$: exit doesn't take more than one argument\n", STDERR_FILENO);

