/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:31:20 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/09/30 18:31:21 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_malloc_err(t_err *err)
{
	err->err_no = MALLOC_ERROR;
	err->msg = "malloc: failed to allocate memory\n";
}

void	set_pipe_err(t_err *err)
{
	err->err_no = PIPE_ERROR;
	err->msg = "pipe failed\n";
}

void	set_tmpfile_err(t_err *err)
{
	err->err_no = TMPFILE_ERROR;
	err->msg = "cannot create temp file for here-document\n";
}

static void	print_err_msg(t_err *err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err->err_no == UNEXPECTED_TOK)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(err->msg, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd(err->msg, STDERR_FILENO);
}

// TODO: data->return_status = data->err.err_no; (after print_err_msg)
int	check_error(t_data *data, t_list *env)
{
	if (data->err.err_no == OK)
		return (1);
	if (data->err.err_no == HEREDOC_ABORT)
		return (clean_up(data), 0);
	print_err_msg(&(data->err));
	clean_up(data);
	if (data->err.err_no == MALLOC_ERROR)
	{
		ft_lstclear(&env, free);
		rl_clear_history();
		exit(1);
	}
	return (0);
}
