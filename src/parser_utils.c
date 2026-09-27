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

int	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT ||
			type == APPEND || type == HEREDOC);
}

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

t_redir	*handle_redir(t_list *tok)
{
	t_type	type;
	char	*file;
	t_redir	*res;

	type = ((t_token *)tok->content)->type;
	file = ((t_token *)tok->next->content)->lexeme;
	res = ft_redirnew_file(type, file);
	if (!res)
		return (NULL); // Error-handling should be here
	((t_token *)tok->next->content)->lexeme = NULL;
	return (res);
}

t_redir	*handle_heredoc(t_list *tok)
{
	t_redir	*res;
	int		fds[2];
	char	*line;
	char	*delimiter;

	if (pipe(fds) != 0)
		return (NULL); // Error-handling should be here
	delimiter = ((t_token *)tok->next->content)->lexeme;
	line = readline(">");
	while (line != NULL)
	{
		if (ft_memcmp((void *)delimiter, (void *)line, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(fds[1], line, ft_strlen(line));
		write(fds[1], "\n", 1);
		line = readline(">");
	}
	close(fds[1]);
	res = ft_redirnew_fd(HEREDOC, fds[0]);
	if (!res)
		return (NULL); // Error-handling should be here
	((t_token *)tok->next->content)->lexeme = NULL;
	return (res);
}
