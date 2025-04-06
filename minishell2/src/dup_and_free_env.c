/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** dup_&_free_env
*/

#include "../include/my.h"

static void free_if_fails(char **env, int count)
{
    if (env == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(env[i]);
    }
}

char **dup_env(char **envp)
{
    int count = 0;
    char **new_env;

    while (envp[count] != NULL)
        count++;
    new_env = malloc((count + 1) * sizeof(char *));
    if (new_env == NULL) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        new_env[i] = my_strdup(envp[i]);
        if (new_env[i] == NULL) {
            free_if_fails(envp, i);
            free(new_env);
            return NULL;
        }
    }
    new_env[count] = NULL;
    return new_env;
}
