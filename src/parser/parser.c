/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:01:42 by julauren          #+#    #+#             */
/*   Updated: 2026/04/07 16:37:10 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	parenthesis_control(t_token *token_list, t_env *envc)
{
	t_token	*tmp;
	int		l_p;
	int		r_p;

	l_p = 0;
	r_p = 0;
	tmp = token_list->next;
	while (!tmp)
	{
		if (tmp->type == LEFT_PARENTHESIS)
			l_p++;
		if (tmp->type == RIGHT_PARENTHESIS)
			r_p++;
		tmp = tmp->next;
	}
	if (l_p != r_p)
	{
		error_parser(token_list, envc, OPEN_PARENTHESIS);
		return (1);
	}
	return (0);
}

void	parser(t_token *token_list, t_env *envc)
{
	if (parenthesis_control(token_list, envc) && expand(token_list, envc))
		return ;
}
