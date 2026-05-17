/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:38 by julauren          #+#    #+#             */
/*   Updated: 2026/05/17 08:25:56 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/error.h"

void	error_lexer(t_error error)
{
	if (error == MALLOC)
		ft_putendl_fd("Error malloc", 2);
	if (error == OPEN_QUOTE)
		ft_putendl_fd("Error open quote", 2);
}
