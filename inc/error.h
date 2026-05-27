/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlanehar <dlanehar@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/17 07:43:23 by julauren          #+#    #+#             */
/*   Updated: 2026/05/27 14:00:56 by dlanehar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "../src/libft/libft.h"
# include "minishell.h"

typedef enum e_error
{
	OK,
	MALLOC,
	OPEN_QUOTE,
	INVALID_LIMITER,
	FD,
	WRITE,
	READ,
	NULL_ARG,
	UNSET_ENV
}	t_error;

void	error_envc(t_env *envc);
void	error_lexer(t_error error);
void	error_parser(t_token *token_list, t_error error);
void	error_heredoc(t_error error);
void	error_envc(t_env *envc);

void	ft_free_envc(t_env *envc);

#endif
