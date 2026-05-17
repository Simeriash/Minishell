/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 12:20:14 by julauren          #+#    #+#             */
/*   Updated: 2026/05/17 12:49:06 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/error.h"

void	error_envc(t_env *envc)
{
	ft_putendl_fd("Error malloc", 2);
	if (envc)
		ft_free_envc(envc);
}
