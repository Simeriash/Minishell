/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:27:58 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/13 15:37:05 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_for_nl(char *args)
{
	int i;
	int	print_nl;

	i = 0;
	print_nl = 1;
	if (args[i] == '-')
	{
		i++;
		while (args[i])
		{
			if (args[i] == 'n')
				print_nl = 0;
			else
			{
				print_nl = 1;
				break ;
			}
			i++;
		}
	}
	return (print_nl);
}

int	ft_echo(char *path, char **args, t_envpcpy **envpcpy)
{
	int	i;
	int	ret_val;
	int	print_nl;

	(void)path;
	(void)envpcpy;
	i = 0;
	ret_val = 0;
	if (!args)
		return (1);
	if (ft_strcmp("echo", args[i]) == 0)
		i++;
	print_nl = check_for_nl(args[i]);
		i++;
	while (args[i])
	{
		//check if first arg is a -n or any combo of ns. if a non n appears, treat as a word

		ret_val = printf("%s", args[i]);
		if (!ret_val)
			return (-1);
		if (args[i + 1])
			ret_val = printf(" ");
		i++;
	}
	if (print_nl)
		ret_val = printf("\n");
	return (0);
}

