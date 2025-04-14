/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** my_strndup
*/

#include <stdlib.h>

char *my_strndup(const char *src, size_t n)
{
    size_t len = 0;
    char *new_str;

    if (src == NULL) {
        return NULL;
    }
    while (src[len] != '\0' && len < n) {
        len++;
    }
    new_str = malloc(len + 1);
    if (new_str == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < len; i++) {
        new_str[i] = src[i];
    }
    new_str[len] = '\0';
    return new_str;
}
