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

void	print_cmd_err_msg(t_err_type type, int err_no, char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (type == IS_DIR_ERR)
		ft_putstr_fd("Is a directory", STDERR_FILENO);
	else if (ft_strchr(msg, '/') == NULL)
		ft_putstr_fd("command not found...", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(err_no), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	print_err_msg(t_err *err)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (err->type == UNEXPECTED_TOK)
	{
		ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(err->msg, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
		return ;
	}
	if (err->type == CMD_ERROR || err->type == CMD_NOT_FOUND 
			|| err->type == IS_DIR_ERR)
	{
		print_cmd_err_msg(err->type, err->err_no, err->msg);
		return ;
	}
	ft_putstr_fd(err->msg, STDERR_FILENO);
	ft_putstr_fd(strerror(err->err_no), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int	get_status(t_err_type type)
{
	if (type == MALLOC_ERROR || type == SYSCALL_ERR)
		return (1);
	if (type == UNCLOSED_QUOTE || type == UNEXPECTED_TOK || type == END_PIPE
			|| type == END_REDIR)
		return (2);
	if (type == CMD_ERROR || type == IS_DIR_ERR)
		return (126);
	if (type == CMD_NOT_FOUND)
		return (127);
	if (type == HEREDOC_ABORT)
		return (130);
	return (0);
}

int	check_error(t_data *data, t_list *env, int *status)
{
	if (data->err.type == OK)
		return (1);
	*status = get_status(data->err.type);
	if (data->err.type == HEREDOC_ABORT)
		return (clean_up(data), 0);
	print_err_msg(&(data->err));
	clean_up(data);
	if (data->err.type == MALLOC_ERROR)
	{
		ft_lstclear(&env, free);
		rl_clear_history();
		exit(1);
	}
	return (0);
}
