/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:29:23 by dlanehar          #+#    #+#             */
/*   Updated: 2026/04/03 17:30:21 by dlanehar         ###   ########.fr       */
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

typedef	struct s_envpcpy
{
	char *key;
	char *value;
	struct s_envpcpy *next;
}	t_envpcpy;

int			ft_echo(char **ch_ar, int print_nl);
int			ft_cd(char *path ,t_envpcpy **envpcpy);
int			ft_exit(int exit_val, t_envpcpy **delete);
int			ft_pwd(t_envpcpy **envpcpy);
int			ft_env(t_envpcpy **envpcpy);
int			ft_unset(char **key, t_envpcpy **envpcpy);
int			ft_export(char *path, char **args, t_envpcpy **envpcpy);

t_envpcpy	*ft_lstnew(char *newkey, char *newvalue);
void		ft_lstaddback(t_envpcpy **lst, t_envpcpy *new);
t_envpcpy	*ft_lstlast(t_envpcpy *lst);
int			ft_lstsize(t_envpcpy *lst);
int			ft_strcmp(const char *s1, const char *s2);

char		*find_env_var(char *key, t_envpcpy **envpcpy);
t_envpcpy	*find_env_var_pos(char *key, t_envpcpy **envpcpy);
int			change_env_var(char *key, char *value, t_envpcpy **envpcpy);

#endif
