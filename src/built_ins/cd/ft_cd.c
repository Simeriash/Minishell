/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:55:04 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/25 14:30:01 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static	int	change_env_var(char *key, char *value, t_envpcpy **envpcpy)
{
	t_envpcpy *tmp;

	if (!value || !envpcpy || !*envpcpy)
		return (0);
	tmp = find_env_var_pos(key, envpcpy);
	if (!tmp)
		return (0);
	free(tmp->key);
	free(tmp->value);
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	return (0);
}

int	ft_cd(char *path ,t_envpcpy **envpcpy)
{
	char *buf;
	char *new;
	int	i;
	int	ret_val;

	if (!path)
	{
		new = find_env_var("HOME", envpcpy);
		if (!new){
			printf("cd: no such file or directory: HOME is not set.\n");
			return (-1);
		}
		buf = getcwd(NULL, 0);
		i = change_env_var("OLDPWD", buf, envpcpy);
		free(buf);
		i = change_env_var("PWD", new, envpcpy);
		ret_val = chdir(new);
		return (ret_val);
	}
	buf = getcwd(NULL, 0); //store this in OLDPWD
	i = change_env_var("OLDPWD", buf, envpcpy);
	if (i < 0)
		return (-1);
	free(buf);
	ret_val = chdir(path); //change directory
	new = getcwd(NULL, 0); //store the now-current directory
	i = change_env_var("PWD", new, envpcpy);
	if (i < 0)
		return (-1);
	free(new);
	return (ret_val);
}

