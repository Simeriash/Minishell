/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:38 by julauren          #+#    #+#             */
/*   Updated: 2026/03/28 12:16:28 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include <unistd.h>

void	error_lexer(t_error error)
{
	(void)error;
	write(2, "Error\n", 7);
	//	/!\		A REFAIRE
}
