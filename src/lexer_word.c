#include "minishell.h"

static char	*extract_lexeme(char *line, int *i, t_err *err)
{
	char	*res;
	int		start;
	char	quote;

	start = *i;
	while (line[*i] && !is_space(line[*i]) && !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
		{
			quote = line[(*i)++];
			while (line[*i] && line[*i] != quote)
				(*i)++;
			if (!line[*i])
				return (set_quote_err(err, quote), NULL);
		}
		(*i)++;
	}
	res = ft_substr(line, start, *i - start);
	if (!res)
		return (set_malloc_err(err), NULL);
	return (res);
}

t_token	*read_word(char *line, int *i, t_err *err)
{
	t_token		*tok;
	char *lexeme;

	lexeme = extract_lexeme(line, i, err);
	if (!lexeme)
		return (NULL);
	tok = new_token(WORD, lexeme);
	if (!tok)
		return (set_malloc_err(err), free(lexeme), NULL);
	return (tok);
}
