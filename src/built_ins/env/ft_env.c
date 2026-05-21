/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:10:38 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/21 14:51:14 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **args, t_envpcpy **envpcpy) // FROM INT TO T_ERRORS
{
	t_envpcpy	*tmp;
	int			ret_val;

	(void)args;
	if (!envpcpy)
		return (1); // NULL_ARG
	tmp = *envpcpy;
	while (tmp)
	{
		if (tmp->value != NULL)
		{
			ret_val = printf("%s=%s\n", tmp->key, tmp->value);
			if (ret_val < 0)
				return (-1); // WRITE ERROR
		}
		tmp = tmp->next;
	}
	return (0); // SUCCESS
}
