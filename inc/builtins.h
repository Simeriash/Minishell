/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:29:23 by dlanehar          #+#    #+#             */
/*   Updated: 2026/03/24 15:11:26 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "../src/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <errno.h>

int	ft_echo(char **ch_ar, int print_nl);
int	ft_cd(char **envpcpy, char *path);
int	ft_exit(int exit_val);
int	ft_pwd(char **envpcpy);
int	ft_env(char **envpcpy);


#endif
