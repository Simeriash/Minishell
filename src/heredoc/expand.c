/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 08:35:51 by julauren          #+#    #+#             */
/*   Updated: 2026/06/21 12:22:18 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

static int	next_expander(char **cmd, t_env *envc, t_index *index, int *status)
{
	char	*new_value;
	int		len;
	t_ctrl	ctrl;

	ctrl.status = *status;
	ctrl.state = HEREDOC_MODE;
	new_value = check_new_value(*cmd, envc, index, ctrl);
	if (!new_value || change_value(cmd, new_value, index->i, index->j))
	{
		error_heredoc(MALLOC, status);
		return (1);
	}
	len = ft_strlen(new_value);
	free(new_value);
	index->i = index->i + len - 1;
	return (0);
}

int	heredoc_expander(char **cmd, t_env *envc, int *status)
{
	t_index	index;

	index.i = 0;
	while ((*cmd)[index.i] != '\0')
	{
		if ((*cmd)[index.i] == '$')
		{
			(index.i)++;
			if ((*cmd)[index.i] == '\0')
				return (0);
			if (ft_isspace((*cmd)[index.i]))
				continue ;
			index.j = index.i + 1;
			if (next_expander(cmd, envc, &index, status))
				return (1);
		}
		else
			(index.i)++;
	}
	return (0);
}
