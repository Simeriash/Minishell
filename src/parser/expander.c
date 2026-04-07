/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:46:10 by julauren          #+#    #+#             */
/*   Updated: 2026/04/07 17:40:38 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static char	*check_env(t_token *token, t_env *envc, int *i, int *j)
{
	char	*key;
	char	*new_value;

	while (ft_isalnum(token->value[*j]) || token->value[*j] == '_')
		(*j)++;
	key = ft_substr(token->value, *i, *j - *i);
	if (!key)
		return (NULL);
	new_value = check_key(key, envc);
	free(key);
	if (!new_value)
		return (NULL);
	return (new_value);
}

static char	*check_new_value(t_token *token, t_env *envc, int *i, int *j)
{
	char	*new_value;

	if (token->value[*i] == '?')
	{
		// new_value = retour du status de la dernière cmd;
	}
	else if ((token->value[*i] == '_' && (ft_isspace(token->value[*j])
				|| token->value[*j] == '\0'))
		|| (!ft_isalpha(token->value[*i]) && token->value[*i] != '_'))
	{
		new_value = malloc(sizeof(*new_value));
		if (!new_value)
			return (NULL);
		new_value = "";
	}
	else if (ft_isalpha(token->value[*i]) || token->value[*i] == '_')
	{
		new_value = check_env(token, envc, i, j);
		if (!new_value)
			return (NULL);
	}
	return (new_value);
}

t_error	expander(t_token *token, t_env *envc)
{
	int		i;
	int		j;
	char	*new_value;

	i = 0;
	while (token->value[i] != '\0')
	{
		new_value = NULL;
		if (token->value[i] == '$')
		{
			i++;
			if (token->value[i] == '\0')
				return (0);
			if (ft_isspace(token->value[i]))
				continue ;
			j = i + 1;
			new_value = check_new_value(token, envc, &i, &j);
			if (!new_value && change_value(token, new_value, i, j))
				return (MALLOC);
		}
		i++;
	}
	return (0);
}
