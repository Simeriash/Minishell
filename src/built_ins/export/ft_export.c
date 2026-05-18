/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:00 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/18 15:54:59 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_valid_var(char *key)
{
	int	i;

	i = 0;
	if (!(key[i] == '_' || ft_isalpha(key[i])))
	{
		printf("bash: export: `%s': not a valid identifier\n", key);
		return (-1);
	}
	i++;
	while (key[i] && key[i] != '=')
	{
		if (!(key[i] == '_' || ft_isalnum(key[i])))
		{
			printf("bash: export: `%s': not a valid identifier\n", key);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	must_append(char *in)
{
	int		i;

	i = 0;
	while (in[i] && in[i] != '=')
	{
		if (in[i] == '+' && in[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

static	int get_key(char *in, char **to_change)
{
	int		i;

	i = 0;
	while (in[i] && in[i] != '=' && in[i] != '+')
		i++;
	*to_change = malloc(i + 1);
	if (!(*to_change))
		return (-1);
	ft_strlcpy(*to_change, in, i + 1);
	return (0);
}

static	int get_value(char *in, char **to_change)
{
	int		i;

	i = 0;
	while (in[i] && in[i] != '=')
		i++;
	if (in[i] != '=')
	{
		*to_change = NULL;
		return (0);
	}
	i++;
	*to_change = ft_strdup(in + i);
	if (!(*to_change))
		return (-1);
	return (0);
}

static	int	append_value(t_envpcpy *target_node, char *new_value)
{
	char *tmp;

	if (!target_node->value)
		target_node->value = ft_strdup(new_value);
		if (!target_node->value)
		{

		}
	else
	{
		tmp = ft_strjoin(target_node->value, new_value);
		if (!tmp)
			return (-1);
		free(target_node->value);
		target_node->value = tmp;
	}
	return (0);
}

int	ft_export(char *path, char **args, t_envpcpy **envpcpy)
{
	int			i;
	char		*key;
	char		*new_value;
	int			error;
	t_envpcpy	*target_node;

	(void)path;
	i = 0;
	if (!args)
		return (-1);
	if (!args[i])
	{
		print_env_in_alpha_order(envpcpy);
		return (0);
	}
	while (args[i])
	{
		error = get_key(args[i], &key);
		if (error < 0)
			return (-1);
		if (check_valid_var(key) < 0)
		{
			i++;
			free(key);
			continue ;
		}
		error = get_value(args[i], &new_value);
		if (error < 0)
			return (-1);
		target_node = find_env_var_pos(key, envpcpy);
		if (must_append(args[i]))
		{
			if (target_node)
				append_value(target_node, new_value);
			else
				create_new_export(key, new_value, envpcpy);
		}
		else
		{
			if (!target_node)
				create_new_export(key, new_value, envpcpy);
			else
			{
				if (new_value)
				{
					free(target_node->value);
					target_node->value = ft_strdup(new_value);
					if (!target_node->value)
					{
						free(new_value);
						free(key);
						return (-1);
					}
				}
			}
		}
		free(new_value);
		free(key);
		i++;
	}
	return (0);
}
