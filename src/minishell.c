/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:09:01 by julauren          #+#    #+#             */
/*   Updated: 2026/06/11 14:36:43 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/execute.h"
#include "../inc/parser.h"

static void	handler(int signum)
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

static int	cmd_minishell(char *cmd, t_env *envc, t_ast **ast, int status)
{
	t_token	*token;

	if (cmd[0] == '\0')
	{
		free(cmd);
		return (1);
	}
	token = lexer(cmd);
	free(cmd);
	if (!token)
		return (1);
	*ast = parser(token, envc, status);
	if (!(*ast))
		return (1);
	return (0);
}

static char	*ft_readline(void)
{
	char	*cmd;

	set_signal_action(0);
	cmd = readline("\033[32mGhost\\>: \033[39m");
	if (cmd)
		add_history(cmd);
	set_signal_action(1);
	return (cmd);
}

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	t_env	*envc;
	t_ast	*ast;
	int		status;

	(void)argc;
	(void)argv;
	status = 0;
	envc = env_copy(envp);
	if (!envc)
		return (1);
	while (1)
	{
		cmd = ft_readline();
		if (!cmd)
			break ;
		if (cmd_minishell(cmd, envc, &ast, status))
			continue ;
		status = execute_tree(ast, &envc, STDIN_FILENO, STDOUT_FILENO);
		free_ast(ast);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	ft_free_envc(envc);
	return (0);
}
