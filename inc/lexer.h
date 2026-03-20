/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 14:21:25 by julauren          #+#    #+#             */
/*   Updated: 2026/03/20 11:50:58 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND
}	t_type;

typedef struct s_token
{
	t_type			type;		//	type de mot
	char			*value;		//	texte
	struct s_token	*next;		//	pointeur vers le token suivant
}	t_token;

typedef enum e_state
{
	STATE_GENERAL,
	STATE_DQUOTE,
	STATE_SQUOTE
}	t_state;

t_token	*init_token_list(void);

#endif
