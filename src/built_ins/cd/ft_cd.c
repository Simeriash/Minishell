/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:55:04 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/24 15:15:46 by dlanehar         ###   ########.fr       */
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

static	int	find_env_var_pos(char **envpcpy, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	if (!envpcpy)
		return (-1);
	while (envpcpy[i])
	{
		if (ft_strncmp(envpcpy[i], key, len) == 0  && envpcpy[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static	int	change_env_var(char **envpcpy, char *key, char *new)
{
	int	i;
	char *temp;

	if (!new || !envpcpy)
		return (-1);
	i = find_env_var_pos(envpcpy, key);
	if (i < 0)
		return (-1);
	free(envpcpy[i]);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (-1);
	envpcpy[i] = ft_strjoin(temp, new);
	if (!envpcpy[i])
		return (-1);
	free(temp);
	return (i);
}

int	ft_cd(char **envpcpy, char *path)
{
	char *buf;
	char *new;
	int	i;
	int	ret_val;

	if (!path)
	{
		new = find_env_var(envpcpy, "HOME");
		new = NULL;
		if (!new){
			printf("cd: no such file or directory: HOME is not set.\n");
			return (-1);
		}
		buf = getcwd(NULL, 0);
		i = change_env_var(envpcpy, "OLDPWD", buf);
		free(buf);
		i = change_env_var(envpcpy, "PWD", new);
		ret_val = chdir(new);
		return (ret_val);
	}
	buf = getcwd(NULL, 0); //store this in OLDPWD
	i = change_env_var(envpcpy, "OLDPWD", buf);
	if (i < 0)
		return (-1);
	free(buf);
	ret_val = chdir(path); //change directory
	new = getcwd(NULL, 0); //store the now-current directory
	i = change_env_var(envpcpy, "PWD", new);
	if (i < 0)
		return (-1);
	free(new);
	return (ret_val);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	if (argv[1] && !ft_strncmp(argv[1], "-n", 2))
// 		ft_echo(argv+2, 0);
// 	else
// 		ft_echo(argv+1, 1);
// }
