/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** unsetenv
*/


#include "../include/my.h"

static void remove_env_help(char **new_env, info_t *info, int *i, int index)
{
    int j = 0;

    while (info->env[j] != NULL) {
        if (j == index && info->env[j + 1] == NULL)
            break;
        if (j == index)
            j++;
        new_env[*i] = my_strdup(info->env[j]);
        (*i)++;
        j++;
    }
}

static int remove_env(int index, info_t *info)
{
    int env_len = get_env_len(info->env);
    char **new_env = malloc(sizeof(char *) * (env_len));
    int i = 0;

    if (new_env == NULL)
        return 0;
    remove_env_help(new_env, info, &i, index);
    new_env[i] = NULL;
    for (i = 0; info->env[i] != NULL; i++) {
        free(info->env[i]);
    }
    free(info->env);
    info->env = new_env;
    return 1;
}

int my_unsetenv(info_t *info)
{
    char *name;
    char *val;
    int index;

    if (get_name_and_val(&name, &val, info->input) == 0)
        return 0;
    index = my_getenv_index(name, info->env);
    if (index == -1) {
        my_puterror("could not find env NAME\n");
    } else {
        remove_env(index, info);
    }
    return 1;
}
