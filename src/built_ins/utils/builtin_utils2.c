/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:29:14 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/25 14:32:17 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char *find_env_var(char *key, t_envpcpy **envpcpy)
{
	int	i;
	int	len;
	t_envpcpy *tmp;

	i = 0;
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
