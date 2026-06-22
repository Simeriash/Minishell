/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:04:42 by julauren          #+#    #+#             */
/*   Updated: 2026/02/02 12:24:00 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*dest;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 || !s2)
	{
		if (!s1)
			dest = ft_strdup(s2);
		if (!s2)
			dest = ft_strdup(s1);
		return (dest);
	}
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	dest = malloc(sizeof (*dest) * len);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len);
	ft_strlcat(dest, s2, len);
	return (dest);
}
