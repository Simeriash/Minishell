/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:37:26 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/11 08:48:41 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	copy_export_data(char **kdup, char **vdup, char *key, char *value)
{
	*kdup = ft_strdup(key);
	if (!(*kdup))
		return (1);
	*vdup = NULL;
	if (value)
	{
		*vdup = ft_strdup(value);
		if (!(*vdup))
		{
			free(*kdup);
			return (1);
		}
	}
	return (0);
}

int	create_new_export(char *key, char *value, t_env **envpcpy)
{
	t_env	*new;
	char	*key_dup;
	char	*value_dup;

	if (!key || !envpcpy)
		return (1);
	if (copy_export_data(&key_dup, &value_dup, key, value) != 0)
		return (1);
	new = ft_lstnew(key_dup, value_dup);
	if (!new)
	{
		free(key_dup);
		free(value_dup);
		return (1);
	}
	ft_lstaddback(envpcpy, new);
	return (0);
}

int	append_value(t_env *node, char *value)
{
	char	*tmp;

	if (!node->value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (1);
	}
	else
	{
		tmp = ft_strjoin(node->value, value);
		if (!tmp)
			return (1);
		free(node->value);
		node->value = tmp;
	}
	return (0);
}

int	set_value(t_env *node, char *value)
{
	char	*dup;

	if (!value)
		return (0);
	// if (!value)
	// {
	// 	free (node->value);
	// 	node->value = NULL;
	// 	return (0);
	// }
	dup = ft_strdup(value);
	if (!dup)
		return (1);
	free(node->value);
	node->value = dup;
	return (0);
}

int	env_set(char *key, char *value, t_env **envpcpy, t_env_mode mode)
{
	t_env		*node;
	int				ret_val;

	if (!key || !envpcpy)
		return (1);
	node = get_env_node(key, envpcpy);
	if (node)
	{
		if (value == NULL)
			return (0);
		if (mode == ENV_APPEND)
			ret_val = append_value(node, value);
		else
			ret_val = set_value(node, value);
		return (ret_val);
	}
	ret_val = create_new_export(key, value, envpcpy);
	return (ret_val);
}
