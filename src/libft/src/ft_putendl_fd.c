/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 13:09:36 by julauren          #+#    #+#             */
/*   Updated: 2025/12/12 15:32:46 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putendl_fd(char *str, int fd)
{
	ssize_t	i;
	int		j;

	i = ft_putstr_fd(str, fd);
	if (i < 0)
		return (i);
	j = ft_putchar_fd('\n', fd);
	if (j < 0)
		return (j);
	i++;
	return (i);
}
