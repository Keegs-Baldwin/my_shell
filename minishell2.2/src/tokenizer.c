/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** Tokenizer functions for minishell command parsing
*/

#include "../includes/my.h"

static token_t *create_token(int type, char *value)
{
    token_t *token = malloc(sizeof(token_t));

    if (token == NULL) {
        free(value);
        return NULL;
    }
    token->type = type;
    token->value = value;
    token->next = NULL;
    return token;
}

static token_t *get_word_token(const char *input, int *pos)
{
    int start = *pos;
    char *value;

    while (input[*pos] != '\0' && !is_delimiter(input[*pos])) {
        (*pos)++;
    }
    value = my_strndup(input + start, *pos - start);
    if (value == NULL) {
        return NULL;
    }
    return create_token(TOKEN_WORD, value);
}

static token_t *get_redirect_token(const char *input, int *pos)
{
    char *value;

    if (input[*pos] == '<') {
        value = my_strdup("<");
        (*pos)++;
    } else if (input[*pos] == '>' && input[*pos + 1] == '>') {
        value = my_strdup(">>");
        (*pos) += 2;
    } else {
        value = my_strdup(">");
        (*pos)++;
    }
    if (value == NULL) {
        return NULL;
    }
    return create_token(TOKEN_REDIRECT, value);
}

static token_t *get_pipe_or_or_token(const char *input, int *pos)
{
    char *value;

    if (input[*pos] == '|' && input[*pos + 1] == '|') {
        value = my_strdup("||");
        (*pos) += 2;
    } else {
        value = my_strdup("|");
        (*pos)++;
    }
    if (value == NULL) {
        return NULL;
    }
    return create_token(value[1] == '|' ? TOKEN_OR : TOKEN_PIPE, value);
}

static token_t *get_and_token(const char *input, int *pos)
{
    char *value;

    if (input[*pos] == '&' && input[*pos + 1] == '&') {
        value = my_strdup("&&");
        (*pos) += 2;
    } else {
        my_puterror("Invalid token: '&'\n");
        return NULL;
    }
    if (value == NULL) {
        return NULL;
    }
    return create_token(TOKEN_AND, value);
}

static token_t *get_semicolon_token(const char *input, int *pos)
{
    char *value = my_strdup(";");

    if (value == NULL) {
        return NULL;
    }
    (*pos)++;
    return create_token(TOKEN_SEMICOLON, value);
}

static token_t *get_next_token(const char *input, int *pos)
{
    char c = input[*pos];

    if (my_strchr("<>|&;", c) == NULL) {
        return get_word_token(input, pos);
    }
    if (c == '<' || c == '>') {
        return get_redirect_token(input, pos);
    }
    if (c == '|') {
        return get_pipe_or_or_token(input, pos);
    }
    if (c == '&') {
        return get_and_token(input, pos);
    }
    return get_semicolon_token(input, pos);
}

token_t *append_token_to_list(token_t *tokens,
    token_t *new_token, token_t **tail)
{
    if (new_token == NULL) {
        free_tokens(tokens);
        return NULL;
    }
    if (tokens == NULL) {
        tokens = new_token;
        *tail = new_token;
    } else {
        (*tail)->next = new_token;
        *tail = new_token;
    }
    return tokens;
}

token_t *tokenize(char *input)
{
    token_t *tokens = NULL;
    token_t *tail = NULL;
    int pos = 0;
    token_t *new_token;

    while (input[pos] != '\0') {
        skip_spaces(input, &pos);
        if (input[pos] == '\0')
            break;
        new_token = get_next_token(input, &pos);
        tokens = append_token_to_list(tokens, new_token, &tail);
        if (tokens == NULL) {
            return NULL;
        }
    }
    return tokens;
}
