/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 08:26:14 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/17 09:24:39 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"
#include "../../../inc/error.h"

void	write_exit_msg(int error, char *word_arg)
{
	write(1, "exit\n", 5);
	if (error == 1)
		write(2, "Ghost: exit: too many arguments\n", 33);
	if (error == 2)
	{
		write(2, "Ghost: exit: ", 14);
		write(2, word_arg, ft_strlen(word_arg));
		write(2, ": numeric argument required\n", 29);
	}
}
