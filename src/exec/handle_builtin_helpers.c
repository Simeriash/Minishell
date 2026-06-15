/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin_helpers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 08:52:20 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/15 11:03:15 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/execute.h"

int	save_fds(t_fds *fds, int *saved_in, int *saved_out)
{
	if (fds->fd_in < 0 || fds->fd_out < 0)
		return (1);
	*saved_in = dup(fds->fd_in);
	if (*saved_in < 0)
		return (1);
	*saved_out = dup(fds->fd_out);
	if (*saved_out < 0)
	{
		close(*saved_in);
		return (1);
	}
	return (0);
}

int	redirect_builtin_fds(t_fds *fds)
{
	int	error;

	if (fds->fd_in != STDIN_FILENO)
	{
		error = dup2(fds->fd_in, STDIN_FILENO);
		if (error < 0)
			return (1);
	}
	if (fds->fd_out != STDOUT_FILENO)
	{
		error = dup2(fds->fd_out, STDOUT_FILENO);
		if (error < 0)
			return (1);
	}
	return (0);
}

int	restore_standard_fds(int saved_in, int saved_out)
{
	if (saved_in >= 0)
	{
		if (dup2(saved_in, STDIN_FILENO) == -1)
			return (1);
		close(saved_in);
	}
	if (saved_out >= 0)
	{
		if (dup2(saved_out, STDOUT_FILENO) == -1)
			return (1);
		close(saved_out);
	}
	return (0);
}

void	close_redirects(t_fds *fds)
{
	if (fds->redir_in == 1 && fds->fd_in > STDERR_FILENO)
	{
		close (fds->fd_in);
		fds->redir_in = 0;
	}
	if (fds->redir_out == 1 && fds->fd_out > STDERR_FILENO)
	{
		close (fds->fd_out);
		fds->redir_out = 0;
	}
}

int	builtin_redir_setup(t_ast *node, t_fds *fds, int *saved_in, int *saved_out)
{
	int	error;

	error = save_fds(fds, saved_in, saved_out);
	if (error == 1)
		return (1);
	apply_redirects(node, fds);
	if (fds->fd_in < 0 || fds->fd_out < 0)
	{
		close_redirects(fds);
		close(*saved_in);
		close(*saved_out);
		return (1);
	}
	error = redirect_builtin_fds(fds);
	if (error == 1)
	{
		close_redirects(fds);
		close(*saved_in);
		close(*saved_out);
		return (1);
	}
	return (0);
}
