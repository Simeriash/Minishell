/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helpers1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/19 10:34:49 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/21 11:00:37 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	cvi_error_check(char *input, int i)
{
	printf("inside cvi_error\n");
	if (input[i] == '+')
	{
		printf("bash: export: `%s': not a valid identifier\n", input);
		return (-1);
	}
	if (!(input[i] == '_' || ft_isalnum(input[i])))
	{
		printf("bash: export: `%s': not a valid identifier\n", input);
		return (-1);
	}
	return (0);
}

int	must_append(char *in)
{
	int		i;

	i = 0;
	while (in[i] && in[i] != '=')
	{
		if (in[i] == '+' && in[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	get_key(char *in, char **to_change) // FROM INT TO T_ERRORS
{
	int		i;

	i = 0;
	while (in[i] && in[i] != '=' && in[i] != '+')
		i++;
	*to_change = malloc(i + 1);
	if (!(*to_change))
		return (-1); // MALLOC FAIL
	ft_strlcpy(*to_change, in, i + 1);
	return (0); // SUCCESS
}

int	get_value(char *in, char **to_change) // FROM INT TO T_ERRORS
{
	int		i;

	i = 0;
	while (in[i] && in[i] != '=')
		i++;
	if (in[i] != '=')
	{
		*to_change = NULL;
		return (0); // SUCCESS
	}
	i++;
	*to_change = ft_strdup(in + i);
	if (!(*to_change))
		return (-1); // MALLOC FAIL
	return (0); // SUCCESS
}
