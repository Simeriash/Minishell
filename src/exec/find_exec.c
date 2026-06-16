/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 13:20:21 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/16 15:49:49 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

char	**create_paths(t_exec_err *err, t_env **env)
{
	char	*path;
	char	**ret;

	path = find_env_var("PATH", env);
	if (!path)
		return (NULL);
	ret = ft_split(path, ':');
	if (!ret)
	{
		*err = EXEC_MALLOC_FAIL;
		return (NULL);
	}
	return (ret);
}

char	*create_exec_path(char *path, char *cmd)
{
	char	*tmp;
	char	*ret;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*create_candidate(char *cmd, char **paths, t_exec_err *err)
{
	char		*candidate;
	struct stat	st;
	int			i;

	(void)err;
	i = 0;
	while (paths[i])
	{
		candidate = create_exec_path(paths[i], cmd);
		if (!candidate)
			return (NULL);
		if (stat(candidate, &st) == 0)
		{
			if (S_ISREG(st.st_mode) && access(candidate, X_OK) == 0)
				return (candidate);
		}
		free(candidate);
		i++;
	}
	return (NULL);
}
