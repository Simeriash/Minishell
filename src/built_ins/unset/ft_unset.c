/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:15 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/21 14:59:20 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	free_node(t_envpcpy *to_free)
{
	free(to_free->key);
	free(to_free->value);
	free(to_free);
}

static int	key_in_array(char *lookingfor, char **keys)
{
	int	i;

	i = 0;
	while (keys[i])
	{
		if (ft_strcmp(lookingfor, keys[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	unlink_node(t_envpcpy *tmp, t_envpcpy *prev, t_envpcpy **envpcpy)
{
	t_envpcpy	*next;

	next = tmp->next;
	if (!prev)
		*envpcpy = next;
	else
		prev->next = next;
	free_node(tmp);
}

int	ft_unset(char **args, t_envpcpy **envpcpy) // FROM INT TO T_ERRORS
{
	t_envpcpy	*tmp;
	t_envpcpy	*prev;
	t_envpcpy	*next;

	if (!envpcpy)
		return (1); // NULL_ARG
	if (!args || !args[0])
		return (0); // SUCCESS
	tmp = *envpcpy;
	prev = NULL;
	while (tmp)
	{
		if (key_in_array(tmp->key, args))
		{
			next = tmp->next;
			unlink_node(tmp, prev, envpcpy);
			tmp = next;
		}
		else
		{
			prev = tmp;
			tmp = tmp->next;
		}
	}
	return (0); // SUCCESS
}
