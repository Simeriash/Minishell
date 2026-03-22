/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:56:58 by julauren          #+#    #+#             */
/*   Updated: 2026/03/21 14:22:58 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static void	search_type(char *str, int *i, t_type *type)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
			*type = HEREDOC;
		else
			*type = IN;
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
			*type = APPEND;
		else
			*type = OUT;
	}
	else if (str[*i] == '|')
	{
		if (str[*i + 1] == '|')
			*type = OR;
		else
			*type = PIPE;
	}
}

int	meta_token(char *str, t_token *token_list, int *i)
{
	t_type	type;

	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
		search_type(str, i, &type);
	else if (str[*i] == '&')
	{
		if (str[*i + 1] == '&')
			type = AND;
		else
			return (1);
	}
	else if (str[*i] == '(')
		type = LEFT_PARENTHESIS;
	else
		type = RIGHT_PARENTHESIS;
	if (add_after(token_list, type, NULL))
		return (1);
	(*i)++;
	if (type == HEREDOC || type == APPEND || type == OR || type == AND)
		(*i)++;
	return (0);
}
