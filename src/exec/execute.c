/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:39:08 by dlanehar          #+#    #+#             */
/*   Updated: 2026/04/09 13:41:57 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include <string.h>

int execute_tree(t_tree *node);

int	pipething(t_tree *node)
{
	int		fd[2];
	char	buf[100];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		execute_tree(node->left);
	}
}

int execute_tree(t_tree *node)
{
	if (node->value == PIPE)
	{
		pipething(node);
		pid_t pid = fork();

		if (pid == 0)
		{
			printf("%s\n", tmp->left->str);
			close(fd[0]);
			write(fd[1], tmp->left->str, strlen(tmp->left->str));
			free(tmp->str);
			close(fd[1]);
			return (0);
		}
		else
		{
			close(fd[1]);
			waitpid(pid, NULL, 0);
			read(fd[0], buf, 100);
			printf("%s\n", buf);
			close(fd[0]);
		}
		return (0);
	}
	return 0;
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
		else
			node->str = my_strdup(value);
	}
	return (node);
}

int main(int argc, char **argv)
{
	t_tree *n1 = makenode("PIPE");
	t_tree *n2 = makenode("banana");
	t_tree *n3 = makenode("book balls");

	n1->left = n2;
	n1->right = n3;

	execute_tree(n1);

	free(n1);
	free(n2);
	free(n3);
}
