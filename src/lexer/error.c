/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:38 by julauren          #+#    #+#             */
/*   Updated: 2026/04/14 12:55:33 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"

void	error_lexer(t_error error)
{
	(void)error;
	ft_putendl_fd("Error", 2);
	//	/!\		A REFAIRE
}
