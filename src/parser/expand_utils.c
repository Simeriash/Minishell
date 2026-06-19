/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:46:10 by julauren          #+#    #+#             */
/*   Updated: 2026/06/19 15:53:20 by julauren         ###   ########.fr       */
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

static char	*env_init(char *value, t_env *envc, int i, int *j)
{
	char	*key;
	char	*tmp;

	while (ft_isalnum(value[*j]) || value[*j] == '_')
		(*j)++;
	key = ft_substr(value, i, *j - i);
	if (!key)
		return (NULL);
	tmp = check_key(key, envc);
	free(key);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*check_env(char *value, t_env *envc, int i, int *j)
{
	char	*new_value;
	char	*tmp;
	int		len;

	tmp = env_init(value, envc, i, j);
	if (!tmp)
		return (NULL);
	if (tmp[0] == '\0')
		return (tmp);
	len = ft_strlen(tmp);
	new_value = malloc(sizeof(*new_value) * (len + 4));
	if (!new_value)
	{
		free(tmp);
		return (NULL);
	}
	new_value[0] = '\0';
	ft_strlcat(new_value, "\"", 3);
	ft_strlcat(new_value, tmp, len + 3);
	ft_strlcat(new_value, "\"", len + 3);
	free(tmp);
	return (new_value);
}

void	ft_memcpy_exp(char *str, t_index *index, int delta)
{
	int	i;
	int	j;

	i = index->i;
	j = index->i + delta;
	while (str[j])
	{
		str[i] = str[j];
		i++;
		j++;
	}
	str[i] = str[j];
	(index->i)--;
	(index->j)--;
}

int	condition_to_expand(t_token *token, t_index index, t_state state)
{
	if (ft_isspace(token->value[index.i])
		|| (state == DOUBLE_QUOTE && token->value[index.i] == '"'))
		return (1);
	return (0);
}
