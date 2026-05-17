/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:59:51 by julauren          #+#    #+#             */
/*   Updated: 2026/05/17 08:31:51 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include "lexer.h"
# include "error.h"

# include <stdlib.h>

typedef struct s_arg
{
	char			*str;
	struct s_arg	*next;
}	t_arg;

int		heredoc(char *eof, t_env *envc);

/*====================expander====================*/

int		expand(t_token *token_list, t_env *envc);
char	*check_new_value(char *value, t_env *envc, int i, int *j);
int		change_value(char **value, char *new_value, int start, int end);
char	*check_env(char *value, t_env *envc, int i, int *j);
int		more_token(t_token **token);
void	delete_quotes(t_token *token_list);

/*=======================ast=======================*/

t_ast	*ast_creation(t_token *token, t_token *stop, t_type type);
t_ast	*init_ast(t_type type, t_cmd *cmd, t_ast *left, t_ast *right);
t_ast	*cmd_node(t_token *token, t_token *stop);
int		add_redir(t_redir **redir, t_token **token);
int		add_arg(t_arg **arg, char *str);
int		free_ast(t_ast *ast);
void	free_cmd(t_cmd *cmd);
void	free_struct(t_arg *arg, t_redir *redir);

#endif
