/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** clean_str
*/

#include "../include/my.h"

static int tab_or_space(char c)
{
    return (c == ' ' || c == '\t');
}

static void process_char(char c, char *out, int *j, int *space)
{
    int is_space;

    is_space = tab_or_space(c);
    if (is_space && !(*space)) {
        out[*j] = ' ';
        (*j)++;
        *space = 1;
    } else if (!is_space) {
        out[*j] = c;
        (*j)++;
        *space = 0;
    }
}

char *clean_string(const char *input)
{
    char *output;
    int i;
    int j = 0;
    int space = 0;
    int len;

    if (!input)
        return NULL;
    len = my_strlen(input);
    output = malloc(len + 1);
    if (!output)
        return NULL;
    for (i = 0; i < len; i++)
        process_char(input[i], output, &j, &space);
    if (j > 0 && output[j - 1] == ' ')
        j--;
    output[j] = '\0';
    return output;
}
