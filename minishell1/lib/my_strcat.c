/*
** EPITECH PROJECT, 2024
** my_strcat
** File description:
** No fle there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "../include/my.h"

char *my_strcat(char *dest, char const *src)
{
    int len = 0;
    int i;

    while (dest[len] != '\0') {
        len++;
    }
    for (i = 0; src[i] != '\0'; i++) {
        dest[len + i] = src[i];
    }
    dest[len + i] = '\0';
    return dest;
}
