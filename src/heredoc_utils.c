/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 21:38:42 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/17 21:38:45 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	warn_eof(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document delimited by "
		"end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

char	*make_tmp_path(int n)
{
	char	*number;
	char	*path;

	number = ft_itoa(n);
	if (!number)
		return (NULL);
	path = ft_strjoin("/tmp/.minishell_heredoc_", number);
	free(number);
	return (path);
}
