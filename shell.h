#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void run_shell(char *prog_name);
int execute_cmd(char **args, char *prog_name);

char *find_command(char *command);
char *get_path(void);
char *build_path(char *dir, char *command);
size_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);

#endif
