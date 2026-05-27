/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:27:04 by julauren          #+#    #+#             */
/*   Updated: 2026/05/19 16:27:25 by julauren         ###   ########.fr       */
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

int		delimiter(int *limiter, char *eof);
void	error_heredoc(t_error error);

#endif
