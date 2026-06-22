/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:20:08 by julauren          #+#    #+#             */
/*   Updated: 2025/12/17 16:18:05 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(const char *str, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	size_t	slen;
	char	*dest;

	if (!str)
		return (NULL);
	slen = ft_strlen(str);
	if (start >= slen)
		size = 0;
	else if (len > slen - start)
		size = slen - start;
	else
		size = len;
	dest = malloc(sizeof (*dest) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (i < size && str[start + i] != '\0')
	{
		dest[i] = str[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
