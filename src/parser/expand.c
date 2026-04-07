/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:16 by julauren          #+#    #+#             */
/*   Updated: 2026/04/07 13:32:43 by julauren         ###   ########.fr       */
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
	free(new_value);
	free(token->value);
	token->value = str;
	return (0);
}

static char	*check_key(char *key, t_env *envc)
{
	t_env	*tmp;
	char	*str;

	tmp = envc->next;
	while (tmp != NULL)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
		{
			str = ft_strdup(tmp->value);
			if (!str)
				return (NULL);
			return (str);
		}
		tmp = tmp->next;
	}
	str = malloc(sizeof(*str));
	if (!str)
		return (NULL);
	str = "";
	return (str);
}

static t_error	expander(t_token *token, t_env *envc)
{
	int		i;
	int		j;
	char	*key;
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
			if (token->value[i] == '?')
			{
				// new_value = retour du status de la dernière cmd;
			}
			else if ((token->value[i] == '_' && (ft_isspace(token->value[j])
						|| token->value[j] == '\0'))
				|| (!ft_isalpha(token->value[i]) && token->value[i] != '_'))
			{
				new_value = malloc(sizeof(*new_value));
				if (!new_value)
					return (MALLOC);
				new_value = "";
			}
			else if (ft_isalpha(token->value[i])
				|| token->value[i] == '_')
			{
				while (ft_isalnum(token->value[j]) || token->value[j] == '_')
					j++;
				key = ft_substr(token->value, i, j - i);
				if (!key)
					return (MALLOC);
				new_value = check_key(key, envc);
				free(key);
				if (!new_value)
					return (MALLOC);
			}
			if (new_value && change_value(token, new_value, i, j))
				return (MALLOC);
		}
		i++;
	}
	return (0);
}

int	expand(t_token *token_list, t_env *envc)
{
	t_token	*tmp;
	t_error	error;

	tmp = token_list->next;
	while (tmp != NULL)
	{
		if (tmp->type == EXPAND)
		{
			error = expander(tmp, envc);
			if (error)
			{
				error_parser(token_list, envc, error);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
