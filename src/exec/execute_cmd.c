/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:41:20 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/16 15:38:29 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

static	char *copy_direct_path(char *cmd, t_exec_err *err)
{
	char *ret;

	ret = ft_strdup(cmd);
	if (!ret)
	{
		*err = EXEC_MALLOC_FAIL;
		return (NULL);
	}
	return (ret);
}

char	*find_executable(char *cmd, t_exec_err *err, t_env **env)
{
	char	**paths;
	char	*ret;

	*err = EXEC_OK;
	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		ret = copy_direct_path(cmd, err);
		return (ret);
	}
	paths = create_paths(err, env);
	if (!paths)
	{
		if (*err == EXEC_MALLOC_FAIL)
			return (NULL);
		ret = ft_strdup(cmd);
	}
	else
	{
		ret = create_candidate(cmd, paths, err);
		free_array(paths);
	}
	return (ret);
}

int	handle_builtin(t_ast *node, t_env **env, t_fds *fds)
{
	t_builtin_func	func;
	int				ret_stat;

	func = get_builtin(node->cmd->args, env);
	if (func)
	{
		ret_stat = execute_builtin(env, node, fds, func);
		return (ret_stat);
	}
	return (-1);
}

int	prep_command(t_ast *node, t_env **env, char **exec)
{
	t_exec_err	err;

	*exec = find_executable(node->cmd->args[0], &err, env);
	if (!*exec)
	{
		ft_printf_fd(2, "Ghost: %s: command not found\n", node->cmd->args[0]);
		*exec = NULL;
		return (127);
	}
	return (0);
}

int	execute_cmd(t_ast *node, t_env **envp, t_fds *fds)
{
	char	*executable;
	int		error;
	int		status;

	if (!node->cmd->args)
		return (0);
	error = handle_builtin(node, envp, fds);
	if (error != -1)
		return (error);
	error = prep_command(node, envp, &executable);
	if (error)
		return (error);
	status = run_command(node, fds, executable, envp);
	free(executable);
	return (status);
}
