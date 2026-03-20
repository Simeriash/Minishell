/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:27:58 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/20 15:34:06 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(char **argv, int print_nl)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (print_nl)
		printf("\n");
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 2))
		ft_echo(argv+2, 0);
	else
		ft_echo(argv+1, 1);
}
