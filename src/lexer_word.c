#include "minishell.h"



static char	*extract_lexeme(char *line, int *i, t_lex_err *err)
{
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
				return (*err = LEX_UNCLOSED_QUOTE, NULL);
		}
		(*i)++;
	}
	*err = LEX_ALLOC;
	return (ft_substr(line, start, *i - start));
}


t_token	*read_word(char *line, int *i, t_lex_err *err)
{
	t_token		*tok;
	char *lexeme;

	lexeme = extract_lexeme(line, i, err);
	if (!lexeme)
		return (NULL);
	tok = new_token(WORD, lexeme);
	if (!tok)
		return (*err = LEX_ALLOC, free(lexeme), NULL);
	*err = LEX_OK;
	return (tok);
}
