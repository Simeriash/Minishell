/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:40:12 by julauren          #+#    #+#             */
/*   Updated: 2026/03/27 14:36:57 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include <unistd.h>

void	exit_parser(t_token *token_list, t_env *envc, t_error error)
{
	(void)error;
	(void)envc;
	free_token(token_list);
	// free_env(envc);
	write(2, "Error parser\n", 14);
	//	/!\		A REFAIRE
}
