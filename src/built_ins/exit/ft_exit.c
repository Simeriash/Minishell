/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:50:55 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/24 13:37:50 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_exit(int exit_val)
{
	exit(exit_val);
}

// int	main(int argc, char **argv)
// {
// 	int ctrl;
// 	int i = ft_atoi(argv[1], &ctrl);
// 	ft_exit(i);
// }
