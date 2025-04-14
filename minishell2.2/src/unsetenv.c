/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** unsetenv
*/

#include "../includes/my.h"

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

static void remove_env_var(char **env, int index)
{
    free(env[index]);
    while (env[index + 1] != NULL) {
        env[index] = env[index + 1];
        index++;
    }
    env[index] = NULL;
}

static int process_single_var(const char *var_name, env_t *env)
{
    int index;
    char *v_name;

    if (!is_valid_var_name(var_name)) {
        my_puterror("unsetenv: Variable name must contain");
        my_puterror(" alphanumeric characters or underscore\n");
        return 0;
    }
    v_name = my_strdup(var_name);
    index = my_getenv_index(v_name, env->env);
    free(v_name);
    if (index != -1) {
        remove_env_var(env->env, index);
        return 1;
    }
    return 0;
}

int my_unsetenv(ast_t *node, env_t *env)
{
    int i = 1;
    int result = 0;

    if (node->argv[1] == NULL) {
        my_puterror("unsetenv: Too few arguments\n");
        return 1;
    }
    while (node->argv[i] != NULL) {
        result |= process_single_var(node->argv[i], env);
        i++;
    }
    return result;
}
