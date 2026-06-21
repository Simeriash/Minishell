/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 09:40:34 by julauren          #+#    #+#             */
/*   Updated: 2026/06/21 10:02:49 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../src/libft/libft.h"
# include "minishell.h"
# include "error.h"

# include <stdlib.h>

typedef enum e_state
{
	NORMAL,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE,
	HEREDOC_MODE
}	t_state;

typedef enum e_ret
{
	NEXT,
	CONTINUE,
	BREAK,
	NUL
}	t_ret;

void	shell_space(char *str, int *i);
int		end_condition(char *str, int *i);
void	state_condition(char c, t_state *state);

/*====================linked_list====================*/

t_token	*init_token_list(int *status);
int		add_after(t_token *token, t_type type, char *value);
void	free_token(t_token *token_list);

/*===================token_creation===================*/

t_error	meta_token(char *str, t_token *token, int *i);

#endif
