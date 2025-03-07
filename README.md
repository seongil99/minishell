# Minishell

A simplified shell implementation based on bash, developed as part of the 42 curriculum.

## Overview

Minishell is a simple command-line interpreter that replicates the basic functionality of bash. It includes features such as command execution, built-in commands, environment variable management, redirection, pipes, and signal handling.

## Features

- **Command parsing and execution**: Executes commands with arguments
- **Built-in commands**:
  - `cd`: Change directory
  - `pwd`: Print working directory
  - `echo`: Display text
  - `env`: Display environment variables
  - `export`: Set environment variables
  - `unset`: Remove environment variables
  - `exit`: Exit the shell
- **Input/Output redirection**:
  - `>`: Output redirection (overwrite)
  - `>>`: Output redirection (append)
  - `<`: Input redirection
  - `<<`: Heredoc
- **Pipes**: Execute commands in a pipeline
- **Environment variable expansion**: `$VAR` expands to the value of VAR
- **Exit status access**: `$?` expands to the exit status of the last command
- **Signal handling**: Handles Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT)
- **Quotes**: Handles single and double quotes
- **Subshells**: Executes commands in subshells with `()`
- **Logic operators**:
  - `&&`: AND operator (execute second command only if first succeeds)
  - `||`: OR operator (execute second command only if first fails)
- **Tilde expansion**: `~` expands to home directory path
- **Pathname expansion (bonus)**: Wildcard `*` support

## Implementation Details

### Parser

The shell uses a LALR (Look-Ahead LR) parser to parse command-line input. The parsing phase converts the raw input string into a token list, which is then analyzed according to a formal grammar that defines the shell syntax.

### Command Execution

Commands are executed in a forked process, while built-in commands are executed in the main process. Pipes and redirections are implemented using file descriptors and process management.

### Signal Handling

The shell handles signals such as SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) differently based on the context (interactive mode vs command execution mode).

### Memory Management

The project uses custom memory allocation wrappers and data structures to ensure clean memory management and prevent leaks.

## Getting Started

### Prerequisites

- GCC compiler
- GNU Make
- Readline library (`libreadline-dev` on Debian/Ubuntu)

### Building

Clone the repository and build using make:

```bash
git clone https://github.com/seongil99/minishell.git
cd minishell
make
```

### Running

Execute the shell:

```bash
./minishell
```

## Code Structure

- **builtins/**: Built-in command implementations
- **cmds/**: Command execution and management
- **environments/**: Environment variable handling
- **expansions/**: Variable, tilde, and pathname expansion
- **libft/**: Custom C library functions
- **operators/**: Redirection, pipe, and logical operator handlers
- **parsing/**: Lexer and parser implementation
- **termi_signal/**: Terminal and signal handling
- **utils/**: Utility functions and data structures
- **main.c**: Main entry point and shell loop

## License

This project is developed as part of the 42 curriculum.

## Authors

- seonyoon (seonyoon@student.42seoul.kr)
- sihkang (sihkang@student.42seoul.kr)
