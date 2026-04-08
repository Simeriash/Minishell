/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:51:01 by julauren          #+#    #+#             */
/*   Updated: 2026/04/08 16:44:30 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static t_ast	*ini_ast(t_node_type type, t_cmd cmd, t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = malloc(sizeof(*ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	if (type == NODE_CMD)
		ast->cmd = cmd;
	else
	{
		ast->cmd.args = NULL;
		ast->cmd.redir = NULL;
	}
	ast->left = left;
	ast->right = right;
	return (ast);
}

t_ast	*ast_creation(t_token *token_list)
{
	t_ast	*ast;

	return (ast);
}
