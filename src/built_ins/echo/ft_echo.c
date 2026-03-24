/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:27:58 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/24 09:56:40 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_echo(char **ch_ar, int print_nl)
{
	int	i;
	int	ret_val;

	i = 0;
	ret_val = 0;
	if (!ch_ar)
		return (1);
	while (ch_ar[i])
	{
		ret_val = printf("%s", ch_ar[i]);
		if (!ret_val)
			return (-1);
		if (ch_ar[i + 1])
			ret_val = printf(" ");
		i++;
	}
	if (print_nl)
		ret_val = printf("\n");
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	if (argv[1] && !ft_strncmp(argv[1], "-n", 2))
// 		ft_echo(argv+2, 0);
// 	else
// 		ft_echo(argv+1, 1);
// }
