/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** tokenizer
*/

#include "../includes/my.h"

void skip_spaces(const char *input, int *pos)
{
    while (input[*pos] == ' ' || input[*pos] == '\t') {
        (*pos)++;
    }
}

int is_delimiter(char c)
{
    return c == ' ' || c == '\t' || c == '<' || c == '>' ||
    c == '|' || c == '&' || c == ';';
}

void free_tokens(token_t *tokens)
{
    token_t *next;

    while (tokens != NULL) {
        next = tokens->next;
        free(tokens->value);
        free(tokens);
        tokens = next;
    }
}
