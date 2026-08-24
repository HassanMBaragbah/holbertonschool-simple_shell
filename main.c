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
 * @command: full path of the command to execute
 * @prog_name: program name for error printing
 *
 * Return: 0 on success, -1 on failure
 */
int execute_cmd(char *command, char *prog_name)
{
	pid_t child_pid;
	int status;
	char *args[2];

	args[0] = command;
	args[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror(prog_name);
		return (-1);
	}

	if (child_pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
		{
			perror(prog_name);
			_exit(1);
		}
	}
	else
	{
		wait(&status);
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

		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		if (line[0] == '\0')
			continue;

		execute_cmd(line, prog_name);
	}

	free(line);
}
