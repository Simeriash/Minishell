/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:40:12 by julauren          #+#    #+#             */
/*   Updated: 2026/06/17 07:55:38 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/error.h"
#include "../../inc/lexer.h"

void	error_parser(t_token *token_list, t_error error, int *status)
{
	free_token(token_list);
	if (error == MALLOC)
	{
		ft_putendl_fd("Error malloc", 2);
		*status = 1;
	}
}
