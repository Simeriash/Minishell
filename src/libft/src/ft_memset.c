/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:36:42 by julauren          #+#    #+#             */
/*   Updated: 2025/12/17 16:07:57 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	char	*tmp;
	size_t	i;

	tmp = str;
	i = 0;
	while (i < n)
	{
		tmp[i] = c;
		i++;
	}
	return (str);
}
