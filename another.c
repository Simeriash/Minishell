#include "./inc/minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>

void free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char *create_exec_path(char *path, char *cmd)
{
	char *tmp;
	char *ret;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	ret = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!ret)
		return (NULL);
	return (ret);
}

char **create_paths(t_exec_err *err)
{
	char	*path;
	char	**ret;

	path = getenv("PATH");
	if (!path)
	{
		*err = EXEC_NO_PATH;
		return (NULL);
	}
	ret = ft_split(path, ':');
	if (!ret)
	{
		*err = EXEC_MALLOC_FAIL;
		return (NULL);
	}
	return (ret);
}

void	cleanup_helper(char *first_file, char *first_dir)
{
	if (first_dir)
		free(first_dir);
	if (first_file)
		free(first_file);
	return ;
}

//-------------------------------------

/*

static int get_candidate_type(struct stat *st)
{
    if (!S_ISDIR(st->st_mode) &&
        (st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
        return 0; // executable

    if (!S_ISDIR(st->st_mode))
        return 1; // file

    return 2; // directory
}

static void store_fallback(char *candidate, int type,
                          char **first_file, char **first_dir)
{
    if (type == 1)
    {
        if (!*first_file)
            *first_file = candidate;
        else
            free(candidate);
    }
    else if (type == 2)
    {
        if (!*first_dir)
            *first_dir = candidate;
        else
            free(candidate);
    }
}

original if stat block

if (stat(candidate, &st) == 0)
{
    int type = get_candidate_type(&st);

    if (type == 0)
    {
        cleanup_helper(first_file, first_dir);
        return candidate;
    }

    store_fallback(candidate, type, &first_file, &first_dir);
}
else
{
    free(candidate);
}

*/

//-------------------------------------

char *create_candidate(char *cmd, char **paths, t_exec_err *err)
{
	struct stat	st;
	char		*candidate;
	char		*first_file;
	char		*first_dir;
	int			i;

	i = 0;
	first_file = NULL;
	first_dir = NULL;
	while (paths[i])
	{
		candidate = create_exec_path(paths[i], cmd);
		if (!candidate)
		{
			cleanup_helper(first_file, first_dir);
			// if (first_dir)
			// 	free(first_dir);
			// if (first_file)
			// 	free(first_file);
			*err = EXEC_MALLOC_FAIL;
			return (NULL);
		}
		if (stat(candidate, &st) == 0)
		{
			if (!S_ISDIR(st.st_mode) &&
				(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
				{
					cleanup_helper(first_file, first_dir);
					// if (first_dir)
					// 	free(first_dir);
					// if (first_file)
					// 	free(first_file);
					return (candidate);
				}
			if (!S_ISDIR(st.st_mode))
			{
				if (!first_file)
					first_file = candidate;
				else
					free(candidate);
			}
			else
			{
				if (!first_dir)
					first_dir = candidate;
				else
					free(candidate);
			}
		}
		else
			free(candidate);
		i++;
	}
	if (first_file)
	{
		if (first_dir)
			free(first_dir);
		return (first_file);
	}
	return (first_dir);
}



char *find_executable(char *cmd, t_exec_err *err)
{
	char	**paths;
	int		i;
	char	*ret;

	if (!cmd || !*cmd)
	{
		*err = EXEC_NOT_FOUND;
		return (NULL);
	}
	if (ft_strchr(cmd, '/'))
		return (ret);
	i = 0;
	paths = create_paths(err);
	if (!paths)
	{
		return (NULL);
	ret = create_candidate(cmd, paths, err);
	free_array(paths);
	return (ret);
}

// char *find_executable(char *cmd)
// {
// 	char	**path_array;
// 	int		i;
// 	char	*ret;
// 	char	*not_exec;

// 	not_exec = NULL;
// 	if (!cmd)
// 		return (NULL);
// 	if (access(cmd, F_OK) == 0)
// 		return strdup(cmd);
// 	i = 0;
// 	path_array = create_path_array();
// 	while (path_array[i])
// 	{
// 		ret = create_exec_path(path_array[i], cmd);
// 		if (!ret)
// 		{
// 			free_array(path_array);
// 			exit(121);
// 		}
// 		if (access(ret, F_OK) == 0)
// 		{
// 			if (access(ret, X_OK) == 0)
// 			{
// 				if (not_exec)
// 					free(not_exec);
// 				free_array(path_array);
// 				return (ret);
// 			}
// 			if (!not_exec)
// 				not_exec = ret;
// 			else
// 				free(ret);
// 		}
// 		else
// 			free(ret);
// 		i++;
// 	}
// 	free_array(path_array);
// 	if (not_exec)
// 		return (not_exec);
// 	return (NULL);
// }

int main(int argc, char **argv, char **envp)
{
	char	*cmd = argv[1];
	char	*executable;
	t_exec_err	err;
	pid_t	exec;
	int		status;

	executable = find_executable(cmd, &err);
	if (!executable)
	{
		//check err;
		if (!cmd)
			cmd = "BOOTYLICIOUS";
		printf("%s: command not found\n", cmd);
		return (127);
	}
	exec = fork();
	if (exec == 0)
	{
		execve(executable, argv + 1, envp);
		perror("execve");
		exit(126);
	}
	waitpid(exec, &status, 0);
	free(executable);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
