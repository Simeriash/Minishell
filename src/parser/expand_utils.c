/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:46:10 by julauren          #+#    #+#             */
/*   Updated: 2026/05/08 10:20:05 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static char	*check_key(char *key, t_env *envc)
{
	t_env	*tmp;
	char	*str;

	tmp = envc->next;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			str = ft_strdup(tmp->value);
			if (!str)
				return (NULL);
			return (str);
		}
		tmp = tmp->next;
	}
	str = malloc(sizeof(*str));
	if (!str)
		return (NULL);
	str[0] = '\0';
	return (str);
}

char	*check_env(t_token *token, t_env *envc, int i, int *j)
{
	char	*key;
	char	*new_value;

	while (ft_isalnum(token->value[*j]) || token->value[*j] == '_')
		(*j)++;
	key = ft_substr(token->value, i, *j - i);
	if (!key)
		return (NULL);
	new_value = check_key(key, envc);
	free(key);
	if (!new_value)
		return (NULL);
	return (new_value);
}
