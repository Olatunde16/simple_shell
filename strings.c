#include "main.h"

/**
 *print - prints a str to stdout
 *@str: str to be printed
 *@d: destination to print out to
 *
 *Return: void, return nothing
 */
void print(char *str, int d)
{
	int c = 0;

	for (; str[c] != '\0'; c++)
		write(d, &str[c], 1);
}

/**
 *rm_addedline - removes new line from a str
 *@str: str to be used
 *
 *
 *Return: void
 */

void rm_addedline(char *str)
{
	int c = 0;

	while (str[c] != '\0')
	{
		if (str[c] == '\n')
			break;
		c++;
	}
	str[c] = '\0';
}

/**
 *_strcpy - copies a str to another buffer
 *@here: source to copy from
 *@there: destination to copy to
 *
 * Return: void
 */

void _strcpy(char *here, char *there)
{
	int c = 0;

	for (; here[c] != '\0'; c++)
		there[c] = here[c];
	there[c] = '\0';
}

/**
 *_strlen - counts str length
 *@str: str to be counted
 *
 * Return: length of the str
 */

int _strlen(char *str)
{
	int len = 0;

	if (str == NULL)
		return (len);
	for (; str[len] != '\0'; len++)
		;
	return (len);
}
