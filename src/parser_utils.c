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

static char	*strip_delimiter(char *str)
{
	char	*res;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			continue ;
		j++;
	}
	res = ft_calloc(j + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			continue ;
		res[j++] = str[i];
	}
	free(str);
	return (res);
}

static void capture_input(char *delimiter, int fd)
{
	char	*line;

	line = readline(">");
	while (line != NULL)
	{
		if (ft_memcmp((void *)delimiter,
			(void *)line, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(">");
	}
	free(line);
}

t_redir	*handle_heredoc(t_list *tok)
{
	t_redir	*res;
	char	*delimiter;
	int		fds[2];

	if (pipe(fds) != 0)
		return (NULL); // Error-handling should be here
	delimiter = strip_delimiter(((t_token *)tok->next->content)->lexeme);
	if (!delimiter)
		return (NULL); // Error
	capture_input(delimiter, fds[1]);
	close(fds[1]);
	res = ft_redirnew_fd(HEREDOC, fds[0]);
	if (!res)
		return (NULL); // Error-handling should be here
	free(delimiter);
	((t_token *)tok->next->content)->lexeme = NULL;
	return (res);
}
