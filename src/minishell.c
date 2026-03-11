/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:09:01 by julauren          #+#    #+#             */
/*   Updated: 2026/03/11 17:46:02 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main()
{
	char	*cmd;

	cmd = readline("Ghost\\>: ");
	printf("%s\n", cmd);
	free(cmd);
}
