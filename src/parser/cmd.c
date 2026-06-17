/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:06:30 by julauren          #+#    #+#             */
/*   Updated: 2026/06/17 14:20:25 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static char	**struct_to_tab(t_arg *arg)
{
	char	**tab;
	int		i;
	t_arg	*tmp;

	i = 1;
	tmp = arg;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(*tab) * (i + 1));
	if (!tab)
		return (NULL);
	tmp = arg;
	i = 0;
	while (tmp != NULL)
	{
		tab[i] = tmp->str;
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	free_struct(arg, NULL, NULL);
	return (tab);
}

static t_cmd	*cmd_struct(t_arg *arg, t_redir *redir)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	if (!cmd)
	{
		free_struct(arg, redir, NULL);
		return (NULL);
	}
	cmd->redir = redir;
	if (!arg)
	{
		cmd->args = NULL;
		return (cmd);
	}
	cmd->args = struct_to_tab(arg);
	if (!(cmd->args))
	{
		free_struct(arg, redir, cmd);
		return (NULL);
	}
	return (cmd);
}

static int	loop(t_token **token, t_arg **arg, t_redir **redir)
{
	if ((*token)->type == WORD || (*token)->type == EXPAND)
	{
		if (add_arg(arg, (*token)->value))
		{
			free_struct(*arg, *redir, NULL);
			return (1);
		}
	}
	else if ((*token)->type == IN || (*token)->type == OUT
		|| (*token)->type == HEREDOC || (*token)->type == APPEND)
	{
		if (add_redir(redir, token))
		{
			free_struct(*arg, *redir, NULL);
			return (1);
		}
	}
	return (0);
}

t_ast	*cmd_node(t_token *token, t_token *stop)
{
	t_ast	*ast;
	t_cmd	*cmd;
	t_token	*new_token;
	t_redir	*redir;
	t_arg	*arg;

	arg = NULL;
	redir = NULL;
	new_token = token->next;
	while (new_token != NULL && new_token != stop)
	{
		if (loop(&new_token, &arg, &redir))
			return (NULL);
		new_token = new_token->next;
	}
	cmd = cmd_struct(arg, redir);
	if (!cmd)
		return (NULL);
	ast = init_ast(CMD, cmd, NULL, NULL);
	return (ast);
}
