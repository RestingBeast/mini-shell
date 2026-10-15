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
	err->type = MALLOC_ERROR;
	err->msg = "malloc: failed to allocate memory\n";
}

void	set_syscall_err(t_err *err)
{
	err->type = SYSCALL_ERR;
	err->err_no = errno;
}

void	set_cmd_err(t_err *err, char *cmd)
{
	err->type = CMD_ERROR;
	err->err_no = errno;
	err->msg = cmd;
}

void	set_cmd_not_found_err(t_err *err, char *cmd)
{
	err->type = CMD_NOT_FOUND;
	err->err_no = errno;
	err->msg = cmd;
}

void	set_dir_err(t_err *err, char *cmd)
{
	err->type = IS_DIR_ERR;
	err->msg = cmd;
}
