/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:46:00 by julauren          #+#    #+#             */
/*   Updated: 2026/05/17 16:01:11 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/envc.h"

static t_env	*change_value(t_env *envc, char *key)
{
	t_env	*tmp;

	tmp = envc->next;
	while (tmp != NULL)
	{
		if (!ft_strcmp(key, tmp->key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int	init_envc(t_env *envc)
{
	t_env	*tmp;

	tmp = change_value(envc, "SHELL");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup("/minishell");
		if (!(tmp->value))
			return (1);
	}
	tmp = change_value(envc, "SHLVL");
	if (tmp)
		(tmp->value[0])++;
	tmp = change_value(envc, "OLDPWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = NULL;
	}
	return (0);
}
