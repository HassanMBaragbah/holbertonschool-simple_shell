#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

/* Core Functions */
void run_shell(char *prog_name);
int execute_cmd(char *command, char *prog_name);

#endif /* SHELL_H */
