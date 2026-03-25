/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:59:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/25 14:29:47 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_envpcpy **envpcpy)
{
	char	*w_dir;

	w_dir = find_env_var("PWD", envpcpy);
	if (!w_dir)
	{
		printf("PWD is undset\n");
		return (-1);
	}
	printf("%s\n", w_dir);
	return (0);
}
