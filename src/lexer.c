/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 06:41:04 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/13 14:43:59 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*read_operator(char *line, int *i, t_err *err)
{
	t_type	type;
	t_token	*tok;

	if (line[*i] == '|')
		type = PIPE;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		type = HEREDOC;
	else if (line[*i] == '<')
		type = REDIR_IN;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		type = APPEND;
	else
		type = REDIR_OUT;
	if (type == HEREDOC || type == APPEND)
		(*i)++;
	(*i)++;
	tok = new_token(type, NULL);
	if (!tok)
		return (set_malloc_err(err), NULL);
	return (tok);
}

static int	add_token(t_list **tokens, t_token *tok, t_err *err)
{
	t_list	*node;

	node = NULL;
	if (!tok)
		return (0);
	if (!syntax_check(tokens, tok, err))
		return (free_token(tok), free_tokens(*tokens), 0);
	node = ft_lstnew(tok);
	if (!node)
	{
		free_token(tok);
		free_tokens(*tokens);
		set_malloc_err(err);
		return (0);
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

static t_token	*read_token(char *line, int *i, t_err *err)
{
	t_token	*tok;

	if (is_operator(line[*i]))
		tok = read_operator(line, i, err);
	else
		tok = read_word(line, i, err);
	return (tok);
}

t_list	*lexer(char *line, t_err *err)
{
	t_list	*tokens;
	t_token	*tok;
	int		i;

	err->err_no = OK;
	if (!line)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else
		{
			tok = read_token(line, &i, err);
			if (!tok)
				return (free_tokens(tokens), NULL);
			if (!add_token(&tokens, tok, err))
				return (NULL);
		}
	}
	last_token_check(&tokens, err);
	return (tokens);
}
