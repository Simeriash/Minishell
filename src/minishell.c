/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 13:09:01 by julauren          #+#    #+#             */
/*   Updated: 2026/03/24 15:13:32 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "builtins.h"

int	check_for_space(char **envp, char *cmd)
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
	if (!ft_strncmp(cmd, "cd", i))
	{
		ch_ar = ft_split(cmd, ' ');
		ret_val = ft_cd(envp, *(ch_ar + 1));
		i = 0;
		while (ch_ar[i])
			free(ch_ar[i++]);
		free(ch_ar);
		return (ret_val);
	}
	if (!ft_strncmp(cmd, "pwd", i))
	{
		ch_ar = ft_split(cmd, ' ');
		ret_val = ft_pwd(envp);
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
			ft_exit(0);
		ret_val = ft_exit(ft_atoi(*(ch_ar + 1), ptr));
		return (ret_val);
	}
	if (!ft_strncmp(cmd, "env", i))
	{
		ft_env(envp);
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

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char **envpcpy;

	(void)argc;
	(void)argv;

	int	i = 0;
	while (envp[i])
		i++;
	printf("num of envp = %d\n", i);
	envpcpy = malloc((i + 1) * sizeof(char *));
	i = 0;
	while (envp[i]){
		envpcpy[i] = ft_strdup(envp[i]);
		//printf("%s\n", envpcpy[i]);
		i++;
	}
	envpcpy[i] = NULL;
	while(1)
	{
		cmd = readline("Ghost\\>: ");
		check_for_space(envpcpy, cmd);
		free(cmd);
	}
	i = 0;
	while(envpcpy[i])
	{
		free(envpcpy[i]);
		i++;
	}
	free(envpcpy);
}
