/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 15:50:55 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/13 11:37:54 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == APPEND || type == HEREDOC);
}

void	init_shell(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err.type = OK;
	data->err.err_no = 0;
	data->err.msg = "";
	set_sigaction();
}

/*
** Frees what one command line allocated. The pointers are reset so that
** calling it twice (e.g. clean_up() then clean_exit()) is safe.
*/
void	clean_up(t_data *data)
{
	free(data->line);
	free_tokens(data->tokens);
	ft_nodeclear(data->tree);
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
}

/*
** Frees everything the shell owns, before the shell or a child exits.
*/
void	clean_exit(t_data *data)
{
	clean_up(data);
	ft_lstclear(&(data->env), free);
	rl_clear_history();
}
