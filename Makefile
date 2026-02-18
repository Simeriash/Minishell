NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -g # -fsanitize=address

HEADER := minishell.h

LIBFT := src/libft/libft.a

SOURCES := minishell.c

SRC_DIR := src/
SRC := $(addprefix $(SRC_DIR), $(SOURCES))

OBJ_DIR := obj/
OBJ := $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(MAKE) -C src/libft
	$(CC) $(CFLAGS) $(OBJ) -lreadline -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

clean :
	$(MAKE) -C src/libft -B clean
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)

fclean : clean
	$(MAKE) -C src/libft -B fclean
	rm -rf $(NAME)

re : fclean all
