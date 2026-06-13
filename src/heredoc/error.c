/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:05:03 by julauren          #+#    #+#             */
/*   Updated: 2026/06/13 11:02:52 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/error.h"

void	error_heredoc(t_error error)
{
	if (error == INVALID_LIMITER)
		ft_putendl_fd("bash: syntax error near unexpected token `newline'", 2);
	else if (error == FD)
		ft_putendl_fd("Error FD", 2);
	else if (error == MALLOC)
		ft_putendl_fd("Error malloc", 2);
}
