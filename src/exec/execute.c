/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:39:08 by dlanehar          #+#    #+#             */
/*   Updated: 2026/04/30 12:32:52 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <string.h>

int execute_tree(t_tree *node, char **envp, int in_fd, int out_fd);

int my_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;

    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

#include <stdlib.h>

char *my_strdup(const char *src)
{
    int i = 0;
    char *dup;

    // find length
    while (src[i])
        i++;

    // allocate memory (+1 for '\0')
    dup = malloc(sizeof(char) * (i + 1));
    if (!dup)
        return NULL;

    // copy string
    i = 0;
    while (src[i])
    {
        dup[i] = src[i];
        i++;
    }
    dup[i] = '\0';

    return dup;
}

t_tree *makenode(char *value)
{
	static int i = 0;
	t_tree *node = malloc(sizeof(t_tree));
	if (node != NULL)
	{
		node->left = NULL;
		node->right = NULL;
		node->value = i;
		i++;
		if (my_strcmp(value, "PIPE") == 0)
			node->type = PIPE;
		else if (my_strcmp(value, "AND") == 0)
			node->type = AND;
		else
		{
			node->type = CMD;
			if (strcmp("hello", value) == 0)
			{
				node->args = ft_split("ls", ' ');
				int j = 0;
				while (node->args[j])
					printf("node args: %s\n", node->args[j++]);
			}
			else if (strcmp("everyone", value) == 0)
			{
				node->args = ft_split("wc", ' ');
				int f = 0;
				while (node->args[f])
					printf("node args: %s\n", node->args[f++]);
			}
			node->str = my_strdup(value);
		}
	}
	return (node);
}

/*
	prefer method where we count number of tokens to then establish number of pipes to make.
	this allows creation of pid array that will then be used for waitpid.

	something along the lines of pid = ft_calloc();
	pid[i] = fork;
	then later
	while pid[i] != NULL
	{
		waitpid(pid[i], &status, 0);
	}
*/

int execute_pipe(t_tree *node, char **envp, int in_fd, int out_fd)
{
	int		fd[2];
	int		current_in;
	pid_t   pid;
	pid_t	last_pid;
	int		status;
	int		ret;

	current_in = in_fd;
	while (node->type == PIPE)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			close(fd[0]);
			execute_tree(node->left, envp, current_in, fd[1]);
			exit(1);
		}
		close(fd[1]);
		if (current_in != STDIN_FILENO)
			close(current_in);
		current_in = fd[0];
		node = node->right;
	}
	last_pid = fork();
	if (last_pid == 0)
	{
		ret = execute_tree(node, envp, current_in, out_fd);
		exit(ret);
	}
	if (current_in != STDIN_FILENO)
		close(current_in);
	while (1)
	{
    	pid = wait(&status);
    	if (pid <= 0)
        	break;
    	if (pid == last_pid)
    	    ret = status;
	}
	if (WIFEXITED(ret))
		return WEXITSTATUS(ret);
	if (WIFSIGNALED(ret))
		return 128 + WTERMSIG(ret);
	return (0);
}

int execute_tree(t_tree *node, char **envp, int in_fd, int out_fd)
{
	int ret;

	//--- PIPE ----
	int		fds[2];
	int		status;
	pid_t	left_node;
	pid_t	right_node;
	//--- ENDPIPE ---

	if (node->type == AND)
	{
		ret = execute_tree(node->left, envp, in_fd, out_fd);
		if (ret == 0)
			ret = execute_tree(node->right, envp, in_fd, out_fd);
		printf("It worked!\n");
		return (ret);
	}
	if (node->type == OR)
	{
		ret = execute_tree(node->left, envp, in_fd, out_fd);
		if (ret != 0)
			ret = execute_tree(node->right, envp, in_fd, out_fd);
		return (ret);
	}
	if (node->type == PIPE)
	{
		ret = execute_pipe(node, envp, in_fd, out_fd);
		return (ret);
	}
	if (node->type == CMD)
	{
		printf("We in this bih\n");
		execute_cmd(node, node->args, envp, in_fd, out_fd);
		return 0;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{

	t_tree *head = makenode("PIPE");
	t_tree *node_l = makenode("hello");
	t_tree *node_r = makenode("everyone");

	head->left = node_l;
	head->right = node_r;

	printf("Head: PIPE, left: CMD, right: CMD\n");
	execute_tree(head, envp, STDIN_FILENO, STDOUT_FILENO);
	free(head);
	free(node_l);
	free(node_r);
}
