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

static void	wait_last_child(pid_t pid, int *status)
{
	int	estatus;

	waitpid(pid, &estatus, 0);
	if (WIFEXITED(estatus))
		*status = WEXITSTATUS(estatus);
	else if (WIFSIGNALED(estatus))
	{
		*status = 128 + WTERMSIG(estatus);
		if (WTERMSIG(estatus) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(estatus) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

/*
** The shell ignores Ctrl-C while it waits, so only the child is killed.
*/
void	wait_children(pid_t pid, int *status, int processes)
{
	int	wstatus;

	if (processes == 0)
		return ;
	set_wait_sig();
	if (pid != -1)
	{
		wait_last_child(pid, status);
		processes--;
	}
	while (processes-- > 0)
		waitpid(-1, &wstatus, 0);
	set_sigaction();
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

void	set_last_pid(t_data *data, int pid)
{
	data->last_pid = pid;
	(data->processes)++;
}
