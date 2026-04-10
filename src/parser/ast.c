/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:51:01 by julauren          #+#    #+#             */
/*   Updated: 2026/04/10 13:18:56 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static t_ast	*init_ast(t_type type, t_cmd *cmd, t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = malloc(sizeof(*ast));
	if (!ast)
		return (NULL);
	ast->type = type;
	ast->cmd = cmd;
	ast->left = left;
	ast->right = right;
	return (ast);
}

static t_ast	*ast_node(t_token *token, t_token *stop, t_type t_1, t_type t_2)
{
	t_ast	*ast;
	t_ast	*tmp_1;
	t_ast	*tmp_2;
	t_token	*new_token;

	new_token = token->next;
	while (new_token != NULL && new_token != stop)
	{
		if (new_token->type == t_1)
		{
			tmp_1 = ast_creation(token, new_token, t_2);
			tmp_2 = ast_creation(new_token, stop, t_1);
			if ((!tmp_1 || !tmp_2) && !free_ast(tmp_1) && !free_ast(tmp_2))
				return (NULL);
			ast = init_ast(t_1, NULL, tmp_1, tmp_2);
			return (ast);
		}
		new_token = new_token->next;
	}
	ast = malloc(sizeof(*ast));
	if (!ast)
		return (NULL);
	ast->type = NONE;
	return (ast);
}

static t_ast	*ast_next_creation(t_token *token, t_token *stop, t_type type)
{
	t_ast	*ast;

	if (type == PIPE || type == AND || type == OR)
	{
		ast = ast_node(token, stop, PIPE, WORD);
		if (ast && ast->type == NONE)
			free(ast);
		else
			return (ast);
	}
	if (type == WORD || type == PIPE || type == AND || type == OR)
	{

	}
	return (NULL);
}

t_ast	*ast_creation(t_token *token, t_token *stop, t_type type)
{
	t_ast	*ast;

	if (type == OR)
	{
		ast = ast_node(token, stop, OR, AND);
		if (ast && ast->type == NONE)
			free(ast);
		else
			return (ast);
	}
	if (type == AND || type == OR)
	{
		ast = ast_node(token, stop, AND, PIPE);
		if (ast && ast->type == NONE)
			free(ast);
		else
			return (ast);
	}
	ast = ast_next_creation(token, stop, type);
	return (ast);
}
