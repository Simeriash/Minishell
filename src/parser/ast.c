/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:51:01 by julauren          #+#    #+#             */
/*   Updated: 2026/04/29 15:13:40 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static t_ast	*ast_node(t_token *token, t_token *stop, t_type t_1, t_type t_2)
{
	t_ast	*ast;
	t_ast	*ast_1;
	t_ast	*ast_2;
	t_token	*new_token;
	t_cmd	*cmd;

	new_token = token->next;
	while (new_token != NULL && new_token != stop)
	{
		if (t_2 == NONE && new_token->type == WORD)
		{
			cmd = looking_for_cmd(new_token, stop);
			if (!cmd)
				return (NULL);
			if (cmd->args == NULL && cmd->redir->type == NONE)
				free_cmd(&cmd);
			ast = init_ast(CMD, cmd, NULL, NULL);
			return (ast);
		}
		else if (new_token->type == t_1)
		{
			ast_1 = ast_creation(token, new_token, t_2);
			ast_2 = ast_creation(new_token, stop, t_1);
			if ((!ast_1 || !ast_2) && !free_ast(&ast_1) && !free_ast(&ast_2))
				return (NULL);
			ast = init_ast(t_1, NULL, ast_1, ast_2);
			return (ast);
		}
		new_token = new_token->next;
	}
	ast = init_ast(NONE, NULL, NULL, NULL);
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
		ast = ast_node(token, stop, WORD, NONE);
		if (ast && ast->type == NONE)
			free(ast);
		else
			return (ast);
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
