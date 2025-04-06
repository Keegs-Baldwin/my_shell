```markdown
# Minishell Projects

This repository contains two projects: **Minishell1** and **Minishell2**, which are custom implementations of a UNIX-like shell written in C. Each project builds upon the previous one, with Minishell2 introducing additional features. Below is an explanation of what each shell can do, how to use them, and their limitations.

---

## Minishell1

### Description
Minishell1 is a basic UNIX command interpreter based on TCSH. It supports simple command execution without advanced features like pipes or redirections. The shell includes built-in commands and correctly handles environment variables.

### Features
- Displays a prompt (`$>`).
- Executes basic commands found in the system's `PATH` or via direct paths (e.g., `/bin/ls`).
- Built-in commands:
  - `cd`: Change the current directory.
  - `setenv`: Set an environment variable.
  - `unsetenv`: Remove an environment variable.
  - `env`: Display all environment variables.
  - `exit`: Exit the shell.
- Handles errors gracefully by displaying appropriate error messages and returning error codes.
- Restores the initial environment after execution.

### How to Use
1. Compile the program using the provided Makefile:
   ```
   make
   ```
2. Run the shell:
   ```
   ./mysh
   ```
3. Enter commands at the `$>` prompt. For example:
   ```
   $> pwd
   $> cd /tmp
   $> ls -l
   ```

### Examples
```
$> pwd
/tmp
$> cd test
$> pwd
/tmp/test
```

---

## Minishell2

### Description
Minishell2 builds on Minishell1 by introducing support for semicolons (`;`) and pipes (`|`). However, it does not support input (`>`, ``).

### Features
- All features from Minishell1.
- Support for semicolon-separated commands (e.g., `command1; command2`).
- Basic pipe functionality (`|`) for inter-process communication.
- Error handling with exit codes (`84` for errors, `0` for success).

### How to Use
1. Compile the program using the provided Makefile:
   ```
   make
   ```
2. Run the shell:
   ```
   ./mysh
   ```
3. Enter commands at the `$>` prompt, including semicolons or pipes where needed. For example:
   ```
   $> ls -l; pwd
   $> ls | wc -l
   ```

### Examples
```
$> ls -l; ls | wc -l
total 4
drwxr-xr-x 2 user user 4096 Mar 17 16:28 folder1
-rw-r--r-- 1 user user    0 Mar 17 16:28 file.txt
3

$> mkdir test; cd test; ls | wc -c > output.txt; cat output.txt
5
```

---

## Compilation and Cleanup

Both Minishell projects include a Makefile with standard rules:
- Compile: `make`
- Clean object files: `make clean`
- Remove all generated files: `make fclean`
- Recompile from scratch: `make re`

---

## Limitations

### Minishell1:
- Does not support advanced features like pipes, redirections, or background processes.

### Minishell2:
- Does not implement input (``, `>>`).

---

## Error Handling

Both shells handle errors by displaying appropriate messages on standard error and exiting with specific error codes:
- Success: Exit code `0`.
- Errors: Exit code `84`.

---

## Notes

These projects are designed as educational exercises in UNIX system programming and are not intended for production use. Feel free to explore and modify the code to add new features!
```
