/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:18:27 by julauren          #+#    #+#             */
/*   Updated: 2026/06/02 11:10:59 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

ssize_t	ft_putnbr_fd(long n, int fd)
{
	char	*str;
	int		i;

	str = ft_itoa(n);
	if (!str)
		return (-1);
	i = ft_putstr_fd(str, fd);
	free(str);
	return (i);
}
