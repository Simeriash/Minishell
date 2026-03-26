/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:15 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/26 10:59:49 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_node(t_envpcpy *to_free)
{
	free(to_free->key);
	free(to_free->value);
	free(to_free);
}

int	ft_unset(char *key, t_envpcpy **envpcpy)
{
	t_envpcpy	*tmp;
	t_envpcpy	*prev;
	int			len;

	if (!key || !envpcpy)
		return (-1);
	tmp = *envpcpy;
	prev = NULL;
	len = ft_strlen(key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0 && tmp->key[len] == '\0')
		{
			if (prev == NULL) //this means that we found key in the head node.
				*envpcpy = tmp->next;
			else
				prev->next = tmp->next;
			free_node(tmp);
			return (0);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (-1);
}
