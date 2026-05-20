/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:29:14 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/20 14:19:42 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*find_env_var(char *key, t_envpcpy **envpcpy)
{
	int			i;
	int			len;
	t_envpcpy	*tmp;

	i = 0;
	if (!key)
		return (NULL);
	len = ft_strlen(key);
	tmp = *envpcpy;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0 && tmp->key[len] == '\0')
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_envpcpy	*get_env_node(char *key, t_envpcpy **envpcpy)
{
	int			i;
	int			len;
	t_envpcpy	*tmp;

	i = 0;
	if (!key)
		return (NULL);
	len = ft_strlen(key);
	tmp = *envpcpy;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0 && tmp->key[len] == '\0')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

// int	change_env_var(char *key, char *value, t_envpcpy **envpcpy)
// {
// 	t_envpcpy	*tmp;

// 	if (!value || !envpcpy || !*envpcpy)
// 		return (0);
// 	tmp = get_env_node(key, envpcpy);
// 	if (!tmp)
// 		return (-2);
// 	free(tmp->key);
// 	free(tmp->value);
// 	tmp->key = ft_strdup(key);
// 	if (!tmp->key)
// 		return (-1);
// 	tmp->value = ft_strdup(value);
// 	if (!tmp->value)
// 		return (-1);
// 	return (0);
// }
