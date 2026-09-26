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
	return (type == REDIR_IN || type == REDIR_OUT || type == APPEND);
}

int	count_args(t_list *tokens)
{
	int	res;
	t_token	*tok;

	res = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
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

static int	is_delimiter(char *delimiter, char *line)
{
	int	len;

	len = ft_strlen(delimiter);
	if (ft_strncmp(delimiter, line, len) != 0)
		return (0);
	if (line[len] == '\n' && delimiter[len] == '\0')
		return (1);
	return (0);
}

t_redir	*handle_heredoc(t_list *tok)
{
	t_redir	*res = NULL;
	int		fds[2];
	char	*line;
	char	*delimiter;

	if (pipe(fds) != 0)
		return (NULL); // Error-handling should be here
	delimiter = ((t_token *)tok->next->content)->lexeme;
	line = get_next_line(0);
	while (line != NULL)
	{
		if (is_delimiter(delimiter, line) == 1)
			break ;
		printf("%s", line);
		line = get_next_line(0);
	}
	close(fds[0]);
	close(fds[1]);
	return (res);
}
