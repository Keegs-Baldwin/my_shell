/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** Command execution functions
*/
#include "../includes/my.h"

static void setup_redirections(ast_t *node)
{
    if (node->in_fd != STDIN_FILENO) {
        dup2(node->in_fd, STDIN_FILENO);
        close(node->in_fd);
    }
    if (node->out_fd != STDOUT_FILENO) {
        dup2(node->out_fd, STDOUT_FILENO);
        close(node->out_fd);
    }
}

static void command_find(char **path, env_t *env, ast_t *node)
{
    *path = find_command_in_path(node->argv[0], env);
    if (!*path) {
        my_puterror(node->argv[0]);
        my_puterror(": Command not found.\n");
        exit(EXIT_FAILURE);
    }
}

void execute_command(ast_t *node, env_t *env)
{
    char *cmd_path;

    setup_redirections(node);
    if (is_builtin(node->argv[0])) {
        execute_builtin(node, env);
        return;
    }
    cmd_path = node->argv[0];
    if (strchr(node->argv[0], '/') == NULL)
        command_find(&cmd_path, env, node);
    execve(cmd_path, node->argv, env->env);
    perror(node->argv[0]);
    if (cmd_path != node->argv[0])
        free(cmd_path);
    exit(EXIT_FAILURE);
}

void execute_command_or_fork(ast_t *node, env_t *env)
{
    pid_t pid;

    if (is_builtin(node->argv[0])) {
        execute_command(node, env);
    } else {
        pid = fork();
        if (pid == 0) {
            execute_command(node, env);
            return;
        }
        if (pid > 0) {
            waitpid(pid, NULL, 0);
        } else {
            perror("fork");
        }
    }
}

static void execute_pipe_child(ast_t *node, env_t *env,
    int *pipefd, int is_left)
{
    if (is_left) {
        close(pipefd[0]);
        if (node->left->out_fd == STDOUT_FILENO)
            node->left->out_fd = pipefd[1];
        execute_node(node->left, env);
    } else {
        close(pipefd[1]);
        if (node->right->in_fd == STDIN_FILENO)
            node->right->in_fd = pipefd[0];
        execute_node(node->right, env);
    }
    exit(EXIT_SUCCESS);
}

static void execute_pipe(ast_t *node, env_t *env)
{
    int pipefd[2];
    pid_t pid1;
    pid_t pid2;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }
    pid1 = fork();
    if (pid1 == 0)
        execute_pipe_child(node, env, pipefd, 1);
    pid2 = fork();
    if (pid2 == 0)
        execute_pipe_child(node, env, pipefd, 0);
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

void wait_and_exacute(int status, ast_t *node, env_t *env)
{
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        execute_node(node->right, env);
    }
}

static void execute_and(ast_t *node, env_t *env)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        execute_node(node->left, env);
        exit(EXIT_SUCCESS);
    } else if (pid > 0) {
        waitpid(pid, &status, 0);
        wait_and_exacute(status, node, env);
    } else {
        perror("fork");
    }
}

static void execute_semicolon(ast_t *node, env_t *env)
{
    execute_node(node->left, env);
    execute_node(node->right, env);
}

void execute_node(ast_t *node, env_t *env)
{
    if (!node)
        return;
    switch (node->type) {
    case NODE_PIPE:
        execute_pipe(node, env);
        break;
    case NODE_CMD:
        execute_command_or_fork(node, env);
        break;
    case NODE_AND:
        execute_and(node, env);
        break;
    case NODE_SEMICOLON:
        execute_semicolon(node, env);
        break;
    default:
        break;
    }
}
