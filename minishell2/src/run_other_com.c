/*
** EPITECH PROJECT, 2025
** B-PSU-200-BAR-2-1-minishell1-keigan.baldwin
** File description:
** run_other_com
*/

#include "../include/my.h"


void handle_child(char *path, char **input, char **env)
{
    execve(path, input, env);
}

static void print_with_int(char *str, int x)
{
    my_putstr(str);
    my_putnbr(x);
    my_putstr("\n");
}

static void stat_check(int *exit_s, int wstatus)
{
    if (WIFEXITED(wstatus)) {
        *exit_s = WEXITSTATUS(wstatus);
        return;
    }
    if (WIFSIGNALED(wstatus)) {
        print_with_int("killed by signal ", WTERMSIG(wstatus));
        return;
    }
    if (WIFSTOPPED(wstatus)) {
        print_with_int("stopped by signal ", WSTOPSIG(wstatus));
        return;
    }
    if (WIFCONTINUED(wstatus)) {
        my_putstr("continued\n");
        return;
    }
}

int handle_parent(pid_t pid)
{
    int wstatus;
    pid_t w;
    int exit_s = 0;

    do {
        w = waitpid(pid, &wstatus, WUNTRACED | WCONTINUED);
        if (w == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        stat_check(&exit_s, wstatus);
    } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
    return exit_s;
}

int run_other_com(char *command, info_t *info)
{
    char *path = find_exc(command, info->env);
    int exit = 0;
    pid_t cpid;

    if (path == NULL) {
        my_putstr(command);
        my_putstr(": Command not found.\n");
        return 1;
    }
    cpid = fork();
    if (cpid == 0) {
        handle_child(path, my_str_to_word_array(info->input, " "), info->env);
    } else {
        exit = handle_parent(cpid);
    }
    free(path);
    return exit;
}
