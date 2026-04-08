/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:59:51 by julauren          #+#    #+#             */
/*   Updated: 2026/04/08 16:24:54 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../src/libft/libft.h"
# include "lexer.h"

# include <stdlib.h>

//	/!\		A CHANGER !!	(OU PAS)
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**args;
	t_redir	*redir;
}	t_cmd;

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR
}	t_node_type;

typedef struct s_ast
{
	t_node_type		type;
	t_cmd			cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

void	error_parser(t_token *token_list, t_env *envc, t_error error);

/*====================expander====================*/

int		expand(t_token *token_list, t_env *envc);
t_error	expander(t_token *token, t_env *envc);
char	*check_key(char *key, t_env *envc);
int		change_value(t_token *token, char *new_value, int start, int end);

/*=======================ast=======================*/

t_ast	*ast_creation(t_token *token_list);

#endif
