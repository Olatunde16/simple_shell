#include <stdio.h>

/**
 * _env - prints the environment
 *
 * Return: Always 0.
 */
int _env(int ac, char **av, char **env)
{
    unsigned int c;

    c = 0;
    while (env[c] != NULL)
    {
        printf("%s\n", env[c]);
        c++;
    }
    return (0);
}

/**
 * _getenv - finds PATH member from environ
 * @name: pointer to PATH string
 *
 * Return: pointer to PATH member string or NULL if not found
 */
char *_getenv(const char *filename)
{
	int c, result;

	for (c = 0; environ[c]; c++)
	{
		result = _PATHstrcmp(filename, environ[i]);
		if (result == 0)
		{
			return (environ[c]);
		}
	}
	return (NULL);
}/**
 * _getenv - finds PATH member from environ
 * @name: pointer to PATH string
 *
 * Return: pointer to PATH member string or NULL if not found
 */
char *_getenv(const char *filename)
{
	int c, result;

	for (c = 0; environ[c]; c++)
	{
		result = _PATHstrcmp(filename, environ[i]);
		if (result == 0)
		{
			return (environ[c]);
		}
	}
	return (NULL);
}/**
 * _getenv - finds PATH member from environ
 * @name: pointer to PATH string
 *
 * Return: pointer to PATH member string or NULL if not found
 */
char *_getenv(const char *filename)
{
	int c, result;

	for (c = 0; environ[c]; c++)
	{
		result = _PATHstrcmp(filename, environ[c]);
		if (result == 0)
		{
			return (environ[c]);
		}
	}
	return (NULL);
}

