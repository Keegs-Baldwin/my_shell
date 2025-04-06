/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell2-keigan.baldwin
** File description:
** input redirections, pipe handling and process tracking
*/

#include "../include/my.h"

static void safe_re(char *file, int flags, int fd)
{
    int new_fd = 0;

    new_fd = open(file, flags, 0644);
    if (new_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    dup2(new_fd, fd);
    close(new_fd);
}

void process_redirections(char **args)
{
    int i = 0;

    for (i = 0; args[i]; i++) {
        if (args[i + 1] == NULL) {
            break;
        }
        if (my_strcmp(args[i], "<") == 0) {
            safe_re(args[i + 1], O_RDONLY, STDIN_FILENO);
            i++;
        }
        if (my_strcmp(args[i], ">") == 0) {
            safe_re(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
            i++;
        }
        if (my_strcmp(args[i], ">>") == 0) {
            safe_re(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
            i++;
        }
    }
}

static int track_child_process(pid_t pid)
{
    int wstatus = 0;
    int exit_status = 0;
    pid_t w = 0;

    do {
        w = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(wstatus)) {
            exit_status = WEXITSTATUS(wstatus);
        }
        if (WIFSIGNALED(wstatus)) {
            my_putstr("Terminated by signal\n");
        }
    } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    return exit_status;
}

static int create_pipe_and_fork(int *pipe_fds)
{
    if (pipe(pipe_fds) == -1) {
        perror("pipe");
        return -1;
    }
    return 0;
}

char *validate_executable(char **args, info_t *info)
{
    char *executable_path = find_exc(args[0], info->env);

    if (executable_path == NULL) {
        my_putstr(args[0]);
        my_putstr(": Command not found.\n");
    }
    return executable_path;
}

void run_child_p(char **args, info_t *info, int prev_fd, int pipe_fds[2])
{
    if (prev_fd != STDIN_FILENO) {
        dup2(prev_fd, STDIN_FILENO);
        close(prev_fd);
    }
    dup2(pipe_fds[1], STDOUT_FILENO);
    close(pipe_fds[0]);
    process_redirections(args);
    execve(validate_executable(args, info), args, info->env);
    perror("execve");
}

int execute_pipe_command(char **com, info_t *info, command_t *b, int *prev_fd)
{
    int pipe_fds[2] = {0};
    char **args = NULL;
    int status = 0;
    pid_t child_pid;

    args = my_str_to_word_array(com[0], " ");
    if (com[1] != NULL) {
        if (create_pipe_and_fork(pipe_fds) == -1)
            return 1;
        child_pid = fork();
        if (child_pid == 0)
            run_child_p(args, info, *prev_fd, pipe_fds);
        close(pipe_fds[1]);
        *prev_fd = pipe_fds[0];
        status = track_child_process(child_pid);
    } else {
        status = execute_single_command(args, info, b, *prev_fd);
    }
    free(args);
    return status;
}

int execute_piped_commands(char **commands, info_t *info, command_t *builtins)
{
    int prev_fd = STDIN_FILENO;
    int status = 0;
    int i = 0;

    while (commands[i] != NULL) {
        status = execute_pipe_command(&commands[i], info, builtins, &prev_fd);
        i++;
    }
    return status;
}
