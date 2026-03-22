/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 09:30:19 by julauren          #+#    #+#             */
/*   Updated: 2026/03/22 10:17:16 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int	quote_condition(char c, t_state state)
{
	if ((c == '\'' && state == SIMPLE_QUOTE)
		|| (c == '"' && state == DOUBLE_QUOTE))
		return (1);
	return (0);
}

static int	strlen(char *str, t_state state)
{
	int	len;

	len = 0;
	while (str[len] && !quote_condition(str[len], state))
		len++;
	if ((state == SIMPLE_QUOTE && str[len] != '\'')
		|| (state == DOUBLE_QUOTE && str[len] != '"'))
		len = -1;
	return (len);
}

int	quote_token(char *str, t_token *token_list, int *i, t_state state)
{
	int		len;
	int		j;
	char	*value;
	t_type	type;

	(*i)++;
	len = strlen(&str[*i], state);
	if (len == -1)
		return (1);
	value = malloc(sizeof(*value) * (len + 1));
	if (!value)
		return (1);
	j = 0;
	while (!quote_condition(str[*i], state))
		value[j++] = str[(*i)++];
	value[j] = '\0';
	if (state == SIMPLE_QUOTE)
		type = WORD;
	else
		type = EXPAND;
	if (add_after(token_list, type, value))
		return (1);
	return (0);
}
