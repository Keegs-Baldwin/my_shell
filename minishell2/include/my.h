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

typedef struct info_s {
    char **env;
    char *input;
    char *cur_dir;
    int is_stdin;
}info_t;

typedef struct {
    char *cmd;
    int (*func)(info_t *);
}command_t;
//clean string
typedef struct clean_helper_s {
    int i;
    int start;
    int j;
    int space;
    int len;
} clean_helper_t;


char **my_str_to_word_array(const char *str, const char *separators);
int my_strlen(const char *str);
int my_strncmp(const char *s1, const char *s2, int n);
char *my_strncpy(char *dest, const char *src, int length);
char *find_exc(char *name, char **env);
int my_strcmp(char const *s1, char const *s2);
char *my_strcat(char *dest, char const *src);
char *my_strdup(char const *src);
char *my_strcpy(char *dest, char const *src);
int check_input(char **env);

//env stuff
int put_env(info_t *info);
char *my_getenv(char *name, char **env);
int disp_env(info_t *info);
void free_env(char **env);
int my_unsetenv(info_t *info);
int my_getenv_index(char *name, char **env);
int get_env_len(char **env);
int get_name_and_val(char **name, char **val, char *input);
int replace_env(int index, char *name, char *val, info_t *info);


char **dup_env(char **envp);

//lib stuff
char *join_strs_with_x(char *str1, char *str2, char *x);
int my_putstr(char const *str);
int my_puterror(char const *str);
void my_putnbr(int nb);
char *clean_string(char *input);
char *my_strchr(const char *s, int c);

//cd stuff
int run_cd(info_t *info);

// dir stuuf
int search_dir(char *dir, char *name);

//other com
int run_other_com(char *command, info_t *info);
char *get_commands(char *input);

//change out
int change_out(int num, char *file);

//check helpers
void fill_struct(info_t *info, char **env);
void free_info(info_t *info);

//input
int check_input(char **env);

//input_to func
int input_to_func(info_t *info);

//input_to_functions
int process_input(info_t *info);

void process_redirections(char **args);
int execute_piped_commands(char **commands, info_t *info, command_t *builtins);
int execute_single_command(char **args, info_t *info, command_t *com, int in);
int run_external_command(char **args, info_t *info, int input_fd);
char *validate_executable(char **args, info_t *info);

#endif
