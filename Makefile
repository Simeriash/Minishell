NAME := minishell

CC := cc
CFLAGS := -Wall -Wextra -Werror -g # -fsanitize=address

HEADER := minishell.h

LIBFT := src/Libft/libft.a

SOURCES :=

SRC_DIR := src/
SRC := $(addprefix $(SRC_DIR), $(SOURCES))

OBJ_DIR := obj/
OBJ := $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))

.PHONY : all clean fclean re

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(OBJ)
	$(MAKE) -C src/Libft
	$(CC) $(CFLAGS) $(OBJ) -o $@

$(OBJ_DIR) :
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I $(HEADER) -c $< -o $@

clean :
	$(MAKE) -C src/Libft -B clean
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)

fclean : clean
	$(MAKE) -C src/Libft -B fclean
	rm -rf $(NAME)

re : fclean all
