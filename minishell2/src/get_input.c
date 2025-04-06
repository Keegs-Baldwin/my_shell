/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell2-keigan.baldwin
** File description:
** get_imput
*/

#include "../include/my.h"

void free_com(char **coms)
{
    for (int i = 0; coms[i] != NULL; i++) {
        free(coms[i]);
    }
}

void change_input(info_t *info, char *com)
{
    if (info->input != NULL) {
        free(info->input);
        info->input = NULL;
    }
    info->input = my_strdup(com);
    free(com);
}

int n_loop(char *commands, info_t *info)
{
    size_t len = 0;
    char *clean_com;
    int re;

    do {
        clean_com = clean_string(commands);
        if (my_strncmp(clean_com, "exit", 4) == 0) {
            free(clean_com);
            free(commands);
            return 0;
        }
        change_input(info, clean_com);
        re = process_input(info);
        commands = NULL;
    } while ((getline(&commands, &len, stdin) >= 0));
    free(commands);
    return re;
}

static int run_funcs(info_t *info, char *command)
{
    if (!info->is_stdin)
        return n_loop(command, info);
    if (info->input != NULL) {
        free(info->input);
        info->input = NULL;
    }
    info->input = my_strdup(command);
    free(command);
    process_input(info);
}

static int free_str(char *str)
{
    free(str);
    return 0;
}

static void prompt_user(info_t *info)
{
    if (info->is_stdin)
        write(1, "->", 2);
}

int main_loop(info_t *info)
{
    size_t len = 0;
    int read;
    char *dirty_str = NULL;
    char *clean_com;

    while (1) {
        prompt_user(info);
        read = getline(&dirty_str, &len, stdin);
        if (!info->is_stdin)
            break;
        clean_com = clean_string(dirty_str);
        if (!clean_com)
            continue;
        if (my_strncmp(clean_com, "exit", 4) == 0)
            return free_str(clean_com);
        run_funcs(info, clean_com);
        dirty_str = NULL;
    }
    return run_funcs(info, clean_string(dirty_str));
}

int check_input(char **env)
{
    info_t info;
    int re;

    fill_struct(&info, env);
    re = main_loop(&info);
    free_info(&info);
    return re;
}
