/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:41:20 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/12 11:31:56 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/execute.h"

char	*find_executable(char *cmd, t_exec_err *err)
{
	char	**paths;
	char	*ret;

	*err = EXEC_OK;
	if (!cmd || !*cmd)
	{
		*err = EXEC_NOT_FOUND;
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
	{
		ret = ft_strdup(cmd);
		if (!ret)
		{
			*err = EXEC_MALLOC_FAIL;
			return (NULL);
		}
		return (ret);
	}
	paths = create_paths(err);
	if (!paths)
		return (NULL);
	ret = create_candidate(cmd, paths, err);
	free_array(paths);
	return (ret);
}

/*
	Code below: Replace argv with node->args. Remove char **argv from the
	prototype of the fucntion.

	envp is still to be determined with Julien. Where it's placed and how to
	access it.

	char *cmd = argv[1] > char *cmd; cmd = node->args[0];
*/
// void redir_fd_helper(int *fd, char *path, int flags)
// {
// 	if (*fd != -1)
// 		close(*fd);
// 	*fd = open (path, flags, 0664);
// }

// void apply_redirects(t_ast *node, int *fd_in, int *fd_out)
// {
// 	t_redir *tmp;

// 	tmp = node->cmd->redir;
// 	if (!node->cmd->redir || !node->cmd->redir->type)
// 		return ;
// 	while (tmp)
// 	{
// 		if (tmp->type == IN)
// 			redir_fd_helper(fd_in, tmp->file, O_RDONLY);
// 		else if (tmp->type == OUT)
// 			redir_fd_helper(fd_out, tmp->file,
// 				O_CREAT | O_WRONLY | O_TRUNC);
// 		else if (tmp->type == APPEND)
// 			redir_fd_helper(fd_out, tmp->file,
// 				O_CREAT | O_WRONLY | O_APPEND);
// 		tmp = tmp->next;
// 	}
// 	return ;
// }

void	error_handling(int err)
{
	if (err == EXEC_MALLOC_FAIL)
	{
		write(2, "Malloc error.", 13);
		exit(-1);
	}
}

// char *env_join(char *key, char *value)
// {
// 	int len1;
// 	int len2;
// 	char *res;
// 	int i;
// 	int	j;

// 	len1 = strlen(key);
// 	len2 = strlen(value);
// 	res = malloc(len1 + len2 + 2);
// 	i = 0;
// 	j = 0;
// 	if (!res)
// 		return NULL;
// 	while (key[j])
// 		res[i++] = key[j++];
// 	res[i++] = '=';
// 	j = 0;
// 	while (value[j])
// 		res[i++] = value[j++];
// 	res[i] = '\0';
// 	return res;
// }

// t_error make_env_execve(t_env **envpc, char ***array)
// {
// 	size_t		size;
// 	size_t		i;
// 	t_env	*tmp;

// 	tmp = (*envpc);
// 	size = ft_lstsize(*envpc);
// 	i = 0;
// 	(*array) = malloc((size + 1) * sizeof(char *));
// 	if (!(*array))
// 		return (MALLOC);
// 	(*array)[size] = NULL;
// 	while (tmp)
// 	{
// 		if (tmp->value)
// 			(*array)[i] = env_join(tmp->key, tmp->value);
// 		else
// 			(*array)[i] = ft_strdup(tmp->key);
// 		if (!(*array)[i])
// 			return (MALLOC);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	(*array)[i] = NULL;
// 	return(OK);
// }

static void	child_exec(t_ast *node, t_fds *fds, char *exec,	char **arr)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	apply_redirects(node, &fds->fd_in, &fds->fd_out);
	if (fds->fd_in >= 0 && fds->fd_out >= 0)
	{
		if (fds->fd_in != STDIN_FILENO)
		{
			dup2(fds->fd_in, STDIN_FILENO);
			close(fds->fd_in);
		}
		if (fds->fd_out != STDOUT_FILENO)
		{
			dup2(fds->fd_out, STDOUT_FILENO);
			close(fds->fd_out);
		}
		execve(exec, node->cmd->args, arr);
	}
	rl_clear_history(); //after this line, check stat to see what type the executable was so we can create the appropriate erorr msg
	printf("CoolCustomShell: %s: %s\n", exec, strerror(errno));
	free(exec);
	free_array(arr);
	exit(126);
}

// int	execute_builtin(t_env **env, t_ast *node, t_fds *fds, t_builtin_func func)
// {
// 	// t_builtin_func	func;
// 	int				error;
// 	int				saved_fd_in;
// 	int				saved_fd_out;

// 	// func = get_builtin(node->cmd->args, env);
// 	saved_fd_in = dup(fds->fd_in);
// 	saved_fd_out = dup(fds->fd_out);
// 	apply_redirects(node, &fds->fd_in, &fds->fd_out);
// 	if (fds->fd_in < 0)
// 	{
// 		error_helper(node);
// 		close(saved_fd_out);
// 		return (1);
// 	}
// 	if (fds->fd_in != STDIN_FILENO)
// 		dup2(fds->fd_in, STDIN_FILENO);
// 	if (fds->fd_out != STDOUT_FILENO)
// 		dup2(fds->fd_out, STDOUT_FILENO);
// 	error = func(node->cmd->args, env);
// 	dup2(saved_fd_in, STDIN_FILENO);
// 	close(saved_fd_in);
// 	dup2(saved_fd_out, STDOUT_FILENO);
// 	close(saved_fd_out);
// 	if (fds->fd_in != STDIN_FILENO)
// 		close (fds->fd_in);
// 	if (fds->fd_out != STDOUT_FILENO)
// 		close (fds->fd_out);
// 	if (ft_strcmp("exit", node->cmd->args[0]) == 0)
// 	{
// 		free_ast(node);
// 		exit(error);
// 	}
// 	return (error);
// }

// if (func)
// 	{
// 		error = func(argv, envp);
// 		if (ft_strcmp("exit", argv[0]) == 0)
// 		{
// 			free_ast(node);
// 			free_array(envp_array);
// 			exit(error);
// 		}
// 		free_array(envp_array);
// 		return (error);
// 	}

// int	command_handling

char *handle_executable(t_ast *node)
{
	t_exec_err	err;
	char		*exe;

	exe = find_executable(node->cmd->args[0], &err);
	if (!exe)
	{
		ft_printf_fd(2, "Ghost: %s: command not found\n", node->cmd->args[0]);
		return (NULL);
	}
	return (exe);
}

int	handle_builtin(t_ast *node, t_env **env, t_fds *fds)
{
	t_builtin_func	func;
	int				ret_stat;

	func = get_builtin(node->cmd->args, env);
	if (func)
	{
		ret_stat = execute_builtin(env, node, fds, func);
		return (ret_stat);
	}
	return (-1);
}

int	reap_child_process(pid_t child_process)
{
	int	status;

	waitpid(child_process, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	prep_for_execve(t_ast *node, t_env **env, char **exec, char ***env_array)
{
	*exec = handle_executable(node);
	if (!exec)
		return (127);
	*env_array = make_env_execve((*env)->next);
	if (!env_array)
	{
		free (exec);
		return (1);
	}
	return (0);
}

int	run_command(t_ast *node, t_fds *fds, char *exec,	char **env_array)
{
	pid_t	child_proc;
	int		ret_stat;

	child_proc = fork();
	if (child_proc == -1)
	{
		free (exec);
		free_array (env_array);
		return (1);
	}
	if (child_proc == 0)
		child_exec(node, fds, exec, env_array);
	ret_stat = reap_child_process(child_proc);
	return (ret_stat);
}

int	execute_cmd(t_ast *node, t_env **envp, t_fds *fds)
{
	char	*executable;
	int		error;
	int		status;
	char	**env_array;

	if (!node->cmd->args)
		return (0);
	error = handle_builtin(node, envp, fds);
	if (error != -1)
		return (error);
	error = prep_for_execve(node, envp, &executable, &env_array);
	if (error)
		return (error);
	status = run_command(node, fds, executable, env_array);
	return (status);
}
