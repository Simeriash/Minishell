/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:29:14 by dlanehar          #+#    #+#             */
/*   Updated: 2026/04/03 11:03:57 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char *find_env_var(char *key, t_envpcpy **envpcpy)
{
	int	i;
	int	len;
	t_envpcpy *tmp;

	i = 0;
	if (!key)
		return (NULL);
	len = ft_strlen(key);
	tmp = *envpcpy;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0  && tmp->key[len] == '\0')
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_envpcpy	*find_env_var_pos(char *key, t_envpcpy **envpcpy)
{
	int	i;
	int	len;
	t_envpcpy *tmp;

	i = 0;
	if (!key)
		return (NULL);
	len = ft_strlen(key);
	tmp = *envpcpy;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0  && tmp->key[len] == '\0')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_env_var(char *key, char *value, t_envpcpy **envpcpy)
{
	t_envpcpy *tmp;

	if (!value || !envpcpy || !*envpcpy)
		return (0);
	tmp = find_env_var_pos(key, envpcpy);
	if (!tmp)
		return (0);
	free(tmp->key);
	free(tmp->value);
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	return (0);
}
