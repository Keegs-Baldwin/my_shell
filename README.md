
# 🐚 Minishell Projects

This repository contains two projects: **Minishell1** and **Minishell2**, which are custom implementations of a UNIX command interpreter written in C.  
Each project builds upon the behavior of the TCSH shell.

---

## 📁 Minishell1

### 📌 Description

**Minishell1** is a basic UNIX command-line interpreter.  
It supports simple command execution without advanced features like pipes or redirections. The shell includes built-in commands and manages the environment.

### ✨ Features

- Displays a prompt (`$>`)
- Executes commands via:
  - System `PATH`
  - Direct paths (e.g., `/bin/ls`)
- Built-in commands:
  - `cd` – Change current directory
  - `setenv` – Set an environment variable
  - `unsetenv` – Remove an environment variable
  - `env` – Display all environment variables
  - `exit` – Exit the shell
- Handles errors with messages printed to standard error
- Manages `PATH` and environment variables correctly

### ▶️ How to Use

1. Compile using the provided Makefile:
   ```bash
   make
   ```
2. Run the shell:
   ```bash
   ./mysh
   ```
3. Enter commands at the `$>` prompt:
   ```bash
   $> pwd
   $> cd test
   $> pwd
   ```

### 💡 Example

```sh
$> pwd
/tmp
$> cd test
$> pwd
/tmp/test
```

---

## ⚙️ Minishell2

### 📌 Description

**Minishell2** expands on **Minishell1** with more advanced shell features, including:

- Pipes (`|`) for output/input chaining
- Redirections:
  - `>` : Redirect output (overwrite)
  - `>>`: Redirect output (append)
  - `<` : Redirect input

### 💡 Example Usage

```sh
$> ls -l; ls -l | wc -l
total 4
drwxr-xr-x 2 johan johan 4096 Mar 17 16:28 tata
-rw-r--r-- 1 johan johan    0 Mar 17 16:28 toto
3

$> mkdir test ; cd test ; ls -a ; ls | cat | wc -c > tutu ; cat tutu
. ..
5
```

---

## 🛠️ Compilation & Cleanup

Both projects use a standard `Makefile` with the following rules:

- Compile:
  ```bash
  make
  ```
- Clean object files:
  ```bash
  make clean
  ```
- Remove all generated files:
  ```bash
  make fclean
  ```
- Recompile from scratch:
  ```bash
  make re
  ```

---

## 🚨 Error Handling

Errors are handled gracefully:
- Relevant messages are printed to the error output
- On error, the shell exits with code `84`
- On success, it exits with code `0`

---

## 📝 Notes

These projects are educational exercises in UNIX system programming.  
Feel free to explore, modify, and experiment with the code!

---
