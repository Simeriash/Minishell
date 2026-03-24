# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Directories
SRC_DIR = src
INC_DIR = inc
LIBFT_DIR = src/libft
BUILTINS_DIR = $(SRC_DIR)/built_ins
OBJ_DIR = obj

# Executable
NAME = minishell

# Sources
SRCS = $(SRC_DIR)/minishell.c \
       $(SRC_DIR)/lexer/lexer.c \
       $(BUILTINS_DIR)/echo/ft_echo.c \
       $(BUILTINS_DIR)/cd/ft_cd.c \
       $(BUILTINS_DIR)/exit/ft_exit.c \
	   $(BUILTINS_DIR)/pwd/ft_pwd.c \
	   $(BUILTINS_DIR)/env/ft_env.c \

# Object files in obj/ folder
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Include flags
INC_FLAGS = -I$(INC_DIR) -I$(LIBFT_DIR) -Irea

# Rules
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

# Compile objects, creating subdirectories if needed
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
