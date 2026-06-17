/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 15:29:23 by dlanehar          #+#    #+#             */
/*   Updated: 2026/06/17 11:18:47 by dlanehar         ###   ########.fr       */
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
# include "minishell.h"

// typedef enum e_errors
// {
// 	SUCCESS,
// 	MALLOC_FAIL,
// 	WRITE_FAIL,
// 	READ_FAIL,
// 	NULL_ARG,
// 	UNSET_ENV,

// }	t_errors;

// typedef struct s_envpcpy
// {
// 	char				*key;
// 	char				*value;
// 	struct s_envpcpy	*next;
// }	t_env;

typedef struct s_export_inputs
{
	char			*key;
	char			*value;
	t_env			*target_node;
}	t_export_inputs;

typedef enum e_env_mode
{
	ENV_REPLACE,
	ENV_APPEND
}	t_env_mode;

typedef int	(*t_builtin_func)(char **args, t_env **envpcpy);

typedef struct s_builtins
{
	char			*cmd;
	t_builtin_func	function;
}	t_builtins;

int			ft_cd(char **args, t_env **envpcpy);
int			ft_echo(char **args, t_env **envpcpy);
int			ft_env(char **args, t_env **envpcpy);
int			ft_exit(char **args, t_env **delete);
int			ft_export(char **args, t_env **envpcpy);
int			ft_pwd(char **args, t_env **envpcpy);
int			ft_unset(char **args, t_env **envpcpy);

t_env		*ft_lstnew(char *newkey, char *newvalue);
void		ft_lstaddback(t_env **lst, t_env *new);
t_env		*ft_lstlast(t_env *lst);
int			ft_lstsize(t_env *lst);
int			ft_strcmp(const char *s1, const char *s2);

char		*find_env_var(char *key, t_env **envpcpy);
t_env		*get_env_node(char *key, t_env **envpcpy);
// int			change_env_var(char *key, char *value, t_env **envpcpy);

int			create_new_export(char *key, char *value, t_env **envpcpy);

int			print_env_in_alpha_order(t_env **envpcpy);

int			cvi_error_check(char *input, int i);
int			must_append(char *in);
int			get_key(char *in, char **to_change);
int			get_value(char *in, char **to_change);
int			append_value(t_env *node, char *value);

int			env_set(char *key, char *value, t_env **envpcpy, t_env_mode mode);
//int			append_export(t_export_inputs *data, t_env **envpcpy);
//int			set_export(t_export_inputs *data, t_env **envpcpy);
void		print_error(char *cmd, char *bad_input, int err);

void		write_exit_msg(int exit_value, char *word_arg);
long long	create_num(unsigned long long limit, const char *str, int *ctrl);
long long	ft_longatoi(const char *str, int *ctrl);
int			is_number(char *str);

int			count_args(char **args);

#endif
