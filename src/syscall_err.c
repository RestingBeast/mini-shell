/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_err.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 19:11:45 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/14 19:11:46 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_malloc_err(t_err *err)
{
	err->err_no = MALLOC_ERROR;
	err->payload.msg = "malloc: failed to allocate memory\n";
}

void	set_pipe_err(t_err *err)
{
	err->err_no = PIPE_ERROR;
	err->payload.err_no = errno;
}

void	set_tmpfile_err(t_err *err)
{
	err->err_no = TMPFILE_ERROR;
	err->payload.err_no = errno;
}

void	set_fork_err(t_err *err)
{
	err->err_no = FORK_ERROR;
	err->payload.err_no = errno;
}
