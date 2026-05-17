/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 10:42:34 by julauren          #+#    #+#             */
/*   Updated: 2026/05/17 12:48:36 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/envc.h"

t_env	*init_envc_list(void)
{
	t_env	*envc;

	envc = malloc(sizeof(*envc));
	if (!envc)
	{
		error_envc(NULL);
		return (NULL);
	}
	envc->key = NULL;
	envc->value = NULL;
	envc->next = NULL;
	return (envc);
}

int	add_after(t_env *envc, char *key, char *value)
{
	t_env	*new_envc;

	new_envc = malloc(sizeof(*new_envc));
	if (!new_envc)
	{
		if (key)
			free(key);
		if (value)
			free(value);
		return (1);
	}
	new_envc->key = key;
	new_envc->value = value;
	new_envc->next = envc->next;
	envc->next = new_envc;
	return (0);
}

void	ft_free_envc(t_env *envc)
{
	t_env	*tmp;
	t_env	*new_envc;

	new_envc = envc->next;
	while (new_envc)
	{
		tmp = new_envc->next;
		if (new_envc->key)
			free(new_envc->key);
		if (new_envc->value)
			free(new_envc->value);
		free(new_envc);
		new_envc = tmp;
	}
	free(envc);
}
