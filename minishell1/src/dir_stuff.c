/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** dir_stuff
*/

#include "../include/my.h"

int search_dir(char *dir, char *name)
{
    struct dirent *cur;
    DIR *open_dir = opendir(dir);

    if (open_dir == NULL){
        return 0;
    }
    cur = readdir(open_dir);
    while (cur != NULL) {
        if (my_strcmp(cur->d_name, name) == 0) {
            closedir(open_dir);
            return 1;
        }
        cur = readdir(open_dir);
    }
    closedir(open_dir);
    return 0;
}
