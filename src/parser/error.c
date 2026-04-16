/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:40:12 by julauren          #+#    #+#             */
/*   Updated: 2026/04/14 13:35:24 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	error_parser(t_token *token_list, t_env *envc, t_error error)
{
	(void)error;
	(void)envc;
	free_token(token_list);
	// free_env(envc);
	ft_putendl_fd("Error parser", 2);
	//	/!\		A REFAIRE
}
