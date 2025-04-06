/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** join_with_x
*/

#include "../include/my.h"

char *join_strs_with_x(char *str1, char *str2, char *x)
{
    char *re = malloc((my_strlen(str1) + my_strlen(str2)) + my_strlen(x) + 1);

    if (re == NULL) {
        my_puterror("error mallocing\n");
        return NULL;
    }
    if (str1 == NULL)
    return NULL;
    my_strcpy(re, str1);
    my_strcat(re, x);
    if (str2 == NULL)
        return re;
    my_strcat(re, str2);
    return re;
}
