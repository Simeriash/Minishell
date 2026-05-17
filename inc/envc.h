/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envc.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 08:48:24 by julauren          #+#    #+#             */
/*   Updated: 2026/05/17 12:43:45 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVC_H
# define ENVC_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include "error.h"

t_env	*init_envc_list(void);
int		add_after(t_env *envc, char *key, char *value);
void	ft_free_envc(t_env *envc);
t_env	*env_copy(char **envp);

#endif
