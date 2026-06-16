/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:42:36 by julauren          #+#    #+#             */
/*   Updated: 2026/06/16 16:13:45 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	ast_init(t_ast **ast, t_ast *init_ast)
{
	if ((*ast)->left && (*ast)->type == PIPE)
		ast_init(&(*ast)->left, init_ast);
	if ((*ast)->cmd && !(*ast)->cmd->args && !(*ast)->cmd->redir)
	{
		free((*ast)->cmd);
		free(*ast);
		*ast = NULL;
		return ;
	}
	(*ast)->ast = init_ast;
	if ((*ast)->right && (*ast)->type == PIPE)
		ast_init(&(*ast)->right, init_ast);
}

static int	redir_out(t_ast *ast, t_redir *redir, int *status)
{
	int		fd;

	if (redir->type == OUT || redir->type == APPEND)
	{
		if (!redir->file)
		{
			ft_putendl_fd("Ghost: syntax error near unexpected \
token `newline'", 2);
			*status = 2;
			return (1);
		}
		if (!ast->cmd->args)
		{
			fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			*status = 2;
			close(fd);
		}
	}
	return (0);
}

static int	redir_in(t_redir *redir, int *status)
{
	if (redir->type == IN)
	{
		if (!redir->file)
		{
			ft_putendl_fd("Ghost: syntax error near unexpected \
token `newline'", 2);
			*status = 2;
			return (1);
		}
		if (access(redir->file, F_OK))
		{
			ft_printf_fd(2, "Ghost: %s: %s\n", redir->file, strerror(errno));
			*status = 1;
			return (1);
		}
	}
	return (0);
}

int	next_pipe(t_ast *ast, int *status)
{
	t_redir	*tmp;

	if (ast->cmd)
	{
		if (ast->cmd->redir)
		{
			tmp = ast->cmd->redir;
			while (tmp)
			{
				if (redir_in(tmp, status) || redir_out(ast, tmp, status))
					return (1);
				tmp = tmp->next;
			}
		}
	}
	return (0);
}

int	pipe_error(t_ast *ast, int *status)
{
	int		i;

	i = 0;
	if (ast->left && pipe_error(ast->left, status))
		i++;
	if (ast->type == PIPE)
	{
		if ((!ast->left || !ast->right)
			|| (ast->left && ast->left->type != PIPE && !ast->left->cmd)
			|| (ast->right && ast->right->type != PIPE && !ast->right->cmd))
		{
			ft_putendl_fd("Ghost: syntax error near unexpected \
token `|'", 2);
			*status = 2;
			return (1);
		}
	}
	if (next_pipe(ast, status))
		return (1);
	if (ast->right && pipe_error(ast->right, status))
		i++;
	if (i)
		return (1);
	return (0);
}
