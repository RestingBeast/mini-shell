#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
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
