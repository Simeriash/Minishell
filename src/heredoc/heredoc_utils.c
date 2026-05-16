/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/16 12:31:31 by julauren          #+#    #+#             */
/*   Updated: 2026/05/16 15:33:23 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

//	/!\ A EFFACER
static void	state_condition(char c, t_state *state)
{
	if (c == '\'' && *state == NORMAL)
		*state = SIMPLE_QUOTE;
	else if (c == '\'' && *state == SIMPLE_QUOTE)
		*state = NORMAL;
	else if (c == '"' && *state == NORMAL)
		*state = DOUBLE_QUOTE;
	else if (c == '"' && *state == DOUBLE_QUOTE)
		*state = NORMAL;
}

static int	test_limiter(char *eof, int i, int *limiter, t_state state)
{
	if (i == 2)
	{
		// error_heredoc(invalid_limiter);
		return (1);
	}
	if (state != NORMAL)
	{
		error_heredoc(OPEN_QUOTE);
		return (1);
	}
	if ((eof[0] == '\'' || eof[0] == '"') && eof[0] == eof[i - 1])
		*limiter = 0;
	else if ((eof[0] == '\'' || eof[0] == '"')
		&& eof[0] != eof[i - 1])
	{
		// error_heredoc(invalid_limiter);
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
			// error_heredoc(invalid_limiter);
			return (1);
		}
		i++;
	}
	if (test_limiter(eof, i, limiter, state))
		return (1);
	if (*limiter == 0)
		change_eof(eof);
	return (0);
}
