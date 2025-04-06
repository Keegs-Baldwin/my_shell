/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** find_exc
*/

#include "../include/my.h"

char *my_getenv(char *name, char **env)
{
    int i = 0;

    while (env[i] != NULL) {
        if (my_strncmp(env[i], name, my_strlen(name)) == 0) {
            return env[i];
        }
        i++;
    }
    return NULL;
}

char *find_exc_helper(char *env_path, char *name)
{
    char *path_copy = my_strdup(env_path);
    char *path_token;
    char *result = NULL;

    path_token = strtok(path_copy, "=");
    path_token = strtok(NULL, ":");
    while (path_token != NULL) {
        if (search_dir(path_token, name)) {
            result = join_strs_with_x(path_token, name, "/");
            break;
        }
        path_token = strtok(NULL, ":");
    }
    free(path_copy);
    return result;
}

char *find_exc(char *name, char **env)
{
    char *env_path = my_getenv("PATH", env);
    char *re;

    if (env_path == NULL)
        return NULL;
    re = find_exc_helper(env_path, name);
    return re;
}
