/*
** EPITECH PROJECT, 2024
** B-CPE-110-BAR-1-1-organized-keigan.baldwin
** File description:
** org
*/

#ifndef INCLUDED_ORG_H
    #define INCLUDED_ORG_H
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/wait.h>
    #include <dirent.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <errno.h>
    #include <sys/wait.h>

typedef enum {
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_REDIRECT,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_SEMICOLON
} token_type_t;

typedef struct token_s {
    char *value;
    token_type_t type;
    struct token_s *next;
} token_t;

typedef enum {
    NODE_CMD,
    NODE_PIPE,
    NODE_AND,
    NODE_OR,
    NODE_REDIR,
    NODE_SEMICOLON
} node_type_t;

typedef struct ast_s {
    node_type_t type;
    char **argv;
    int in_fd;
    int out_fd;
    struct ast_s *left;
    struct ast_s *right;
} ast_t;

typedef struct env {
    char **env;
} env_t;

typedef struct {
    char *cmd;
    int (*func)(ast_t *, env_t *);
}command_t;


//main loop
void shell_loop(env_t *env);

void execute_node(ast_t *node, env_t *env);
char **dup_env(char **envp);



//buitins
int execute_builtin(ast_t *node, env_t *env);
int put_env(ast_t *node, env_t *env);
//env helpers
int my_getenv_index(char *name, char **env);
int get_env_len(char **env);
void free_env(char **env);

int disp_env(ast_t *node, env_t *env);
int run_cd(ast_t *node, env_t *env);
int my_unsetenv(ast_t *node, env_t *env);
int run_exit(ast_t *node, env_t *env);

int replace_env(int index, char *name, char *val, env_t *env);


//lib
int my_strcmp(const char *s1, const char *s2);
void my_putnbr(int nb);
char *my_strncpy(char *dest, const char *src, int length);
char *join_strs_with_x(char *str1, char *str2, char *x);
char *my_strchr(const char *s, int c);
char *my_strcat(char *dest, const char *src);
void my_putchar(char c);
int my_putstr(const char *str);
char *my_strdup(const char *src);
char **my_str_to_word_array(const char *str, const char *sep);
int my_strncmp(const char *s1, const char *s2, int n);
int my_strlen(const char *str);
int my_puterror(char const *str);
char *my_strcpy(char *dest, char const *src);
char *my_strndup(const char *src, size_t n);

//void add_token(token_t **list, char *value, token_type_t_t type);
void process_redirectoken_t(token_t **tokens, char *input, int *pos);
void process_pipe_token(token_t **tokens, char *input, int *pos);
void process_and_token(token_t **tokens, char *input, int *pos);
void process_word_token(token_t **tokens, char *input, int *pos);
token_t *tokenize(char *input);
int open_input_file(const char *filename);
int open_output_file(const char *filename, int append);
// void setup_redirections(ast_t *node);
void add_token(token_t **list, char *value, token_type_t type);

void execute_command(ast_t *node, env_t *env);
int execute_builtin(ast_t *node, env_t *env);
ast_t *parse_command(token_t **tok);
token_t *tokenize(char *input);
char *find_command_in_path(const char *cmd, env_t *env);
ast_t *parse(token_t **tok);

//parser redirect
void handle_redirect_output(ast_t *node, char *filename, int append);
void handle_redirect_input(ast_t *node, char *filename);

/* Prototypes for non-static functions (used externally) */
int is_builtin(const char *cmd);
void execute_command(ast_t *node, env_t *env);
void execute_command_or_fork(ast_t *node, env_t *env);
void execute_node(ast_t *node, env_t *env);


ast_t *parse_pipe(token_t **tok);
int process_token(token_t **tok, char ***argv,
    int *arg_count, ast_t *node);
//parser create
ast_t *create_semicolon_node(ast_t *left);
ast_t *create_and_node(ast_t *left);
ast_t *create_pipe_node(ast_t *left);
ast_t *create_command_node(void);

//token help
void free_tokens(token_t *tokens);
void skip_spaces(const char *input, int *pos);
int is_delimiter(char c);

#endif
