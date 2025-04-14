/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** mod_env
*/

#include "../includes/my.h"

static void free_env_a(env_t *env)
{
    for (int i = 0; env->env[i] != NULL; i++)
        free(env->env[i]);
    free(env->env);
}

static int free_if_dup_fail(int i, char **new_env)
{
    if (new_env[i] == NULL) {
        for (int j = 0; j < i; j++)
            free(new_env[j]);
        free(new_env);
        return 0;
    }
}

int add_new(env_t *env, char *name, char *val)
{
    char **new_env = malloc(sizeof(char *) * (get_env_len(env->env) + 2));
    int i = 0;

    if (new_env == NULL)
        return 0;
    while (env->env[i] != NULL) {
        new_env[i] = my_strdup(env->env[i]);
        if (free_if_dup_fail(i, new_env) == 0)
            return 0;
        i++;
    }
    new_env[i] = join_strs_with_x(name, val, "=");
    new_env[i + 1] = NULL;
    free_env_a(env);
    env->env = new_env;
    return 1;
}

int replace_env(int index, char *name, char *val, env_t *env)
{
    char *new_str = join_strs_with_x(name, val, "=");

    free(env->env[index]);
    env->env[index] = new_str;
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
    len = my_strlen(*val);
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

static int is_valid_var_name(const char *name)
{
    for (int i = 0; name[i] != '\0'; i++) {
        if (!((name[i] >= 'a' && name[i] <= 'z') ||
            (name[i] >= 'A' && name[i] <= 'Z') ||
            (name[i] >= '0' && name[i] <= '9') ||
            name[i] == '_')) {
            return 0;
        }
    }
    return 1;
}

int put_env(ast_t *node, env_t *env)
{
    char *name;
    char *value;
    int index;

    if (node->argv[1] == NULL)
        return disp_env(node, env);
    name = node->argv[1];
    if (node->argv[2] != NULL)
        value = node->argv[2];
    else
        value = "";
    if (is_valid_var_name(name) == 0) {
        my_puterror("setenv: Variable name must contain alphanumerics\n");
        return 0;
    }
    index = my_getenv_index(name, env->env);
    if (index == -1)
        return add_new(env, name, value);
    else
        return replace_env(index, name, value, env);
}
