/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 13:20:21 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/04 11:26:01 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "parser.h"

int	get_candidate_type(struct stat *st)
{
	if (!S_ISDIR(st->st_mode) && (st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		return (0);
	if (!S_ISDIR(st->st_mode))
		return (1);
	return (2);
}

char	**create_paths(t_exec_err *err)
{
	char	*path;
	char	**ret;

	path = getenv("PATH");
	if (!path)
	{
		*err = EXEC_NO_PATH;
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

char	*handle_candidate(char *path, char *cmd, char *f_b, t_exec_err *err)
{
	char	*ret;

	ret = create_exec_path(path, cmd);
	if (!ret)
	{
		cleanup_helper(f_b);
		*err = EXEC_MALLOC_FAIL;
		return (NULL);
	}
	return (ret);
}

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

// char	*process_candidate(char *candidate, char *fallback, t_exec_err *err)
// {
// 	struct stat	st;
// 	int		type;

// 	if (stat(candidate, &st) != 0)
// 	{
// 		free(candidate);
// 		return (fallback);
// 	}
// 	type = get_candidate_type(&st);
// 	if (type == 0)
// 	{
// 		cleanup_helper(fallback);
// 		return (candidate);
// 	}
// }

char	*create_candidate(char *cmd, char **paths, t_exec_err *err)
{
	struct stat	st;
	char		*candidate;
	char		*fallback;
	int			type;
	int			i;

	i = 0;
	fallback = NULL;
	while (paths[i])
	{
		candidate = handle_candidate(paths[i], cmd, fallback, err);
		if (!candidate && *err == EXEC_MALLOC_FAIL)
			return (NULL);
		if (stat(candidate, &st) == 0)
		{
			type = get_candidate_type(&st);
			if (type == 0)
			{
				cleanup_helper(fallback);
				return (candidate);
			}
			fallback = set_fallback_path(type, candidate, fallback);
		}
		else
			free(candidate);
		i++;
	}
	return (fallback);
}
