/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:09:01 by julauren          #+#    #+#             */
/*   Updated: 2026/05/27 09:40:10 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execute.h"
#include "../inc/parser.h"

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
	char	*cmd;
	t_token	*token;
	t_env	*envc;
	t_ast	*ast;
	(void)argc;
	(void)argv;

	envc = env_copy(envp);
	while (1)
	{
		signal(SIGINT, &handler);
		signal(SIGQUIT, SIG_IGN);
		cmd = readline("Ghost\\>: ");
		if (!cmd)
			break ;
		if (cmd[0] == '\0')
		{
			free(cmd);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		// char **splinput = ft_split(input, ' ');
		// free(input);
		// t_tree *head = makenode("PIPE");
		// t_tree *node_l = makenode(splinput[0]);
		// t_tree *node_r = makenode(splinput[1]);

		// head->left = node_l;
		// head->right = node_r;
		// head->head = head;
		token = lexer(cmd);
		ast = parser(token, envc);
		execute_tree(ast, envp, STDIN_FILENO, STDOUT_FILENO);
		free_ast(ast);
		free(cmd);
		free_token(token);
		// free_array(splinput);

	}
	free(cmd);
	ft_free_envc(envc);
	printf("exit\n");
	return (0);
}

