/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:30:30 by julauren          #+#    #+#             */
/*   Updated: 2026/05/28 11:53:12 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

int	g_sig;

static int	init_heredoc(char *eof, int *limiter, int *fd, pid_t *pid)
{
	if (delimiter(limiter, eof))
		return (1);
	*fd = open("minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*fd < 0)
	{
		error_heredoc(FD);
		return (1);
	}
	g_sig = 0;
	*pid = fork();
	return (0);
}

static int	cmd_heredoc(char **cmd, char *eof)
{
	set_signal_heredoc(0);
	*cmd = readline("heredoc>: ");
	set_signal_heredoc(1);
	if (!(*cmd))
	{
		if (!g_sig)
			ft_putendl_fd("warning: here-document at line 1 delimited\
by end-of-file (wanted `eof')", 2);
		return (1);
	}
	if (!ft_strcmp(*cmd, eof))
		return (1);
	return (0);
}

static int	heredoc_suite(char **cmd, t_token *token_list, t_env *envc, int fd)
{
	if (heredoc_expander(cmd, envc))
	{
		free_heredoc(token_list, envc, *cmd, fd);
		return (1);
	}
	return (0);
}

static void	printline(char *cmd, int fd)
{
	ft_putendl_fd(cmd, fd);
	free(cmd);
}

int	heredoc(char *eof, t_token *token_list, t_env *envc)
{
	char	*cmd;
	int		fd;
	int		limiter;
	pid_t	pid;
	int		status;

	if (init_heredoc(eof, &limiter, &fd, &pid))
		return (1);
	if (pid == 0)
	{
		while (1)
		{
			if (cmd_heredoc(&cmd, eof))
				break ;
			if (limiter && heredoc_suite(&cmd, token_list, envc, fd))
				exit (1);
			printline(cmd, fd);
		}
		free_heredoc(token_list, envc, cmd, fd);
		exit(0);
	}
	else
		wait(&status);
	close(fd);
	return (0);
}
