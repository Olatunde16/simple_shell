#include "main.h"

/**
 * ignore - removes/ignores everything after a '#' char
 * @input: input to be used
 *
 * Return: void
 */
void ignore(char *input)
{
	int c = 0;

	if (input[c] == '#')
		input[c] = '\0';
	while (input[c] != '\0')
	{
		if (input[c] == '#' && input[c - 1] == ' ')
			break;
		c++;
	}
	input[c] = '\0';
}
