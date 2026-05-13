/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:00 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/13 15:53:53 by dlanehar         ###   ########.fr       */
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

static void sort_array(t_envpcpy **arr, int size)
{
	int i = 0;
	int min_index;
	int	j;
	t_envpcpy *tmp;

	while (i < size - 1)
	{
		min_index = i;
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp(arr[j]->key, arr[min_index]->key) < 0)
				min_index = j;
			j++;
		}
		if (min_index != i)
		{
			tmp = arr[i];
			arr[i] = arr[min_index];
			arr[min_index] = tmp;
		}
		i++;
	}
}

static int	print_env_in_alpha_order(t_envpcpy **envpcpy)
{
	t_envpcpy	**arr;
	int			size;
	int			i;
	int			j;
	t_envpcpy	*tmp;

	size = ft_lstsize(*envpcpy);
	if (size == 0)
		return 0;
	arr = malloc(size * sizeof(t_envpcpy *));
	if (!arr)
		return -1;
	i = 0;
	tmp = *envpcpy;
	while (tmp)
	{
		arr[i] = tmp;
		tmp = tmp->next;
		i++;
	}
	sort_array(arr, size);
	j = 0;
	while (j < size)
	{
		printf("declare -x %s", arr[j]->key);
		if (arr[j]->value || (arr[j]->value && arr[j]->value[0] == '\0'))
			printf("=\"%s\"", arr[j]->value);
		printf("\n");
		j++;
	}
	free(arr);
	return 0;
}

int	check_valid_var(char *key)
{
	if (key[0] != '_')
	{
		if (!ft_isalpha(key[0]))
		{
			printf("bash: export: `%s': not a valid identifier\n", key);
			return (-1);
		}
		else
			return (0);
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
	if (ft_strcmp("export", args[i]) == 0)
		i++;
	if (!args[i])
	{
		print_env_in_alpha_order(envpcpy);
		return (0);
	}
	while (args[i])
	{
		if (check_valid_var(args[i]) < 0)
		{
			i++;
			continue ;
		}
		error = get_key(args[i], &key);
		if (error < 0)
			return (-1);
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
