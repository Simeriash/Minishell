/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 13:43:26 by julauren          #+#    #+#             */
/*   Updated: 2026/06/13 09:52:20 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/libft.h"

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_type
{
	NONE,
	WORD,
	CMD,
	EXPAND,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	RET
}	t_type;

typedef struct s_token
{
	t_type			type;
	char			*value;
	struct s_token	*next;
}	t_token;

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
	t_token			*token;
	struct s_ast	*ast;
	t_type			type;
	t_cmd			*cmd;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

t_token	*lexer(char *str, int *status);
t_ast	*parser(t_token *token_list, t_env *envc, int *status);
int		heredoc(char *eof, t_token *token_list, t_env *envc, int status);
t_env	*env_copy(char **envp);

#endif
