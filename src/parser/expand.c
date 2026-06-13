/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:16 by julauren          #+#    #+#             */
/*   Updated: 2026/06/13 10:42:01 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	change_value(char **value, char *new_value, int start, int end)
{
	char	*str;
	int		len;
	int		tmp;

	tmp = ft_strlen(new_value);
	len = ft_strlen(*value) - (end - start + 1) + tmp;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
	{
		free(new_value);
		return (1);
	}
	ft_strlcpy(str, *value, start);
	ft_strlcat(str, new_value, len + 1);
	ft_strlcat(str, &(*value)[end], len + 1);
	free(*value);
	*value = str;
	return (0);
}

char	*check_new_value(char *value, t_env *envc, t_index *index, int status)
{
	char	*new_value;

	new_value = NULL;
	if (value[(*index).i] == '?')
		new_value = ft_itoa(status);
	else if ((value[(*index).i] == '_' && (ft_isspace(value[(*index).j])
				|| value[(*index).j] == '\0'))
		|| (!ft_isalpha(value[(*index).i]) && value[(*index).i] != '_'))
	{
		new_value = malloc(sizeof(*new_value));
		if (!new_value)
			return (NULL);
		new_value[0] = '\0';
	}
	else if (ft_isalpha(value[(*index).i]) || value[(*index).i] == '_')
		new_value = check_env(value, envc, (*index).i, &(index->j));
	return (new_value);
}

static	int	next_expander(t_token *token, t_env *envc, t_index *index, \
int status)
{
	char	*new_value;
	int		len;

	if (token->value[index->i] == '"' || token->value[index->i] == '\'')
		return (0);
	new_value = check_new_value(token->value, envc, index, status);
	if (!new_value
		|| change_value(&token->value, new_value, index->i, index->j))
		return (1);
	len = ft_strlen(new_value);
	free(new_value);
	index->i = index->i + len - 1;
	return (0);
}

static int	expander(t_token *token, t_env *envc, int status)
{
	t_index	index;
	t_state	state;

	index.i = 0;
	state = NORMAL;
	while (token->value[index.i] != '\0')
	{
		state_condition(token->value[index.i], &state);
		if (state != SIMPLE_QUOTE && token->value[index.i] == '$')
		{
			(index.i)++;
			if (token->value[index.i] == '\0')
				return (0);
			if (ft_isspace(token->value[index.i]))
				continue ;
			index.j = index.i + 1;
			if (next_expander(token, envc, &index, status))
				return (1);
			if (state == NORMAL)
				token->type = EXPAND;
		}
		else
			(index.i)++;
	}
	return (0);
}

int	expand(t_token *token_list, t_env *envc, int status)
{
	t_token	*tmp;

	tmp = token_list->next;
	while (tmp != NULL)
	{
		if (tmp->type == HEREDOC && tmp->next)
			tmp = tmp->next;
		else if ((tmp->type == WORD) && (expander(tmp, envc, status)
				|| (tmp->type == EXPAND && more_token(&tmp))))
		{
			error_parser(token_list, MALLOC);
			return (1);
		}
		tmp = tmp->next;
	}
	delete_quotes(token_list);
	if (token_list->next == NULL)
	{
		free_token(token_list);
		return (1);
	}
	return (0);
}
