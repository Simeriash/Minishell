/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 11:26:31 by julauren          #+#    #+#             */
/*   Updated: 2026/05/28 11:27:04 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

void	handler_heredoc(int signum, siginfo_t *info, void *none)
{
	extern int	g_sig;

	(void)info;
	(void)none;
	if (signum == SIGINT)
	{
		g_sig = 1;
		close(0);
	}
}

void	set_signal_heredoc(int i)
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
	if (i == 0)
	{
		act.sa_sigaction = &handler_heredoc;
		act.sa_flags = SA_SIGINFO;
	}
	else
		act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
}
