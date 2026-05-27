/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:51:01 by julauren          #+#    #+#             */
/*   Updated: 2026/05/27 15:24:44 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	free_cmd(t_cmd *cmd)
{
	t_redir	*tmp;
	t_redir	*redir;

	if (!cmd)
		return ;
	if (cmd->args)
		free(cmd->args);
	redir = cmd->redir;
	while (redir != NULL)
	{
		tmp = redir->next;
		free(redir);
		redir = tmp;
	}
	free(cmd);
}

int	free_ast(t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->cmd)
		free_cmd(ast->cmd);
	if (ast->left)
		free_ast(ast->left);
	if (ast->right)
		free_ast(ast->right);
	if (ast->token)
		free_token((ast->token));
	free(ast);
	return (0);
}

t_ast	*init_ast(t_type type, t_cmd *cmd, t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = malloc(sizeof(*ast));
	if (!ast)
	{
		free_cmd(cmd);
		free_ast(left);
		free_ast(right);
		return (NULL);
	}
	ast->token = NULL;
	ast->type = type;
	ast->cmd = cmd;
	ast->left = left;
	ast->right = right;
	return (ast);
}

static t_ast	*ast_node(t_token *token, t_token *stop)
{
	t_ast	*ast;
	t_ast	*ast_1;
	t_ast	*ast_2;
	t_token	*new_token;

	new_token = token->next;
	while (new_token != NULL && new_token != stop)
	{
		if (new_token->type == PIPE)
		{
			ast_1 = ast_creation(token, new_token, CMD);
			ast_2 = ast_creation(new_token, stop, PIPE);
			if ((!ast_1 || !ast_2) && !free_ast(ast_1) && !free_ast(ast_2))
				return (NULL);
			ast = init_ast(PIPE, NULL, ast_1, ast_2);
			return (ast);
		}
		new_token = new_token->next;
	}
	ast = init_ast(NONE, NULL, NULL, NULL);
	return (ast);
}

t_ast	*ast_creation(t_token *token, t_token *stop, t_type type)
{
	t_ast	*ast;

	if (type == PIPE)
	{
		ast = ast_node(token, stop);
		if (ast && ast->type == NONE)
			free(ast);
		else
			return (ast);
	}
	if (type == CMD || type == PIPE)
		ast = cmd_node(token, stop);
	return (ast);
}
