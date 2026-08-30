# Simple Shell - holbertonschool-simple_shell

## Description
This project is a custom UNIX command-line interpreter (shell) written in C as part of the Software Engineering curriculum at Holberton School. It implements the core behavior of a basic UNIX shell /bin/sh, including reading command-line inputs, parsing arguments, searching execution paths using PATH, handling processes (fork, execve, wait), and running built-in shell commands.

## Features
* Displays an interactive prompt (($) ) when attached to a terminal.
* Handles both interactive and non-interactive execution modes.
* Resolves executable paths using the PATH environment variable.
* Passes command-line arguments to executed programs.
* Handles End-Of-File (Ctrl+D) gracefully.
* Implements built-in commands:
  * exit: Exits the shell with the status of the last executed command.
  * env: Prints the current environment variables.
* Formats error outputs to match /bin/sh standards using argv[0].

## Requirements
* OS: Ubuntu 20.04 LTS
* Compiler: gcc using flags -Wall -Werror -Wextra -pedantic -std=gnu89
* Style: Code follows the Betty coding style standard.
* Memory: Clean memory management without leaks.

## Compilation
All files are compiled using the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode
Launch the shell executable directly:
```bash
$ ./hsh
($) /bin/ls
main.c path.c shell.h hsh
($) ls -l /tmp
total 0
($) env
USER=ubuntu
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
($) exit
$
```

### Non-Interactive Mode
Pipe commands into the shell via standard input:
```bash
$ echo "/bin/ls" | ./hsh
main.c path.c shell.h hsh

$ echo "ls -l" | ./hsh
total 24
-rw-r--r-- 1 ubuntu ubuntu 1200 Aug 26 23:00 main.c
-rw-r--r-- 1 ubuntu ubuntu 2100 Aug 26 23:00 path.c
-rw-r--r-- 1 ubuntu ubuntu  450 Aug 26 23:00 shell.h
-rwxr-xr-x 1 ubuntu ubuntu 8900 Aug 26 23:00 hsh
```

## Project Files
* main.c - Entry point, shell main loop, command execution, and built-in functions.
* path.c - Utility functions for string manipulation and PATH resolution algorithms.
* shell.h - Header file containing function prototypes, structure declarations, and include guards.
* man_1_simple_shell - Manual page for the custom shell executable.
* AUTHORS - List of project contributors.

## Authors
* Hassan Baragbah
* Shatha Alghamdi