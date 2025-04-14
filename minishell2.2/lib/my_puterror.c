/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** my_puterror
*/

#include "../includes/my.h"

void my_putchar_e(char c)
{
    write(2, &c, 1);
}

int my_puterror(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar_e(str[i]);
        i++;
    }
    return 0;
}
