/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:16:00 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/12 10:07:46 by dlanehar         ###   ########.fr       */
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
		return (1);
	}
	i++;
	while (in[i] && in[i] != '=')
	{
		if (in[i] == '+' && in[i + 1] == '=')
			return (0);
		if (cvi_error_check(in, i) != 0)
			return (1);
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
	if (error != 0)
		return (1);
	error = get_value(arg, value);
	if (error != 0)
	{
		free(*key);
		*key = NULL;
		return (1);
	}
	return (0);
}

static int	process_input(char *arg, t_env **envpcpy)
{
	char		*key;
	char		*value;
	t_env_mode	mode;
	int			error;

	mode = ENV_REPLACE;
	key = NULL;
	value = NULL;
	error = set_key_and_value(arg, &key, &value);
	if (error != 0)
		return (1);
	if (must_append(arg))
		mode = ENV_APPEND;
	env_set(key, value, envpcpy, mode);
	free(key);
	free(value);
	if (error != 0)
		return (1);
	return (0);
}

int	ft_export(char **args, t_env **envpcpy)
{
	int			i;
	int			error;

	i = 1;
	if (!args)
		return (1);
	if (!args[i])
	{
		print_env_in_alpha_order(envpcpy);
		return (0);
	}
	while (args[i])
	{
		error = check_valid_input(args[i]);
		if (error != 0)
		{
			i++;
			continue ;
		}
		printf("why are we here\n");
		error = process_input(args[i], envpcpy);
		if (error != 0)
			return (1);
		i++;
	}
	return (error);
}
