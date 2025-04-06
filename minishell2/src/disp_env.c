/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** disp_env
*/

#include "../include/my.h"

int disp_env(info_t *info)
{
    int i = 0;
    char *token = strtok(info->input, " ");

    if (strtok(NULL, "\0") != NULL)
        return 0;
    while (info->env[i] != NULL) {
        my_putstr(info->env[i]);
        my_putstr("\n");
        i++;
    }
    return 1;
}
