#include "minishell.h"



static char	*extract_lexeme(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !is_space(line[*i]) && !is_operator(line[*i])
		&& line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	return (ft_substr(line, start, *i - start));
}


t_token	*read_word(char *line, int *i)
{
	t_token		*tok;
	char *lexeme;

lexeme = extract_lexeme(line, i);
if (!lexeme)
	return  (NULL);
tok = new_token(WORD, lexeme);
if (!tok)
	return (free(lexeme), NULL);
	return (tok);
}
