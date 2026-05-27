/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:46:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/27 12:10:54 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include "builtins.h"
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
#include <signal.h>

typedef enum e_exec_err
{
	EXEC_OK,
	EXEC_NOT_FOUND,
	EXEC_NO_PATH,
	EXEC_MALLOC_FAIL
} t_exec_err;

// typedef enum {
//   PIPE,
//   CMD,
//   AND,
//   OR
// } e_cmdtype;

// typedef enum e_redir_type
// {
// 	IN,
// 	OUT,
// 	APPEND
// }	t_redir_type;

// typedef struct s_redirs
// {
// 	t_redir_type redir_type;
// 	char *redir_file;
// 	struct s_redirs *redirs_next;
// }	t_redirs;

// typedef struct s_cmd
// {
// 	char **args;
// 	t_redirs *redirs;

// }	t_cmd;


// typedef struct s_tree
// {
// 	struct s_tree *head;
// 	e_cmdtype type;
// 	int value;
// 	t_cmd	*cmd;
// 	struct s_tree	*left;
// 	struct s_tree	*right;
// } t_tree;

int execute_cmd(t_ast *node, char **argv, t_env **envp, int fd_in, int fd_out);
int execute_tree(t_ast *node, t_env **envp, int in_fd, int out_fd);
void free_array(char **array);
builtin_func	get_builtin(char **args, t_env **envpcpy);
t_ast *makenode(char *value);
void free_tree(t_ast *node);

#endif
