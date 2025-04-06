/*
** EPITECH PROJECT, 2024
** my_strcmp
** File description:
** No file there, just an epitech header example.
** You can even have multiple lines if you want!
*/

#include "../include/my.h"

int my_strcmp(char const *s1, char const *s2)
{
    if (s1 == NULL || s2 == NULL) {
        if (s1 == s2)
            return 0;
        if (s1 != NULL) {
            return 1;
        } else {
            return -1;
        }
    }
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}
