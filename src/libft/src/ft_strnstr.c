/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:26:26 by julauren          #+#    #+#             */
/*   Updated: 2025/12/12 15:32:46 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;
	char	*t1;
	char	*t2;

	if (s2[0] == 0)
		return ((char *)s1);
	t1 = (char *)s1;
	t2 = (char *)s2;
	i = 0;
	while (t1[i] != '\0' && i < n)
	{
		j = 0;
		while (t1[i + j] == t2[j] && t2[j] != '\0' && i + j < n)
			j++;
		if (t2[j] == '\0')
			return (&t1[i]);
		i++;
	}
	return (NULL);
}
