/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:16:36 by julauren          #+#    #+#             */
/*   Updated: 2025/12/17 16:15:12 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*tmp;

	i = ft_strlen(str);
	tmp = (char *)str;
	while (i >= 0)
	{
		if (tmp[i] == (char )c)
			return (&tmp[i]);
		i--;
	}
	return (NULL);
}
