##
## EPITECH PROJECT, 2024
## Epitech
## File description:
## Minishell2 Makefile
##

CC = gcc
CFLAGS = -g3 -I./includes

SRC =	src/main.c \
		src/add_env.c \
		src/dup_and_free_env.c \
		src/env_helper.c \
		src/execute_builtin.c \
		lib/my_strcmp.c \
		lib/my_putnbr.c \
		lib/my_strncpy.c \
		lib/join_with_x.c \
		lib/my_strchr.c \
		lib/my_strcat.c \
		lib/my_putstr.c \
		lib/my_strdup.c \
		lib/str_to_array.c \
		lib/my_strncmp.c \
		lib/my_strlen.c \
		lib/my_puterror.c \
		lib/my_strcpy.c \
		src/disp_env.c \
		src/cd.c \
		src/unsetenv.c \
		src/find_command.c \
		src/executor.c\
		src/parser.c \
		src/redirect_utils.c \
		src/shell_loop.c \
		src/parser_redirect.c \
		src/tokenizer.c \
		src/tokenizer_h.c \
		lib/my_strndup.c \
		src/parser2.c

OBJ = $(SRC:.c=.o)

NAME = mysh

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f *~
	rm -f src/*.o
	rm -f lib/*.o
	find . -name "*.o" -type f -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
