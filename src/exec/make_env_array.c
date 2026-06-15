/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 13:31:31 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/15 11:04:29 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

char	*env_join(char *key, char *value)
{
	int		len1;
	int		len2;
	char	*res;

	len1 = ft_strlen(key);
	len2 = ft_strlen(value);
	res = malloc(len1 + len2 + 2);
	if (!res)
		return (NULL);
	ft_memcpy(res, key, len1);
	res[len1] = '=';
	ft_memcpy(res + len1 + 1, value, len2);
	res[len1 + len2 + 1] = '\0';
	return (res);
}

char	**make_env_execve(t_env *envpc)
{
	size_t	size;
	size_t	i;
	t_env	*tmp;
	char	**env_array;

	tmp = envpc;
	size = ft_lstsize(envpc);
	i = 0;
	env_array = ft_calloc((size + 1), sizeof(char *));
	if (!env_array)
		return (NULL);
	while (tmp)
	{
		if (tmp->key && tmp->value)
			env_array[i] = env_join(tmp->key, tmp->value);
		else if (tmp->key)
			env_array[i] = ft_strdup(tmp->key);
		if (!env_array[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	return (env_array);
}
