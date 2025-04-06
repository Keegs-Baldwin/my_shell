/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** check_input
*/

#include "../include/my.h"

static void fill_struct(info_t *info, char **env)
{
    size_t size = 128;
    char *dir_buffer = malloc(size);

    info->env = dup_env(env);
    info->input = NULL;
    while (dir_buffer != NULL) {
        if (getcwd(dir_buffer, size) != NULL)
            break;
        size *= 2;
        free(dir_buffer);
        dir_buffer = malloc(size);
    }
    info->cur_dir = dir_buffer;
}

static void free_info(info_t *info)
{
    if (info->cur_dir != NULL)
        free(info->cur_dir);
    if (info->cur_dir != NULL)
        free(info->input);
    for (int i = 0; info->env[i] != NULL; i++) {
        free(info->env[i]);
    }
    free(info->env);
}

static void input_loop(info_t *info)
{
    size_t len = 0;
    int read;
    char *dirty_str = NULL;

    while (1) {
        write(1, "~>", 2);
        read = getline(&dirty_str, &len, stdin);
        dirty_str[read - 1] = '\0';
        info->input = clean_string(dirty_str);
        free(dirty_str);
        dirty_str = NULL;
        if (input_to_func(info) == -1)
            break;
        free(info->input);
        info->input = NULL;
    }
}

static int handle_exit(info_t *info, int exit_s)
{
    free(info->input);
    info->input = NULL;
    return exit_s;
}

static int input_loop_for_pipe(info_t *info)
{
    size_t len = 0;
    int read;
    int exit_s = 0;
    char *dirty_str = NULL;

    while (1) {
        read = getline(&dirty_str, &len, stdin);
        if (read <= 0)
            break;
        dirty_str[read - 1] = '\0';
        info->input = clean_string(dirty_str);
        free(dirty_str);
        exit_s = input_to_func(info);
        free(info->input);
        info->input = NULL;
        if (exit_s == -1)
        break;
    }
    return handle_exit(info, exit_s);
}

int check_input(char **env)
{
    size_t len = 0;
    int read;
    info_t info;
    int exit_s = 0;

    fill_struct(&info, env);
    if (isatty(0)) {
        input_loop(&info);
    } else {
        exit_s = input_loop_for_pipe(&info);
    }
    free_info(&info);
    if (exit_s == -1)
        return 0;
    return exit_s;
}

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

int input_to_func(info_t *info)
{
    char *command = get_commands(info->input);
    int stat = 0;
    command_t *commands = init_commands();

    for (int i = 0; commands[i].cmd; i++) {
        if (my_strcmp(command, commands[i].cmd) == 0) {
            commands[i].func(info);
            free(command);
            free(commands);
            return stat;
        }
    }
    if (my_strcmp(command, "exit") == 0) {
        stat = -1;
    } else {
        stat = run_other_com(command, info);
    }
    free(commands);
    free(command);
    return stat;
}
