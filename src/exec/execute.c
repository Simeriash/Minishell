/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:39:08 by dlanehar          #+#    #+#             */
/*   Updated: 2026/04/15 08:29:39 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <string.h>

int execute_tree(t_tree *node, char **envp);
int	execute_pipe(t_tree *node, char **envp);
int	execute_cmd(t_tree *node, char **envp);

int execute_tree(t_tree *node, char **envp)
{
	if (node->value == PIPE)
		execute_pipe(node, envp);
	if (node->value == CMD)
		execute_cmd(node, envp);
	if (node->value == 99)
		printf("%s\n", node->str);
	return 0;
}

int	execute_cmd(t_tree *node, char **envp)
{
	char *arr[2] = {"wc", NULL};

	execve("/bin/wc", arr, envp);
}

int	pipefunc(int *fd, int unused, int used, int newfd, t_tree *side, char **envp)
{
	int ret;

	close(fd[unused]);
	dup2(fd[used], newfd);
	ret = execute_tree(side, envp);
	close(fd[used]);
	return (ret);
}

int	execute_pipe(t_tree *node, char **envp)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		ret = 0;
	int		status;

	if (pipe(fd) < 0)
		return (0);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute_tree(node->left, envp);
		exit (ret);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		execute_tree(node->right, envp);
		exit (ret);
	}
	close(fd[0]);
	close(fd[1]);
	return (0);
}

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
			node->value = PIPE;
		else if (my_strcmp(value, "CMD") == 0)
			node->value = CMD;
		else
		{
			node->value = 99;
			node->str = my_strdup(value);
		}
	}
	return (node);
}

int main(int argc, char **argv, char **envp)
{
	t_tree *n1 = makenode("PIPE");
	t_tree *n2 = makenode("PIPE");
	t_tree *n3 = makenode("CMD");

	n1->left = n2;
	n1->right = n3;

	execute_tree(n1, envp);

	free(n1);
	free(n2);
	free(n3);
}
