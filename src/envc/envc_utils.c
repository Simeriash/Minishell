/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:46:00 by julauren          #+#    #+#             */
/*   Updated: 2026/05/19 15:36:26 by julauren         ###   ########.fr       */
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

static int	ft_get_oldpwd(t_env *envc, char *value)
{
	char	*key;

	key = ft_strdup("OLDPWD");
	if (!key)
		return (1);
	if (add_after_envc(envc, key, value))
	{
		free(key);
		free(value);
		return (1);
	}
	return (0);
}

static char	*ft_getpwd(t_env *envc)
{
	char	*buf;
	char	*value;
	char	*key;

	buf = NULL;
	value = getcwd(buf, 0);
	free(buf);
	key = ft_strdup("PWD");
	if (!key)
	{
		free(value);
		return (NULL);
	}
	if (add_after_envc(envc, key, value))
	{
		free(value);
		free(key);
		return (NULL);
	}
	return (value);
}

static int	init_pwd(t_env *envc)
{
	t_env	*tmp;
	char	*value;

	tmp = change_value(envc, "PWD");
	if (!tmp)
	{
		value = ft_getpwd(envc);
		if (!value)
			return (1);
	}
	else
	{
		value = ft_strdup(tmp->value);
		if (!value)
			return (1);
	}
	tmp = change_value(envc, "OLDPWD");
	if (!tmp && ft_get_oldpwd(envc, value))
		return (1);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = value;
	}
	return (0);
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
	if (init_pwd(envc))
		return (1);
	return (0);
}
