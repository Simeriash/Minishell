/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 15:10:38 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/24 15:14:40 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_env(char **envpcpy)
{
	int	i;

	i = 0;
	while (envpcpy[i])
		printf("%s\n", envpcpy[i++]);
	return (0);
}
