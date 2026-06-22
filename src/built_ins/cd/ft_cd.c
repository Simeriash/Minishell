/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:55:04 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/22 09:15:28 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"

static int	update_oldpwd_pwd(char *old, char *new, t_env **envpcpy)
{
	int				ret_val;

	ret_val = 0;
	if (old)
	{
		ret_val = env_set("OLDPWD", old, envpcpy, ENV_REPLACE);
		if (ret_val < 0)
			return (1);
	}
	if (new)
	{
		ret_val = env_set("PWD", new, envpcpy, ENV_REPLACE);
		if (ret_val < 0)
			return (1);
	}
	return (ret_val);
}

static int	chdir_success(char **current, char **old, t_env **envpcpy)
{
	int	ret_val;

	ret_val = 0;
	if (!*old)
	{
		*old = ft_strdup("");
		if (!*old)
			return (1);
	}
	*current = getcwd(NULL, 0);
	if (!*current)
	{
		ft_printf_fd(2, "cd: error retrieving current directory: getcwd: ");
		ft_printf_fd(2, "cannot access parent directories: ");
		ft_printf_fd(2, "%s\n", strerror(errno));
		return (0);
	}
	ret_val = update_oldpwd_pwd(*old, *current, envpcpy);
	if (ret_val != 0)
		return (1);
	return (ret_val);
}

static int	cd_executor(char *cd_input, t_env **envpcpy)
{
	int		ret_val;
	char	*old_path;
	char	*current_path;
	int		err;

	if (cd_input[0] == '\0')
		return (0);
	current_path = NULL;
	old_path = getcwd(NULL, 0);
	ret_val = chdir(cd_input);
	if (ret_val == 0)
		ret_val = chdir_success(&current_path, &old_path, envpcpy);
	else
	{
		err = errno;
		print_error("cd", cd_input, err);
		ret_val = 1;
	}
	free(old_path);
	free(current_path);
	return (ret_val);
}

static	int	cd_to_home(t_env **envpcpy)
{
	char	*new;
	int		ret_val;

	new = find_env_var("HOME", envpcpy);
	if (!new)
	{
		write(2, "Ghost: ", ft_strlen("Ghost: "));
		write(2, "cd", ft_strlen("cd"));
		write(2, ": ", 2);
		write(2, "HOME not set", ft_strlen("HOME not set"));
		write(2, "\n", 1);
		return (0);
	}
	ret_val = cd_executor(new, envpcpy);
	return (ret_val);
}

int	ft_cd(char **args, t_env **envpcpy)
{
	int		ret_val;

	if (count_args(args) > 2)
	{
		write(2, "Ghost: cd: too many arguments\n", 31);
		return (1);
	}
	if (!args[1] || (args[1] && ft_strcmp("--", args[1]) == 0))
	{
		ret_val = cd_to_home(envpcpy);
		return (ret_val);
	}
	ret_val = cd_executor(args[1], envpcpy);
	return (ret_val);
}
