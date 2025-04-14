/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** parser2
*/

#include "../includes/my.h"

ast_t *create_command_node(void)
{
    ast_t *node = malloc(sizeof(ast_t));

    if (!node)
        return NULL;
    node->type = NODE_CMD;
    node->in_fd = STDIN_FILENO;
    node->out_fd = STDOUT_FILENO;
    node->left = NULL;
    node->right = NULL;
    node->argv = NULL;
    return node;
}

ast_t *create_pipe_node(ast_t *left)
{
    ast_t *pipe_node = malloc(sizeof(ast_t));

    if (!pipe_node)
        return NULL;
    pipe_node->type = NODE_PIPE;
    pipe_node->argv = NULL;
    pipe_node->in_fd = STDIN_FILENO;
    pipe_node->out_fd = STDOUT_FILENO;
    pipe_node->left = left;
    pipe_node->right = NULL;
    return pipe_node;
}

ast_t *create_and_node(ast_t *left)
{
    ast_t *and_node = malloc(sizeof(ast_t));

    if (!and_node)
        return NULL;
    and_node->type = NODE_AND;
    and_node->argv = NULL;
    and_node->in_fd = STDIN_FILENO;
    and_node->out_fd = STDOUT_FILENO;
    and_node->left = left;
    and_node->right = NULL;
    return and_node;
}

ast_t *create_semicolon_node(ast_t *left)
{
    ast_t *semicolon_node = malloc(sizeof(ast_t));

    if (!semicolon_node)
        return NULL;
    semicolon_node->type = NODE_SEMICOLON;
    semicolon_node->argv = NULL;
    semicolon_node->in_fd = STDIN_FILENO;
    semicolon_node->out_fd = STDOUT_FILENO;
    semicolon_node->left = left;
    semicolon_node->right = NULL;
    return semicolon_node;
}
