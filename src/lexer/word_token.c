/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_token.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 14:44:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/22 09:46:59 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int	end_condition(char c)
{
	if (c == '\0' || ft_isspace(c) || c == '<' || c == '>' || c == '|'
		|| c == '&' || c == '(' || c == ')' || c == '\'' || c == '"')
		return (1);
	return (0);
}

static int	strlen(char *str)
{
	int	len;

	len = 0;
	while (!end_condition(str[len]))
		len++;
	return (len);
}

t_error	word_token(char *str, t_token *token_list, int *i)
{
	int		len;
	int		j;
	char	*value;

	len = strlen(&str[*i]);
	value = malloc(sizeof(*value) * (len + 1));
	if (!value)
		return (MALLOC);
	j = 0;
	while (!end_condition(str[*i]))
		value[j++] = str[(*i)++];
	value[j] = '\0';
	if (add_after(token_list, WORD, value))
		return (MALLOC);
	return (0);
}
