/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:16 by julauren          #+#    #+#             */
/*   Updated: 2026/03/26 16:43:32 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static t_error	expander(char *value, t_env *envc)
{
	return (0);
}

int	expand(t_token *token_list, t_env *envc)
{
	t_token	*tmp;
	t_error	error;

	tmp = token_list->next;
	while (tmp != NULL)
	{
		if (tmp->type == EXPAND)
		{
			error = expander(tmp->value, envc);
			if (error)
			{
				exit_parser(token_list, envc, error);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
