/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:15 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/27 14:11:00 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../inc/error.h"

static void	free_node(t_env *to_free)
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

static void	unlink_node(t_env *tmp, t_env *prev, t_env **envpcpy)
{
	t_env	*next;

	next = tmp->next;
	if (!prev)
		*envpcpy = next;
	else
		prev->next = next;
	free_node(tmp);
}

int	ft_unset(char **args, t_env **envpcpy)
{
	t_env	*tmp;
	t_env	*prev;
	t_env	*next;

	if (!envpcpy)
		return (NULL_ARG);
	if (!args || !args[0])
		return (OK);
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
	return (OK);
}
