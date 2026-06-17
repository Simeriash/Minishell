/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:30:30 by julauren          #+#    #+#             */
/*   Updated: 2026/06/17 10:47:08 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

int	g_sig;

static int	init_heredoc(char *eof, t_var *var, pid_t *pid, int *status)
{
	if (delimiter(&var->limiter, eof, status))
		return (1);
	var->fd = open("minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (var->fd < 0)
	{
		error_heredoc(FD, status);
		return (1);
	}
	g_sig = 0;
	*pid = fork();
	return (0);
}

static int	cmd_heredoc(char **cmd, char *eof, int *status)
{
	rl_clear_history();
	set_signal_heredoc(0);
	*cmd = readline("heredoc>: ");
	set_signal_heredoc(1);
	if (!(*cmd))
	{
		if (!g_sig)
		{
			ft_printf_fd(2, "warning: here-document at line 1 delimited\
by end-of-file (wanted `%s')\n", eof);
			*status = 2;
		}
		else
			*status = 130;
		return (1);
	}
	if (!ft_strcmp(*cmd, eof))
		return (1);
	return (0);
}

static int	heredoc_suite(char **cmd, t_token *token_list, t_env *envc, \
t_var *var)
{
	if (heredoc_expander(cmd, envc, var->status))
	{
		free_heredoc(token_list, envc, *cmd, var->fd);
		return (1);
	}
	return (0);
}

static void	printline(char *cmd, int fd)
{
	ft_putendl_fd(cmd, fd);
	free(cmd);
}

int	heredoc(char *eof, t_token *token_list, t_env *envc, int *status)
{
	char	*cmd;
	pid_t	pid;
	int		pid_status;
	t_var	var;

	var.status = status;
	if (init_heredoc(eof, &var, &pid, status))
		return (1);
	if (pid == 0)
	{
		while (1)
		{
			if (cmd_heredoc(&cmd, eof, status))
				break ;
			if (var.limiter && heredoc_suite(&cmd, token_list, envc, &var))
				exit (1);
			printline(cmd, var.fd);
		}
		free_heredoc(token_list, envc, cmd, var.fd);
		exit(0);
	}
	else
		wait(&pid_status);
	close(var.fd);
	return (0);
}
