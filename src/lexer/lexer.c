/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:19:55 by julauren          #+#    #+#             */
/*   Updated: 2026/03/25 18:19:59 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int	state_condition(char *str, int *i, t_state *state)
{
	while (ft_isspace(str[*i]))
		(*i)++;
	if (str[*i] == '\0')
		return (1);
	if (str[*i] == '\'' && *state == NORMAL)
		*state = SIMPLE_QUOTE;
	else if (str[*i] == '\'' && *state == SIMPLE_QUOTE)
		*state = NORMAL;
	else if (str[*i] == '"' && *state == NORMAL)
		*state = DOUBLE_QUOTE;
	else if (str[*i] == '"' && *state == DOUBLE_QUOTE)
		*state = NORMAL;
	return (0);
}

static int	normal_state(char *str, t_token *token_list, int *i)
{
	t_error	error;

	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|' || str[*i] == '&'
		|| str[*i] == '(' || str[*i] == ')')
	{
		error = meta_token(str, token_list, i);
		if (error)
		{
			exit_lexer(token_list, error);
			return (1);
		}
	}
	else
	{
		error = word_token(str, token_list, i);
		if (error)
		{
			exit_lexer(token_list, error);
			return (1);
		}
	}
	return (0);
}

static int	quote_state(char *str, t_token *token_list, int *i, t_state state)
{
	t_error	error;

	if (state == SIMPLE_QUOTE || state == DOUBLE_QUOTE)
	{
		error = quote_token(str, token_list, i, state);
		if (error)
		{
			exit_lexer(token_list, error);
			return (1);
		}
	}
	return (0);
}

static t_ret	lex_next(char *str, t_token *token_list, int *i, t_state *state)
{
	if (state_condition(str, i, state))
		return (BREAK);
	if (*state == NORMAL)
	{
		if (str[*i] == '\'' || str[*i] == '"')
		{
			if (str[++(*i)] == '\0')
				return (BREAK);
			return (0);
		}
		if (normal_state(str, token_list, i))
			return (NUL);
	}
	else if (quote_state(str, token_list, i, *state))
		return (NUL);
	return (0);
}

t_token	*lexer(char *str)
{
	int		i;
	t_ret	ret;
	t_state	state;
	t_token	*token_list;

	token_list = init_token_list();
	i = 0;
	state = NORMAL;
	while (str[i] != '\0')
	{
		ret = lex_next(str, token_list, &i, &state);
		if (ret == BREAK)
			break ;
		if (ret == NUL)
			return (NULL);
	}
	return (token_list);
}
