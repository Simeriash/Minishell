/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:50:55 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/15 10:49:15 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../inc/builtins.h"

// static int	ft_longatoi(const char *str, int *ctrl)
// {
// }

static void	free_env(t_env **delete)
{
	t_env	*tmp;
	t_env	*next;

	tmp = *delete;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
		tmp = next;
	}
	return ;
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
		free_env(delete);
		return (1);
	}
	if (args[1])
	{
		if (check_alpha(args[1]))
			exit_value = 2;
		else
			exit_value = ft_atoi(args[1], &ctrl);
	}
	if (ctrl != 0)
		exit_value = 2;
	free_env(delete);
	rl_clear_history();
	return (exit_value);
}
