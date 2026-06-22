/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 14:17:33 by julauren          #+#    #+#             */
/*   Updated: 2026/06/22 08:13:29 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static void	free_tab_i(char **tab, int n)
{
	int	i;

	if (!tab)
		return ;
	i = n + 1;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

static void	free_all_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	new_token(t_token **token, t_index *index)
{
	char	**tab;
	int		i;
	char	*str;
	char	*tmp;

	tab = split_token((*token)->value, index);
	if (!tab)
		return (1);
	if (tab[0][0] == '\0')
	{
		free(tab[0]);
		free(tab);
		return (0);
	}
	i = 0;
	tmp = ft_strdup((*token)->value);
	if (!tmp)
	{
		free_all_tab(tab);
		return (1);
	}
	printf("index : %i\t%c\n", index->i, (*token)->value[index->i]);
	if (index->i == 1)
	{
		free((*token)->value);
		(*token)->value = tab[i++];
	}
	// else if (index->i >= 2 && ft_isspace((*token)->value[index->i - 2]))
	// {
	// 	ft_strlcpy(&(*token)->value[index->i], "\"", 2);
	// }
	else if (index->i >= 2 && !ft_isspace((*token)->value[index->i - 2]))
	{
		ft_strlcpy(&(*token)->value[index->i - 1], tab[i], ft_strlen(tab[i]) + 1);
		free(tab[0]);
		i++;
	}
	while (tab[i])
	{
		if (add_after(*token, WORD, tab[i]))
		{
			free_tab_i(tab, i);
			free(tmp);
			return (1);
		}
		*token = (*token)->next;
		i++;
	}
	free(tab);
	printf("%i\t%s\t%c\n", index->j, tmp, tmp[index->j]);
	if (ft_isspace(tmp[index->j]))
	{
		str = ft_strdup(&tmp[index->j - 1]);
		free(tmp);
		if (!str)
			return (1);
		if (add_after(*token, WORD, str))
		{
			free (str);
			return (1);
		}
	if (tmp)
		free(tmp);
	}
	*token = (*token)->next;
	index->i = 0;
	// if ((*token)->value[index->i] == '"' && ft_isspace((*token)->value[index->i + 1]))
	// {

	// }
	return (0);
}
