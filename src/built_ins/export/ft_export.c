/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:00 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/19 14:52:22 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_valid_input(char *in)
{
	int	i;

	i = 0;
	if (!(in[i] == '_' || ft_isalpha(in[i])))
	{
		printf("bash: export: `%s': not a valid identifier\n", in);
		return (-1);
	}
	i++;
	while (in[i] && in[i] != '=')
	{
		if (in[i] == '+' && in[i + 1] == '=')
			return (0);
		if (cvi_error_check(in, i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

static int	set_key_and_value(char *arg, char **key, char **value)
{
	int	error;

	*key = NULL;
	*value = NULL;
	error = get_key(arg, key);
	if (error < 0)
		return (-1);
	error = get_value(arg, value);
	if (error < 0)
	{
		free(*key);
		*key = NULL;
		return (-1);
	}
	return (0);
}

static	int	apply_rule(char *arg, t_export_inputs *data, t_envpcpy **envpcpy)
{
	int	error;

	error = 0;
	if (must_append(arg))
		error = append_export(data, envpcpy);
	else
		error = set_export(data, envpcpy);
	return (error);
}

static int	process_input(char *arg, t_envpcpy **envpcpy)
{
	t_export_inputs	data;
	int				error;

	data.key = NULL;
	data.value = NULL;
	data.target_node = NULL;
	error = set_key_and_value(arg, &data.key, &data.value);
	if (error < 0)
		return (-1);
	data.target_node = find_env_var_pos(data.key, envpcpy);
	error = apply_rule(arg, &data, envpcpy);
	free(data.key);
	free(data.value);
	if (error < 0)
		return (-1);
	return (0);
}

int	ft_export(char *path, char **args, t_envpcpy **envpcpy)
{
	int			i;
	int			error;

	(void)path;
	i = 0;
	if (!args)
		return (-1);
	if (!args[i])
	{
		print_env_in_alpha_order(envpcpy);
		return (0);
	}
	while (args[i])
	{
		if (check_valid_input(args[i]) < 0)
		{
			i++;
			continue ;
		}
		error = process_input(args[i], envpcpy);
		if (error < 0)
			return (-1);
		i++;
	}
	return (0);
}
