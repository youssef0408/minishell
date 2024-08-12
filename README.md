# Minishell

## Description

Minishell is a project to develop a simplified Unix shell. The goal is to create a lightweight version of a shell that can handle basic commands, redirections, pipes, and environment variables. This project will help you understand the internal workings of Unix shells and work with low-level system calls in C.

## Features

- **Prompt Display**: The shell displays a prompt waiting for new commands.
- **Command History**: Functional command history management.
- **Command Execution**: Search and launch executables based on the PATH environment variable or relative/absolute paths.
- **Quoting Handling**: Manage single quotes (') and double quotes (") for interpreting metacharacters.
- **Redirections**:
  - `<` to redirect input.
  - `>` to redirect output.
  - `<<` to read input until a delimiter is encountered.
  - `>>` to append output.
- **Pipes**: Connect the output of each command in a pipeline to the input of the next command.
- **Environment Variables**: Substitute environment variables and handle `$?`.
- **Signal Handling**: Manage `ctrl-C`, `ctrl-D`, and `ctrl-\` signals.
- **Built-in Commands**:
  - `echo` with `-n` option.
  - `cd` with relative or absolute paths.
  - `pwd` without options.
  - `export` without options.
  - `unset` without options.
  - `env` without options or arguments.
  - `exit` without options.

## Installation

Clone the repository and build the project using `make`:

```bash
git clone <https://github.com/youssef0408/minishell.git>
cd minishell
make
./minishell
