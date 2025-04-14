/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** Parser implementation with 20-line limit per function
*/
#include "../includes/my.h"

static void free_command_resources(char **argv, int arg_count, ast_t *node)
{
    for (int i = 0; i < arg_count; i++)
        free(argv[i]);
    free(argv);
    free(node);
}

static ast_t *prepare_command_result(char **argv, int arg_count, ast_t *node)
{
    argv[arg_count] = NULL;
    node->argv = argv;
    return node;
}

ast_t *parse_command(token_t **tok)
{
    ast_t *node = create_command_node();
    char **argv;
    int arg_count;

    if (!node)
        return NULL;
    argv = malloc(64 * sizeof(char *));
    if (!argv) {
        free(node);
        return NULL;
    }
    arg_count = 0;
    while (*tok && ((*tok)->type == TOKEN_WORD ||
        (*tok)->type == TOKEN_REDIRECT)) {
        if (!process_token(tok, &argv, &arg_count, node)) {
            free_command_resources(argv, arg_count, node);
            return NULL;
        }
    }
    return prepare_command_result(argv, arg_count, node);
}

static void handle_redirect(ast_t *node, token_t **tok)
{
    char *op = (*tok)->value;

    *tok = (*tok)->next;
    if (!*tok || (*tok)->type != TOKEN_WORD) {
        my_puterror("Syntax error: Missing filename after redirection\n");
        return;
    }
    if (my_strcmp(op, "<") == 0)
        handle_redirect_input(node, (*tok)->value);
    else if (my_strcmp(op, ">") == 0)
        handle_redirect_output(node, (*tok)->value, 0);
    if (my_strcmp(op, ">>") == 0)
        handle_redirect_output(node, (*tok)->value, 1);
    *tok = (*tok)->next;
}

static int add_arg_to_command(char ***argv, int *arg_count, char *arg)
{
    (*argv)[*arg_count] = my_strdup(arg);
    if (!(*argv)[*arg_count])
        return 0;
    (*arg_count)++;
    return 1;
}

int process_token(token_t **tok, char ***argv,
    int *arg_count, ast_t *node)
{
    if ((*tok)->type == TOKEN_REDIRECT) {
        handle_redirect(node, tok);
        return 1;
    } else {
        if (!add_arg_to_command(argv, arg_count, (*tok)->value))
            return 0;
        *tok = (*tok)->next;
        return 1;
    }
}

static ast_t *parse_and(token_t **tok)
{
    ast_t *left = parse_pipe(tok);
    ast_t *and_node;

    if (!left)
        return NULL;
    if (*tok && (*tok)->type == TOKEN_AND) {
        and_node = create_and_node(left);
        if (!and_node)
            return left;
        *tok = (*tok)->next;
        and_node->right = parse_and(tok);
        return and_node;
    }
    return left;
}

static ast_t *parse_semicolon(token_t **tok)
{
    ast_t *left = parse_and(tok);
    ast_t *semicolon_node;

    if (!left)
        return NULL;
    if (*tok && (*tok)->type == TOKEN_SEMICOLON) {
        semicolon_node = create_semicolon_node(left);
        if (!semicolon_node)
            return left;
        *tok = (*tok)->next;
        semicolon_node->right = parse_semicolon(tok);
        return semicolon_node;
    }
    return left;
}

ast_t *parse_pipe(token_t **tok)
{
    ast_t *left = parse_command(tok);
    ast_t *pipe_node;

    if (!left)
        return NULL;
    if (*tok && (*tok)->type == TOKEN_PIPE) {
        pipe_node = create_pipe_node(left);
        if (!pipe_node)
            return left;
        *tok = (*tok)->next;
        pipe_node->right = parse_pipe(tok);
        return pipe_node;
    }
    return left;
}

ast_t *parse(token_t **tok)
{
    return parse_semicolon(tok);
}
