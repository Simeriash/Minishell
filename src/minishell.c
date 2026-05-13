/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:09:01 by julauren          #+#    #+#             */
/*   Updated: 2026/05/13 14:55:54 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "./exec/execute.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	while (1)
	{
		signal(SIGINT, &handler);
		signal(SIGQUIT, SIG_IGN);
		char *input = readline("TestShell > ");
		if (!input)
		{
			printf("exit\n");
			return (0);
		}
		if (strcmp(input, "") == 0)
			continue ;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		char **splinput = ft_split(input, ' ');
		free(input);
		t_tree *head = makenode("PIPE");
		t_tree *node_l = makenode(splinput[0]);
		t_tree *node_r = makenode(splinput[1]);

		head->left = node_l;
		head->right = node_r;
		head->head = head;
		execute_tree(head, envp, STDIN_FILENO, STDOUT_FILENO);
		free_tree(head);
		free_array(splinput);

	}
	return (0);
}
