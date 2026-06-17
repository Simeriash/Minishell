/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:29:14 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/17 08:01:10 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"

char	*find_env_var(char *key, t_env **envpcpy)
{
	int			len;
	t_env		*tmp;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	tmp = (*envpcpy)->next;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0 && tmp->key[len] == '\0')
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

t_env	*get_env_node(char *key, t_env **envpcpy)
{
	int			len;
	t_env		*tmp;

	if (!key)
		return (NULL);
	len = ft_strlen(key);
	tmp = (*envpcpy)->next;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len) == 0 && tmp->key[len] == '\0')
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_error(char *cmd, char *bad_input, int err)
{
	write(2, "Ghost: ", 8);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (bad_input)
	{
		write(2, bad_input, ft_strlen(bad_input));
		write(2, ": ", 2);
	}
	write(2, strerror(err), ft_strlen(strerror(err)));
	write(2, "\n", 1);
	return ;
}
