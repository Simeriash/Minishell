/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:38:57 by julauren          #+#    #+#             */
/*   Updated: 2026/04/14 12:43:47 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static t_ret	lexer_next3(t_token **last, char *s)
{
	if (add_after(*last, WORD, s))
	{
		error_lexer(MALLOC);
		return (NUL);
	}
	*last = (*last)->next;
	return (0);
}

static t_ret	lexer_next2(char *str, char **s, int *i, int start)
{
	t_state	state;

	state = NORMAL;
	while (str[*i] != '\0' && ((state == NORMAL && !end_condition(str[*i]))
			|| state == SIMPLE_QUOTE || state == DOUBLE_QUOTE))
		state_condition(str[(*i)++], &state);
	if (state != NORMAL)
	{
		error_lexer(OPEN_QUOTE);
		return (NUL);
	}
	*s = ft_substr(str, start, *i - start);
	if (!(*s))
	{
		error_lexer(MALLOC);
		return (NUL);
	}
	if (((*s)[0] == '\'' && (*s)[1] == '\'')
		|| ((*s)[0] == '"' && (*s)[1] == '"'))
	{
		free(*s);
		return (CONTINUE);
	}
	return (0);
}

static t_ret	lexer_next(char *str, t_token **last, int *i)
{
	t_error	error;
	t_ret	ret;
	char	*s;
	int		start;

	start = *i;
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|' || str[*i] == '&'
		|| str[*i] == '(' || str[*i] == ')' || str[*i] == '\n')
	{
		error = meta_token(str, *last, i);
		if (error)
		{
			error_lexer(error);
			return (NUL);
		}
		*last = (*last)->next;
		return (CONTINUE);
	}
	ret = lexer_next2(str, &s, i, start);
	if (ret != 0)
		return (ret);
	ret = lexer_next3(last, s);
	return (ret);
}

t_token	*lexer(char *str)
{
	int		i;
	t_ret	ret;
	t_token	*token_list;
	t_token	*last;

	token_list = init_token_list();
	if (!token_list)
		return (NULL);
	i = 0;
	last = token_list;
	while (str[i] != '\0')
	{
		shell_space(str, &i);
		if (str[i] == '\0')
			break ;
		ret = lexer_next(str, &last, &i);
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
