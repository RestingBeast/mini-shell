/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 16:14:46 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/17 16:14:48 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The shell ignores Ctrl-C while it waits, so only the child is killed.
*/
void	wait_child(pid_t pid, int *status)
{
	int	wstatus;

	set_wait_sig();
	waitpid(pid, &wstatus, 0);
	set_sigaction();
	if (WIFEXITED(wstatus))
		*status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		*status = 128 + WTERMSIG(wstatus);
		if (WTERMSIG(wstatus) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(wstatus) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

void	close_fds(int in_fd, int out_fd)
{
	if (in_fd >= 0)
		close(in_fd);
	if (out_fd >= 0)
		close(out_fd);
}

void	init_exec(t_exec *exec)
{
	exec->in_fd = -1;
	exec->out_fd = -1;
	exec->close_fd = -1;
	exec->args = NULL;
}
