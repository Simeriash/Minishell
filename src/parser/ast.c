/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:51:01 by julauren          #+#    #+#             */
/*   Updated: 2026/05/06 09:41:17 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static t_ast	*ast_node(t_token *token, t_token *stop, t_type t_1, t_type t_2)
{
	t_ast	*ast;
	t_ast	*ast_1;
	t_ast	*ast_2;
	t_token	*new_token;

	new_token = token->next;
	while (new_token != NULL && new_token != stop)
	{
		if (new_token->type == t_1)
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
		ast = ast_node(token, stop, PIPE, CMD);
		if (ast && ast->type == NONE)
			free(ast);
		else
			return (ast);
	}
	if (type == CMD || type == PIPE || type == AND || type == OR)
	{
		ast = looking_for_cmd(token, stop);
		return (ast);
	}
	ast = init_ast(NONE, NULL, NULL, NULL);
	return (ast);
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

t_ast	*create_ast(t_token *token_list, t_token **stop)
{
	t_ast	*ast;
	t_ast	*ast_1;
	t_ast	*ast_2;
	t_ast	*ast_tmp;
	t_token	*token;
	t_type	type;

	//ast = ast_creation(token_list, NULL, OR);
	if (token_list->type != LEFT_PARENTHESIS)
	{
		token = token_list->next;
		while (!token && token->type != LEFT_PARENTHESIS)
			token = token->next;
		if (token != token_list->next)
		{
			ast_1 = ast_creation(token_list, token, OR);
			ast_2 = create_ast(token, stop);
			ast_tmp = init_ast(PARENTHESIS, NULL, NULL, NULL);
			if ((!ast_1 || !ast_2 || !ast_tmp) && !free_ast(&ast_1) && !free_ast(&ast_2) && free_ast(&ast_tmp))
				return (NULL);
			ast_tmp->left = ast_2;
			type = which_type(token_list, token);
			ast = init_ast(type, NULL, ast_1, ast_tmp);
			return (ast);
		}
	}
	else
	{
		token = token_list->next;
		while (!token && token->type != LEFT_PARENTHESIS)
			token = token->next;
	}
	return (ast);
}
