/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:19:55 by julauren          #+#    #+#             */
/*   Updated: 2026/03/22 13:21:27 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	exit_lexer(char *str, t_token *token_list)
{
	free(str);
	if (token_list)
		free_token(token_list);
	exit(EXIT_FAILURE);
}

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

static void	normal_state(char *str, t_token *token_list, int *i)
{
	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|' || str[*i] == '&'
		|| str[*i] == '(' || str[*i] == ')')
	{
		if (meta_token(str, token_list, i))
			exit_lexer(str, token_list);
	}
	else if (word_token(str, token_list, i))
		exit_lexer(str, token_list);
}

static void	quote_state(char *str, t_token *token_list, int *i, t_state state)
{
	if ((state == SIMPLE_QUOTE || state == DOUBLE_QUOTE)
		&& quote_token(str, token_list, i, state))
		exit_lexer(str, token_list);
}

t_token	*lexer(char *str)
{
	int		i;
	t_state	state;
	t_token	*token_list;

	token_list = init_token_list(str);
	i = 0;
	state = NORMAL;
	while (str[i] != '\0')
	{
		if (state_condition(str, &i, &state))
			break ;
		if (state == NORMAL)
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				if (str[++i] == '\0')
					break ;
				continue ;
			}
			normal_state(str, token_list, &i);
		}
		else
			quote_state(str, token_list, &i, state);
	}
	return (token_list);
}
