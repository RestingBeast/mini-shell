#include "minishell.h"

t_token	*new_token(t_type type, char *lexeme)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->lexeme = lexeme;
	tok->type = type;
	return (tok);
}

static t_token	*read_operator(char *line, int *i)
{
	t_type	type;

	if (line[*i] == '|')
		type = PIPE;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		type = HEREDOC;
	else if (line[*i] == '<')
		type = REDIR_IN;
	else if (line[*i] == '>' && line[*i + 1] == '>')
		type = APPEND;
	else
		type = REDIR_OUT;
	if (type == HEREDOC || type == APPEND)
		(*i)++;
	(*i)++;
	return (new_token(type, NULL));
}

static int	add_token(t_list **tokens, t_token *tok)
{
	t_list	*node;

	node = NULL;
	if (!tok)
	        return (0);
	node = ft_lstnew(tok);
	if (!node)
	{
		free_token(tok);
		free_tokens(*tokens);
		*tokens = NULL;
		return (0);
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

static t_token	*read_token(char *line, int *i, t_err_no *err)
{
	t_token	*tok;

	*err = MALLOC_ERROR;
	if (is_operator(line[*i]))
		tok = read_operator(line, i);
	else
		tok = read_word(line, i, err);
	if (tok)
		*err = OK;
	return (tok);
}

t_list	*lexer(char *line, t_err_no *err)
{
	t_list	*tokens;
	t_token	*tok;
	int		i;

	*err = OK;
	if (!line)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else
		{
			tok = read_token(line, &i, err);
			if (!tok)
				return (free_tokens(tokens), NULL);
			if (!add_token(&tokens, tok))
				return (*err = MALLOC_ERROR, NULL);
		}
	}
	return (tokens);
}
