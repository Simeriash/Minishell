/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:59:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/18 10:27:12 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(t_envpcpy **envpcpy)
{
	char	*cwd;
	char	*w_dir;
	int		ret_val;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		w_dir = find_env_var("PWD", envpcpy);
		if (!w_dir)
		{
			ret_val = write(2, "PWD is unset\n", 14);
			if (ret_val < 0)
				return (ret_val);
			return (-1);
		}
		ret_val = printf("%s\n", w_dir);
		if (ret_val < 0)
			return (ret_val);
		return (0);
	}
	ret_val = printf("%s\n", cwd);
	if (ret_val < 0)
		return (ret_val);
	free(cwd);
	return (0);
}
