/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 12:31:31 by julauren          #+#    #+#             */
/*   Updated: 2026/05/29 11:29:56 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

static int	test_limiter(char *eof, int i, int *limiter)
{
	if ((eof[0] && eof[1]) && (eof[0] == eof[1])
		&& (eof[0] == '\'' || eof[0] == '"'))
	{
		error_heredoc(INVALID_LIMITER);
		return (1);
	}
	if ((eof[0] == '\'' || eof[0] == '"') && eof[0] == eof[i - 1])
		*limiter = 0;
	else if ((eof[0] == '\'' || eof[0] == '"') && eof[0] != eof[i - 1])
	{
		error_heredoc(INVALID_LIMITER);
		return (1);
	}
	return (0);
}

static void	change_eof(char *eof)
{
	int		i;
	int		j;
	t_state	state;

	i = 0;
	j = 1;
	state = NORMAL;
	state_condition(eof[i], &state);
	while (state != NORMAL && eof[j] != '\0')
	{
		eof[i++] = eof[j++];
		state_condition(eof[j], &state);
	}
	if (eof[j] == '\0' || eof[++j] == '\0')
		eof[i] = eof[j];
}

int	delimiter(int *limiter, char *eof)
{
	int		i;
	t_state	state;

	i = 0;
	*limiter = 1;
	state = NORMAL;
	while (eof[i] != '\0')
	{
		state_condition(eof[i], &state);
		if (ft_isspace(eof[i]))
		{
			error_heredoc(INVALID_LIMITER);
			return (1);
		}
		i++;
	}
	if (test_limiter(eof, i, limiter))
		return (1);
	if (*limiter == 0)
		change_eof(eof);
	return (0);
}

void	free_heredoc(t_token *token_list, t_env *envc, char *cmd, int fd)
{
	close(fd);
	free_token(token_list);
	ft_free_envc(envc);
	if (cmd)
		free(cmd);
	else
	{
		unlink("minishell_heredoc");
		exit (0);
	}
}
