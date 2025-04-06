/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** main
*/

#include "../include/my.h"


int main(int argc, char **argv, char **env)
{
    if (argc != 1) {
        return 84;
    }
    return check_input(env);
}
