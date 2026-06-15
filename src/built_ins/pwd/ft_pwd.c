/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 12:59:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/15 10:55:52 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"

int	ft_pwd(char **args, t_env **envpcpy)
{
	char	*cwd;
	char	*w_dir;
	int		ret_val;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		w_dir = find_env_var("PWD", envpcpy);
		if (!w_dir)
		{
			ret_val = write(2, "PWD is unset\n", 14);
			return (1);
		}
		ret_val = printf("%s\n", w_dir);
		if (ret_val < 0)
			return (1);
		return (0);
	}
	ret_val = printf("%s\n", cwd);
	if (ret_val < 0)
		return (1);
	free(cwd);
	return (0);
}
