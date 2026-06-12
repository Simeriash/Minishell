/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 12:41:20 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/12 08:51:22 by dlanehar         ###   ########.fr       */
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

void	error_helper(t_ast *node)
{
	write(2, "Ghost\\>: ", ft_strlen("Ghost\\>: "));
	write(2, node->cmd->redir->file, ft_strlen(node->cmd->redir->file));
	write(2, ": ", 2);
	write(2, strerror(errno), ft_strlen(strerror(errno)));
	write(2, "\n", 1);
}

int	execute_builtin(t_env **env, t_ast *node, t_fds *fds)
{
	t_builtin_func	func;
	int				error;
	int				saved_fd_in;
	int				saved_fd_out;

	func = get_builtin(node->cmd->args, env);
	if (func)
	{
		saved_fd_in = dup(fds->fd_in);
		saved_fd_out = dup(fds->fd_out);
		apply_redirects(node, &fds->fd_in, &fds->fd_out);
		if (fds->fd_in < 0)
		{
			error_helper(node);
			close(saved_fd_out);
			return (1);
		}
		if (fds->fd_in != STDIN_FILENO)
			dup2(fds->fd_in, STDIN_FILENO);
		if (fds->fd_out != STDOUT_FILENO)
			dup2(fds->fd_out, STDOUT_FILENO);
		error = func(node->cmd->args, env);
		dup2(saved_fd_in, STDIN_FILENO);
		close(saved_fd_in);
		dup2(saved_fd_out, STDOUT_FILENO);
		close(saved_fd_out);
		if (fds->fd_in != STDIN_FILENO)
			close (fds->fd_in);
		if (fds->fd_out != STDOUT_FILENO)
			close (fds->fd_out);
		if (ft_strcmp("exit", node->cmd->args[0]) == 0)
		{
			free_ast(node);
			exit(error);
		}
		return (1);
	}
	return (0);
}

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

int	execute_cmd(t_ast *node, t_env **envp, t_fds *fds)
{
	char		*executable;
	t_exec_err	err;
	t_error		error;
	pid_t		exec;
	int			status;
	char		**envp_array;

	if (!node->cmd->args)
		return (0);
	if (execute_builtin(envp, node, fds))
		return (OK);
	executable = find_executable(node->cmd->args[0], &err);
	if (!executable)
	{
		//check err;
		if (!node->cmd->args[0])
			return (1);
		printf("CoolCustomShell: %s: command not found\n", node->cmd->args[0]);
		return (127);
	}
	error = make_env_execve((*envp)->next, &envp_array);
	exec = fork();
	if (exec == 0)
		child_exec(node, fds, executable, envp_array);
	waitpid(exec, &status, 0);
	free(executable);
	free_array(envp_array);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
