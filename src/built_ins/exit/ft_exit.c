/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:50:55 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/16 09:54:47 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"
#include "../../../inc/error.h"

static long long	create_num(unsigned long long limit, const char *str,
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

static long long	ft_longatoi(const char *str, int *ctrl)
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
	int		exit_value;
	int		ctrl;

	ctrl = 0;
	exit_value = 0;
	if (count_args(args) > 2)
	{
		write(2, "Ghost: exit: too many arguments", 31);
		ft_free_envc(*delete);
		return (1);
	}
	if (args[1])
	{
		if (check_alpha(args[1]))
			exit_value = 2;
		else
			exit_value = ft_longatoi(args[1], &ctrl);
	}
	if (ctrl != 0)
		exit_value = 2;
	ft_free_envc(*delete);
	rl_clear_history();
	write(1, "exit\n", 6);
	return (exit_value);
}
