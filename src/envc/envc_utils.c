/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 14:46:00 by julauren          #+#    #+#             */
/*   Updated: 2026/06/19 17:58:23 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/envc.h"

static t_env	*check_key(t_env *envc, char *key)
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

static char	*ft_getpwd(void)
{
	char	*buf;
	char	*value;

	buf = NULL;
	value = getcwd(buf, 0);
	free(buf);
	return (value);
}

static int	init_env_node(t_env *envc, char *var, char *value)
{
	t_env	*tmp;
	char	*new_value;
	char	*key;

	tmp = check_key(envc, var);
	new_value = ft_strdup(value);
	if (!(new_value))
		return (1);
	if (tmp)
	{
		free(tmp->value);
		tmp->value = new_value;
	}
	else
	{
		key = ft_strdup(var);
		if (!key)
		{
			free(new_value);
			return (1);
		}
		if (add_after_envc(envc, key, new_value))
			return (1);
	}
	return (0);
}

static int	init_env_shlvl(t_env *envc)
{
	t_env	*tmp;

	tmp = check_key(envc, "SHLVL");
	if (tmp)
		(tmp->value[0])++;
	else
	{
		if (init_env_node(envc, "SHLVL", "1"))
			return (1);
	}
	return (0);
}

int	init_envc(t_env *envc)
{
	char	*new_pwd;

	new_pwd = ft_getpwd();
	if (!new_pwd || init_env_node(envc, "SHELL", "/minishell")
		|| init_env_node(envc, "PWD", new_pwd)
		|| init_env_node(envc, "OLDPWD", " "))
	{
		free(new_pwd);
		return (1);
	}
	free(new_pwd);
	if (init_env_shlvl(envc))
		return (1);
	if (init_env_node(envc, "PATH", "/home/julauren/bin:/home/julauren/\
.nix-profile/bin:/nix/var/nix/profiles/default/bin:/usr/local/sbin:/usr/local/bin:\
/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"))
		return (1);
	return (0);
}
