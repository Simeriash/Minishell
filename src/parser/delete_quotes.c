/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 14:58:22 by julauren          #+#    #+#             */
/*   Updated: 2026/04/16 15:01:43 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	delete_quotes(t_token *token_list)
{
	int		i;
	int		j;
	t_state	state;
	t_token	*tmp;

	tmp = token_list->next;
	state = NORMAL;
	while (tmp != NULL)
	{
		i = 0;
		j = 0;
		if (tmp->type == WORD)
		{
			while (tmp->value[i] != '\0')
			{
				state_condition(tmp->value[j], &state);
				if (state != NORMAL)
				{
					j++;
					while (state != NORMAL && tmp->value[j] != '\0')
					{
						tmp->value[i++] = tmp->value[j++];
						state_condition(tmp->value[j], &state);
					}
					j++;
					if (tmp->value[j] == '\0')
					{
						tmp->value[i] = tmp->value[j];
						break ;
					}
					continue ;
				}
				if (state == NORMAL && j != i)
				{
					while (state == NORMAL && tmp->value[j] != '\0')
					{
						tmp->value[i++] = tmp->value[j++];
						state_condition(tmp->value[j], &state);
					}
					if (tmp->value[j] == '\0')
					{
						tmp->value[i] = tmp->value[j];
						break ;
					}
					state = NORMAL;
					continue ;
				}
				i++;
				j++;
			}
		}
		tmp = tmp->next;
	}
}
