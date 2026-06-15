/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 13:20:21 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/15 11:00:24 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

static char	*handle_candidate(char *path, char *cmd, char *f_b, t_exec_err *err)
{
	char	*ret;

	ret = create_exec_path(path, cmd);
	if (!ret)
	{
		if (f_b)
			free(f_b);
		*err = EXEC_MALLOC_FAIL;
		return (NULL);
	}
	return (ret);
}

static char	*process_candidate(char *candidate, char **fallback
												, t_exec_err *err)
{
	struct stat	st;
	int			type;

	if (stat(candidate, &st) != 0)
	{
		free (candidate);
		return (NULL);
	}
	type = get_candidate_type(&st);
	if (type == 0)
	{
		if (*fallback)
			free(*fallback);
		return (candidate);
	}
	*fallback = set_fallback_path(type, candidate, *fallback);
	if (*fallback == NULL && *err == EXEC_MALLOC_FAIL)
		return (NULL);
	return (NULL);
}

char	*create_candidate(char *cmd, char **paths, t_exec_err *err)
{
	char		*candidate;
	char		*fallback;
	char		*result;
	int			i;

	i = 0;
	fallback = NULL;
	while (paths[i])
	{
		candidate = handle_candidate(paths[i], cmd, fallback, err);
		if (!candidate && *err == EXEC_MALLOC_FAIL)
			return (NULL);
		result = process_candidate(candidate, &fallback, err);
		if (result)
			return (result);
		if (!result && *err == EXEC_MALLOC_FAIL)
			return (NULL);
		i++;
	}
	return (fallback);
}
