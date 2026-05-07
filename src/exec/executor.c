/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/06 10:04:33 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/07 15:47:41 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void free_tree(t_tree *node);

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;

    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_tree *build_pipe(t_tree *node, char **envp, int *current_in)
{
	int		fd[2];
	pid_t	pid;

	while (node->type == PIPE)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			execute_tree(node->left, envp, *current_in, fd[1]);

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
		return (128 + WTERMSIG(ret_val));
	return (0);
}

int execute_pipe(t_tree *node, char **envp, int in_fd, int out_fd)
{
	//int		fd[2];
	int		current_in;
	//pid_t   pid;
	pid_t	last_pid;
	int		ret;

	current_in = in_fd;
	node = build_pipe(node, envp, &current_in);
	last_pid = fork();
	if (last_pid == 0)
	{
		ret = execute_tree(node, envp, current_in, out_fd);
		exit(ret);
	}
	if (current_in != STDIN_FILENO)
		close(current_in);
	ret = wait_pids(last_pid);
	return (ret);
}

int execute_tree(t_tree *node, char **envp, int in_fd, int out_fd)
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

t_tree *makenode(char *value)
{
	static int i = 0;
	t_tree *node = calloc(1, sizeof(t_tree));
	node->cmd = NULL;
	if (node != NULL)
	{
		node->left = NULL;
		node->right = NULL;
		node->value = i;
		i++;
		if (my_strcmp(value, "PIPE") == 0)
			node->type = PIPE;
		else
		{
			node->type = CMD;
			node->cmd = calloc(1, sizeof(t_cmd));
			node->cmd->redirs = NULL;
			node->cmd->args = ft_split(value, ' ');
			int j = 0;
			while (node->cmd->args[j])
				printf("node args: %s\n", node->cmd->args[j++]);
		}
	}
	return (node);
}

void free_redirs(t_redirs *r)
{
	t_redirs *tmp;

	while (r)
	{
		tmp = r->redirs_next;
		free(r->redir_file);
		free(r);
		r = tmp;
	}
}

void free_cmd(t_cmd *cmd)
{
	int i;

	if (!cmd)
		return;

	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
			free(cmd->args[i++]);
		free(cmd->args);
	}

	free_redirs(cmd->redirs);
	free(cmd);
}

void free_tree(t_tree *node)
{
	if (!node)
		return;

	free_tree(node->left);
	free_tree(node->right);

	if (node->type == CMD)
		free_cmd(node->cmd);

	free(node);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	t_tree *head = makenode("PIPE");
	t_tree *node_l = makenode(argv[1]);
	t_tree *node_r = makenode(argv[2]);

	head->left = node_l;
	head->right = node_r;
	head->head = head;

	printf("Head: PIPE, left: CMD, right: CMD\n");
	execute_tree(head, envp, STDIN_FILENO, STDOUT_FILENO);
	free_tree(head);
}
