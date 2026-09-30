#include "minishell.h"

t_token	*new_token(t_type type)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->lexeme = NULL;
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
	return (new_token(type));
}

static int	add_token(t_list **tokens, t_token *tok)
{
	t_list	*node;

	node = NULL;
	if (tok)
		node = ft_lstnew(tok);
	if (!node)
	{
		if (tok)
			free_token(tok);
		free_tokens(*tokens);
		*tokens = NULL;
		return (0);
	}
	ft_lstadd_back(tokens, node);
	return (1);
}

t_list	*lexer(char *line)
{
	t_list	*tokens;
	t_token	*tok;
	int		i;

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
			if (is_operator(line[i]))
				tok = read_operator(line, &i);
			else
				tok = read_word(line, &i);
			if (!add_token(&tokens, tok))
				return (NULL);
		}
	}
	return (tokens);
}
