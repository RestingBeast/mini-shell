/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 00:00:00 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/16 00:00:00 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_handler(int signum, void (*handler)(int))
{
	struct sigaction	act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = handler;
	sigaction(signum, &act, NULL);
}

/*
** In the child, before execve(): the program gets the default
** Ctrl-C and Ctrl-\ behaviour, not the shell's.
*/
void	set_child_sig(void)
{
	set_handler(SIGINT, SIG_DFL);
	set_handler(SIGQUIT, SIG_DFL);
}

/*
** In the shell while it waits for a child: Ctrl-C only kills the child.
** Call set_sigaction() after the wait to restore the prompt handlers.
*/
void	set_wait_sig(void)
{
	set_handler(SIGINT, SIG_IGN);
	set_handler(SIGQUIT, SIG_IGN);
}
