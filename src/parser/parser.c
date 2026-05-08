/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:01:42 by julauren          #+#    #+#             */
/*   Updated: 2026/05/06 12:04:23 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_ast	*parser(t_token *token_list, t_env *envc)
{
	t_ast	*ast;

	if (expand(token_list, envc))
		return (NULL);
	ast = ast_creation(token_list, NULL, PIPE);
	if (!ast)
	{
		error_parser(token_list, envc, MALLOC);
		return (NULL);
	}
	return (ast);
}
