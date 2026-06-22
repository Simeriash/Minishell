/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 13:23:35 by julauren          #+#    #+#             */
/*   Updated: 2026/06/21 18:20:49 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	count_token(char *str, t_index *index)
{
	int	i;
	int	count;

	i = index->i;
	count = 0;
	i++;
	while (str[i] != '\0' && i < index->j)
	{
		while (ft_isspace(str[i]) && str[i] != '\0' && i < index->j)
			i++;
		if (str[i] == '\0')
			return (0);
		while (!ft_isspace(str[i]) && str[i] != '\0' && i < index->j)
			i++;
		count++;
	}
	return (count);
}

static void	ft_free_tab(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**tab_token(char *str,char **tab, t_index *index, int nb_token)
{
	int	n;
	int	start;
	int	end;

	end = index->i;
	n = 0;
	// end = 0;
	while (n < nb_token && end < index->j)
	{
		start = end;
		while (ft_isspace(str[start]) && str[start] != '\0' && start < index->j)
			start++;
		end = start;
		while (!ft_isspace(str[end]) && str[end] != '\0' && end < index->j)
			end++;
		tab[n] = ft_substr(str, start, end - start);
		if (!tab[n])
		{
			ft_free_tab(tab, n);
			return (NULL);
		}
		n++;
	}
	return (tab);
}

char	**split_token(char *str, t_index *index)
{
	int		nb_token;
	char	**tab;

	if (!str)
		return (NULL);
	nb_token = count_token(str, index);
	tab = malloc(sizeof (*tab) * (nb_token + 1));
	if (!tab)
		return (NULL);
	tab[nb_token] = NULL;
	if (nb_token == 0)
	{
		tab[0] = ft_strdup("");
		if (!tab[0])
		{
			free(tab);
			return (NULL);
		}
		return (tab);
	}
	tab = tab_token(str, tab, index, nb_token);
	return (tab);
}
