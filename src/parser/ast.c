/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:51:01 by julauren          #+#    #+#             */
/*   Updated: 2026/04/10 09:53:45 by julauren         ###   ########.fr       */
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

t_ast	*ast_creation(t_token *token, t_token *stop, t_type type)
{
	t_ast	*ast;
	t_ast	*tmp_1;
	t_ast	*tmp_2;
	t_token	*new_token;
	t_token	*tmp;

	new_token = token->next;
	tmp = new_token;
	if (type == OR)
	{
		while (new_token != NULL && new_token != stop)
		{
			if (new_token->type == OR)
			{
				tmp_1 = ast_creation(token, new_token, AND);
				tmp_2 = ast_creation(new_token, stop, OR);
				if ((!tmp_1 || !tmp_2) && !free_ast(tmp_1) && !free_ast(tmp_2))
					return (NULL);
				ast = init_ast(OR, NULL, tmp_1, tmp_2);
				return (ast);
			}
		}
	}
	new_token = tmp;
	if (type == AND || type == OR)
	{
		while (new_token != NULL && new_token != stop)
		{
			if (new_token->type == AND)
			{
				tmp_1 = ast_creation(token, new_token, PIPE);
				tmp_2 = ast_creation(new_token, stop, AND);
				if ((!tmp_1 || !tmp_2) && !free_ast(tmp_1) && !free_ast(tmp_2))
					return (NULL);
				ast = init_ast(AND, NULL, tmp_1, tmp_2);
				return (ast);
			}
		}
	}
	new_token = tmp;
	if (type == PIPE || type == AND || type == OR)
	{
		while (new_token != NULL && new_token != stop)
		{
			if (new_token->type == PIPE)
			{
				tmp_1 = ast_creation(token, new_token, WORD);
				tmp_2 = ast_creation(new_token, stop, PIPE);
				if ((!tmp_1 || !tmp_2) && !free_ast(tmp_1) && !free_ast(tmp_2))
					return (NULL);
				ast = init_ast(PIPE, NULL, tmp_1, tmp_2);
				return (ast);
			}
		}
	}
	return (ast);
}
