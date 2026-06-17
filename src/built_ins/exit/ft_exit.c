/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:50:55 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/17 09:37:51 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"
#include "../../../inc/error.h"

long long	create_num(unsigned long long limit, const char *str,
								int *ctrl)
{
	unsigned long long	num;
	int					i;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (num > (limit - (str[i] - '0')) / 10)
		{
			num = 0;
			*ctrl = -1;
			return (0);
		}
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num);
}

long long	ft_longatoi(const char *str, int *ctrl)
{
	int					i;
	int					sign;
	unsigned long long	num;
	unsigned long long	limit;

	i = 0;
	num = 0;
	sign = 1;
	limit = LLONG_MAX;
	if (str[i] == '-')
	{
		sign = -sign;
		limit = (unsigned long long)LLONG_MAX + 1;
	}
	if (str[i] == '-' || str[i] == '+')
		i++;
	num = create_num(limit, str + i, ctrl);
	return ((long long)sign * num);
}

static int	check_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_exit(char **args, t_env **delete)
{
	int	exit_value;
	int	ctrl;
	int	error;

	(void)delete;
	ctrl = 0;
	exit_value = 0;
	error = 0;
	if (args[1])
	{
		if (check_alpha(args[1]))
			error = 2;
		else if (count_args(args) > 2)
			error = 1;
		else
		{
			exit_value = ft_longatoi(args[1], &ctrl);
			if (ctrl == -1)
				error = 2;
		}
	}
	write_exit_msg(error, args[1]);
	if (error)
		exit_value = error;
	return (exit_value);
}
