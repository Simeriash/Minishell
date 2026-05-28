/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 08:48:09 by julauren          #+#    #+#             */
/*   Updated: 2026/05/28 15:03:34 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/envc.h"

static int	ft_str_chr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

static int	next_copy(char *envpi, t_env *last)
{
	int		n;
	char	*key;
	char	*value;

	n = ft_str_chr(envpi);
	key = ft_substr(envpi, 0, n);
	if (!key)
		return (1);
	value = ft_substr(envpi, n + 1, ft_strlen(envpi));
	if (!value)
	{
		free(key);
		return (1);
	}
	if (add_after_envc(last, key, value))
		return (1);
	return (0);
}

t_env	*env_copy(char **envp)
{
	t_env	*envc;
	t_env	*last;
	int		i;

	envc = init_envc_list();
	if (!envc)
		return (NULL);
	last = envc;
	i = 0;
	while (envp[i])
	{
		if (next_copy(envp[i], last))
		{
			error_envc(envc);
			return (NULL);
		}
		last = last->next;
		i++;
	}
	if (init_envc(envc))
	{
		error_envc(envc);
		return (NULL);
	}
	return (envc);
}
