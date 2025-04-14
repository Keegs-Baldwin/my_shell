/*
** EPITECH PROJECT, 2025
** minishell2.2
** File description:
** Redirection utility functions
*/

#include "../includes/my.h"

int open_input_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror(filename);
    }
    return fd;
}

int open_output_file(const char *filename, int append)
{
    int flags = O_WRONLY | O_CREAT;
    int fd;

    if (append) {
        flags |= O_APPEND;
    } else {
        flags |= O_TRUNC;
    }
    fd = open(filename, flags, 0644);
    if (fd == -1) {
        perror(filename);
    }
    return fd;
}
