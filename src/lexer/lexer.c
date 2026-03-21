/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:19:55 by julauren          #+#    #+#             */
/*   Updated: 2026/03/21 15:25:28 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	lexer(char *str)
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
	state = GENERAL;
	while (str[i] != '\0')
	{
		while (ft_isspace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '\'' && state == GENERAL)
			state = SIMPLE_QUOTE;
		else if (str[i] == '\'' && state == SIMPLE_QUOTE)
			state = GENERAL;
		else if (str[i] == '"' && state == GENERAL)
			state = DOUBLE_QUOTE;
		else if (str[i] == '"' && state == DOUBLE_QUOTE)
			state = GENERAL;
		if (state == GENERAL)
		{
			if (str[i] == '<' || str[i] == '>' || str[i] == '|'
				|| str[i] == '&' || str[i] == '(' || str[i] == ')')
			{
				if (create_token_meta(str, token_list, &i, &nb_token))
					break ;
			}
			else
			{
				if (create_token_word(str, token_list, &i, &nb_token))
					break ;
			}
		}
		else if (state == SIMPLE_QUOTE)
		{
			i++;
			//create_token_quote(token_list, &i, SIMPLE_QUOTE);
		}
		else if (state == DOUBLE_QUOTE)
		{
			i++;
			//create_token_quote(token_list, &i, DOUBLE_QUOTE);
		}
		// i++;
	}
	if (state != GENERAL || nb_token == -1)
	{
		/*error open quote*/;
	}
}
