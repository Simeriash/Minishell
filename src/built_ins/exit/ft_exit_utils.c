/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/17 08:26:14 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/22 09:15:53 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"
#include "../../../inc/error.h"

int	count_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

void	write_exit_msg(int error, char *word_arg)
{
	if (error == 1)
		write(2, "Ghost: exit: too many arguments\n", 33);
	if (error == 2)
	{
		write(2, "Ghost: exit: ", 14);
		write(2, word_arg, ft_strlen(word_arg));
		write(2, ": numeric argument required\n", 29);
	}
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (ft_isalpha(str[i]))
		return (1);
	if (str[i] == '+' || str[i] == '-')
	{
		i++;
		if (!ft_isdigit(str[i]))
			return (1);
	}
	while (ft_isdigit(str[i]))
		i++;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '\0')
		return (0);
	return (1);
}
