#include "shell.h"

/**
 * main - entry point for the simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	(void)argc;

	run_shell(argv[0]);

	return (0);
}

/**
 * execute_cmd - executes a command using fork and execve
 * @args: array of command arguments
 * @prog_name: program name for error printing
 *
 * Return: 0 on success, -1 on failure
 * I have edited the function to handel the path 
 */
int execute_cmd(char **args, char *prog_name)
{
	pid_t child_pid;
	int status;
	char *path;

	path = find_command(args[0]);

	if (path == NULL)
	{
		perror(prog_name);
		return (-1);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		perror(prog_name);

		if (path != args[0])
			free(path);

		return (-1);
	}

	if (child_pid == 0)
	{
		if (execve(path, args, environ) == -1)
		{
			perror(prog_name);
			_exit(1);
		}
	}
	else
	{
		wait(&status);

		if (path != args[0])
			free(path);
	}

	return (0);
}

/**
 * run_shell - main loop for reading and processing commands
 * @prog_name: name of the executable for error printing
 */
void run_shell(char *prog_name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char *args[1024];
	char *token;
	int i;

	while (1)
	{
		if (isatty(STDIN_FILENO) == 1)
			write(STDOUT_FILENO, "($) ", 4);

		nread = getline(&line, &len, stdin);

		if (nread == -1)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		i = 0;
		token = strtok(line, " \t\n");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \t\n");
		}
		args[i] = NULL;

		if (args[0] == NULL)
			continue;

		execute_cmd(args, prog_name);
	}

	free(line);
}
