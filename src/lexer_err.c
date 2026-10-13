/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 02:34:43 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/13 14:43:59 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks the new token TOK against the last one, like bash:
**   - a word is always fine
**   - a pipe cannot come first or right after another pipe
**   - after a redirection there must be a word (the file name)
**   - a redirection right after a pipe is fine: "cat | > out"
** The error names the new token, the one that does not fit.
*/
int	syntax_check(t_list **tokens, t_token *tok, t_err *err)
{
	t_token	*last;

	if (tok->type == WORD)
		return (1);
	last = NULL;
	if (*tokens != NULL)
		last = (t_token *)(ft_lstlast(*tokens))->content;
	if (tok->type == PIPE && (last == NULL || last->type == PIPE))
		return (set_unexp_tok_err(err, PIPE), 0);
	if (last != NULL && is_redir(last->type))
		return (set_unexp_tok_err(err, tok->type), 0);
	return (1);
}

void	last_token_check(t_list **tokens, t_err *err)
{
	t_token	*last;

	if (*tokens == NULL)
		return ;
	last = (t_token *)(ft_lstlast(*tokens))->content;
	if (last->type == WORD)
		return ;
	if (last->type == PIPE)
		set_end_pipe_err(err);
	else
		set_end_redir_err(err);
	free_tokens(*tokens);
	*tokens = NULL;
}
