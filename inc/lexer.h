/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:25 by julauren          #+#    #+#             */
/*   Updated: 2026/03/26 11:54:46 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../src/libft/libft.h"

# include <stdlib.h>

typedef enum e_type
{
	WORD,
	EXPAND,
	PIPE,
	IN,
	OUT,
	HEREDOC,
	APPEND,
	AND,
	OR,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,
	RET
}	t_type;

typedef struct s_token
{
	t_type			type;		//	type de mot
	char			*value;		//	texte
	struct s_token	*next;		//	pointeur vers le token suivant
}	t_token;

typedef enum e_state
{
	NORMAL,
	SIMPLE_QUOTE,
	DOUBLE_QUOTE
}	t_state;

typedef enum e_ret
{
	CONTINUE,
	BREAK,
	NUL
}	t_ret;

typedef enum e_error
{
	OK,
	MALLOC,
	OPEN_QUOTE,
	AMPERSAND
}	t_error;

int		shell_space(int c);

/*====================linked_list====================*/

t_token	*init_token_list(void);
int		add_after(t_token *token, t_type type, char *value);
void	free_token(t_token *token_list);

/*===================token_creation===================*/

t_error	meta_token(char *str, t_token *token_list, int *i);
t_error	word_token(char *str, t_token *token_list, int *i);
t_error	quote_token(char *str, t_token *token_list, int *i, t_state state);
void	exit_lexer(t_token *token_list, t_error error);

t_token	*lexer(char *str);		//	/!\	A ENLEVER
#endif
