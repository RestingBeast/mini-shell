/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 23:48:45 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/13 14:43:59 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "type.h"
# include "libft.h"
# include "error.h"

typedef struct s_token	t_token;

struct s_token
{
	t_type	type;
	char	*lexeme;
};

// lexer.c
t_list	*lexer(char *line, t_err *err);

// lexer_word.c
t_token	*read_word(char *line, int *i, t_err *err);

// lexer_utils.c
int		is_operator(char c);
t_token	*new_token(t_type type, char *lexeme);
void	free_token(void *content);
void	free_tokens(t_list *tokens);

// lexer_err.c
int		syntax_check(t_list **tokens, t_token *tok, t_err *err);
void	last_token_check(t_list **tokens, t_err *err);

#endif
