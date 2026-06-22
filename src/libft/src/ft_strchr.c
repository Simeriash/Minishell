/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:37:31 by julauren          #+#    #+#             */
/*   Updated: 2025/12/17 16:14:20 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(str);
	tmp = (char *)str;
	while (i <= len)
	{
		if (tmp[i] == (char )c)
			return (&tmp[i]);
		i++;
	}
	return (NULL);
}
