/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:37:26 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/19 14:50:21 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	copy_export_data(char **kdup, char **vdup, char *key, char *value)
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

int	create_new_export(t_export_inputs *data, t_envpcpy **envpcpy)
{
	t_envpcpy	*new;
	char		*key_dup;
	char		*value_dup;

	if (!data->key || !envpcpy)
		return (-1);
	if (copy_export_data(&key_dup, &value_dup, data->key, data->value) < 0)
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

int	append_export(t_export_inputs *data, t_envpcpy **envpcpy)
{
	int	ret;

	ret = 0;
	if (data->target_node)
		ret = append_value(data);
	else
		ret = create_new_export(data, envpcpy);
	return (ret);
}

int	set_export(t_export_inputs *data, t_envpcpy **envpcpy)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (!data->target_node)
		ret = create_new_export(data, envpcpy);
	else
	{
		if (data->value)
		{
			tmp = ft_strdup(data->value);
			if (!tmp)
				return (-1);
			if (data->target_node->value)
				free(data->target_node->value);
			data->target_node->value = tmp;
		}
	}
	return (ret);
}
