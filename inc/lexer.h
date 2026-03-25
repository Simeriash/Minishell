/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:25 by julauren          #+#    #+#             */
/*   Updated: 2026/03/22 13:11:57 by julauren         ###   ########.fr       */
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
	RIGHT_PARENTHESIS
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

/*====================linked_list====================*/

t_token	*init_token_list(char *str);
int		add_after(t_token *token, t_type type, char *value);
void	free_token(t_token *token_list);

/*===================token_creation===================*/

int		meta_token(char *str, t_token *token_list, int *i);
int		word_token(char *str, t_token *token_list, int *i);
int		quote_token(char *str, t_token *token_list, int *i, t_state state);
void	exit_lexer(char *str, t_token *token_list);

t_token	*lexer(char *str);		//	/!\	A ENLEVER
#endif
