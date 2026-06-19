/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:01:29 by julauren          #+#    #+#             */
/*   Updated: 2026/06/19 13:43:16 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	second_step(t_token **token, char *old_value, t_index *index, int i)
{
	char	*tmp;

	while (index->i < index->j && !ft_isspace(old_value[index->i]))
		(index->i)++;
	if (index->i == index->j)
	{
		ft_memcpy_exp((*token)->value, index, 1);
		(index->i)++;
		return (0);
	}
	tmp = ft_substr(old_value, i, index->i - i);
	if (!tmp)
		return (1);
	(*token)->value = tmp;
	(*token)->type = WORD;
	(index->i)++;
	tmp = ft_substr(old_value, index->i - 1, ft_strlen(old_value));
	free(old_value);
	if (!tmp)
		return (1);
	if (add_after(*token, WORD, tmp))
	{
		free(tmp);
		return (1);
	}
	index->j = index->j - index->i + 1;
	index->i = 0;
	return (-1);
}

static void	first_step(t_token **token, t_index *index)
{
	int	delta;

	delta = index->i;
	while (delta != index->j && ft_isspace((*token)->value[delta]))
		(delta)++;
	delta = delta - index->i + 1;
	(index->i)--;
	ft_memcpy_exp((*token)->value, index, delta);
	(index->i)++;
	index->j = index->j - delta;
}

static int	quote_mode(t_token **token, t_index *index)
{
	index->i -= 2;
	ft_memcpy_exp((*token)->value, index, 2);
	index->i += 1;
	while ((*token)->value[index->i] != '"')
		(index->i)++;
	ft_memcpy_exp((*token)->value, index, 2);
	return (0);
}

int	more_token(t_token **token, t_index *index, t_state state)
{
	char	*old_value;
	int		ret;
	int		i;

	// printf("%c\n", (*token)->value[(index->i)]);
	if ((*token)->value[(index->i) - 1] != '"')
		return (0);
	if (state == DOUBLE_QUOTE)
	{
		ret = quote_mode(token, index);
		return (ret);
	}
	first_step(token, index);
	while (*token && (*token)->value[index->i] != '\0')
	{
		i = 0;
		while (ft_isspace((*token)->value[i]) && i <= index->j)
			(i)++;
		index->i += i;
		if ((*token)->value[index->i] == '"')
			break ;
		old_value = (*token)->value;
		ret = second_step(token, old_value, index, i);
		if (ret >= 0)
			return (ret);
		*token = (*token)->next;
		(*token)->type = EXPAND;
	}
	if ((*token)->value[index->i + 1] == '\0')
		(*token)->value[0] = '\0';
	else
	{
		i = index->i;
		// index->i = 1;
		ft_memcpy_exp((*token)->value, index, i);
		index->i = 1;
	}
	return (0);
}
