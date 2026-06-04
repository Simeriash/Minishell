/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 13:31:31 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/04 10:29:10 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"

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

t_error	make_env_execve(t_env *envpc, char ***array)
{
	size_t		size;
	size_t		i;
	t_env		*tmp;

	tmp = envpc;
	size = ft_lstsize(envpc);
	i = 0;
	(*array) = ft_calloc((size + 1), sizeof(char *));
	if (!(*array))
		return (MALLOC);
	while (tmp)
	{
		if (tmp->key && tmp->value)
			(*array)[i] = env_join(tmp->key, tmp->value);
		else if (tmp->key)
			(*array)[i] = ft_strdup(tmp->key);
		if (!(*array)[i])
			return (MALLOC);
		i++;
		tmp = tmp->next;
	}
	return (OK);
}
