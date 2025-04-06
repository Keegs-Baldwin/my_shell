/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell2-keigan.baldwin
** File description:
** input_to_fun
*/

#include "../include/my.h"

static command_t *init_commands(void)
{
    command_t *commands = malloc(5 * sizeof(command_t));

    if (commands == NULL) {
        return NULL;
    }
    commands[0] = (command_t){"cd", run_cd};
    commands[1] = (command_t){"setenv", put_env};
    commands[2] = (command_t){"unsetenv", my_unsetenv};
    commands[3] = (command_t){"env", disp_env};
    commands[4] = (command_t){NULL, NULL};
    return commands;
}

static void free_coms(command_t *coms, char *com)
{
    free(com);
    free(coms);
}

int input_to_func(info_t *info)
{
    int stat = 0;
    char *command = get_commands(info->input);
    command_t *commands = init_commands();

    for (int i = 0; commands[i].cmd; i++) {
        if (my_strcmp(command, commands[i].cmd) == 0) {
            stat = commands[i].func(info);
            free_coms(commands, command);
            return stat;
        }
    }
    stat = run_other_com(command, info);
    free_coms(commands, command);
    return stat;
}
