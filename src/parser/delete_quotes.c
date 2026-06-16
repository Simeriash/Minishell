/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:58:22 by julauren          #+#    #+#             */
/*   Updated: 2026/06/16 09:51:16 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static t_ret	state_normal(t_token *token, t_state *state, int *i, int *j)
{
	if (*state == NORMAL && *j != *i)
	{
		while (*state == NORMAL && token->value[*j] != '\0')
		{
			token->value[(*i)++] = token->value[(*j)++];
			state_condition(token->value[*j], state);
		}
		if (token->value[*j] == '\0')
		{
			token->value[*i] = token->value[*j];
			return (BREAK);
		}
		*state = NORMAL;
		return (CONTINUE);
	}
	return (0);
}

static t_ret	state_quote(t_token *token, t_state *state, int *i, int *j)
{
	if (*state != NORMAL)
	{
		(*j)++;
		if ((*state == SIMPLE_QUOTE && token->value[*j] == '\'')
			|| (*state == DOUBLE_QUOTE && token->value[*j] == '"'))
		{
			(*j)++;
			*state = NORMAL;
			return (CONTINUE);
		}
		while (*state != NORMAL && token->value[*j] != '\0')
		{
			token->value[(*i)++] = token->value[(*j)++];
			state_condition(token->value[*j], state);
		}
		if (token->value[*j] == '\0' || token->value[++(*j)] == '\0')
		{
			token->value[*i] = token->value[*j];
			return (BREAK);
		}
		return (CONTINUE);
	}
	return (0);
}

static void	next_delete(t_token *token, t_state *state, int *i, int *j)
{
	t_ret	ret;

	while (token->value[*i] != '\0')
	{
		state_condition(token->value[*j], state);
		ret = state_quote(token, state, i, j);
		if (ret == BREAK)
			break ;
		if (ret == CONTINUE)
			continue ;
		ret = state_normal(token, state, i, j);
		if (ret == BREAK)
			break ;
		if (ret == CONTINUE)
			continue ;
		(*i)++;
		(*j)++;
	}
}

void	delete_quotes(t_token *token_list)
{
	int		i;
	int		j;
	t_state	state;
	t_token	*tmp;

	tmp = token_list->next;
	state = NORMAL;
	while (tmp != NULL)
	{
		i = 0;
		j = 0;
		if (tmp->type == HEREDOC)
		{
			tmp = tmp->next;
			if (!tmp)
				break ;
		}
		else if (tmp->type == WORD)
			next_delete(tmp, &state, &i, &j);
		tmp = tmp->next;
	}
}
