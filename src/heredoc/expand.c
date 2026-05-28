/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 08:35:51 by julauren          #+#    #+#             */
/*   Updated: 2026/05/28 10:27:36 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

static int	next_expander(char **cmd, t_env *envc, int *i, int *j)
{
	char	*new_value;
	int		len;

	new_value = check_new_value(*cmd, envc, *i, j);
	if (new_value && change_value(cmd, new_value, *i, *j))
	{
		error_heredoc(MALLOC);
		return (1);
	}
	len = ft_strlen(new_value);
	free(new_value);
	*i = *i + len - 1;
	return (0);
}

int	heredoc_expander(char **cmd, t_env *envc)
{
	int	i;
	int	j;

	i = 0;
	while ((*cmd)[i] != '\0')
	{
		if ((*cmd)[i] == '$')
		{
			i++;
			if ((*cmd)[i] == '\0')
				return (0);
			if (ft_isspace((*cmd)[i]))
				continue ;
			j = i + 1;
			if (next_expander(cmd, envc, &i, &j))
				return (1);
		}
		else
			i++;
	}
	return (0);
}
