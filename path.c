#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: string
 *
 * Return: length of string
 */
size_t _strlen(const char *str)
{
	size_t len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}

/**
 * _strncmp - compares two strings up to n bytes
 * @s1: first string
 * @s2: second string
 * @n: number of bytes
 *
 * Return: 0 if equal, otherwise difference
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);

		if (s1[i] == '\0')
			return (0);
	}

	return (0);
}

/**
 * get_path - gets PATH from environment
 *
 * Return: pointer to PATH value, or NULL
 */
char *get_path(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], "PATH=", 5) == 0)
			return (environ[i] + 5);
	}

	return (NULL);
}

/**
 * build_path - builds a full command path
 * @dir: directory
 * @command: command
 *
 * Return: allocated full path, or NULL
 */
char *build_path(char *dir, char *command)
{
	size_t dir_len;
	size_t cmd_len;
	size_t i;
	size_t j;
	char *full_path;

	dir_len = _strlen(dir);
	cmd_len = _strlen(command);

	full_path = malloc(dir_len + cmd_len + 2);

	if (full_path == NULL)
		return (NULL);

	for (i = 0; i < dir_len; i++)
		full_path[i] = dir[i];

	full_path[i++] = '/';

	for (j = 0; j < cmd_len; j++)
		full_path[i++] = command[j];

	full_path[i] = '\0';

	return (full_path);
}

/**
 * find_command - finds a command using PATH
 * @command: command to search for
 *
 * Return: full path if found, otherwise NULL
 */
char *find_command(char *command)
{
	char *path;
	char *path_copy;
	char *dir;
	char *full_path;
	size_t path_len;
	size_t i;

	if (command == NULL)
		return (NULL);

	/*
	 * If command is already something like:
	 * /bin/ls
	 * check it directly.
	 */
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
			return (command);

		return (NULL);
	}

	path = get_path();

	if (path == NULL || _strlen(path) == 0)
	return (NULL);

	path_len = _strlen(path);

	path_copy = malloc(path_len + 1);

	if (path_copy == NULL)
		return (NULL);

	for (i = 0; i <= path_len; i++)
		path_copy[i] = path[i];

	dir = strtok(path_copy, ":");

    
	while (dir != NULL)
	{
		full_path = build_path(dir, command);

		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);

		dir = strtok(NULL, ":");
	}

	free(path_copy);

	return (NULL);
}
