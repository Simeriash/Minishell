/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:06:30 by julauren          #+#    #+#             */
/*   Updated: 2026/05/14 11:14:25 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static char	**struct_to_tab(t_arg *arg, int i)
{
	char	**tab;
	int		j;
	t_arg	*tmp;

	tab = malloc(sizeof(*tab) * (i + 1));
	if (!tab)
		return (NULL);
	tmp = arg;
	j = 0;
	while (tmp != NULL)
	{
		tab[j] = tmp->str;
		tmp = tmp->next;
		j++;
	}
	tab[j] = NULL;
	free_struct(arg, NULL);
	return (tab);
}

static int	cmd_struct(t_cmd *cmd, t_arg *arg, t_redir *redir)
{
	int		i;
	t_arg	*tmp;

	cmd->redir = redir;
	if (!arg)
	{
		cmd->args = NULL;
		return (0);
	}
	i = 1;
	tmp = arg;
	while (tmp->next != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	cmd->args = struct_to_tab(arg, i);
	if (!(cmd->args))
	{
		free_struct(arg, redir);
		free(cmd);
		return (1);
	}
	return (0);
}

static int	loop(t_token **token, t_arg **arg, t_redir **redir)
{
	if ((*token)->type == WORD)
	{
		if (add_arg(arg, (*token)->value))
		{
			free_struct(*arg, *redir);
			return (1);
		}
	}
	else if ((*token)->type == IN || (*token)->type == OUT
		|| (*token)->type == HEREDOC || (*token)->type == APPEND)
	{
		if (add_redir(redir, token))
		{
			free_struct(*arg, *redir);
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
	cmd = malloc(sizeof(*cmd));
	if (!cmd)
	{
		free_struct(arg, redir);
		return (NULL);
	}
	if (cmd_struct(cmd, arg, redir))
		return (NULL);
	ast = init_ast(CMD, cmd, NULL, NULL);
	return (ast);
}
