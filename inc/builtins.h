/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:29:23 by dlanehar          #+#    #+#             */
/*   Updated: 2026/05/21 14:59:10 by dlanehar         ###   ########.fr       */
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

// typedef enum e_errors
// {
// 	SUCCESS,
// 	MALLOC_FAIL,
// 	WRITE_FAIL,
// 	READ_FAIL,
// 	NULL_ARG,
// 	UNSET_ENV,

// }	t_errors;

typedef struct s_envpcpy
{
	char				*key;
	char				*value;
	struct s_envpcpy	*next;
}	t_envpcpy;

typedef struct s_export_inputs
{
	char			*key;
	char			*value;
	t_envpcpy		*target_node;
}	t_export_inputs;

typedef enum e_env_mode
{
	ENV_REPLACE,
	ENV_APPEND
}	t_env_mode;

int			ft_cd(char **args, t_envpcpy **envpcpy);
int			ft_echo(char **args, t_envpcpy **envpcpy);
int			ft_env(char **args, t_envpcpy **envpcpy);
int			ft_exit(char **args , t_envpcpy **delete);
int			ft_export(char **args, t_envpcpy **envpcpy);
int			ft_pwd(char **args, t_envpcpy **envpcpy);
int			ft_unset(char **args, t_envpcpy **envpcpy);

t_envpcpy	*ft_lstnew(char *newkey, char *newvalue);
void		ft_lstaddback(t_envpcpy **lst, t_envpcpy *new);
t_envpcpy	*ft_lstlast(t_envpcpy *lst);
int			ft_lstsize(t_envpcpy *lst);
int			ft_strcmp(const char *s1, const char *s2);

char		*find_env_var(char *key, t_envpcpy **envpcpy);
t_envpcpy	*get_env_node(char *key, t_envpcpy **envpcpy);
// int			change_env_var(char *key, char *value, t_envpcpy **envpcpy);

int			create_new_export(char *key, char *value, t_envpcpy **envpcpy);

int			print_env_in_alpha_order(t_envpcpy **envpcpy);

int			cvi_error_check(char *input, int i);
int			must_append(char *in);
int			get_key(char *in, char **to_change);
int			get_value(char *in, char **to_change);
int			append_value(t_envpcpy *node, char *value);

int			env_set(char *key, char *value, t_envpcpy **envpcpy, t_env_mode mode);
//int			append_export(t_export_inputs *data, t_envpcpy **envpcpy);
//int			set_export(t_export_inputs *data, t_envpcpy **envpcpy);
void		print_error(char *cmd, char *bad_input, int err);

#endif
