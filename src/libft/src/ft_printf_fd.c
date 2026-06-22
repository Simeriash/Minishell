/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:51:43 by julauren          #+#    #+#             */
/*   Updated: 2026/06/02 11:51:00 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_puttab(char **tab, int fd)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tab[i])
	{
		len += ft_putendl_fd(tab[i], fd);
		i++;
	}
	return (len);
}

static int	ft_type(va_list param, const char *str, int *i, int fd)
{
	int	len;

	*i = *i + 1;
	if (str[*i] == 'c')
		len = ft_putchar_fd(va_arg(param, int), fd);
	else if (str[*i] == 's')
		len = ft_putstr_fd(va_arg(param, char *), fd);
	else if (str[*i] == 'p')
		len = ft_putnbr(va_arg(param, size_t), 16, 1, 1);
	else if (str[*i] == 'd' || str[*i] == 'i')
		len = ft_putnbr_fd(va_arg(param, int), fd);
	else if (str[*i] == 'u')
		len = ft_putnbr_fd(va_arg(param, unsigned int), fd);
	else if (str[*i] == 'x')
		len = ft_putnbr(va_arg(param, unsigned int), 16, 0, 1);
	else if (str[*i] == 'X')
		len = ft_putnbr(va_arg(param, unsigned int), 16, 0, 0);
	else if (str[*i] == '%')
		len = ft_putchar_fd('%', fd);
	else if (str[*i] == 't')
		len = ft_puttab(va_arg(param, char **), fd);
	else
		len = ft_putstr_fd("", fd);
	return (len);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	param;
	int		i;
	int		len;
	int		tmp;

	i = 0;
	len = 0;
	if (!str)
		return (-1);
	va_start(param, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
			tmp = ft_type(param, str, &i, fd);
		else
			tmp = ft_putchar_fd(str[i], fd);
		if (tmp == -1)
			return (-1);
		len += tmp;
		i++;
	}
	va_end(param);
	return (len);
}
