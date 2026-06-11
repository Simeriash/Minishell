/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:27:04 by julauren          #+#    #+#             */
/*   Updated: 2026/06/11 14:12:38 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include "lexer.h"
# include "parser.h"
# include "error.h"

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct s_var
{
	int	fd;
	int	limiter;
	int	status;
}	t_var;

void	free_heredoc(t_token *token_list, t_env *envc, char *cmd, int fd);
int		heredoc_expander(char **cmd, t_env *envc, int status);
int		delimiter(int *limiter, char *eof);
void	set_signal_heredoc(int i);
void	error_heredoc(t_error error);

#endif
