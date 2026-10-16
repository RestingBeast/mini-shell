#include "minishell.h"

static int	get_flags(t_type type)
{
	if (type == REDIR_IN)
		return (O_RDONLY);
	if (type == REDIR_OUT)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	if (type == APPEND)
		return (O_CREAT | O_APPEND | O_WRONLY);
	return (0);
}

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd >= 0)
		close(in_fd);
	if (out_fd >= 0)
		close(out_fd);
}

static void	set_fds(t_type type, int *in_fd, int *out_fd, int fd)
{
	if (type == REDIR_IN || type == HEREDOC)
	{
		close_fds(*in_fd, -1);
		*in_fd = fd;
	}
	else
	{
		close_fds(-1, *out_fd);
		*out_fd = fd;
	}
}

static	int	copy_heredoc_fd(t_redir *rdr, int *in_fd)
{
	int	fd;
	
	fd = dup(rdr->target.fd);
	if (fd == -1)
		return (0);
	set_fds(rdr->type, in_fd, NULL, fd);
	return (1);
}

int	resolve_redir(t_list *redir, t_err *err, int *in_fd, int *out_fd)
{
	t_redir	*rdr;
	int		fd;

	*in_fd = -1;
	*out_fd = -1;
	while (redir != NULL)
	{
		rdr = (t_redir *)(redir->content);
		if (rdr->ambiguous)
			return (close_fds(*in_fd, *out_fd),
				set_ambiguous_err(err, rdr->target.file), 0);
		if (rdr->type != HEREDOC)
		{
			fd = open(rdr->target.file, get_flags(rdr->type), 0666);
			if (fd == -1)
				return (set_file_err(err, rdr->target.file),
					close_fds(*in_fd, *out_fd), 0);
			set_fds(rdr->type, in_fd, out_fd, fd);
		}
		else
			if (!copy_heredoc_fd(rdr, in_fd))
				return (close_fds(*in_fd, *out_fd), set_syscall_err(err), 0);
		redir = redir->next;
	}
	return (1);
}
