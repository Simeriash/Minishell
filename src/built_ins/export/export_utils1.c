/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:37:26 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/21 11:06:22 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	copy_export_data(char **kdup, char **vdup, char *key, char *value) // FROM INT TO T_ERRORS
{
	*kdup = ft_strdup(key);
	if (!(*kdup))
		return (-1); // MALLOC FAIL
	*vdup = NULL;
	if (value)
	{
		*vdup = ft_strdup(value);
		if (!(*vdup))
		{
			free(*kdup);
			return (-1); // MALLOC FAIL
		}
	}
	return (0); // SUCCESS
}

int	create_new_export(char *key, char *value, t_envpcpy **envpcpy) // FROM INT TO T_ERRORS
{
	t_envpcpy	*new;
	char		*key_dup;
	char		*value_dup;

	if (!key || !envpcpy)
		return (-1); // NULL ARG
	if (copy_export_data(&key_dup, &value_dup, key, value) < 0)
		return (-1); // MALLOC FAIL
	new = ft_lstnew(key_dup, value_dup);
	if (!new)
	{
		free(key_dup);
		free(value_dup);
		return (-1); // MALLOC FAIL
	}
	ft_lstaddback(envpcpy, new);
	return (0); // SUCCESS
}

int	append_value(t_envpcpy *node, char *value) // FROM INTO TO T_ERRORS
{
	char	*tmp;

	if (!node->value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
			return (-1); // MALLOC_FAIL
	}
	else
	{
		tmp = ft_strjoin(node->value, value);
		if (!tmp)
			return (-1); // MALLOC FAIL
		free(node->value);
		node->value = tmp;
	}
	return (0); // SUCCESS
}

int	set_value(t_envpcpy *node, char *value) // FROM INT TO T_ERRORS
{
	char	*dup;

	dup = ft_strdup(value);
	if (!dup)
		return (-1); // MALLOC FAIL
	free(node->value);
	node->value = dup;
	return (0); // SUCCESS
}

int	env_set(char *key, char *value, t_envpcpy **envpcpy, t_env_mode mode) // FROM INT TO T_ERRORS
{
	t_envpcpy		*node;
	int				ret_val; // BECOME ERROR??

	if (!key || !envpcpy)
		return (-1); // NULL_ARG
	node = get_env_node(key, envpcpy);
	if (node)
	{
		if (mode == ENV_APPEND)
			ret_val = append_value(node, value);
		else
			ret_val = set_value(node, value);
		return (ret_val); // RETURN RET VAL (T_ERRORS)
	}
	ret_val = create_new_export(key, value, envpcpy);
	return (ret_val);
}
