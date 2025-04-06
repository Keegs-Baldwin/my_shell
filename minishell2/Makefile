##
## EPITECH PROJECT, 2024
## Epitech
## File description:
## task 05 day 5 find square root
##

CC = gcc
CFLAGS = -g3

SRC =	src/main.c \
		src/find_exc.c \
		src/disp_env.c \
		src/add_env.c \
		src/unsetenv.c \
		lib/str_to_array.c \
		lib/my_strlen.c \
		lib/my_strncmp.c \
		lib/my_strncpy.c \
		lib/my_strcmp.c \
		lib/my_strcat.c \
		lib/my_strdup.c \
		lib/join_with_x.c\
		lib/my_strchr.c\
		src/cd.c\
		src/dir_stuff.c\
		src/dup_and_free_env.c\
		lib/my_putstr.c\
		lib/my_puterror.c\
		lib/my_putnbr.c\
		src/run_other_com.c\
		src/env_helper.c\
		lib/clean_str.c\
		src/get_command.c\
		src/check_inputs_helpers.c\
		src/get_input.c\
		src/pipe_handling.c\
		src/command_execution.c

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
	rm -f src/*.o lib/*.o

fclean: clean
	rm -f $(NAME)

re: all clean
