/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 15:05:03 by julauren          #+#    #+#             */
/*   Updated: 2026/05/16 15:26:53 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

void	error_heredoc(t_error error)
{
	if (error == OPEN_QUOTE)
		ft_putendl_fd("Open quote", 2);
}
