/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:09:01 by julauren          #+#    #+#             */
/*   Updated: 2026/04/03 12:47:50 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"
#include <string.h>

int	check_for_space(char *cmd, t_envpcpy **envpcpy)
{
	int	i;
	int	ret_val;
	char **ch_ar;
	int *ptr;

	i = 0;
	ptr = 0;
	if (!cmd)
		return (1);
	while (cmd[i])
	{
		if (cmd[i] == ' ')
			break ;
		i++;
	}
	if (!ft_strncmp(cmd, "unset", i))
	{
		ch_ar = ft_split(cmd, ' ');
		ret_val = ft_unset(ch_ar + 1, envpcpy);
		i = 0;
		while (ch_ar[i])
			free(ch_ar[i++]);
		free(ch_ar);
		return (ret_val);
	}
	if (!ft_strncmp(cmd, "export", i))
	{
		i = 0;
		ch_ar = ft_split(cmd, ' ');
		ft_export(NULL, ch_ar, envpcpy);
		while (ch_ar[i])
			free(ch_ar[i++]);
		free(ch_ar);
		return (0);
	}
	if (!ft_strncmp(cmd, "cd", i))
	{
		ch_ar = ft_split(cmd, ' ');
		ret_val = ft_cd(*(ch_ar + 1), envpcpy);
		i = 0;
		while (ch_ar[i])
			free(ch_ar[i++]);
		free(ch_ar);
		return (ret_val);
	}
	if (!ft_strncmp(cmd, "pwd", i))
	{
		ch_ar = ft_split(cmd, ' ');
		ret_val = ft_pwd(envpcpy);
		i = 0;
		while (ch_ar[i])
			free(ch_ar[i++]);
		free(ch_ar);
		return (ret_val);
	}
	if (!ft_strncmp(cmd, "exit", i))
	{
		ch_ar = ft_split(cmd, ' ');
		if (!ch_ar + 1)
		{
			i = 0;
			while (ch_ar[i])
				free(ch_ar[i++]);
			free(ch_ar);
			ft_exit(0, envpcpy);
		}
		ret_val = ft_exit(ft_atoi(*(ch_ar + 1), ptr), envpcpy);
		return (ret_val);
	}
	if (!ft_strncmp(cmd, "env", i))
	{
		ft_env(envpcpy);
	}
	if (!ft_strncmp(cmd, "echo", i))
	{
		ch_ar = ft_split(cmd, ' ');
		ret_val = ft_echo(ch_ar + 1, 1);
		i = 0;
		while (ch_ar[i])
			free(ch_ar[i++]);
		free(ch_ar);
		return (ret_val);
	}
	return (0);
}

char *get_key(char *envp)
{
	char *key;
	int i = 0;
	int	j = 0;

	while (envp[i])
	{
		if (envp[i] == '=')
			break ;
		i++;
	}
	key = malloc((i + 1) * sizeof(char));
	while (j < i)
	{
		key[j] = envp[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char *get_value(char *envp)
{
	char *value;
	int i = 0;

	while (envp[i])
	{
		if (envp[i] == '=')
			break ;
		i++;
	}
	value = ft_strdup(envp + i + 1);
	return (value);
}

t_envpcpy	*create_envpcpy(char **envp)
{
	char *key;
	char *value;
	t_envpcpy *head;
	t_envpcpy *new;
	int i;

	i = 0;
	head = NULL;
	while (envp[i])
	{
		key = get_key(envp[i]);
		value = get_value(envp[i]);
		new = ft_lstnew(key, value);
		if (ft_strncmp(key, "PWD", 3) == 0)
			printf("%s=%s\n", key, value);
		ft_lstaddback(&head, new);
		i++;
	}
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	t_envpcpy *envpcpy;
	t_envpcpy *tmp;
	t_envpcpy *next;
	char	*cmd;

	(void)argc;
	(void)argv;
	envpcpy = create_envpcpy(envp);
	tmp = envpcpy;
	while(1)
	{
		cmd = readline("Ghost\\>: ");
		check_for_space(cmd, &envpcpy);
		free(cmd);
	}
	while (tmp)
	{
		next = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = next;
	}
	return (0);
}

