/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** str_to_array
*/

#include <stdlib.h>
#include <string.h>
#include "../include/my.h"

static int is_separator(const char *str, const char *sep)
{
    return my_strncmp(str, sep, my_strlen(sep)) == 0;
}

static int count_words(const char *str, const char *sep)
{
    int count = 0;
    int len = my_strlen(sep);

    while (*str) {
        if (!is_separator(str, sep))
            count++;
        while (*str && !is_separator(str, sep))
            str++;
        if (*str)
            str += len;
    }
    return count;
}

static char *get_next_word(const char **str, const char *sep)
{
    const char *start = *str;
    int length = 0;
    char *word = NULL;

    while (**str && !is_separator(*str, sep)) {
        (*str)++;
        length++;
    }
    if (length == 0)
        return NULL;
    word = malloc(sizeof(char) * (length + 1));
    if (!word)
        return NULL;
    my_strncpy(word, start, length);
    word[length] = '\0';
    return word;
}

char **my_str_to_word_array(const char *str, const char *sep)
{
    int word_count = count_words(str, sep);
    char **word_array = malloc((word_count + 1) * sizeof(char *));
    int i = 0;
    int sep_len = my_strlen(sep);

    if (!word_array)
        return NULL;
    while (*str) {
        if (!is_separator(str, sep)) {
            word_array[i] = get_next_word(&str, sep);
            i++;
        } else
            str += sep_len;
    }
    word_array[i] = NULL;
    return word_array;
}
