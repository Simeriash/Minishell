/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:10:38 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/11 08:49:03 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **args, t_env **envpcpy)
{
	t_env	*tmp;
	int		ret_val;

	(void)args;
	if (!envpcpy)
		return (1);
	tmp = *envpcpy;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			ret_val = printf("%s=%s\n", tmp->key, tmp->value);
			if (ret_val < 0)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
