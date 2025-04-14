/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** execute_builtin
*/

#include "../includes/my.h"

int is_builtin(const char *cmd)
{
    const char *builtins[] = {"cd", "setenv", "unsetenv", "env", "exit", NULL};
    int i = 0;

    while (builtins[i] != NULL) {
        if (my_strcmp(cmd, builtins[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

static command_t *init_commands(void)
{
    command_t *commands = malloc(6 * sizeof(command_t));

    if (commands == NULL) {
        return NULL;
    }
    commands[0] = (command_t){"cd", run_cd};
    commands[1] = (command_t){"setenv", put_env};
    commands[2] = (command_t){"unsetenv", my_unsetenv};
    commands[3] = (command_t){"env", disp_env};
    commands[4] = (command_t){"exit", run_exit};
    commands[5] = (command_t){NULL, NULL};
    return commands;
}

int execute_builtin(ast_t *node, env_t *env)
{
    command_t *commands = init_commands();
    int stat = 0;

    if (commands == NULL) {
        return 0;
    }
    for (int i = 0; commands[i].cmd; i++) {
        if (my_strcmp(node->argv[0], commands[i].cmd) == 0) {
            stat = commands[i].func(node, env);
            free(commands);
            return stat;
        }
    }
    free(commands);
    return stat;
}

static int is_valid_number(const char *str)
{
    for (int i = 0; str[i]; i++)
        if (str[i] < '0' || str[i] > '9')
            return 0;
    return 1;
}

int run_exit(ast_t *node, env_t *env)
{
    int exit_code = 0;

    if (node->argv[1]) {
        if (!is_valid_number(node->argv[1])) {
            my_puterror("exit: Expression Syntax\n");
            return 1;
        }
        exit_code = atoi(node->argv[1]);
    }
    free_env(env->env);
    exit(exit_code);
}
