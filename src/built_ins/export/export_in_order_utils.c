/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_in_order_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 15:22:13 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/27 12:33:33 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static t_env	**create_env_array(int size, t_env **envpcpy)
{
	t_env	**array;
	t_env	*tmp;
	int			i;

	i = 0;
	tmp = *envpcpy;
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
	int			i;
	int			min_index;
	int			j;
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

static void	print_env_array(t_env **array, int size) // FROM VOID TO T_ERRORS
{
	int	i;
	//INT ERROR;

	i = 0;
	while (i < size)
	{
		printf("declare -x %s", array[i]->key); // ADD ERROR =
		// IF (ERROR < 0)
		//	RETURN (WRITE_ERROR);
		if (array[i]->value)
		//{
			printf("=\"%s\"", array[i]->value); // ADD ERROR =
			// IF (ERROR < 0)
			//	RETURN (WRITE_ERROR);
		//}
		printf("\n"); // ADD ERROR =
		//IF (ERROR < 0)
		//	RETURN (WRITE_ERROR);
		i++;
	}
	//RETURN (SUCCESS);
}

int	print_env_in_alpha_order(t_env **envpcpy) // FROM INT TO T_ERRORS
{
	t_env	**env_array;
	int			size;
	//T_ERRORS ERROR;

	// ERROR = SUCCESS;
	size = ft_lstsize(*envpcpy);
	if (size == 0)
		return (0); // NULL ARG
	env_array = create_env_array(size, envpcpy);
	if (!env_array)
		return (-1); // MALLOC FAIL
	sort_env_array(env_array, size);
	print_env_array(env_array, size); // ADD ERROR =
	free(env_array);
	return (0); // RETURN (ERROR);
}
