/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:37:26 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/18 15:05:30 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int copy_export_data(char **kdup, char **vdup, char *key, char *value)
{
	*kdup = ft_strdup(key);
	if (!(*kdup))
		return (-1);
	*vdup = NULL;
	if (value)
	{
		*vdup = ft_strdup(value);
		if (!(*vdup))
		{
			free(*kdup);
			return (-1);
		}
	}
	return (0);
}

int	create_new_export(char *key, char *value, t_envpcpy **envpcpy)
{
	t_envpcpy	*new;
	char		*key_dup;
	char		*value_dup;

	if (!key || !envpcpy)
		return (-1);
	if (copy_export_data(&key_dup, &value_dup, key, value) < 0)
		return (-1);
	new = ft_lstnew(key_dup, value_dup);
	if (!new)
	{
		free(key_dup);
		free(value_dup);
		return (-1);
	}
	ft_lstaddback(envpcpy, new);
	return (0);
}
