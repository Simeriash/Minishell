/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:27:58 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/18 10:08:17 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	check_dash_n(char *args)
{
	int	i;

	i = 0;
	if (!args || args[i] != '-')
		return (0);
	i++;
	if (args[i] == '\0')
		return (0);
	while (args[i])
	{
		if (args[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	print_words(int index, char **args, int nl_flag)
{
	int	ret_val;

	ret_val = 0;
	while (args[index])
	{
		ret_val = printf("%s", args[index]);
		if (ret_val < 0)
			return (ret_val);
		if (args[index + 1])
		{
			ret_val = printf(" ");
			if (ret_val < 0)
				return (ret_val);
		}
		index++;
	}
	if (nl_flag)
	{
		ret_val = printf("\n");
		if (ret_val < 0)
			return (ret_val);
	}
	return (ret_val);
}

int	ft_echo(char *path, char **args, t_envpcpy **envpcpy)
{
	int	i;
	int	ret_val;
	int	nl_flag;

	(void)path;
	(void)envpcpy;
	i = 0;
	nl_flag = 1;
	if (!args)
		return (1);
	while (args[i] && check_dash_n(args[i]))
	{
		i++;
		nl_flag = 0;
	}
	ret_val = print_words(i, args, nl_flag);
	if (ret_val < 0)
		return (ret_val);
	return (0);
}
