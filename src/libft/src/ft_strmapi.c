/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 13:50:00 by julauren          #+#    #+#             */
/*   Updated: 2025/12/17 16:24:55 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strmapi(const char *src, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;
	char			*tmp;

	if (!src || !f)
		return (NULL);
	tmp = (char *)src;
	str = malloc(sizeof (*str) * (ft_strlen(tmp) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (tmp[i] != '\0')
	{
		str[i] = (f)(i, tmp[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
