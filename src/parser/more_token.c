/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:01:29 by julauren          #+#    #+#             */
/*   Updated: 2026/04/16 11:48:18 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	second_step(t_token **token, char *old_value, int *i)
{
	char	*tmp;

	tmp = ft_substr(old_value, 0, *i);
	if (!tmp)
		return (1);
	(*token)->value = tmp;
	(*i)++;
	while ((*token)->value[*i] != '\0' && ft_isspace((*token)->value[*i]))
		i++;
	if ((*token)->value[*i] == '\0')
	{
		free(old_value);
		return (0);
	}
	tmp = ft_substr(old_value, *i, ft_strlen(old_value));
	free(old_value);
	if (!tmp)
		return (1);
	if (add_after(*token, WORD, tmp))
	{
		free(tmp);
		return (1);
	}
	return (-1);
}

static int	first_step(t_token **token, t_state *state, int *i)
{
	state_condition((*token)->value[*i], state);
	while ((*token)->value[*i] != '\0' && *state == NORMAL
		&& !ft_isspace((*token)->value[*i]))
		state_condition((*token)->value[++(*i)], state);
	if ((*token)->value[*i] == '\0')
		return (1);
	return (0);
}

int	more_token(t_token **token)
{
	int		i;
	int		ret;
	t_state	state;
	char	*old_value;

	i = 0;
	state = NORMAL;
	while ((*token)->value[i] != '\0')
	{
		old_value = (*token)->value;
		if (first_step(token, &state, &i))
			return (0);
		if (state == NORMAL && ft_isspace((*token)->value[i]))
		{
			ret = second_step(token, old_value, &i);
			if (ret >= 0)
				return (ret);
			*token = (*token)->next;
			i = 0;
		}
		else
			i++;
	}
	return (0);
}
