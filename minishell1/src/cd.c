/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** cd
*/

#include "../include/my.h"

static int set_to_home_dir(info_t *info)
{
    char *home_env = my_getenv("HOME", info->env);
    char *home_val = NULL;

    if (home_env == NULL){
        my_puterror("no home dir\n");
        return 0;
    }
    for (int i = 0; home_env[i] != '\0'; i++) {
        if (home_env[i] == '=') {
            home_val = &home_env[i + 1];
            break;
        }
    }
    if (home_val == NULL) {
        my_puterror("Invalid HOME environment variable\n");
        return 0;
    }
    free(info->cur_dir);
    info->cur_dir = my_strdup(home_val);
    return 1;
}

static int get_val(char **name, char *input)
{
    char *token;

    if (input == NULL || name == NULL)
        return 0;
    token = strtok(input, " ");
    if (token == NULL)
        return 0;
    *name = strtok(NULL, " ");
    if (*name == NULL)
        return 0;
    if (strtok(NULL, " ") != NULL)
        return 0;
    return 1;
}

static int move_back_one_dir(char **dir)
{
    char *cur_dir = *dir;
    int dir_len = my_strlen(cur_dir);
    char *new_dir = NULL;

    if (dir_len <= 2)
        return 0;
    while (cur_dir[dir_len] != '/') {
        dir_len--;
    }
    new_dir = malloc(dir_len + 1);
    for (int i = 0; i < dir_len; i++) {
        new_dir[i] = cur_dir[i];
    }
    new_dir[dir_len] = '\0';
    free(*dir);
    *dir = new_dir;
    return 1;
}

static int move_to_x_dir_helper(char *cur_in, char **dir)
{
    int re;
    char *dir_dup = my_strdup(*dir);

    if (cur_in[0] == '\0') {
        free(dir_dup);
        return 0;
    }
    if (my_strcmp(cur_in, "..") == 0) {
        free(dir_dup);
        return move_back_one_dir(dir);
    }
    re = search_dir(*dir, cur_in);
    if (re == 1) {
        free(*dir);
        *dir = join_strs_with_x(dir_dup, cur_in, "/");
        free(dir_dup);
        return re;
    }
    free(dir_dup);
    return re;
}

static void free_word_array(char **array)
{
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
}

static int move_to_x_dir(char *input, info_t *info)
{
    char **split_input = my_str_to_word_array(input, "/");
    char *new_dir = my_strdup(info->cur_dir);
    int result = 1;

    if (!new_dir || !split_input) {
        free(new_dir);
        free_word_array(split_input);
        return 0;
    }
    for (int i = 0; split_input[i] != NULL && result; i++)
        result = move_to_x_dir_helper(split_input[i], &new_dir);
    free_word_array(split_input);
    if (result) {
        free(new_dir);
        return 0;
    }
    free(info->cur_dir);
    info->cur_dir = new_dir;
    return 1;
}

static void what_cd(info_t *info, int *update, char *val)
{
    if (val == NULL) {
        *update = set_to_home_dir(info);
        return;
    }
    if (my_strcmp(val, "..") == 0) {
        *update = move_back_one_dir(&info->cur_dir);
        return;
    }
    if (my_strcmp(val, ".") == 0) {
        *update = 0;
        return;
    }
    *update = move_to_x_dir(val, info);
}

void run_cd(info_t *info)
{
    char *val = NULL;
    int update = 0;

    get_val(&val, info->input);
    what_cd(info, &update, val);
    if (update) {
        chdir(info->cur_dir);
    }
}
