# 🐚 Minishell Projects

This repository contains three projects: **Minishell2.2**, **Minishell2**, and **Minishell1**, which are custom implementations of a UNIX command interpreter written in C.  
Each project builds upon the behavior of the TCSH shell, introducing more features and complexity at each stage.

---

## 🧠 Minishell2.2 (AST-Based)

### 📌 Description

**Minishell2.2** is the most advanced version of the minishell series.  
It builds upon **Minishell2** by implementing command parsing with an **Abstract Syntax Tree (AST)** and includes support for both:

- Logical operators:
  - `&&` – Execute next command only if the previous one succeeds
  - `;` – Command separator
- All features from **Minishell2** (pipes, redirections)

Using an AST structure allows more accurate parsing and execution flow, closer to how real shells operate.

### 💡 Example Usage

```sh
$> mkdir test && cd test && ls -a ; echo done
. ..
done
```

---

## ⚙️ Minishell2

### 📌 Description

**Minishell2** builds on **Minishell1** with support for key shell features, including:

- Pipes (`|`) for chaining command output/input
- Redirections:
  - `>` : Redirect output (overwrite)
  - `>>`: Redirect output (append)
  - `<` : Redirect input
- Basic command separators with `;`

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

## 📁 Minishell1

### 📌 Description

**Minishell1** is a basic UNIX command-line interpreter designed as an introduction to shell development.  
It supports only simple command execution and a few built-in commands. No piping, redirection, or command chaining.

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
- Error handling via standard error messages
- Proper environment and `PATH` management

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

## 🛠️ Compilation & Cleanup

All projects use a standard `Makefile` with the following rules:

- **Compile:**
  ```bash
  make
  ```
- **Clean object files:**
  ```bash
  make clean
  ```
- **Remove all generated files:**
  ```bash
  make fclean
  ```
- **Recompile from scratch:**
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
