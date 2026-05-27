/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:40:12 by julauren          #+#    #+#             */
/*   Updated: 2026/05/27 15:24:41 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/error.h"
#include "../../inc/lexer.h"

void	error_parser(t_token *token_list, t_error error)
{
	free_token(token_list);
	if (error == MALLOC)
		ft_putendl_fd("Error malloc", 2);
}
