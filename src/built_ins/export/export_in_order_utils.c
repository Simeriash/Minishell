/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_in_order_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:22:13 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/18 15:40:48 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_envpcpy **create_env_array(int size, t_envpcpy **envpcpy)
{
	t_envpcpy	**array;
	t_envpcpy	*tmp;
	int			i;

	i = 0;
	tmp = *envpcpy;
	array = malloc(size * sizeof(t_envpcpy *));
	if (!array)
		return (NULL);
	while (tmp)
	{
		array[i] = tmp;
		i++;
		tmp = tmp->next;
	}
	return (array);
}

static void sort_env_array(t_envpcpy **arr, int size)
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

static void print_env_array(t_envpcpy **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("declare -x %s", array[i]->key);
		if (array[i]->value || (array[i]->value && array[i]->value[0] == '\0'))
			printf("=\"%s\"", array[i]->value);
		printf("\n");
		i++;
	}
}

int	print_env_in_alpha_order(t_envpcpy **envpcpy)
{
	t_envpcpy	**env_array;
	int			size;
	int			i;
	int			j;
	t_envpcpy	*tmp;

	size = ft_lstsize(*envpcpy);
	if (size == 0)
		return 0;
	env_array = create_env_array(size, envpcpy);
	if (!env_array)
		return (-1);
	sort_env_array(env_array, size);
	print_env_array(env_array, size);
	free(env_array);
	return 0;
}
