/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:43:47 by julauren          #+#    #+#             */
/*   Updated: 2026/02/14 13:50:50 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_free(char *buffer, char **readed_file, int fd)
{
	if (buffer)
		free(buffer);
	if (*readed_file)
	{
		free(readed_file);
		readed_file = NULL;
	}
	if (fd >= 0)
		close(fd);
}

static void	ft_fill_file(char *buffer, char **readed_file, int fd)
{
	char	*tmp;
	ssize_t	size;

	size = 1;
	while (size)
	{
		size = read(fd, buffer, BUFFER_SIZE);
		if (size == -1 || (size == 0 && *readed_file == NULL))
		{
			ft_free(buffer, readed_file, fd);
			return ;
		}
		if (size == 0)
			break ;
		buffer[size] = '\0';
		tmp = ft_strjoin(*readed_file, buffer);
		if (!tmp)
		{
			ft_free(buffer, readed_file, fd);
			return ;
		}
		free(*readed_file);
		*readed_file = tmp;
	}
	free(buffer);
}

char	*ft_read_file(char *str)
{
	int		fd;
	char	*readed_file;
	char	*buffer;

	readed_file = NULL;
	buffer = malloc(sizeof(*buffer) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_free(buffer, NULL, -1);
		return (NULL);
	}
	ft_fill_file(buffer, &readed_file, fd);
	close(fd);
	return (readed_file);
}
