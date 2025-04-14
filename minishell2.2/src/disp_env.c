/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** disp_env
*/

#include "../includes/my.h"

int disp_env(ast_t *node, env_t *env)
{
    int i = 0;

    while (env->env[i] != NULL) {
        my_putstr(env->env[i]);
        my_putstr("\n");
        i++;
    }
    return 1;
}
