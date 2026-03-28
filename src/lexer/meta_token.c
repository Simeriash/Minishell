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

t_error	meta_token(char *str, t_token *token, int *i)
{
	t_type	type;

	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
		search_type(str, i, &type);
	else if (str[*i] == '&')
	{
		if (str[*i + 1] == '&')
			type = AND;
		else
			return (AMPERSAND);
	}
	else if (str[*i] == '(')
		type = LEFT_PARENTHESIS;
	else if (str[*i] == ')')
		type = RIGHT_PARENTHESIS;
	else
		type = RET;
	if (add_after(token, type, NULL))
		return (MALLOC);
	(*i)++;
	if (type == HEREDOC || type == APPEND || type == OR || type == AND)
		(*i)++;
	return (0);
}
