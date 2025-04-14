/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** main
*/

#include "../includes/my.h"

int main(int argc, char **argv, char **envp)
{
    env_t env;

    env.env = dup_env(envp);
    if (env.env == NULL) {
        return 84;
    }
    shell_loop(&env);
    free_env(env.env);
    return 0;
}
