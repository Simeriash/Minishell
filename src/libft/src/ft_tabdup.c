/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 18:07:19 by julauren          #+#    #+#             */
/*   Updated: 2026/02/12 18:31:48 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_free(char **tab, int n)
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

static void	ft_copy(char **tab, char **tab_dup)
{
	int	i;
	int	j;

	j = 0;
	while (tab[j])
	{
		i = 0;
		while (tab[j][i])
		{
			tab_dup[j][i] = tab[j][i];
			i++;
		}
		tab_dup[j][i] = '\0';
		j++;
	}
	tab_dup[j] = NULL;
}

char	**ft_tabdup(char **tab)
{
	int		line;
	int		i;
	char	**tab_dup;

	line = 0;
	while (tab[line])
		line++;
	tab_dup = malloc(sizeof(*tab_dup) * (line + 1));
	if (!tab_dup)
		return (NULL);
	i = 0;
	while (i < line)
	{
		tab_dup[i] = malloc(sizeof(**tab_dup) * (ft_strlen(tab[i]) + 1));
		if (!tab_dup[i])
		{
			ft_free(tab_dup, i);
			return (NULL);
		}
		i++;
	}
	ft_copy(tab, tab_dup);
	return (tab_dup);
}
