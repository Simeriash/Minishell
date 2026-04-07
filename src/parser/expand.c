/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:35:16 by julauren          #+#    #+#             */
/*   Updated: 2026/04/07 16:48:41 by julauren         ###   ########.fr       */
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
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
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
	str = "";
	return (str);
}

int	change_value(t_token *token, char *new_value, int start, int end)
{
	char	*str;
	int		len;
	int		tmp;

	tmp = ft_strlen(new_value);
	len = ft_strlen(token->value) - (end - start + 1) + tmp;
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
	{
		free(new_value);
		return (1);
	}
	ft_strlcpy(str, token->value, start);
	ft_strlcat(str, new_value, len + 1);
	ft_strlcat(str, &token->value[end], len + 1);
	free(new_value);
	free(token->value);
	token->value = str;
	return (0);
}

int	expand(t_token *token_list, t_env *envc)
{
	t_token	*tmp;
	t_error	error;

	tmp = token_list->next;
	while (tmp != NULL)
	{
		if (tmp->type == EXPAND)
		{
			error = expander(tmp, envc);
			if (error)
			{
				error_parser(token_list, envc, error);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
