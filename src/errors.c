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

static void	print_err_msg(t_err *err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err->err_no == UNEXPECTED_TOK)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(err->payload.msg, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
	}
	else
	{
		if (err->err_no == SYSCALL_ERR || err->err_no == CMD_ERROR
				|| err->err_no == CMD_NOT_FOUND)
			ft_putstr_fd(strerror(err->payload.err_no), STDERR_FILENO);
		else
			ft_putstr_fd(err->payload.msg, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
}

static int	get_status(t_err_no no)
{
	if (no == MALLOC_ERROR || no == SYSCALL_ERR)
		return (1);
	if (no == UNCLOSED_QUOTE || no == UNEXPECTED_TOK || no == END_PIPE
			|| no == END_REDIR)
		return (2);
	if (no == CMD_ERROR || no == IS_DIR_ERR)
		return (126);
	if (no == CMD_NOT_FOUND)
		return (127);
	return (0);
}

int	check_error(t_data *data, t_list *env)
{
	if (data->err.err_no == OK)
		return (1);
	if (data->err.err_no == HEREDOC_ABORT)
		return (clean_up(data), 0);
	data->status = get_status(data->err.err_no);
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
