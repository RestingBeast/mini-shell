#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	free_segment(void *content)
{
	t_segment	*seg;

	seg = (t_segment *)content;
	free(seg->text);
	free(seg);
}

void	free_token(void *content)
{
	t_token	*tok;

	tok = (t_token *)content;
	ft_lstclear(&tok->lexeme, free_segment);
	free(tok);
}

void	free_tokens(t_list *tokens)
{
	ft_lstclear(&tokens, free_token);
}
