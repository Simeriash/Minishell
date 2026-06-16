/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 18:16:55 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/16 09:45:52 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

char	*set_fallback_path(int type, char *candidate, char *fallback)
{
	struct stat	st;
	int			fallback_type;

	if (!fallback)
		return (candidate);
	if (stat(fallback, &st) == 0)
		fallback_type = get_candidate_type(&st);
	else
	{
		free(fallback);
		return (candidate);
	}
	if (type < fallback_type)
	{
		free(fallback);
		return (candidate);
	}
	free(candidate);
	return (fallback);
}

int	get_candidate_type(struct stat *st)
{
	if (!S_ISDIR(st->st_mode) && (st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		return (0);
	if (!S_ISDIR(st->st_mode))
		return (1);
	return (2);
}

char	**create_paths(t_exec_err *err, t_env **env)
{
	char	*path;
	char	**ret;

	path = find_env_var("PATH", env);
	if (!path)
	{
		path = getcwd(NULL, 0);
		if (!path)
			return (NULL);
	}
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
