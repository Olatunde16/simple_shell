#include "main.h"

/**
 *_strcmp - compare two strings
 *@a: first string to be compared
 *@b: second string to be compared
 *
 * Return: difference of the two strings
 */

int _strcmp(char *a, char *b)
{
	int c = 0;

	while (a[c] != '\0')
	{
		if (a[c] != b[c])
			break;
		c++;
	}
	return (a[c] - b[c]);
}

/**
 *_strcat - concatenates two strings
 *@d: string to be concatenated to
 *@s:  string to concatenate
 *
 * Return: address of the new string
 */

char *_strcat(char *d, char *s)
{
	char *new_string =  NULL;
	int len_dest = _strlen(d);
	int len_source = _strlen(s);

	new_string = malloc(sizeof(*new_string) * (len_dest + len_source + 1));
	_strcpy(d, new_string);
	_strcpy(s, new_string + len_dest);
	new_string[len_dest + len_source] = '\0';

	return (new_string);
}

/**
 *_strspn - gets the length of a prefix substring
 *@str1: string to be searched
 *@str2: string to be used
 *
 *Return: number of bytes in the initial segment of 5 which are part of accept
 */

int _strspn(char *str1, char *str2)
{
	int c = 0;
	int fixn = 0;

	while (str1[c] != '\0')
	{
		if (_strchr(str2, str1[c]) == NULL)
			break;
		fixn++;
		c++;
	}
	return (fixn);
}

/**
 *_strcspn - computes segment of str1 which consists of characters not in str2
 *@str1: string to be searched
 *@str2: string to be used
 *
 *Return: index at which a char in str1 exists in str2
 */


int _strcspn(char *str1, char *str2)
{
	int len = 0, c;

	for (c = 0; str1[c] != '\0'; c++)
	{
		if (_strchr(str2, str1[c]) != NULL)
			break;
		len++;
	}
	return (len);
}

/**
 *_strchr - finds/locates a char in a string
 *@str: string to be searched
 *@c: char to be checked
 *
 *Return: pointer to the first occurence of c in str
 */

char *_strchr(char *str, char c)
{
	int c;

	for (c = 0; str[c] != c && str[c] != '\0'; c++)
		;
	if (str[c] == c)
		return (str + c);
	else
		return (NULL);
}
