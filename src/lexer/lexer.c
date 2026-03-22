/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:19:55 by julauren          #+#    #+#             */
/*   Updated: 2026/03/22 10:55:46 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include <stdlib.h>

t_token	*lexer(char *str)
{
	int		i;
	int		nb_token;
	t_state	state;
	t_token	*token_list;

	token_list = init_token_list();
	if (!token_list)
		exit(EXIT_FAILURE);		//		/!\ A CHANGER !!
	i = 0;
	nb_token = 0;
	state = NORMAL;
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '\'' && state == NORMAL)
			state = SIMPLE_QUOTE;
		else if (str[i] == '\'' && state == SIMPLE_QUOTE)
			state = NORMAL;
		else if (str[i] == '"' && state == NORMAL)
			state = DOUBLE_QUOTE;
		else if (str[i] == '"' && state == DOUBLE_QUOTE)
			state = NORMAL;
		if (state == NORMAL)
		{
			if (str[i] == '\'' || str[i] == '"')
			{	i++;
				if (str[i] == '\0')
					break ;
				continue ;
			}
			if (str[i] == '<' || str[i] == '>' || str[i] == '|'
				|| str[i] == '&' || str[i] == '(' || str[i] == ')')
			{
				if (meta_token(str, token_list, &i, &nb_token))
					break ;
			}
			else
			{
				if (word_token(str, token_list, &i, &nb_token))
					break ;
			}
		}
		else if (state == SIMPLE_QUOTE)
		{
			if (quote_token(str, token_list, &i, SIMPLE_QUOTE))
				break ;
		}
		else if (state == DOUBLE_QUOTE)
		{
			if (quote_token(str, token_list, &i, DOUBLE_QUOTE))
				break ;
		}
	}
	if (state != NORMAL || nb_token == -1)
	{
		/*error open quote || malloc*/;
		free_token(token_list);
		exit(EXIT_FAILURE);
	}
	return (token_list);
}
