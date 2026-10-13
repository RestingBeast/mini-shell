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

int	rl_check(void)
{
	if (sig_captured == SIGINT)
		rl_done = 1;
	return (0);
}

static void capture_input(char *delimiter, int fd, t_err *err)
{
	char	*line;

	set_heredoc_sig();
	rl_event_hook = rl_check;
	line = readline("> ");
	while (line != NULL && sig_captured == 0)
	{
		if (ft_memcmp((void *)delimiter,
			(void *)line, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (sig_captured == SIGINT)
		err->err_no = HEREDOC_ABORT;
	if (line == NULL)
		printf("minishell: warning: here-document delimited by end-of-file "
			"(wanted `%s')\n", delimiter);
	free(line);
	rl_event_hook = NULL;
	sig_captured = 0;
}

t_redir	*handle_heredoc(t_list *tok, t_err *err)
{
	t_redir	*res;
	char	*delimiter;
	int		fds[2];

	if (pipe(fds) != 0)
		return (set_pipe_err(err), NULL);
	delimiter = strip_quotes(((t_token *)tok->next->content)->lexeme);
	((t_token *)tok->next->content)->lexeme = NULL;
	if (!delimiter)
		return (set_malloc_err(err), NULL);
	capture_input(delimiter, fds[1], err);
	free(delimiter);
	close(fds[1]);
	res = ft_redirnew_fd(HEREDOC, fds[0]);
	if (!res)
		return (set_malloc_err(err), NULL);
	return (res);
}
