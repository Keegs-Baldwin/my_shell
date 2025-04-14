/*
** EPITECH PROJECT, 2024
** Epitech
** File description:
** project.c
*/

#include "../includes/my.h"

char *my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

char *my_strdup(char const *src)
{
    char *new;

    if (!src)
        return NULL;
    new = malloc(my_strlen(src) + 1);
    if (!new)
        return NULL;
    my_strcpy(new, src);
    return new;
}
