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
	   $(BUILTINS_DIR)/get_builtin.c \
       $(BUILTINS_DIR)/echo/ft_echo.c \
       $(BUILTINS_DIR)/cd/ft_cd.c \
       $(BUILTINS_DIR)/exit/ft_exit.c \
	   $(BUILTINS_DIR)/pwd/ft_pwd.c \
	   $(BUILTINS_DIR)/env/ft_env.c \
	   $(BUILTINS_DIR)/utils/builtin_utils.c $(BUILTINS_DIR)/utils/builtin_utils2.c \
	   $(BUILTINS_DIR)/unset/ft_unset.c \
	   $(BUILTINS_DIR)/export/export_in_order_utils.c $(BUILTINS_DIR)/export/export_utils1.c $(BUILTINS_DIR)/export/ft_export.c $(BUILTINS_DIR)/export/export_helpers1.c \
	   $(SRC_DIR)/exec/execute_cmd.c $(SRC_DIR)/exec/executor.c $(SRC_DIR)/exec/exec_cmd_utils.c $(SRC_DIR)/exec/find_exec.c \
	   $(SRC_DIR)/envc/envc_utils.c $(SRC_DIR)/envc/envc.c $(SRC_DIR)/envc/error.c $(SRC_DIR)/envc/linked_list.c \
	   $(SRC_DIR)/heredoc/error.c $(SRC_DIR)/heredoc/heredoc_utils.c $(SRC_DIR)/heredoc/heredoc.c \
	   $(SRC_DIR)/lexer/error.c $(SRC_DIR)/lexer/lexer_utils.c $(SRC_DIR)/lexer/lexer.c $(SRC_DIR)/lexer/linked_list.c \
	   $(SRC_DIR)/parser/ast.c $(SRC_DIR)/parser/cmd_utils.c $(SRC_DIR)/parser/cmd.c $(SRC_DIR)/parser/delete_quotes.c $(SRC_DIR)/parser/error.c \
	   $(SRC_DIR)/parser/expand_utils.c $(SRC_DIR)/parser/expand.c $(SRC_DIR)/parser/more_token.c $(SRC_DIR)/parser/parser.c


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
