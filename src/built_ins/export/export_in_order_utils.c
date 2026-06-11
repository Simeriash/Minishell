/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_in_order_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:22:13 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/11 08:48:33 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_env	**create_env_array(int size, t_env **envpcpy)
{
	t_env	**array;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = (*envpcpy)->next;
	array = malloc(((size + 1) * sizeof(t_env *)));
	if (!array)
		return (NULL);
	while (tmp)
	{
		array[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

static void	sort_env_array(t_env **arr, int size)
{
	int		i;
	int		min_index;
	int		j;
	t_env	*tmp;

	i = 0;
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

static int	print_env_array(t_env **array, int size)
{
	int	i;
	int	error;

	i = 0;
	while (i < size)
	{
		error = printf("declare -x %s", array[i]->key);
		if (error < 0)
			return (1);
		if (array[i]->value)
		{
			error = printf("=\"%s\"", array[i]->value);
			if (error < 0)
				return (1);
		}
		error = printf("\n");
		if (error < 0)
			return (1);
		i++;
	}
	return (0);
}

int	print_env_in_alpha_order(t_env **envpcpy)
{
	t_env	**env_array;
	int		size;
	int		error;
	t_env	*start;

	start = (*envpcpy)->next;
	size = ft_lstsize(start);
	if (size == 0)
		return (1);
	env_array = create_env_array(size, envpcpy);
	if (!env_array)
		return (1);
	sort_env_array(env_array, size);
	error = print_env_array(env_array, size);
	if (error != 0)
		return (error);
	free(env_array);
	return (0);
}
