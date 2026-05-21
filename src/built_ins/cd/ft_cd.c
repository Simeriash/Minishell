/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:55:04 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/21 10:49:08 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	update_oldpwd_pwd(char *old, char *new, t_envpcpy **envpcpy)
{
	int				ret_val;

	ret_val = 0;
	if (old)
	{
		ret_val = env_set("OLDPWD", old, envpcpy, ENV_REPLACE);
		if (ret_val < 0)
			return (-1);
	}
	if (new)
	{
		ret_val = env_set("PWD", new, envpcpy, ENV_REPLACE);
		if (ret_val < 0)
			return (-1);
	}
	return (ret_val);
}

static int	chdir_success(char **current, char *old, t_envpcpy **envpcpy)
{
	int	ret_val;

	ret_val = 0;
	*current = getcwd(NULL, 0);
	if (!*current)
		return (-1);
	ret_val = update_oldpwd_pwd(old, *current, envpcpy);
	if (ret_val < 0)
		return (-1);
	return (ret_val);
}

static int	cd_executor(char *cd_input, t_envpcpy **envpcpy)
{
	int		ret_val;
	char	*old_path;
	char	*current_path;
	int		err;

	current_path = NULL;
	old_path = getcwd(NULL, 0);
	if (!old_path)
		return (-1);
	ret_val = chdir(cd_input);
	if (ret_val == 0)
		ret_val = chdir_success(&current_path, old_path, envpcpy);
	else
	{
		err = errno;
		print_error("cd", cd_input, err);
	}
	free(old_path);
	free(current_path);
	return (ret_val);
}

static	int	cd_to_home(t_envpcpy **envpcpy)
{
	char	*new;
	int		ret_val;

	new = find_env_var("HOME", envpcpy);
	if (!new)
	{
		write(2, "cd: no such file or directory: HOME is not set.\n", 49);
		return (-1);
	}
	ret_val = cd_executor(new, envpcpy);
	return (ret_val);
}

int	ft_cd(char *path, t_envpcpy **envpcpy)
{
	char	*new;
	int		ret_val;

	if (!path || (path[0] == '~' && path[1] == '\0'))
	{
		ret_val = cd_to_home(envpcpy);
		return (ret_val);
	}
	if (path[0] == '-' && path[1] == '\0')
	{
		new = find_env_var("OLDPWD", envpcpy);
		if (!new || new[0] == '\0')
		{
			printf("bash: cd: OLDPWD not set\n");
			return (-1);
		}
		ret_val = cd_executor(new, envpcpy);
		if (ret_val == 0)
			ft_pwd(envpcpy);
		return (ret_val);
	}
	ret_val = cd_executor(path, envpcpy);
	return (ret_val);
}
