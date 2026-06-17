/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:38 by julauren          #+#    #+#             */
/*   Updated: 2026/06/17 07:50:37 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/error.h"

void	error_lexer(t_error error, int *status)
{
	if (error == MALLOC)
	{
		ft_putendl_fd("Error malloc", 2);
		*status = 1;
	}
	if (error == OPEN_QUOTE)
	{
		ft_putendl_fd("unexpected EOF while looking for matching `''", 2);
		*status = 2;
	}
}
