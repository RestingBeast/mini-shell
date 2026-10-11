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

static char	*get_err_msg(t_err_no err_no)
{
	if (err_no == MALLOC_ERROR)
		return ("malloc: failed to allocated memory\n");
	return (NULL);
}

void	set_syntax_err(t_err *err, char *lexeme)
{
	char	*str;

	err->err_no = SYNTAX_ERROR;
	if (!lexeme)
		err->msg = ft_strdup("syntax error: unclosed quote\n");
	else
	{
		str = ft_strjoin("syntax error near unexpected token `", lexeme);
		err->msg = ft_strjoin(str, "\'\n");
		free(str);
	}
}

int	check_error(t_data *data)
{
	if (data->err.err_no == OK)
		return (1);
//	data->return_status = data->err.err_no;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (data->err.err_no == SYNTAX_ERROR)
		ft_putstr_fd(data->err.msg, STDERR_FILENO);
	else
		ft_putstr_fd(get_err_msg(data->err.err_no), STDERR_FILENO);
	clean_up(data);
	if (data->err.err_no == MALLOC_ERROR)
		exit(1);
	return (0);
}
