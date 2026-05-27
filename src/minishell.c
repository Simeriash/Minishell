/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:09:01 by julauren          #+#    #+#             */
/*   Updated: 2026/05/27 14:02:46 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execute.h"
#include "../inc/parser.h"
#include <readline/chardefs.h>

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
}

static void	set_signal_action(int i)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	if (i == 0)
		act.sa_handler = &handler;
	else
		act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
}

int main(int argc, char **argv, char **envp)
{
	char				*cmd;
	t_token				*token;
	t_env				*envc;
	t_ast				*ast;
	(void)argc;
	(void)argv;

	envc = env_copy(envp);
	while (1)
	{
		set_signal_action(0);
		cmd = readline("Ghost\\>: ");
		if (!cmd)
			break ;
		if (cmd[0] == '\0')
		{
			free(cmd);
			continue ;
		}
		set_signal_action(1);
		token = lexer(cmd);
		free(cmd);
		ast = parser(token, envc);
		if (!ast)
			continue ;
		execute_tree(ast, envp, STDIN_FILENO, STDOUT_FILENO);
		free_token(&token);
		free_ast(ast);
	}
	ft_free_envc(envc);
	printf("exit\n");
	return (0);
}
