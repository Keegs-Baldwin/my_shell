/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** my_strlen
*/

#include "../include/my.h"

int my_strlen(const char *str)
{
    int length = 0;

    if (str == NULL)
        return 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
