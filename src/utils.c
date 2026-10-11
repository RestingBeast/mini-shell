/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 15:50:55 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/12 19:30:12 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err.err_no = OK;
	data->err.msg = NULL;
}

void	clean_up(t_data *data)
{
	free(data->line);
	free(data->err.msg);
	free_tokens(data->tokens);
	ft_nodeclear(data->tree);
}

char	*get_type(t_type type)
{
	if (type == PIPE)
		return ("|");
	if (type == REDIR_IN)
		return ("<");
	if (type == HEREDOC)
		return ("<<");
	if (type == REDIR_OUT)
		return (">");
	if (type == APPEND)
		return (">>");
	return (NULL);
}
