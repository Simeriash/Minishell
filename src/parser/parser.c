/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:01:42 by julauren          #+#    #+#             */
/*   Updated: 2026/06/11 15:06:42 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	search_suite(t_token *token_list, t_token *token, t_env *envc, \
int status)
{
	if (heredoc(token->next->value, token_list, envc, status))
	{
		free_token(token_list);
		return (1);
	}
	else
	{
		free(token->next->value);
		token->next->value = ft_strdup("minishell_heredoc");
		if ((!token->next->value))
		{
			error_parser(token_list, MALLOC);
			return (1);
		}
	}
	return (0);
}

static int	search_heredoc(t_token *token_list, t_env *envc, int status)
{
	t_token	*token;

	token = token_list->next;
	while (token != NULL)
	{
		if (token->type == HEREDOC)
		{
			if (!(token->next) || (token->next && !(token->next->value)))
			{
				free_token(token_list);
				error_heredoc(INVALID_LIMITER);
				return (1);
			}
			if (search_suite(token_list, token, envc, status))
				return (1);
			token = token->next;
		}
		token = token->next;
	}
	return (0);
}

t_ast	*parser(t_token *token_list, t_env *envc, int status)
{
	t_ast	*ast;

	if (expand(token_list, envc, status)
		|| search_heredoc(token_list, envc, status))
		return (NULL);
	ast = ast_creation(token_list, NULL, PIPE);
	if (!ast)
	{
		error_parser(token_list, MALLOC);
		return (NULL);
	}
	ast->token = token_list;
	ast_init(&ast, ast);
	if (pipe_error(ast))
	{
		free_ast(ast);
		return (NULL);
	}
	return (ast);
}
