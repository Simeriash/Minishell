/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:42:38 by julauren          #+#    #+#             */
/*   Updated: 2026/03/26 12:05:10 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/lexer.h"
#include <unistd.h>

void	exit_lexer(t_token *token_list, t_error error)
{
	(void)error;
	if (token_list)
		free_token(token_list);
	write(2, "Error\n", 7);
	//	/!\		A REFAIRE
}
