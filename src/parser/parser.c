/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:01:42 by julauren          #+#    #+#             */
/*   Updated: 2026/05/05 15:01:18 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	check_parenthesis(t_token *token_list, t_env *envc, int *count)
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
		else if (tmp->type == RIGHT_PARENTHESIS)
			r_p++;
		if (l_p < r_p)
			break ;
		tmp = tmp->next;
	}
	*count = l_p;
	if (l_p != r_p)
	{
		error_parser(token_list, envc, OPEN_PARENTHESIS);
		return (1);
	}
	return (0);
}

t_ast	*parser(t_token *token_list, t_env *envc)
{
	t_ast	*ast;
	int		count;

	if (check_parenthesis(token_list, envc, &count) && expand(token_list, envc))
		return (NULL);
	if (count == 0)
		ast = ast_creation(token_list, NULL, OR);
	else
		ast = create_ast(token_list, NULL);
	if (!ast)
	{
		error_parser(token_list, envc, MALLOC);
		return (NULL);
	}
	return (ast);
}
