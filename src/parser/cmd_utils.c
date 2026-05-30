/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 15:39:34 by julauren          #+#    #+#             */
/*   Updated: 2026/05/30 09:30:04 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	add_redir(t_redir **redir, t_token **token)
{
	t_redir	*new_redir;

	new_redir = malloc (sizeof(*new_redir));
	if (!new_redir)
		return (1);
	new_redir->next = NULL;
	if (!(*redir))
		*redir = new_redir;
	else
		(*redir)->next = new_redir;
	new_redir->type = (*token)->type;
	if ((*token)->next && (*token)->next->type == WORD)
	{
		new_redir->file = (*token)->next->value;
		*token = (*token)->next;
	}
	else
		new_redir->file = NULL;
	return (0);
}

int	add_arg(t_arg **arg, char *str)
{
	t_arg	*new_arg;
	t_arg	*tmp;

	new_arg = malloc(sizeof(*new_arg));
	if (!new_arg)
		return (1);
	new_arg->str = str;
	new_arg->next = NULL;
	if (!(*arg))
		*arg = new_arg;
	else
	{
		tmp = *arg;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_arg;
	}
	return (0);
}

void	free_struct(t_arg *arg, t_redir *redir)
{
	t_arg	*tmp_arg;
	t_redir	*tmp_redir;

	while (arg != NULL)
	{
		tmp_arg = arg->next;
		free(arg);
		arg = tmp_arg;
	}
	while (redir != NULL)
	{
		tmp_redir = redir->next;
		free(redir);
		redir = tmp_redir;
	}
}
