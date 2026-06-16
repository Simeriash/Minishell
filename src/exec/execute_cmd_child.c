/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd_child.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 09:05:43 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/16 08:10:00 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/execute.h"

static void	cleanup(char *exec, t_fds *fds, t_env **env, t_ast *node)
{
	rl_clear_history();
	close_redirects(fds);
	ft_free_envc(*env);
	free_ast(node->ast);
	free(exec);
}

static char	**child_setup(t_ast *node, t_fds *fds, t_env **env, char *exec)
{
	char	**env_array;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	apply_redirects(node, fds);
	env_array = make_env_execve((*env)->next);
	if (!env_array || !*env_array)
	{
		free_ast(node->ast);
		ft_free_envc(*env);
		free (exec);
		exit(1);
	}
	return (env_array);
}

int	reap_child_process(pid_t child_process)
{
	int	status;

	waitpid(child_process, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

void	child_exec(t_ast *node, t_fds *fds, char *exec,	t_env **env)
{
	char	**env_array;
	int		status;

	env_array = child_setup(node, fds, env, exec);
	if (fds->fd_in >= 0 && fds->fd_out >= 0)
	{
		if (fds->fd_in != STDIN_FILENO)
		{
			dup2(fds->fd_in, STDIN_FILENO);
			close(fds->fd_in);
		}
		if (fds->fd_out != STDOUT_FILENO)
		{
			dup2(fds->fd_out, STDOUT_FILENO);
			close(fds->fd_out);
		}
		execve(exec, node->cmd->args, env_array);
	}
	status = execve_error_msg(exec);
	cleanup(exec, fds, env, node);
	free_array(env_array);
	exit(status);
}

int	run_command(t_ast *node, t_fds *fds, char *exec, t_env **env)
{
	pid_t	child_proc;
	int		ret_stat;

	child_proc = fork();
	if (child_proc == -1)
	{
		free (exec);
		return (1);
	}
	if (child_proc == 0)
		child_exec(node, fds, exec, env);
	ret_stat = reap_child_process(child_proc);
	return (ret_stat);
}
