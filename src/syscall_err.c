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
	err->msg = "malloc: failed to allocate memory";
}

void	set_syscall_err(t_err *err)
{
	err->type = SYSCALL_ERR;
	err->err_no = errno;
}

void	set_ambiguous_err(t_err *err, char *file)
{
	err->type = AMBIGUOUS_ERR;
	err->msg = file;
}

void	set_file_err(t_err *err, char *file)
{
	err->type = FILE_ERR;
	err->err_no = errno;
	err->msg = file;
}
