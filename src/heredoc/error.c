/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:05:03 by julauren          #+#    #+#             */
/*   Updated: 2026/05/28 11:53:57 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/error.h"

void	error_heredoc(t_error error)
{
	if (error == INVALID_LIMITER)
		ft_putendl_fd("Invalid limiter", 2);
	else if (error == FD)
		ft_putendl_fd("Error FD", 2);
	else if (error == MALLOC)
		ft_putendl_fd("Error malloc", 2);
}
