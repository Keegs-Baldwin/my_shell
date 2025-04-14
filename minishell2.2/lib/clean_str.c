/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell2-keigan.baldwin
** File description:
** clean_str
*/

#include "../includes/my.h"

static int tab_or_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

static void process_char(char c, char *out, int *j, int *space)
{
    int is_space = tab_or_space(c);

    if (is_space && !(*space)){
        out[*j] = ' ';
        (*j)++;
        *space = 1;
    } else if (!is_space) {
        out[*j] = c;
        (*j)++;
        *space = 0;
    }
}

char *clean_string(char *input)
{
    clean_helper_t clean = {0};
    char *output;

    if (!input || *input == '\0' || *input == '\n')
        return NULL;
    clean.len = my_strlen(input);
    while (clean.start < clean.len && tab_or_space(input[clean.start]))
        clean.start++;
    output = malloc(clean.len + 1);
    if (!output)
        return NULL;
    for (clean.i = clean.start; clean.i < clean.len; clean.i++)
        process_char(input[clean.i], output, &clean.j, &clean.space);
    if (clean.j > 0 && output[clean.j - 1] == ' ')
        clean.j--;
    output[clean.j] = '\0';
    free(input);
    return output;
}
