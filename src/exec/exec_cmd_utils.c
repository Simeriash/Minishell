/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:41:01 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/16 08:33:33 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

static void	write_msg(char *exec, char *err_msg)
{
	write(2, "Ghost\\>: ", ft_strlen("Ghost\\>: "));
	write(2, exec, ft_strlen(exec));
	write(2, ": ", 2);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
}

int	execve_error_msg(char *exec)
{
	struct stat	st;

	if (stat(exec, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			write_msg(exec, "Is a directory");
			return (127);
		}
		else if (!S_ISREG(st.st_mode))
			write_msg(exec, "Not a regular file");
		else
			write_msg(exec, strerror(errno));
		return (126);
	}
	else
		write_msg(exec, strerror(errno));
	return (127);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	redir_fd_helper(int *fd, int *owner, char *path, int flags)
{
	int	new_fd;

	new_fd = open (path, flags, 0664);
	if (new_fd < 0)
	{
		if (*owner == 1 && *fd > STDERR_FILENO)
			close(*fd);
		write(2, "Ghost\\>: ", ft_strlen("Ghost\\>: "));
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		write(2, "\n", 1);
		*fd = -1;
		return ;
	}
	if (*owner == 1 && *fd > STDERR_FILENO)
		close(*fd);
	*fd = new_fd;
	*owner = 1;
	return ;
}

void	apply_redirects(t_ast *node, t_fds *fds)
{
	t_redir	*tmp;

	if (!node->cmd->redir || !node->cmd->redir->type)
		return ;
	tmp = node->cmd->redir;
	while (tmp)
	{
		if (tmp->type == IN)
			redir_fd_helper(&fds->fd_in, &fds->redir_in, tmp->file, O_RDONLY);
		else if (tmp->type == OUT)
			redir_fd_helper(&fds->fd_out, &fds->redir_out, tmp->file,
				O_CREAT | O_WRONLY | O_TRUNC);
		else if (tmp->type == APPEND)
			redir_fd_helper(&fds->fd_out, &fds->redir_out, tmp->file,
				O_CREAT | O_WRONLY | O_APPEND);
		else if (tmp->type == HEREDOC)
			redir_fd_helper(&fds->fd_in, &fds->redir_in, tmp->file, O_RDONLY);
		tmp = tmp->next;
	}
	return ;
}
