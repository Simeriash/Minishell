/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:59:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/13 15:55:48 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_envpcpy **envpcpy)
{
	char	*w_dir;

	w_dir = getcwd(NULL, 0);
	if (!w_dir)
	{
		w_dir = find_env_var("PWD", envpcpy);
		if (!w_dir)
		{
			printf("PWD is unset\n");
			return (-1);
		}
		printf("%s\n", w_dir);
		return (0);
	}
	printf("%s\n", w_dir);
	free(w_dir);
	return (0);
}
