/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:19:55 by julauren          #+#    #+#             */
/*   Updated: 2026/04/13 09:54:14 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int	state_condition(char *str, int *i, t_state *state)
{
	while (shell_space(str[*i]))
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

static int	normal_state(char *str, t_token **token, int *i)
{
	t_error	error;

	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|' || str[*i] == '&'
		|| str[*i] == '(' || str[*i] == ')' || str[*i] == '\n')
	{
		error = meta_token(str, *token, i);
		if (error)
		{
			error_lexer(error);
			return (1);
		}
	}
	else
	{
		error = word_token(str, *token, i);
		if (error)
		{
			error_lexer(error);
			return (1);
		}
	}
	return (0);
}

static int	quote_state(char *str, t_token **token, int *i, t_state state)
{
	t_error	error;

	error = quote_token(str, *token, i, state);
	if (error)
	{
		error_lexer(error);
		return (1);
	}
	(*i)++;
	return (0);
}

static t_ret	lex_next(char *str, t_token *token_list, int *i, t_state *state)
{
	static t_token	*last;

	if (!last || (*i == 0 && last))
		last = token_list;
	if (state_condition(str, i, state))
		return (BREAK);
	if (*state == NORMAL)
	{
		if (normal_state(str, &last, i))
			return (NUL);
	}
	else if (quote_state(str, &last, i, *state))
		return (NUL);
	if (*state != NORMAL)
		*state = NORMAL;
	last = last->next;
	return (0);
}

t_token	*lexer(char *str)
{
	int		i;
	t_ret	ret;
	t_state	state;
	t_token	*token_list;

	token_list = init_token_list();
	if (!token_list)
		return (NULL);
	i = 0;
	state = NORMAL;
	while (str[i] != '\0')
	{
		ret = lex_next(str, token_list, &i, &state);
		if (ret == BREAK)
			break ;
		if (ret == NUL)
		{
			free_token(token_list);
			return (NULL);
		}
	}
	return (token_list);
}
