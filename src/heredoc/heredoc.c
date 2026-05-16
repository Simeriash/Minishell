/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 12:30:30 by julauren          #+#    #+#             */
/*   Updated: 2026/05/16 09:30:22 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/heredoc.h"

static int	next_expander(char *cmd, t_env *envc, int *i, int *j)
{
	char	*new_value;
	int		len;

	new_value = check_new_value(cmd, envc, *i, j);
	if (new_value && change_value(cmd, new_value, *i, *j))
		return (1);
	len = ft_strlen(new_value);
	free(new_value);
	*i = *i + len - 1;
	return (0);
}

static int	expander(char *cmd, t_env *envc)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '$')
		{
			i++;
			if (cmd[i] == '\0')
				return (0);
			if (ft_isspace(cmd[i]))
				continue ;
			j = i + 1;
			if (next_expander(cmd, envc, &i, &j))
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	heredoc(char *eof, t_env *envc)
{
	char	*cmd;
	int		fd;
	char	*str;		//	/!\	A EFFACER	(GERER A L'EXEC)

	fd = open("minishell_heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	while (1)
	{
		cmd = readline("heredoc>: ");
		if (!ft_strcmp(cmd, eof))
			break ;
		if (expander(cmd, envc))
		{
			free(cmd);
			return (1);
		}
		ft_putendl_fd(cmd, fd);
		free(cmd);
	}
	close(fd);
	free(cmd);
	str = ft_read_file("minishell_heredoc");		//	/!\	A EFFACER	(GERER A L'EXEC)
	printf("%s", str);		//	/!\	A EFFACER	(GERER A L'EXEC)
	unlink("minishell_heredoc");		//	/!\	A EFFACER	(GERER A L'EXEC)
	free(str);		//	/!\	A EFFACER	(GERER A L'EXEC)
	return (0);
}
