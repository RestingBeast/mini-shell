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
	return (type == REDIR_IN || type == REDIR_OUT ||
			type == APPEND || type == HEREDOC);
}

void	init_shell(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err.err_no = OK;
	data->err.msg = NULL;
	set_sigaction();
}

void	clean_up(t_data *data)
{
	free(data->line);
	free_tokens(data->tokens);
	ft_nodeclear(data->tree);
}

char	*strip_quotes(char *str)
{
	char	*res;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			continue ;
		j++;
	}
	res = ft_calloc(j + 1, sizeof(char));
	if (!res)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == '\"' || str[i] == '\'')
			continue ;
		res[j++] = str[i];
	}
	free(str);
	return (res);
}
