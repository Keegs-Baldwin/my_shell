/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell2-keigan.baldwin
** File description:
** command execution and builtin handling
*/

#include "../include/my.h"


static command_t *init_commands(void)
{
    command_t *commands = malloc(5 * sizeof(command_t));

    if (commands == NULL) {
        return NULL;
    }
    commands[0] = (command_t){"cd", run_cd};
    commands[1] = (command_t){"setenv", put_env};
    commands[2] = (command_t){"unsetenv", my_unsetenv};
    commands[3] = (command_t){"env", disp_env};
    commands[4] = (command_t){NULL, NULL};
    return commands;
}

static int handle_parent_process(pid_t child_pid, char *path, int input_fd)
{
    int status;

    waitpid(child_pid, &status, 0);
    free(path);
    close(input_fd);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

static void redirect_io(int input_fd, int output_fd)
{
    if (input_fd != STDIN_FILENO) {
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);
    }
    if (output_fd != STDOUT_FILENO) {
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);
    }
}

int run_child_process(char **args, char *path, info_t *info, int input_fd)
{
    redirect_io(input_fd, STDOUT_FILENO);
    process_redirections(args);
    execve(path, args, info->env);
    perror("execve");
}

static void execute_c_process(char **args, char *path, info_t *info, int in_fd)
{
    run_child_process(args, path, info, in_fd);
}

int run_external_command(char **args, info_t *info, int input_fd)
{
    char *executable_path = validate_executable(args, info);
    pid_t child_pid;

    if (!executable_path)
        return 1;
    child_pid = fork();
    if (child_pid == -1)
        return perror("fork"), 1;
    if (child_pid == 0)
        execute_c_process(args, executable_path, info, input_fd);
    return handle_parent_process(child_pid, executable_path, input_fd);
}

static int find_and_run_builtin(char **args, info_t *info, command_t *commands)
{
    int i = 0;

    for (i = 0; commands[i].cmd; i++) {
        if (my_strcmp(args[0], commands[i].cmd) == 0)
            return commands[i].func(info);
    }
    return -1;
}

int check_builtin_command(char **args, info_t *info, command_t *commands)
{
    return find_and_run_builtin(args, info, commands);
}

int execute_single_command(char **args, info_t *info, command_t *com, int in_f)
{
    int builtin_result = check_builtin_command(args, info, com);

    if (builtin_result != -1)
        return builtin_result;
    return run_external_command(args, info, in_f);
}

int process_input(info_t *info)
{
    char **piped_commands = NULL;
    command_t *builtins = NULL;
    int status = 0;

    builtins = init_commands();
    piped_commands = my_str_to_word_array(info->input, "|");
    status = execute_piped_commands(piped_commands, info, builtins);
    free(builtins);
    for (int i = 0; piped_commands[i] != NULL; i++)
        free(piped_commands[i]);
    free(piped_commands);
    free(info->input);
    info->input = NULL;
    return status;
}
