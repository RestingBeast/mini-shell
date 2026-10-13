/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:34:39 by psoe              #+#    #+#             */
/*   Updated: 2026/10/13 12:34:39 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** True when C opens or closes a quoted part, and updates *quote:
** *quote is 0 outside quotes, or the quote char we are inside.
** Inside "...", a ' is a normal char (and the same for " inside '...').
*/
int	is_quote_mark(char c, char *quote)
{
	if (*quote == 0 && (c == '\'' || c == '"'))
	{
		*quote = c;
		return (1);
	}
	if (*quote != 0 && c == *quote)
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

static int	unquoted_len(char *str)
{
	int		len;
	int		i;
	char	quote;

	len = 0;
	i = -1;
	quote = 0;
	while (str[++i] != '\0')
	{
		if (!is_quote_mark(str[i], &quote))
			len++;
	}
	return (len);
}

/*
** Removes the quotes that open and close quoted parts, like bash:
** "it's" -> it's    '"hi"' -> "hi"    he"ll"o -> hello
** Nothing is expanded: it is used for the heredoc delimiter.
** STR is always freed, even when malloc fails (then returns NULL).
*/
char	*strip_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	char	quote;

	if (str == NULL)
		return (NULL);
	res = ft_calloc(unquoted_len(str) + 1, sizeof(char));
	if (res == NULL)
		return (free(str), NULL);
	i = -1;
	j = 0;
	quote = 0;
	while (str[++i] != '\0')
	{
		if (!is_quote_mark(str[i], &quote))
			res[j++] = str[i];
	}
	free(str);
	return (res);
}
