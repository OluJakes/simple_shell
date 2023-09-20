# Simple Shell Project

## Description
The Simple Shell Project is a group project aimed at creating a basic UNIX command interpreter (shell) using the C programming language. The goal of this project is to understand the fundamentals of shell programming, including handling user input, executing commands, managing processes, and more.

## Table of Contents
- [Getting Started](#getting-started)
- [Features](#features)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Project Structure](#project-structure)
- [Contributors](#contributors)
- [License](#license)

## Getting Started
To get started with the Simple Shell Project, you need to have a basic understanding of C programming and familiarity with Unix-like systems and command-line interfaces. You'll also need a code editor (e.g., vi, vim, emacs) and a Linux environment for compilation and testing.

## Features
The Simple Shell Project aims to implement a basic shell with the following features:
- Displaying a prompt and waiting for user commands.
- Executing external commands and displaying their output.
- Handling command lines with arguments.
- Managing the PATH environment variable to locate executable files.
- Implementing built-in commands like `exit`, `env`, `cd`, `setenv`, `unsetenv`, `alias`, etc.
- Handling logical operators `&&` and `||`.
- Handling variables replacement like `$$` and `$?`.
- Implementing comments using `#`.
- Reading commands from a file.

## Usage
To use the Simple Shell, follow these steps:
1. Clone or download the project repository.
2. Navigate to the project directory.
3. Compile the shell using the provided compilation command.
4. Run the shell using `./hsh`.

## Built-in Commands
The shell supports the following built-in commands:
- `exit`: Exit the shell.
- `env`: Print the current environment.
- `cd [DIRECTORY]`: Change the current directory.
- `setenv VARIABLE VALUE`: Initialize or modify an environment variable.
- `unsetenv VARIABLE`: Remove an environment variable.
- `alias [name[='value'] ...]`: Print or define aliases.
- `$$`: Display the shell's process ID.
- `$?`: Display the exit status of the last executed command.
- `#`: Use comments to ignore lines in scripts.

## Project Structure
The project repository is structured as follows:
- `shell.c`: The main shell program.
- `exec.c`: Contains functions for executing external commands.
- `builtins.c`: Implements the various built-in commands.
- `helpers.c`: Contains helper functions for string manipulation, parsing, etc.
- Other source files and headers for additional functionalities.

## Contributors
- [Olumide Solanke](https://github.com/OluJakes)


## License
Copyright © 2023 ALX, All rights reserved

Feel free to contribute, suggest improvements, or report issues!

