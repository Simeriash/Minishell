/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:00 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/26 12:21:44 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	create_new_export(char *key, char *value, t_envpcpy **envpcpy)
{
	t_envpcpy	*new;
	char		*tmp1;
	char		*tmp2;

	if (!key)
		return (-1);
	tmp1 = ft_strdup(key);
	if (!tmp1)
		return (-1);
	tmp2 = NULL;
	if (value)
	{
		tmp2 = ft_strdup(value);
		if (!tmp2)
		{
			free(tmp1);
			return (-1);
		}
	}
	new = ft_lstnew(tmp1, tmp2);
	if (!new)
	{
		free(tmp1);
		free(tmp2);
		return (-1);
	}
	ft_lstaddback(envpcpy, new);
	return (0);
}

// static void	free_node(t_envpcpy *to_free)
// {
// 	free(to_free->key);
// 	free(to_free->value);
// 	free(to_free);
// }

int	ft_export(char *key, char *value, t_envpcpy **envpcpy)
{
	t_envpcpy	*tmp;
	int			len;
	int			e;

	if (!key || !envpcpy)
		return (-1);
	tmp = *envpcpy;
	len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0 && tmp->key[len] == '\0')
		{
			if (value)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value); //protect this at some point
			}
			return (0);
		}
		tmp = tmp->next;
	}
	e = create_new_export(key, value, envpcpy);
	if (e < 0)
		return (e);
	return (0);
}
