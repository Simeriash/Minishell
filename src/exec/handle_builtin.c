/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:17:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/12 16:29:04 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/execute.h"
#include "../../inc/parser.h"

static void	error_helper(t_ast *node)
{
	write(2, "Ghost\\>: ", ft_strlen("Ghost\\>: "));
	write(2, node->cmd->redir->file, ft_strlen(node->cmd->redir->file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

t_builtin_func	get_builtin(char **args, t_env **envpcpy)
{
	int					i;
	static t_builtins	func_array[] = {
	{"cd", ft_cd},
	{"echo", ft_echo},
	{"env", ft_env},
	{"exit", ft_exit},
	{"export", ft_export},
	{"pwd", ft_pwd},
	{"unset", ft_unset},
	{NULL, NULL}
	};

	(void)envpcpy;
	i = 0;
	while (func_array[i].cmd)
	{
		if (ft_strcmp(args[0], func_array[i].cmd) == 0)
			return (func_array[i].function);
		i++;
	}
	return (NULL);
}

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
	if (fds->fd_in != STDIN_FILENO)
		close (fds->fd_in);
	if (fds->fd_out != STDOUT_FILENO)
		close (fds->fd_out);
}

// int	builtin_setup(t_ast *node, t_fds *fds, int *saved_in, int *saved_out)
// {
// 	int	error;

// 	error = save_fds(fds, saved_in, saved_out);
// 	if (error == 1)
// 		return (1);
// 	apply_redirects(node, &fds->fd_in, &fds->fd_out);
// 	if (fds->fd_in < 0)
// 		return (1);
// 	error = redirect_builtin_fds(fds);
// 	if (error == 1)
// 		return (1);
// }

int	execute_builtin(t_env **env, t_ast *node, t_fds *fds, t_builtin_func func)
{
	int				error;
	int				status;
	int				saved_fd_in;
	int				saved_fd_out;

	error = save_fds(fds, &saved_fd_in, &saved_fd_out);
	if (error == 1)
		return (1);
	apply_redirects(node, &fds->fd_in, &fds->fd_out); //builtin setup here
	if (fds->fd_in < 0)
	{
		error_helper(node);
		close(saved_fd_in);
		close(saved_fd_out);
		return (1);
	}
	error = redirect_builtin_fds(fds);
	if (error)
		return (1);
	status = func(node->cmd->args, env);
	error = restore_standard_fds(saved_fd_in, saved_fd_out);
	if (error)
		return (1);
	close_redirects(fds);
	if (ft_strcmp("exit", node->cmd->args[0]) == 0)
	{
		free_ast(node);
		exit(status);
	}
	return (status);
}
