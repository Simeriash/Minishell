/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:46:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/04/30 12:50:37 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../libft/libft.h"
# include "../../inc/minishell.h"
//# include <readline/readline.h>
//# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <sys/stat.h>

typedef enum e_exec_err
{
	EXEC_OK,
	EXEC_NOT_FOUND,
	EXEC_NO_PATH,
	EXEC_MALLOC_FAIL
} t_exec_err;

typedef enum {
  PIPE,
  CMD,
  AND,
  OR
} e_cmdtype;

typedef struct s_tree
{
	e_cmdtype type;
	int value;
	char *str;
	char **args;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;

int execute_cmd(t_tree *node, char **argv, char **envp, int fd_in, int fd_out);

#endif
