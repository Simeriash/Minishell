/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 11:50:01 by julauren          #+#    #+#             */
/*   Updated: 2025/12/12 15:37:52 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	ft_intlen(long n, int base, int p)
{
	size_t	i;
	size_t	b;

	if (n == 0)
		return (1);
	i = 0;
	if (!p)
	{
		while (n != 0)
		{
			n /= base;
			i++;
		}
	}
	else
	{
		n = (size_t)n;
		b = base;
		while (n != 0)
		{
			n /= b;
			i++;
		}
	}
	return (i);
}

static char	*ft_itoa_p(long nbr)
{
	size_t	len;
	char	*str;
	int		sign;
	int		i;

	sign = 0;
	if (nbr < 0)
		sign = 1;
	len = ft_intlen(nbr, 10, 0) + sign;
	str = malloc(sizeof (*str) * (len + 1));
	if (!str)
		return (NULL);
	if (sign)
		str[0] = '-';
	i = len - 1;
	while (i >= sign)
	{
		str[i] = (nbr % 10) * (!sign - sign) + 48;
		nbr /= 10;
		i--;
	}
	str[len] = '\0';
	return (str);
}

static char	*ft_itoa_hexa(size_t nbr, int p, int lc)
{
	size_t	len;
	char	*str;
	int		i;

	len = ft_intlen(nbr, 16, p) + p;
	str = malloc(sizeof (*str) * (len + 1));
	if (!str)
		return (NULL);
	if (p)
	{
		str[0] = '0';
		str[1] = 88 + 32 * lc;
	}
	i = len - 1;
	while (i >= p)
	{
		str[i] = (nbr % 16) + 48;
		if (!(ft_isdigit(str[i])))
			str[i] += 7 + 32 * lc;
		nbr /= 16;
		i--;
	}
	str[len] = '\0';
	return (str);
}

int	ft_putnbr(long nbr, int base, int p, int lc)
{
	char	*str;
	int		i;

	if (p == 1 && nbr == 0)
	{
		i = ft_putstr_fd("(nil)", 1);
		return (i);
	}
	if (base == 10)
		str = ft_itoa_p(nbr);
	else
	{
		if (p == 1)
			p++;
		nbr = (size_t)nbr;
		str = ft_itoa_hexa(nbr, p, lc);
	}
	if (!str)
		return (-1);
	i = ft_putstr_fd(str, 1);
	free(str);
	return (i);
}
