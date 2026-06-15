/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:41:20 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/15 11:02:11 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

char	*find_executable(char *cmd, t_exec_err *err, t_env **env)
{
	char	**paths;
	char	*ret;

	*err = EXEC_OK;
	if (!cmd || !*cmd)
	{
		*err = EXEC_NOT_FOUND;
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
		{
			*err = EXEC_MALLOC_FAIL;
			return (NULL);
		}
		return (ret);
	}
	paths = create_paths(err, env);
	if (!paths)
		return (NULL);
	ret = create_candidate(cmd, paths, err);
	free_array(paths);
	return (ret);
}

char	*handle_executable(t_ast *node, t_env **env)
{
	t_exec_err	err;
	char		*exe;

	exe = find_executable(node->cmd->args[0], &err, env);
	if (!exe)
	{
		ft_printf_fd(2, "Ghost: %s: command not found\n", node->cmd->args[0]);
		return (NULL);
	}
	return (exe);
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

int	prep_for_execve(t_ast *node, t_env **env, char **exec)
{
	*exec = handle_executable(node, env);
	if (!*exec)
		return (127);
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
	error = prep_for_execve(node, envp, &executable);
	if (error)
		return (error);
	status = run_command(node, fds, executable, envp);
	free(executable);
	return (status);
}
