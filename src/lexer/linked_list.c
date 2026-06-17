/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 16:06:07 by julauren          #+#    #+#             */
/*   Updated: 2026/06/17 08:55:54 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

t_token	*init_token_list(int *status)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
	{
		error_lexer(MALLOC, status);
		return (NULL);
	}
	token->type = NONE;
	token->value = NULL;
	token->next = NULL;
	return (token);
}

int	add_after(t_token *token, t_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(*new_token));
	if (!new_token)
	{
		if (value)
			free(value);
		return (1);
	}
	new_token->type = type;
	new_token->value = value;
	new_token->next = token->next;
	token->next = new_token;
	return (0);
}

void	free_token(t_token *token_list)
{
	t_token	*token;
	t_token	*tmp;

	token = token_list->next;
	while (token != NULL)
	{
		tmp = token->next;
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		free(token);
		token = tmp;
	}
	free(token_list);
}
