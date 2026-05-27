/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:05:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/27 12:10:54 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

t_env	*ft_lstnew(char *newkey, char *newvalue)
{
	t_env	*test;

	test = malloc(sizeof(t_env));
	if (!test)
		return (NULL);
	test->key = newkey;
	test->value = newvalue;
	test->next = NULL;
	return (test);
}

void	ft_lstaddback(t_env **lst, t_env *new)
{
	t_env	*ptr;

	if (lst != NULL || new != NULL)
	{
		if (*lst != NULL)
		{
			ptr = ft_lstlast(*lst);
			ptr->next = new;
		}
		else
			*lst = new;
	}
}

t_env	*ft_lstlast(t_env *lst)
{
	int	i;
	int	end;

	if (!lst)
		return (NULL);
	i = 0;
	end = ft_lstsize(lst);
	while (i < end - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

int	ft_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
