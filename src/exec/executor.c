/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:04:33 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/27 15:47:56 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"
#include "../../inc/parser.h"

// void free_tree(t_tree *node);

// int my_strcmp(const char *s1, const char *s2)
// {
//     int i = 0;

//     while (s1[i] && s2[i] && s1[i] == s2[i])
//         i++;

//     return ((unsigned char)s1[i] - (unsigned char)s2[i]);
// }

t_ast *build_pipe(t_ast *node, t_env **envp, int *current_in)
{
	int		fd[2];
	pid_t	pid;
	t_ast	*head;

	head = node;
	while (node->type == PIPE)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			execute_tree(node->left, envp, *current_in, fd[1]);
			// if (*current_in != STDIN_FILENO)
			// 	close(*current_in);
			close(fd[1]);
			free_ast(head);
			ft_free_envc(*envp);
			exit(1);
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
			break;
		if (pid == last_pid)
			ret_val = status;
	}
	if (WIFEXITED(ret_val))
		return (WEXITSTATUS(ret_val));
	if (WIFSIGNALED(ret_val))
	{
		if (WTERMSIG(ret_val) == SIGQUIT)
			write(2, "Quit\n", 6);
		dprintf(2 , "\n");
		return (128 + WTERMSIG(ret_val));
	}
	return (0);
}

int execute_pipe(t_ast *node, t_env **envp, int in_fd, int out_fd)
{
	int		current_in;
	pid_t	last_pid;
	int		ret;
	t_ast	*head;

	current_in = in_fd;
	head = node;
	node = build_pipe(node, envp, &current_in);
	last_pid = fork();
	if (last_pid == 0)
	{
		ret = execute_tree(node, envp, current_in, out_fd);
		if (current_in != STDIN_FILENO)
			close(current_in);
		free_ast(head);
		ft_free_envc(*envp);
		exit(ret);
	}
	if (current_in != STDIN_FILENO)
		close(current_in);
	ret = wait_pids(last_pid);
	if (WIFSIGNALED(ret))
	{
		if (WTERMSIG(ret) == SIGQUIT)
			dprintf(2, "Quit");
		dprintf(2, "\n");
		return (128 + WTERMSIG(ret));
	}
	return (ret);
}

int execute_tree(t_ast *node, t_env **envp, int in_fd, int out_fd)
{
	int ret;

	if (node->type == PIPE)
	{
		ret = execute_pipe(node, envp, in_fd, out_fd);
		return (ret);
	}
	if (node->type == CMD)
	{
		ret = execute_cmd(node, node->cmd->args, envp, in_fd, out_fd);
		return (ret);
	}
	return (0);
}

// t_ast *makenode(char *value)
// {
// 	static int i = 0;
// 	if (!value)
// 		return NULL;
// 	t_ast *node = calloc(1, sizeof(t_ast));
// 	node->cmd = NULL;
// 	if (node != NULL)
// 	{
// 		node->left = NULL;
// 		node->right = NULL;
// 		node->value = i;
// 		i++;
// 		if (my_strcmp(value, "PIPE") == 0)
// 			node->type = PIPE;
// 		else
// 		{
// 			node->type = CMD;
// 			node->cmd = calloc(1, sizeof(t_cmd));
// 			node->cmd->redir = NULL;
// 			node->cmd->args = ft_split(value, ' ');
// 		}
// 	}
// 	return (node);
// }

// void free_redirs(t_redir *r)
// {
// 	t_redir *tmp;

// 	while (r)
// 	{
// 		tmp = r->redirs_next;
// 		free(r->redir_file);
// 		free(r);
// 		r = tmp;
// 	}
// }

// void free_cmd(t_cmd *cmd)
// {
// 	int i;

// 	if (!cmd)
// 		return;

// 	if (cmd->args)
// 	{
// 		i = 0;
// 		while (cmd->args[i])
// 			free(cmd->args[i++]);
// 		free(cmd->args);
// 	}

// 	free_redirs(cmd->redir);
// 	free(cmd);
// }

// void free_tree(t_ast *node)
// {
// 	if (!node)
// 		return;

// 	free_tree(node->left);
// 	free_tree(node->right);

// 	if (node->type == CMD)
// 		free_cmd(node->cmd);

// 	free(node);
// }

/*

exec(args)
{
	pid = fork();
	if (0 == pid)
	{
		if (redirect_output)
		{
			dup2 for the output;
		}
		if (redirect_input)
		{
			dup2 for the input;
		}
		close(all);

		exeve(cmd);
	}
	return (pid);
}

cmds array : char **cmd[]

int pipe1[2];src/exec/execute.h
int pipe2[2];

int pids[nbr_cmd];

if (nbr_cmd == 1)
	exec(cmd[0], NULL, NULL);

pipe(pipe1);
pids[0] = exec(cmd[0], pipe1, NULL); Redirect output here, not input
index = 1;
while (cmd[index])
{
	if (index < nbr_cmd -1)
	{
		pipe(pipe2);
		pids[index] = exec(cmd[index], pipe2, pipe1) reirect input and output
		close(pipe1[0]);
		close(pipe1[1]);
		pipe1[0] = pipe2[0];
		pipe1[1] = pipe2[1];
		++index;
		continue;
	}
	pids[index] = exec(cmd[index], NULL, pipe1); Redirect input, not output
	close(pipe[0]);
	close(pipe[1]);
	++index;
}
for (pid in pids)
	waitpid(pid);
*/
