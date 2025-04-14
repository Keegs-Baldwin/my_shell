/*
** EPITECH PROJECT, 2024
** Epitech
** File description:
** project.c
*/

#include "../includes/my.h"

void print_digit(int digit)
{
    char c = digit + '0';

    write(1, &c, 1);
}

void my_putnbr(int nb)
{
    if (nb < 0) {
        write(1, "-", 1);
        nb *= -1;
    }
    if (nb < 10) {
        print_digit(nb);
    } else {
        my_putnbr(nb / 10);
        print_digit(nb % 10);
    }
}
