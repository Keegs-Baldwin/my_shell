/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell2-keigan.baldwin
** File description:
** check_inputs_helpers
*/


#include "../include/my.h"

void fill_struct(info_t *info, char **env)
{
    size_t size = 128;
    char *dir_buffer = malloc(size);

    info->is_stdin = isatty(0);
    info->env = NULL;
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

void free_info(info_t *info)
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
