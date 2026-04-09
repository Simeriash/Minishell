/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 08:46:16 by dlanehar          #+#    #+#             */
/*   Updated: 2026/04/09 10:14:41 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

//# include "../src/libft/libft.h"
//# include <readline/readline.h>
//# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum {
  PIPE,
  AND,
  OR,
  INFILE,
  OUTFILE,
} e_cmdtype;

typedef struct s_tree
{
	e_cmdtype type;
	int value;
	char *str;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;


#endif
