/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:51:01 by julauren          #+#    #+#             */
/*   Updated: 2026/04/09 16:00:03 by julauren         ###   ########.fr       */
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

static void	free_ast(t_ast *ast)
{
	t_redir	*tmp;
	t_redir	*redir;

	if (ast->cmd)
	{
		free(ast->cmd->args);
		redir = ast->cmd->redir;
		while (redir != NULL)
		{
			tmp = redir->next;
			free(redir);
			redir = tmp;
		}
	}
	if (ast->left)
	{
		free_ast(ast->left);
		free(ast->left);
	}
	if (ast->right)
	{
		free_ast(ast->right);
		free(ast->right);
	}
	free(ast);
}

static int	ast_error(t_ast *ast_1, t_ast *ast_2)
{
	if (ast_1)
	{
		free_ast(ast_1);
		ast_1 = NULL;
	}
	if (ast_2)
	{
		free_ast(ast_2);
		ast_2 = NULL;
	}
	return (0);
}

t_ast	*ast_creation(t_token *token_list, t_token *stop)
{
	t_ast		*ast;
	t_ast		*tmp_1;
	t_ast		*tmp_2;
	t_token		*token;

	token = token_list->next;
	while (token != NULL && token != stop)
	{
		if (token->type == OR)
		{
			tmp_1 = ast_creation(token_list, token);
			tmp_2 = ast_creation(token, stop);
			if ((!tmp_1 || !tmp_2) && !ast_error(tmp_1, tmp_2))
				return (NULL);
			ast = init_ast(token->type, NULL, tmp_1, tmp_2);
		}
		if (token->type == AND)
		{
			tmp_1 = ast_creation(token_list, token);
			tmp_2 = ast_creation(token, stop);
			if ((!tmp_1 || !tmp_2) && !ast_error(tmp_1, tmp_2))
				return (NULL);
			ast = init_ast(token->type, NULL, tmp_1, tmp_2);
		}
		if (token->type == PIPE)
		{
			tmp_1 = ast_creation(token_list, token);
			tmp_2 = ast_creation(token, stop);
			if ((!tmp_1 || !tmp_2) && !ast_error(tmp_1, tmp_2))
				return (NULL);
			ast = init_ast(token->type, NULL, tmp_1, tmp_2);
		}
	}
	return (ast);
}
