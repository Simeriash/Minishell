/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:25 by julauren          #+#    #+#             */
/*   Updated: 2026/03/20 15:42:11 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

typedef enum e_type
{
	WORD,
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
	GENERAL,
	DOUBLE_QUOTE,
	SIMPLE_QUOTE
}	t_state;

/*====================linked_list====================*/

t_token	*init_token_list(void);
int		add_after(t_token *token, t_type type, char *value);
void	free_token(t_token *token_list);

#endif
