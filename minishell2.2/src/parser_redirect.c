/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** parser_redirect
*/

#include "../includes/my.h"

void handle_redirect_input(ast_t *node, char *filename)
{
    if (node->in_fd != STDIN_FILENO)
        close(node->in_fd);
    node->in_fd = open_input_file(filename);
}

void handle_redirect_output(ast_t *node, char *filename, int append)
{
    if (node->out_fd != STDOUT_FILENO)
        close(node->out_fd);
    node->out_fd = open_output_file(filename, append);
}
