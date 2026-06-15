/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:17:30 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/15 10:06:36 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/builtins.h"
#include "../../inc/execute.h"
#include "../../inc/parser.h"

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
		free_ast(node->ast);
		if (fds->fd_in != STDIN_FILENO)
			close(fds->fd_in);
		if (fds->fd_out != STDOUT_FILENO)
			close(fds->fd_out);
		exit(status);
	}
	return (status);
}
