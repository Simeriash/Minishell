/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 14:44:43 by julauren          #+#    #+#             */
/*   Updated: 2026/03/21 15:45:17 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

static int	end_condition(char c)
{
	if (c == '\0' || c == ' ' || c == '<' || c == '>' || c == '|' || c == '&'
		|| c == '(' || c == ')')
		return (1);
	return (0);
}

static int	strlen(char *str, int i)
{
	int	len;

	len = 0;
	while (!end_condition(str[i]))
	{
		len++;
		i++;
	}
	return (len);
}

int	create_token_word(char *str, t_token *token_list, int *i, int *nb_token)
{
	int		len;
	int		j;
	char	*value;

	len = strlen(str, *i);
	value = malloc(sizeof(*value) * (len + 1));
	if (!value)
	{
		*nb_token = -1;
		return (1);
	}
	j = 0;
	while (!end_condition(str[*i]))
	{
		value[j] = str[*i];
		j++;
		(*i)++;
	}
	value[j] = '\0';
	if (add_after(token_list, WORD, value))
	{
		*nb_token = -1;
		return (1);
	}
	(*nb_token)++;
	return (0);
}
