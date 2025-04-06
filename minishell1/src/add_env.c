/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** mod_env
*/

#include "../include/my.h"

int add_new(info_t *info, char *name, char *val)
{
    char **new_env = malloc(sizeof(char *) * (get_env_len(info->env) + 2));
    int i = 0;

    if (new_env == NULL)
        return 0;
    while (info->env[i] != NULL) {
        new_env[i] = my_strdup(info->env[i]);
        i++;
    }
    new_env[i] = join_strs_with_x(name, val, "=");
    new_env[i + 1] = NULL;
    for (i = 0; info->env[i] != NULL; i++) {
        free(info->env[i]);
    }
    free(info->env);
    info->env = new_env;
}

int replace_env(int index, char *name, char *val, info_t *info)
{
    char *new_str = join_strs_with_x(name, val, "=");

    info->env[index] = new_str;
    return 1;
}

static int check_for_quotations(char **val)
{
    int len;
    int good_args = 0;

    if (val == NULL || *val == NULL || **val == '\0')
        return 0;
    if (**val == '"') {
        (*val)++;
        good_args++;
    }
    len = strlen(*val);
    if ((*val)[len - 1] == '"') {
        (*val)[len - 1] = '\0';
        good_args++;
    }
    if (good_args == 2) {
        return 1;
    } else {
        return 0;
    }
}

int get_name_and_val(char **name, char **val, char *input)
{
    char *token = strtok(input, " ");
    int good_args = 0;

    *name = strtok(NULL, " ");
    if (name == NULL)
        return 0;
    *val = strtok(NULL, "\0");
    if (val == NULL || *val == NULL) {
        *val = "";
        return 1;
    } else {
        return check_for_quotations(val);
    }
}

void put_env(info_t *info)
{
    int index;
    char *name;
    char *value;

    if (get_name_and_val(&name, &value, info->input) == 0) {
        write(2, "bad args\n", 9);
        return;
    }
    index = my_getenv_index(name, info->env);
    if (index == -1) {
        add_new(info, name, value);
    } else {
        replace_env(index, name, value, info);
    }
}
