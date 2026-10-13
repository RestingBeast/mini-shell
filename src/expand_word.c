/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:34:39 by psoe              #+#    #+#             */
/*   Updated: 2026/10/13 12:34:39 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Joins S1 and S2 into a new string, and frees both of them.
** Returns NULL if malloc failed, or if S1 or S2 was already NULL:
** that way one failed malloc stops the whole word and nothing leaks.
*/
static char	*join_free(char *s1, char *s2)
{
	char	*joined;

	joined = NULL;
	if (s1 != NULL && s2 != NULL)
		joined = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (joined);
}

/*
** True when WORD[I] is a $ outside quotes, right before a quote.
** bash drops that $: $"HOME" and $'HOME' both give HOME.
*/
static int	is_dollar_before_quote(char *word, int i, char quote)
{
	return (word[i] == '$' && quote == 0
		&& (word[i + 1] == '\'' || word[i + 1] == '"'));
}

/*
** Returns a new string: WORD with its variables replaced by their
** values and its quotes removed. Both are done in the same walk,
** because each char needs to know which quote it is in:
**   - a quote that opens or closes a quoted part is dropped
**   - a $ is expanded, except inside '...'
**   - every other char is copied as it is
** Quotes that come from a variable's value are copied, not removed.
** Returns NULL if malloc failed. WORD itself is not changed.
*/
char	*expand_word(char *word, t_list *env, int status)
{
	char	*res;
	char	quote;
	int		i;

	res = ft_strdup("");
	quote = 0;
	i = 0;
	while (res != NULL && word[i] != '\0')
	{
		if (is_quote_mark(word[i], &quote))
			i++;
		else if (is_dollar_before_quote(word, i, quote))
			i++;
		else if (word[i] == '$' && quote != '\'')
			res = join_free(res, expand_dollar(word, &i, env, status));
		else
		{
			res = join_free(res, ft_substr(word, i, 1));
			i++;
		}
	}
	return (res);
}
