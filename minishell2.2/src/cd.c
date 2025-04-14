/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** Implementation of the cd command for minishell
*/

#include "../includes/my.h"

static char *get_home_dir(env_t *env)
{
    int index = my_getenv_index("HOME", env->env);

    if (index == -1) {
        my_puterror("cd: No home directory\n");
        return NULL;
    }
    return env->env[index] + 5;
}

static char *get_old_pwd_dir(env_t *env)
{
    int old_index = my_getenv_index("OLDPWD", env->env);

    if (old_index == -1) {
        my_puterror("cd: OLDPWD not set\n");
        return NULL;
    }
    return env->env[old_index] + 7;
}

static int update_env_vars(env_t *env, char *old_pwd, char *new_pwd)
{
    int old_index = my_getenv_index("OLDPWD", env->env);
    int pwd_index = my_getenv_index("PWD", env->env);

    if (old_index != -1) {
        free(env->env[old_index]);
        env->env[old_index] = join_strs_with_x("OLDPWD", old_pwd, "=");
    }
    if (pwd_index != -1) {
        free(env->env[pwd_index]);
        env->env[pwd_index] = join_strs_with_x("PWD", new_pwd, "=");
    }
    return 1;
}

static int handle_cd_error(ast_t *node, char *path)
{
    my_puterror(node->argv[1]);
    my_puterror(": ");
    if (access(path, F_OK) == -1) {
        my_puterror("No such file or directory.\n");
    } else if (access(path, X_OK) == -1) {
        my_puterror("Permission denied.\n");
    } else {
        my_puterror("Cannot change directory.\n");
    }
    return 1;
}

static char *determine_path(ast_t *node, env_t *env, char *old_pwd)
{
    char *path = NULL;

    if (node->argv[1] == NULL) {
        path = get_home_dir(env);
    }
    if (node->argv[1] && my_strcmp(node->argv[1], "-") == 0) {
        path = get_old_pwd_dir(env);
    }
    if (node->argv[1] && my_strcmp(node->argv[1], "..") == 0) {
        getcwd(old_pwd, 1024);
        path = "..";
    }
    if (path == NULL) {
        path = node->argv[1];
    }
    return path;
}

int run_cd(ast_t *node, env_t *env)
{
    char old_pwd[1024];
    char new_pwd[1024];
    char *path;

    path = determine_path(node, env, old_pwd);
    if (path == NULL)
        return 1;
    getcwd(old_pwd, sizeof(old_pwd));
    if (chdir(path) == -1)
        return handle_cd_error(node, path);
    getcwd(new_pwd, sizeof(new_pwd));
    return update_env_vars(env, old_pwd, new_pwd);
}
