/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:46:10 by julauren          #+#    #+#             */
/*   Updated: 2026/06/17 08:50:05 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

char	*check_key(char *key, t_env *envc)
{
	t_env	*tmp;
	char	*str;

	tmp = envc->next;
	while (tmp != NULL)
	{
		if (ft_strcmp(key, tmp->key) == 0)
		{
			if (tmp->value)
				str = ft_strdup(tmp->value);
			else
				break ;
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

char	*check_env(char *value, t_env *envc, int i, int *j)
{
	char	*key;
	char	*new_value;

	while (ft_isalnum(value[*j]) || value[*j] == '_')
		(*j)++;
	key = ft_substr(value, i, *j - i);
	if (!key)
		return (NULL);
	new_value = check_key(key, envc);
	free(key);
	return (new_value);
}

void	ft_memcpy_exp(char *str, int n)
{
	int	i;
	int	j;

	i = n - 1;
	j = n;
	while (str[j])
	{
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = str[j];
}

int	condition_to_expand(t_token *token, t_index index, t_state state)
{
	if (ft_isspace(token->value[index.i])
		|| (state == DOUBLE_QUOTE && token->value[index.i] == '"'))
		return (1);
	return (0);
}
