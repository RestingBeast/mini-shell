/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 14:28:15 by psoe              #+#    #+#             */
/*   Updated: 2026/10/13 14:28:15 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <errno.h>

static void	warn_eof(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by "
		"end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

static void	capture_input(char *delimiter, int fd, t_err *err)
{
	char	*line;

	g_sig_captured = 0;
	set_heredoc_sig();
	if (isatty(STDIN_FILENO))
		rl_event_hook = rl_check;
	line = readline("> ");
	while (line != NULL && g_sig_captured == 0)
	{
		if (ft_memcmp((void *)delimiter,
				(void *)line, ft_strlen(delimiter) + 1) == 0)
			break ;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
	if (g_sig_captured == SIGINT)
		err->err_no = HEREDOC_ABORT;
	if (line == NULL)
		warn_eof(delimiter);
	free(line);
	rl_event_hook = NULL;
	g_sig_captured = 0;
}

static char	*make_tmp_path(int n)
{
	char	*number;
	char	*path;

	number = ft_itoa(n);
	if (!number)
		return (NULL);
	path = ft_strjoin("/tmp/.minishell_heredoc_", number);
	free(number);
	return (path);
}

/*
** Creates a new empty file in /tmp and opens it for writing.
** O_EXCL makes open() fail when the name is already taken,
** so we try _0, _1, _2... until one is free.
*/
static int	open_tmp_file(char **path, t_err *err)
{
	int	fd;
	int	n;

	n = 0;
	while (1)
	{
		*path = make_tmp_path(n);
		if (!*path)
			return (set_malloc_err(err), -1);
		fd = open(*path, O_WRONLY | O_CREAT | O_EXCL, 0600);
		if (fd != -1)
			return (fd);
		free(*path);
		*path = NULL;
		if (errno != EEXIST)
			return (set_syscall_err(err), -1);
		n++;
	}
}

/*
** The heredoc text goes into a temp file, not a pipe: a pipe holds
** only 64 KB, and nobody reads it before the command runs.
** We write the file, then open it again to read from the start.
** unlink() removes the name right away, but our fd can still read it.
** The file is really deleted when the fd is closed.
*/
t_redir	*handle_heredoc(t_list *tok, t_err *err)
{
	t_redir	*res;
	char	*delimiter;
	char	*path;
	int		fd;

	delimiter = strip_quotes(((t_token *)tok->next->content)->lexeme);
	if (!delimiter)
		return (set_malloc_err(err), NULL);
	((t_token *)tok->next->content)->lexeme = NULL;
	fd = open_tmp_file(&path, err);
	if (fd == -1)
		return (free(delimiter), NULL);
	capture_input(delimiter, fd, err);
	free(delimiter);
	close(fd);
	fd = open(path, O_RDONLY);
	unlink(path);
	free(path);
	if (fd == -1)
		return (set_syscall_err(err), NULL);
	res = ft_redirnew_fd(HEREDOC, fd);
	if (!res)
		return (close(fd), set_malloc_err(err), NULL);
	return (res);
}
