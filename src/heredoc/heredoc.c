/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:30:30 by julauren          #+#    #+#             */
/*   Updated: 2026/05/27 17:17:19 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

int	g_sig;

static int	next_expander(char **cmd, t_env *envc, int *i, int *j)
{
	char	*new_value;
	int		len;

	new_value = check_new_value(*cmd, envc, *i, j);
	if (new_value && change_value(cmd, new_value, *i, *j))
	{
		error_heredoc(MALLOC);
		return (1);
	}
	len = ft_strlen(new_value);
	free(new_value);
	*i = *i + len - 1;
	return (0);
}

static int	expander(char **cmd, t_env *envc, int fd)
{
	int	i;
	int	j;

	i = 0;
	while ((*cmd)[i] != '\0')
	{
		if ((*cmd)[i] == '$')
		{
			i++;
			if ((*cmd)[i] == '\0')
				return (0);
			if (ft_isspace((*cmd)[i]))
				continue ;
			j = i + 1;
			if (next_expander(cmd, envc, &i, &j))
			{
				free(*cmd);
				close(fd);
				return (1);
			}
		}
		else
			i++;
	}
	return (0);
}

int	heredoc(char *eof, t_token *token_list, t_env *envc)
{
	char	*cmd;
	int		fd;
	int		limiter;
	pid_t	pid;
	int		status;

	if (delimiter(&limiter, eof))
		return (1);
	fd = open("minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		error_heredoc(FD);
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		g_sig = 0;
		while (1)
		{
			set_signal_heredoc(0);
			cmd = readline("heredoc>: ");
			set_signal_heredoc(1);
			if (!cmd)
			{
				if (!g_sig)
					ft_putendl_fd("warning: here-document at line 1 delimited\
 by end-of-file (wanted `eof')", 2);
				break ;
			}
			if (!ft_strcmp(cmd, eof))
				break ;
			if (limiter && expander(&cmd, envc, fd))
			{
				free_token(token_list);
				ft_free_envc(envc);
				exit (1);
			}
			ft_putendl_fd(cmd, fd);
			free(cmd);
		}
		close(fd);
		if (!cmd)
		{
			free_token(token_list);
			ft_free_envc(envc);
			unlink("minishell_heredoc");
			exit (1);
		}
		free(cmd);
		free_token(token_list);
		ft_free_envc(envc);
		exit(0);
	}
	else
		wait(&status);
	close(fd);
	return (0);
}
