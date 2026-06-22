/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:59:51 by julauren          #+#    #+#             */
/*   Updated: 2026/06/21 17:30:43 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include "lexer.h"
# include "error.h"

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_arg
{
	char			*str;
	struct s_arg	*next;
}	t_arg;

typedef struct s_index
{
	int	i;
	int	j;
}	t_index;

typedef struct s_ctrl
{
	t_state	state;
	int		status;
}	t_ctrl;

/*====================expander====================*/

int		expand(t_token *token_list, t_env *envc, int *status);
void	ft_memcpy_exp(char *str, t_index *index);
int		condition_to_expand(t_token *token, t_index index, t_state state);
char	*check_new_value(char *value, t_env *envc, t_index *index, t_ctrl ctrl);
int		change_value(char **value, char *new_value, int start, int end);
char	*check_env(char *value, t_env *envc, t_index *index, t_state state);
char	*check_key(char *key, t_env *envc);
int		more_token(t_token **token);
int		new_token(t_token **token, t_index *index);
char	**split_token(char *str, t_index *index);
void	delete_quotes(t_token *token_list);

/*=======================ast=======================*/

t_ast	*ast_creation(t_token *token, t_token *stop, t_type type);
t_ast	*init_ast(t_type type, t_cmd *cmd, t_ast *left, t_ast *right);
t_ast	*cmd_node(t_token *token, t_token *stop);
int		add_redir(t_redir **redir, t_token **token);
int		add_arg(t_arg **arg, char *str);
int		free_ast(t_ast *ast);
void	free_cmd(t_cmd *cmd);
void	free_struct(t_arg *arg, t_redir *redir, t_cmd *cmd);
void	ast_init(t_ast **ast, t_ast *init_ast);
int		pipe_error(t_ast *ast, int *status);

#endif
