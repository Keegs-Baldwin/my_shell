/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** get_command
*/
#include "../include/my.h"

int tab_or_space(char c)
{
    return (c == ' ' || c == '\t');
}

static int find_command_bounds(const char *input, int start)
{
    int end;

    while (input[start] && tab_or_space(input[start]))
        start++;
    end = start;
    while (input[end] && !tab_or_space(input[end]))
        end++;
    return end;
}

char *get_commands(char *input)
{
    int start = 0;
    int end = 0;
    int i = 0;
    char *command;

    if (input == NULL || input[0] == '\0')
    return NULL;
    end = find_command_bounds(input, start);
    command = malloc(end - start + 1);
    if (command == NULL)
        return NULL;
    for (i = 0; start < end; i++) {
        command[i] = input[start];
        start++;
    }
    command[i] = '\0';
    return command;
}
