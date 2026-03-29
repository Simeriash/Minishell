/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julauren <julauren@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:59:51 by julauren          #+#    #+#             */
/*   Updated: 2026/03/29 14:50:42 by julauren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../src/libft/libft.h"
# include "lexer.h"

# include <stdlib.h>

//	/!\		A CHANGER !!	(OU PAS)
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

int		expand(t_token *token_list, t_env *envc);
void	error_parser(t_token *token_list, t_env *envc, t_error error);

#endif
