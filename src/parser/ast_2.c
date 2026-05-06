/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:40:52 by julauren          #+#    #+#             */
/*   Updated: 2026/05/05 13:05:03 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

t_ast	*ast_create(t_token *token_list, t_token *stop, t_type type)
{
	t_ast	*ast;
	t_ast	*ast_1;
	t_ast	*ast_2;
	t_token	*token;
	t_cmd	*cmd;

	if (type == OR)
	{
		token = token_list->next;
		while (token != NULL && token != stop)
		{
			if (token->type == OR)
			{
				ast_1 = ast_create(token_list, token, AND);
				ast_2 = ast_create(token, stop, OR);
				if ((!ast_1 || !ast_2) && !free_ast(&ast_1) && !free_ast(&ast_2))
					return (NULL);
				ast = init_ast(OR, NULL, ast_1, ast_2);
				return (ast);
			}
			token = token->next;
		}
	}
	if (type == AND || type == OR)
	{
		token = token_list->next;
		while (token != NULL && token != stop)
		{
			if (token->type == AND)
			{
				ast_1 = ast_create(token_list, token, AND);
				ast_2 = ast_create(token, stop, PIPE);
				if ((!ast_1 || !ast_2) && !free_ast(&ast_1) && !free_ast(&ast_2))
					return (NULL);
				ast = init_ast(AND, NULL, ast_1, ast_2);
				return (ast);
			}
			token = token->next;
		}
	}
	if (type == PIPE || type == AND || type == OR)
	{
		token = token_list->next;
		while (token != NULL && token != stop)
		{
			if (token->type == PIPE)
			{
				ast_1 = ast_create(token_list, token, PIPE);
				ast_2 = ast_create(token, stop, CMD);
				if ((!ast_1 || !ast_2) && !free_ast(&ast_1) && !free_ast(&ast_2))
					return (NULL);
				ast = init_ast(PIPE, NULL, ast_1, ast_2);
				return (ast);
			}
			token = token->next;
		}
	}
	if (type == CMD || type == PIPE || type == AND || type == OR)
	{
		token = token_list->next;
		while (token != NULL && token != stop)
		{
			if (token->type == CMD)
			{
				cmd = looking_for_cmd(token, stop);
				if (!cmd)
					return (NULL);
				if (cmd->args == NULL && cmd->redir->type == NONE)
					free_cmd(&cmd);
				ast = init_ast(CMD, NULL, NULL, NULL);
				return (ast);
			}
			token = token->next;
		}
	}
	return (ast);
}
