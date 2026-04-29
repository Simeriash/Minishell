/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 17:02:54 by julauren          #+#    #+#             */
/*   Updated: 2026/04/29 15:08:04 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	free_cmd(t_cmd **cmd)
{
	t_redir	*tmp;
	t_redir	*redir;
	int		i;

	if (!(*cmd))
		return ;
	i = -1;
	if ((*cmd)->args)
	{
		while ((*cmd)->args[++i])
			free((*cmd)->args[i]);
		free((*cmd)->args);
	}
	redir = (*cmd)->redir;
	while (redir != NULL)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
	free(*cmd);
	*cmd = NULL;
}

int	free_ast(t_ast **ast)
{
	if (!(*ast))
		return (0);
	if ((*ast)->cmd)
		free_cmd(&((*ast)->cmd));
	if ((*ast)->left)
		free_ast(&((*ast)->left));
	if ((*ast)->right)
		free_ast(&((*ast)->right));
	free(*ast);
	*ast = NULL;
	return (0);
}

t_ast	*init_ast(t_type type, t_cmd *cmd, t_ast *left, t_ast *right)
{
	t_ast	*ast;

	ast = malloc(sizeof(*ast));
	if (!ast)
	{
		free_cmd(&cmd);
		free_ast(&left);
		free_ast(&right);
	}
		return (NULL);
	ast->type = type;
	ast->cmd = cmd;
	ast->left = left;
	ast->right = right;
	return (ast);
}
