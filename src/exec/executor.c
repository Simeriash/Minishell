/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:04:33 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/22 09:17:17 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"
#include "../../inc/parser.h"

void	clean_exit(t_ast *node, t_env **env, int ret)
{
	free_ast(node);
	ft_free_envc(*env);
	rl_clear_history();
	exit(ret);
}

t_ast	*build_pipe(t_ast *node, t_env **envp, int *current_in)
{
	int		fd[2];
	int		ret;
	pid_t	pid;

	while (node->type == PIPE)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			ret = execute_tree(node->left, envp, *current_in, fd[1]);
			if (*current_in > -1 && *current_in != STDIN_FILENO)
				close(*current_in);
			if (fd[1] > -1)
				close(fd[1]);
			clean_exit(node->ast, envp, ret);
		}
		close(fd[1]);
		if (*current_in != STDIN_FILENO)
			close(*current_in);
		*current_in = fd[0];
		node = node->right;
	}
	return (node);
}

int	wait_pids(pid_t last_pid)
{
	int		ret_val;
	int		status;
	pid_t	pid;

	ret_val = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid <= 0)
			break ;
		if (pid == last_pid)
			ret_val = status;
	}
	if (WIFEXITED(ret_val))
		return (WEXITSTATUS(ret_val));
	if (WIFSIGNALED(ret_val))
		return (128 + WTERMSIG(ret_val));
	return (0);
}

int	execute_pipe(t_ast *node, t_env **envp, t_fds *fds)
{
	int		current_in;
	pid_t	last_pid;
	int		ret_val;
	t_ast	*head;

	current_in = fds->fd_in;
	head = node->ast;
	node = build_pipe(node, envp, &current_in);
	last_pid = fork();
	if (last_pid == 0)
	{
		ret_val = execute_tree(node, envp, current_in, fds->fd_out);
		if (current_in != STDIN_FILENO)
			close(current_in);
		clean_exit(head, envp, ret_val);
	}
	if (current_in != STDIN_FILENO)
		close(current_in);
	ret_val = wait_pids(last_pid);
	return (ret_val);
}

int	execute_tree(t_ast *node, t_env **envp, int in_fd, int out_fd)
{
	int		ret;
	t_fds	fds_in_out;

	fds_in_out.fd_in = in_fd;
	fds_in_out.fd_out = out_fd;
	fds_in_out.redir_in = 0;
	fds_in_out.redir_out = 0;
	if (node->type == PIPE)
	{
		ret = execute_pipe(node, envp, &fds_in_out);
		return (ret);
	}
	if (node->type == CMD)
	{
		ret = execute_cmd(node, envp, &fds_in_out);
		if (access("minishell_heredoc", F_OK) == 0)
			unlink("minishell_heredoc");
		return (ret);
	}
	return (0);
}
