/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:07:06 by julauren          #+#    #+#             */
/*   Updated: 2025/12/17 16:23:13 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_str(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		while (str[i] == c && str[i] != '\0')
			i++;
		if (str[i] == '\0')
			return (count);
		while (str[i] != c && str[i] != '\0')
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

static char	**ft_tab(const char *str, char c, char **tab, int nb_str)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	end = 0;
	while (i < nb_str)
	{
		start = end;
		while (str[start] == c && str[start] != '\0')
			start++;
		end = start;
		while (str[end] != c && str[end] != '\0')
			end++;
		tab[i] = ft_substr(str, start, end - start);
		if (!tab[i])
		{
			ft_free_tab(tab, i);
			return (NULL);
		}
		i++;
	}
	return (tab);
}

char	**ft_split(const char *str, char c)
{
	int		nb_str;
	char	**tab;

	if (!str)
		return (NULL);
	nb_str = ft_count_str(str, c);
	tab = malloc(sizeof (*tab) * (nb_str + 1));
	if (!tab)
		return (NULL);
	tab[nb_str] = NULL;
	tab = ft_tab(str, c, tab, nb_str);
	return (tab);
}
