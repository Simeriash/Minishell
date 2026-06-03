/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:42:36 by julauren          #+#    #+#             */
/*   Updated: 2026/06/03 16:31:40 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

void	set_to_null(t_ast **ast)
{
	if ((*ast)->left)
		set_to_null(&(*ast)->left);
	if ((*ast)->cmd && !(*ast)->cmd->args && !(*ast)->cmd->redir)
	{
		free((*ast)->cmd);
		free(*ast);
		*ast = NULL;
	}
	if ((*ast)->right)
		set_to_null(&(*ast)->right);
}

static int	redir_out(t_ast *ast, t_redir *redir)
{
	int		fd;

	if (redir->type == OUT || redir->type == APPEND)
	{
		if (!redir->file)
		{
			ft_putendl_fd("bash: syntax error near unexpected \
token `newline'", 2);
			return (1);
		}
		if (!ast->cmd->args)
		{
			fd = open(redir->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
			close(fd);
		}
	}
	return (0);
}

static int	redir_in(t_redir *redir)
{
	if (redir->type == IN)
	{
		if (!redir->file)
		{
			ft_putendl_fd("bash: syntax error near unexpected \
token `newline'", 2);
			return (1);
		}
		if (access(redir->file, F_OK))
		{
			ft_printf_fd(2, "bash: %s: %s\n", redir->file, strerror(errno));
			return (1);
		}
	}
	return (0);
}

int	pipe_error(t_ast *ast)
{
	t_redir	*tmp;
	int		i;

	i = 0;
	if (ast->left && pipe_error(ast->left))
		i++;
	if (ast->cmd)
	{
		if (ast->cmd->redir)
		{
			tmp = ast->cmd->redir;
			while (tmp)
			{
				if (redir_in(tmp) || redir_out(ast, tmp))
					return (1);
				tmp = tmp->next;
			}
		}
	}
	if (ast->right && pipe_error(ast->right))
		i++;
	return (i);
}
