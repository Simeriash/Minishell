/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:38:57 by julauren          #+#    #+#             */
/*   Updated: 2026/06/01 14:46:16 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int	looking_for_string(char *str, char **s, int *i)
{
	int		start;
	t_state	state;

	start = *i;
	state = NORMAL;
	while (str[*i] != '\0' && ((state == NORMAL && !end_condition(str, i))
			|| state == SIMPLE_QUOTE || state == DOUBLE_QUOTE))
		state_condition(str[(*i)++], &state);
	if (state != NORMAL)
	{
		error_lexer(OPEN_QUOTE);
		return (1);
	}
	*s = ft_substr(str, start, *i - start);
	if (!(*s))
	{
		error_lexer(MALLOC);
		return (1);
	}
	return (0);
}

static int	create_token(char *str, t_token **last, int *i)
{
	t_error	error;
	char	*s;

	if (str[*i] == '<' || str[*i] == '>' || (str[*i] == '|'
			&& str[*i + 1] != '|') || str[*i] == '\n')
	{
		error = meta_token(str, *last, i);
		if (error)
		{
			error_lexer(error);
			return (1);
		}
		*last = (*last)->next;
		return (0);
	}
	if (looking_for_string(str, &s, i))
		return (1);
	if (add_after(*last, WORD, s))
	{
		error_lexer(MALLOC);
		return (1);
	}
	*last = (*last)->next;
	return (0);
}

t_token	*lexer(char *str)
{
	int		i;
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
		if (create_token(str, &last, &i))
		{
			free_token(token_list);
			return (NULL);
		}
	}
	return (token_list);
}
