/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:37:57 by julauren          #+#    #+#             */
/*   Updated: 2026/06/12 17:00:31 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	shell_space(char *str, int *i)
{
	while (str[*i] == 9 || (str[*i] >= 11 && str[*i] <= 13) || str[*i] == 32)
	{
		if (str[*i] == '\'' || str[*i] == '"')
			return ;
		(*i)++;
	}
}

int	end_condition(char *str, int *i)
{
	if (str[*i] == '\0' || ft_isspace(str[*i]) || str[*i] == '<'
		|| str[*i] == '>')
		return (1);
	// if (str[*i] == '|' && str[*i + 1] == '|')
	// {
	// 	(*i)++;
	// 	return (0);
	// }
	// if (str[*i] == '|' && str[*i + 1] != '|')
	// 	return (1);
	if (str[*i] == '|')
		return (1);
	return (0);
}

void	state_condition(char c, t_state *state)
{
	if (c == '\'' && *state == NORMAL)
		*state = SIMPLE_QUOTE;
	else if (c == '\'' && *state == SIMPLE_QUOTE)
		*state = NORMAL;
	else if (c == '"' && *state == NORMAL)
		*state = DOUBLE_QUOTE;
	else if (c == '"' && *state == DOUBLE_QUOTE)
		*state = NORMAL;
}

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
		*type = PIPE;
}

t_error	meta_token(char *str, t_token *token, int *i)
{
	t_type	type;

	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
		search_type(str, i, &type);
	else
		type = RET;
	if (add_after(token, type, NULL))
		return (MALLOC);
	(*i)++;
	if (type == HEREDOC || type == APPEND)
		(*i)++;
	return (0);
}
