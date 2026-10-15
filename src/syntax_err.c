/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 02:34:43 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/13 14:43:59 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_type(t_type type)
{
	if (type == PIPE)
		return ("|");
	if (type == REDIR_IN)
		return ("<");
	if (type == HEREDOC)
		return ("<<");
	if (type == REDIR_OUT)
		return (">");
	if (type == APPEND)
		return (">>");
	return (NULL);
}

void	set_quote_err(t_err *err, char quote)
{
	err->type = UNCLOSED_QUOTE;
	if (quote == '\'')
		err->msg = "unexpected EOF while looking for matching `\'\'";
	else
		err->msg = "unexpected EOF while looking for matching `\"\'";
}

void	set_unexp_tok_err(t_err *err, t_type tok)
{
	err->type = UNEXPECTED_TOK;
	err->msg = get_type(tok);
}

void	set_end_pipe_err(t_err *err)
{
	err->type = END_PIPE;
	err->msg = "syntax error: unexpected end of file";
}

void	set_end_redir_err(t_err *err)
{
	err->type = END_REDIR;
	err->msg = "syntax error near unexpected token `newline\'";
}
