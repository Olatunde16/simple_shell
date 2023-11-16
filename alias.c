#include "main.h"

/**
 * main - Checks if user entered "alias" command
 * print_aliases: Prints all aliases.
 *
 * Return: NULL
 */

void print_aliases(void) 
{
	for (int i = 0; i < num_aliases; i++)
		printf("%s='%s'\n", aliases[i].name, aliases[i].value);
}

/**
 * print_alias: Prints a specific alias by name.
 * name: The name of the alias to be printed
 * Return: NULL
 */

void print_alias(char *name) 
{
	for (int i = 0; i < num_aliases; i++) 
	{
		if (strcmp(aliases[i].name, name) == 0) 
		{
			printf("%s='%s'\n", aliases[i].name, aliases[i].value);
			return;
		}
	}
	
	printf("Alias '%s' not found.\n", name);
}

/**
 * add_alias - Adds a new alias to the array of defined aliases.
 * name: The name of the new alias
 * value: The value of the new alias.
 * Return: NULL
 */

void add_alias(char *name, char *value) 
{
	if (alias_count < MAX_ALIAS_COUNT) 
	{
		strcpy(alias_list[alias_count].name, name);
		strcpy(alias_list[alias_count].value, value);
		alias_count++;
	}
	
	else 
		printf("Alias limit reached. Cannot add more aliases.\n");
}

/**
 * define_alias: Defines or redefines an alias with a given name and value.
 * name: The name of the alias.
 * value: The value of the alias.
 *
 * Return: NULL
 */

void define_alias(char *name, char *value) 
{
	for (int i = 0; i < num_aliases; i++) 
	{
		if (strcmp(aliases[i].name, name) == 0) 
		{
			strcpy(aliases[i].value, value);
			return;
		}
	}
	
	if (num_aliases < MAX_ALIASES) 
	{
		strcpy(aliases[num_aliases].name, name);
		strcpy(aliases[num_aliases].value, value);
		num_aliases++;
	} 
	
	else
		printf("Maximum number of aliases reached.\n");
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
		printf("SimpleShell (PID: %d)> ", getpid());
		
		fgets(input, MAX_INPUT_LENGTH, stdin);
		
		input[strlen(input) - 1] = '\0';
		
		if (strcmp(input, "exit") == 0) 
			break;
		
		else if (strcmp(input, "alias") == 0)
			print_aliases();
		
		else if (strstr(input, "alias ") == input) 
		{
			char *alias_name = input + strlen("alias ");
			print_alias(alias_name);
		} 
		
		else if (strstr(input, "alias ") != NULL && strstr(input, "='") != NULL) 
		{
			char *alias_def = input + strlen("alias ");
			char *name = strtok(alias_def, "='");
			char *value = strtok(NULL, "'");
			define_alias(name, value);
		} 
		
		else 
		{
			char *token = strtok(input, " ");
			num_args = 0;
			
			while (token != NULL) 
			{
				args[num_args++] = token;
				token = strtok(NULL, " ");
			}
			
			args[num_args] = NULL;
			
			int result = execute_command(args);
			
			if (result == 0 && strstr(input, "&&") != NULL) 
			{
				token = strtok(input, "&&");
				token = strtok(NULL, "&&");
				
				if (token != NULL) 
				{
					num_args = 0;
					token = strtok(token, " ");
                    while (token != NULL) {
                        args[num_args++] = token;
                        token = strtok(NULL, " ");
                    }
                    args[num_args] = NULL;
                    result = execute_command(args);
                }
            } else if (result != 0 && strstr(input, "||") != NULL) {
                token = strtok(input, "||");
                token = strtok(NULL, "||");
                if (token != NULL) {
                    num_args = 0;
                    token = strtok(token, " ");
                    while (token != NULL) {
                        args[num_args++] = token;
                        token = strtok(NULL, " ");
                    }
                    args[num_args] = NULL;
                    result = execute_command(args);
                }
            }
        }
    }

    return (0);
}
