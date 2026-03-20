/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 14:55:04 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/20 15:01:14 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_cd()
{

}

int	main(int argc, char **argv)
{
	(void)argc;
	if (argv[1] && !ft_strncmp(argv[1], "-n", 2))
		ft_echo(argv+2, 0);
	else
		ft_echo(argv+1, 1);
}
