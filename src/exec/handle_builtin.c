/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:17:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/17 09:36:19 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/execute.h"
#include "../../inc/parser.h"

static void	clean_exit(t_env **env, t_ast *node, t_fds *fds, int status)
{
	if (fds->fd_in != STDIN_FILENO)
		close(fds->fd_in);
	if (fds->fd_out != STDOUT_FILENO)
		close(fds->fd_out);
	free_ast(node->ast);
	ft_free_envc(*env);
	exit(status);
}

static int	dont_exit(char **args)
{
	int	i;
	int	j;
	int	ctrl;

	ctrl = 0;
	i = 0;
	j = 0;
	if (args[1])
	{
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]))
				i++;
			else
				return (0);
		}
		ft_longatoi(args[1], &ctrl);
		if (ctrl == -1)
			return (0);
		while (args[j])
			j++;
	}
	if (j > 2)
		return (1);
	return (0);
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

int	execute_builtin(t_env **env, t_ast *node, t_fds *fds, t_builtin_func func)
{
	int				error;
	int				status;
	int				saved_fd_in;
	int				saved_fd_out;

	error = builtin_redir_setup(node, fds, &saved_fd_in, &saved_fd_out);
	if (error)
		return (1);
	status = func(node->cmd->args, env);
	error = restore_standard_fds(saved_fd_in, saved_fd_out);
	if (error)
		return (1);
	close_redirects(fds);
	if (ft_strcmp("exit", node->cmd->args[0]) == 0)
	{
		if (dont_exit(node->cmd->args) == 0)
			clean_exit(env, node, fds, status);
	}
	return (status);
}
