/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 11:39:12 by julauren          #+#    #+#             */
/*   Updated: 2026/06/02 11:07:56 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_intlen(long n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(long n)
{
	size_t	len;
	char	*str;
	int		sign;
	int		i;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = ft_intlen(n) + sign;
	str = malloc(sizeof (*str) * (len + 1));
	if (!str)
		return (NULL);
	if (sign)
		str[0] = '-';
	i = len - 1;
	while (i >= sign)
	{
		str[i] = (n % 10) * (!sign - sign) + 48;
		n = n / 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}
