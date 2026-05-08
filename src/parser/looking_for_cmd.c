/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looking_for_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:06:30 by julauren          #+#    #+#             */
/*   Updated: 2026/05/06 13:21:41 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_redir	*node_redir(t_redir *redir, t_type type, char *file)
{
	t_redir	*new_redir;

	new_redir = malloc (sizeof(*new_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->file = file;
	if (redir)
	{
		new_redir->next = redir->next;
		redir->next = new_redir;
	}
	else
		new_redir->next = NULL;
	return (new_redir);
}

static int	add_arg(t_arg *arg, char *str)
{
	t_arg	*new_arg;

	new_arg = malloc(sizeof(*new_arg));
	if (!new_arg)
		return (1);
	new_arg->str = str;
	new_arg->next = NULL;
	arg->next = new_arg;
	return (0);
}

static void	free_all_cmd()
{
	// free t_redir, t_arg & t_cmd;
	// mettre a null token->value apres le free
}

t_ast	*looking_for_cmd(t_token *token, t_token *stop)
{
	t_ast	*ast;
	t_cmd	*cmd;
	t_token	*new_token;
	t_redir	*redir;
	t_redir	*tmp_redir;
	t_arg	*arg;
	t_arg	*tmp_arg;

	arg = malloc(sizeof(*arg));
	if (!arg)
		return (NULL);
	arg->str = NULL;
	arg->next = NULL;
	tmp_arg = arg;
	new_token = token->next;
	while (new_token != NULL && new_token != stop)
	{
		if (new_token->type == WORD)
		{
			if (add_arg(tmp_arg, new_token->value))
			{
				free_all_cmd();
				return (NULL);
			}
			else
				tmp_arg = tmp_arg->next;
		}
		else if (new_token->type == IN || new_token->type == OUT || new_token->type == HEREDOC || new_token->type == APPEND)
		{

		}
		new_token = new_token->next;
	}
	if (cmd->args == NULL && cmd->redir->type == NONE)
		free_cmd(cmd);
	ast = init_ast(CMD, cmd, NULL, NULL);
	return (ast);
}
