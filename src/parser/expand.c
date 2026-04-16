/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:16 by julauren          #+#    #+#             */
/*   Updated: 2026/04/16 10:55:59 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	change_value(t_token *token, char *new_value, int start, int end)
{
	char	*str;
	int		len;
	int		tmp;

	tmp = ft_strlen(new_value);
	len = ft_strlen(token->value) - (end - start + 1) + tmp;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
	{
		free(new_value);
		return (1);
	}
	ft_strlcpy(str, token->value, start);
	ft_strlcat(str, new_value, len + 1);
	ft_strlcat(str, &token->value[end], len + 1);
	free(token->value);
	token->value = str;
	return (0);
}

static char	*check_new_value(t_token *token, t_env *envc, int i, int *j)
{
	char	*new_value;

	if (token->value[i] == '?')
	{
		// new_value = retour du status de la dernière cmd;
	}
	else if ((token->value[i] == '_' && (ft_isspace(token->value[*j])
				|| token->value[*j] == '\0'))
		|| (!ft_isalpha(token->value[i]) && token->value[i] != '_'))
	{
		new_value = malloc(sizeof(*new_value));
		if (!new_value)
			return (NULL);
		new_value = "";
	}
	else if (ft_isalpha(token->value[i]) || token->value[i] == '_')
	{
		new_value = check_env(token, envc, i, j);
		if (!new_value)
			return (NULL);
	}
	return (new_value);
}

static	int	next_expander(t_token *token, t_env *envc, int *i, int *j)
{
	char	*new_value;
	int		len;

	new_value = check_new_value(token, envc, *i, j);
	if (!new_value || change_value(token, new_value, *i, *j))
		return (1);
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
			if (expander(tmp, envc) || more_token(&tmp))
			{
				error_parser(token_list, envc, MALLOC);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
