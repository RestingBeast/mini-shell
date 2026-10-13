/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/29 00:45:01 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/09/29 00:45:02 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig_captured = 0;

static void	handle_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	g_sig_captured = SIGINT;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	handle_heredoc_int(int signum)
{
	if (signum != SIGINT)
		return ;
	g_sig_captured = SIGINT;
}

/*
** readline calls this about 10 times a second while it waits for input
** (when it is set as rl_event_hook). After Ctrl-C it makes readline stop.
*/
int	rl_check(void)
{
	if (g_sig_captured == SIGINT)
		rl_done = 1;
	return (0);
}

void	set_heredoc_sig(void)
{
	struct sigaction	int_act;
	struct sigaction	quit_act;

	ft_bzero(&int_act, sizeof(int_act));
	int_act.sa_handler = &handle_heredoc_int;
	sigaction(SIGINT, &int_act, NULL);
	ft_bzero(&quit_act, sizeof(quit_act));
	quit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &quit_act, NULL);
}

void	set_sigaction(void)
{
	struct sigaction	int_act;
	struct sigaction	quit_act;

	ft_bzero(&int_act, sizeof(int_act));
	int_act.sa_handler = &handle_sigint;
	sigaction(SIGINT, &int_act, NULL);
	ft_bzero(&quit_act, sizeof(quit_act));
	quit_act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &quit_act, NULL);
}
