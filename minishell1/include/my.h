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

typedef struct info_s {
    char **env;
    char *input;
    char *cur_dir;
}info_t;

typedef struct {
    char *cmd;
    void (*func)(info_t *);
}command_t;

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
int input_to_func(info_t *info);

//env stuff
void put_env(info_t *info);
char *my_getenv(char *name, char **env);
void disp_env(info_t *info);
void free_env(char **env);
void my_unsetenv(info_t *info);
int my_getenv_index(char *name, char **env);
int get_env_len(char **env);
int get_name_and_val(char **name, char **val, char *input);


char **dup_env(char **envp);

//lib stuff
char *join_strs_with_x(char *str1, char *str2, char *x);
int my_putstr(char const *str);
int my_puterror(char const *str);
void my_putnbr(int nb);
char *clean_string(const char *input);

//cd stuff
void run_cd(info_t *info);

// dir stuuf
int search_dir(char *dir, char *name);

//other com
int run_other_com(char *command, info_t *info);

char *get_commands(char *input);




#endif
