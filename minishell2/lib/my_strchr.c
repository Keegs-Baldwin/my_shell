/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell2-keigan.baldwin
** File description:
** my_strchr
*/


#include "../include/my.h"

char *my_strchr(const char *s, int c)
{
    while (*s != '\0') {
        if (*s == c)
            return (char *)s;
        s++;
    }
    return NULL;
}
