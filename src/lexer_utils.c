/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 20:19:44 by psoe              #+#    #+#             */
/*   Updated: 2026/10/13 14:43:59 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*new_token(t_type type, char *lexeme)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->lexeme = lexeme;
	tok->type = type;
	return (tok);
}

void	free_token(void *content)
{
	t_token	*tok;

	tok = (t_token *)content;
	free(tok->lexeme);
	free(tok);
}

void	free_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, free_token);
}
