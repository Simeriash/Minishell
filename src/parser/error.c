/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:40:12 by julauren          #+#    #+#             */
/*   Updated: 2026/05/08 12:58:40 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	error_parser(t_token *token_list, t_error error)
{
	free_token(token_list);
	if (error == MALLOC)
		ft_putendl_fd("Error malloc", 2);
}
