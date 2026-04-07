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

	len = 1;
	while (str[len] && !quote_condition(str[len], state))
		len++;
	if ((state == SIMPLE_QUOTE && str[len] != '\'')
		|| (state == DOUBLE_QUOTE && str[len] != '"'))
		return (-1);
	len++;
	return (len);
}

static void	type_condition(char *value, t_type *type, t_state state)
{
	int	i;

	i = 0;
	if (state == SIMPLE_QUOTE)
	{
		*type = WORD;
		return ;
	}
	else
	{
		while (value[i] != '\0')
		{
			if (value[i] == '$')
			{
				*type = EXPAND;
				return ;
			}
			i++;
		}
		*type = WORD;
	}
}

t_error	quote_token(char *str, t_token *token, int *i, t_state state)
{
	int		len;
	int		j;
	char	*value;
	t_type	type;

	len = strlen(&str[*i], state);
	if (len == 0)
		return (0);
	if (len == -1)
		return (OPEN_QUOTE);
	value = malloc(sizeof(*value) * (len + 1));
	if (!value)
		return (MALLOC);
	j = 0;
	value[j++] = str[(*i)++];
	while (!quote_condition(str[*i], state))
		value[j++] = str[(*i)++];
	value[j++] = str[(*i)];
	value[j] = '\0';
	type_condition(value, &type, state);
	if (add_after(token, type, value))
		return (MALLOC);
	return (0);
}
