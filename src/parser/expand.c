/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:16 by julauren          #+#    #+#             */
/*   Updated: 2026/05/16 10:15:58 by julauren         ###   ########.fr       */
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

char	*check_new_value(char *value, t_env *envc, int i, int *j)
{
	char	*new_value;

	new_value = NULL;
	if (value[i] == '?')
	{
		// new_value = retour du status de la dernière cmd;
	}
	else if ((value[i] == '_' && (ft_isspace(value[*j])
				|| value[*j] == '\0'))
		|| (!ft_isalpha(value[i]) && value[i] != '_'))
	{
		new_value = malloc(sizeof(*new_value));
		if (!new_value)
			return (NULL);
		new_value[0] = '\0';
	}
	else if (ft_isalpha(value[i]) || value[i] == '_')
	{
		new_value = check_env(value, envc, i, j);
		if (!new_value)
			return (NULL);
	}
	return (new_value);
}

static	int	next_expander(t_token *token, t_env *envc, int *i, int *j)
{
	char	*new_value;
	int		len;

	new_value = check_new_value(token->value, envc, *i, j);
	if (new_value && change_value(&token->value, new_value, *i, *j))
		return (1);
	token->type = EXPAND;
	len = ft_strlen(new_value);
	free(new_value);
	*i = *i + len - 1;
	return (0);
}

static int	expander(t_token *token, t_env *envc)
{
	int		i;
	int		j;
	t_state	state;

	i = 0;
	state = NORMAL;
	while (token->value[i] != '\0')
	{
		state_condition(token->value[i], &state);
		if (state != SIMPLE_QUOTE && token->value[i] == '$')
		{
			i++;
			if (token->value[i] == '\0')
				return (0);
			if (ft_isspace(token->value[i]))
				continue ;
			j = i + 1;
			if (next_expander(token, envc, &i, &j))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	expand(t_token *token_list, t_env *envc)
{
	t_token	*tmp;

	tmp = token_list->next;
	while (tmp != NULL)
	{
		if (tmp->type == WORD)
		{
			if (expander(tmp, envc)
				|| (tmp->type == EXPAND && more_token(&tmp)))
			{
				error_parser(token_list, MALLOC);
				return (1);
			}
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
