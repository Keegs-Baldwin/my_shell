/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** Find a command in the PATH environment variable
*/

#include "../includes/my.h"

static char *build_full_path(const char *dir, const char *cmd)
{
    char *full_path = malloc(my_strlen(dir) + my_strlen(cmd) + 2);

    if (full_path == NULL)
        return NULL;
    my_strcpy(full_path, dir);
    my_strcat(full_path, "/");
    my_strcat(full_path, cmd);
    return full_path;
}

static char *check_path_access(char *dir, const char *cmd)
{
    char *full_path = build_full_path(dir, cmd);

    if (full_path == NULL)
        return NULL;
    if (access(full_path, X_OK) == 0)
        return full_path;
    free(full_path);
    return NULL;
}

char *find_command_in_path(const char *cmd, env_t *env)
{
    char *path_copy;
    char *dir;
    char *full_path;
    int index = my_getenv_index("PATH", env->env);

    if (index == -1)
        return NULL;
    path_copy = my_strdup(env->env[index] + 5);
    dir = strtok(path_copy, ":");
    while (dir != NULL) {
        full_path = check_path_access(dir, cmd);
        if (full_path != NULL) {
            free(path_copy);
            return full_path;
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}
