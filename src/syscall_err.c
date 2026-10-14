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

void	set_syscall_err(t_err *err)
{
	err->err_no = SYSCALL_ERR;
	err->payload.err_no = errno;
}

void	set_cmd_err(t_err *err)
{
	err->err_no = CMD_ERROR;
	err->payload.err_no = errno;
}

void	set_cmd_not_found_err(t_err *err)
{
	err->err_no = CMD_NOT_FOUND;
	err->payload.err_no = errno;
}

void	set_dir_err(t_err *err)
{
	err->err_no = IS_DIR_ERR;
	err->payload.msg = "Is a directory";
}
