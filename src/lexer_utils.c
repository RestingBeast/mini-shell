#include "minishell.h"

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

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

void	free_token(void *content)
{
	t_token	*tok;

	tok = (t_token *)content;
	free(tok->lexeme);
	free(tok);
}

void	free_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, free_token);
}
