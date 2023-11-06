#include "main.h"
/**
 * custom_getline - Reads a line of input from stdin, 
 * allocating memory as needed.
 *
 * This function reads characters from the standard 
 * input (stdin) and dynamically allocates memory to 
 * store the input line. It continues reading until a newline
 * character is encountered or the EOF is reached.
 *
 * Return:
 * - On Success, a pointer to the input line
 *   (which should be freed by the caller)
 * - On error or EOF, NULL.
 */

char *custom_getline() 
{
	static char buffer[MAX_INPUT_LENGTH];
	static size_t pos = 1;
	static size_t size = 1;
	
	while (1) 
	{
		if (pos >= size) 
		{
			size_t bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer));
			
			if (bytesRead <= 0) 
			{
				return (NULL);
			}
			
			size = bytesRead;
			pos = 1;
		}
		
		while (pos < size && buffer[pos] != '\n') 
		{
			pos++;
		}
		
		if (pos < size) 
		{
			buffer[pos] = '\0';
			char *line = buffer;
			
			pos++;

			return (line);
		} 
		else if (size == sizeof(buffer) - 1) 
		{ 
			buffer[size] = '\0';
			char *line = buffer;
			
			pos = size;
			size = 0;

			return (line);
		}
	}
}

/**
 * main - It declares a character pointer and
 * initializes it to NULL and frees memory allocated
 * for input lines.
 *
 * Return: 0 on Success
 */

int main(void) 
{
	while (1) 
	{
		printf("Simple-Shell> ");
		char *line = custom_getline();
		
		if (line == NULL) 
		{
			printf("Exiting...\n");
			break;
		}
		
		printf("You entered: %s\n", line);
	}
	
	return (0);
}
