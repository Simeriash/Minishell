/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 08:45:02 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/27 12:14:42 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"

builtin_func	get_builtin(char **args, t_env **envpcpy)
{
	static t_builtins func_array[] =
	{
		{"cd", ft_cd},
		{"echo", ft_echo},
		{"env", ft_env},
		{"exit", ft_exit},
		{"export", ft_export},
		{"pwd", ft_pwd},
		{"unset", ft_unset},
		{NULL, NULL}
	};
	int	i;

	(void)envpcpy;
	i = 0;
	while(func_array[i].cmd)
	{
		if (ft_strcmp(args[0], func_array[i].cmd) == 0)
			return (func_array[i].function);
		i++;
	}
	return (NULL);
}
