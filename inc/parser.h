/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:59:51 by julauren          #+#    #+#             */
/*   Updated: 2026/04/18 10:36:07 by julauren         ###   ########.fr       */
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

typedef struct s_redir
{
	t_type			type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**args;
	t_redir	*redir;
}	t_cmd;

typedef struct s_ast
{
	t_type			type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

void	error_parser(t_token *token_list, t_env *envc, t_error error);

/*====================expander====================*/

int		expand(t_token *token_list, t_env *envc);
char	*check_env(t_token *token, t_env *envc, int i, int *j);
int		more_token(t_token **token);
void	delete_quotes(t_token *token_list);

/*=======================ast=======================*/

t_ast	*ast_creation(t_token *token, t_token *stop, t_type type);
t_ast	*init_ast(t_type type, t_cmd *cmd, t_ast *left, t_ast *right);
int		free_ast(t_ast *ast);

#endif
