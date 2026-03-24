/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:59:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/24 13:14:06 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static	char *find_env_var(char **envpcpy, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	if (!envpcpy)
		return (NULL);
	while (envpcpy[i])
	{
		if (ft_strncmp(envpcpy[i], key, len) == 0  && envpcpy[i][len] == '=')
			return (envpcpy[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	ft_pwd(char **envpcpy)
{
	char	*w_dir;

	w_dir = find_env_var(envpcpy, "PWD");
	if (!w_dir)
	{
		printf("PWD is undset\n");
		return (-1);
	}
	printf("%s\n", w_dir);
	return (0);
}
