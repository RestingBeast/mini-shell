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

/*
** Removes quotes like bash: a quote opens a quoted part, and only the
** same kind of quote closes it. Inside, the other kind is a normal
** character: "a'b" -> a'b, 'x"y' -> x"y, E"O"F -> EOF.
** The result is never longer than str, so we allocate strlen(str) + 1.
** On success str is freed; on failure it is left untouched.
*/
char	*strip_quotes(char *str)
{
	char	*res;
	char	quote;
	int		i;
	int		j;

	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!res)
		return (NULL);
	quote = 0;
	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (quote == 0 && (str[i] == '\"' || str[i] == '\''))
			quote = str[i];
		else if (quote != 0 && str[i] == quote)
			quote = 0;
		else
			res[j++] = str[i];
	}
	free(str);
	return (res);
}
