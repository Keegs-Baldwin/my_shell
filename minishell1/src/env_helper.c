/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** env_helper
*/

#include "../include/my.h"

int my_getenv_index(char *name, char **env)
{
    int i = 0;

    while (env[i] != NULL) {
        if (my_strncmp(env[i], name, my_strlen(name)) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}

int get_env_len(char **env)
{
    int len = 0;

    while (env[len] != NULL) {
        len++;
    }
    return len;
}

void free_env(char **env)
{
    int i = 0;

    if (env == NULL)
        return;
    while (env[i] != NULL) {
        free(env[i]);
        i++;
    }
    free(env);
}
