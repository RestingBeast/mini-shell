/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 16:10:06 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/13 16:10:07 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(t_list *tokens)
{
	int	res;
	t_token	*tok;

	res = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == PIPE)
			break ;
		if (tok->lexeme != NULL)
			res++;
		tokens = tokens->next;
	}
	return (res);
}

t_redir	*handle_redir(t_list *tok, t_err *err)
{
	t_type	type;
	char	*file;
	t_redir	*res;

	type = ((t_token *)tok->content)->type;
	file = ((t_token *)tok->next->content)->lexeme;
	res = ft_redirnew_file(type, file);
	if (!res)
		return (set_malloc_err(err), NULL);
	((t_token *)tok->next->content)->lexeme = NULL;
	return (res);
}
