#include "minishell.h"



static char	*extract_lexeme(char *line, int *i, t_err_no *err)
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
				return (*err = SYNTAX_ERROR, NULL);
		}
		(*i)++;
	}
	*err = MALLOC_ERROR;
	return (ft_substr(line, start, *i - start));
}


t_token	*read_word(char *line, int *i, t_err_no *err)
{
	t_token		*tok;
	char *lexeme;

	lexeme = extract_lexeme(line, i, err);
	if (!lexeme)
		return (NULL);
	tok = new_token(WORD, lexeme);
	if (!tok)
		return (*err = MALLOC_ERROR, free(lexeme), NULL);
	*err = OK;
	return (tok);
}
