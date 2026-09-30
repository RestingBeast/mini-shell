#include "minishell.h"

static t_segment	*new_segment(char *text, t_quote quote)
{
	t_segment	*seg;

	if (!text)
		return (NULL);
	seg = malloc(sizeof(t_segment));
	if (!seg)
	{
		free(text);
		return (NULL);
	}
	seg->text = text;
	seg->quote = quote;
	return (seg);
}

static t_segment	*read_quoted(char *line, int *i)
{
	char	q;
	int		start;
	t_quote	quote;

	q = line[*i];
	quote = SINGLE;
	if (q == '"')
		quote = DOUBLE;
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != q)
		(*i)++;
	if (!line[*i])
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		return (NULL);
	}
	(*i)++;
	return (new_segment(ft_substr(line, start, *i - 1 - start), quote));
}

static t_segment	*read_unquoted(char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !is_space(line[*i]) && !is_operator(line[*i])
		&& line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	return (new_segment(ft_substr(line, start, *i - start), NONE));
}

static int	add_segment(t_token *tok, t_segment *seg)
{
	t_list	*node;

	if (!seg)
		return (0);
	node = ft_lstnew(seg);
	if (!node)
	{
		free_segment(seg);
		return (0);
	}
	ft_lstadd_back(&tok->lexeme, node);
	return (1);
}

t_token	*read_word(char *line, int *i)
{
	t_token		*tok;
	t_segment	*seg;

	tok = new_token(WORD);
	if (!tok)
		return (NULL);
	while (line[*i] && !is_space(line[*i]) && !is_operator(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			seg = read_quoted(line, i);
		else
			seg = read_unquoted(line, i);
		if (!add_segment(tok, seg))
		{
			free_token(tok);
			return (NULL);
		}
	}
	return (tok);
}
