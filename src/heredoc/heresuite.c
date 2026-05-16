/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heresuite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 10:50:44 by julauren          #+#    #+#             */
/*   Updated: 2026/05/16 11:33:41 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

static char	*check_key(char *key, t_env *envc)
{
	t_env	*tmp;
	char	*str;

	tmp = envc->next;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
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
	str[0] = '\0';
	return (str);
}

char	*check_env(char *value, t_env *envc, int i, int *j)
{
	char	*key;
	char	*new_value;

	while (ft_isalnum(value[*j]) || value[*j] == '_')
		(*j)++;
	key = ft_substr(value, i, *j - i);
	if (!key)
		return (NULL);
	new_value = check_key(key, envc);
	free(key);
	if (!new_value)
		return (NULL);
	return (new_value);
}

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
