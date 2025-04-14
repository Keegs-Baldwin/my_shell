/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** my_strncpy
*/

#include "../includes/my.h"

char *my_strncpy(char *dest, const char *src, int length)
{
    for (int i = 0; i < length; i++) {
        dest[i] = src[i];
    }
    dest[length] = '\0';
    return dest;
}
