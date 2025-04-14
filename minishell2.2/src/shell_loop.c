/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** shell_loop
*/

#include "../includes/my.h"

static void free_ast(ast_t *node)
{
    if (!node)
    return;
    if (node->in_fd != STDIN_FILENO)
        close(node->in_fd);
    if (node->out_fd != STDOUT_FILENO)
        close(node->out_fd);
    free_ast(node->left);
    free_ast(node->right);
    if (node->argv) {
        for (char **arg = node->argv; *arg; arg++)
            free(*arg);
        free(node->argv);
    }
    free(node);
}

void process_command(ast_t *ast, env_t *env)
{
    execute_node(ast, env);
}

char *read_command_line(size_t *len)
{
    char *line = NULL;
    ssize_t read;

    read = getline(&line, len, stdin);
    if (read == -1) {
        if (line)
            free(line);
        return NULL;
    }
    return line;
}

void process_line_ending(char *line, int read)
{
    if (read > 0 && line[read - 1] == '\n')
        line[read - 1] = '\0';
}

void handle_line_input(char *line, size_t len, ast_t **ast, env_t *env)
{
    token_t *tokens = tokenize(line);

    if (tokens) {
        *ast = parse(&tokens);
        if (*ast) {
            process_command(*ast, env);
            free_ast(*ast);
        }
        free_tokens(tokens);
    }
}

static void print_prompt(void)
{
    if (isatty(0))
        write(1, "$>", 2);
}

void shell_loop(env_t *env)
{
    char *line = NULL;
    size_t len = 0;
    ast_t *ast = NULL;

    while (1) {
        print_prompt();
        fflush(stdout);
        line = read_command_line(&len);
        if (line == NULL)
            break;
        process_line_ending(line, strlen(line));
        if (line[0] == '\0') {
            free(line);
            continue;
        }
        handle_line_input(line, len, &ast, env);
        if (line)
            free(line);
    }
}
