/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 18:41:01 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/31 13:25:08 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/execute.h"

void free_array(char **array) //util
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

// char *create_exec_path(char *path, char *cmd) //cmd util
// {
// 	char *tmp;
// 	char *ret;

// 	tmp = ft_strjoin(path, "/");
// 	if (!tmp)
// 		return (NULL);
// 	ret = ft_strjoin(tmp, cmd);
// 	free(tmp);
// 	if (!ret)
// 		return (NULL);
// 	return (ret);
// }

void	cleanup_helper(char *fallback)
{
	if (fallback)
		free(fallback);
	return ;
}

void redir_fd_helper(int *fd, char *path, int flags)
{
	if (*fd != -1)
		close(*fd);
	*fd = open (path, flags, 0664);
}

void apply_redirects(t_ast *node, int *fd_in, int *fd_out)
{
	t_redir *tmp;

	tmp = node->cmd->redir;
	if (!node->cmd->redir || !node->cmd->redir->type)
		return ;
	while (tmp)
	{
		if (tmp->type == IN)
			redir_fd_helper(fd_in, tmp->file, O_RDONLY);
		else if (tmp->type == OUT)
			redir_fd_helper(fd_out, tmp->file,
				O_CREAT | O_WRONLY | O_TRUNC);
		else if (tmp->type == APPEND)
			redir_fd_helper(fd_out, tmp->file,
				O_CREAT | O_WRONLY | O_APPEND);
		tmp = tmp->next;
	}
	return ;
}
