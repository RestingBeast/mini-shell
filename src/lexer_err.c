#include "minishell.h"

int	syntax_check(t_list **tokens, t_token *tok, t_err *err)
{
	t_token	*last;

	if (*tokens == NULL && tok->type == PIPE)
		return (set_unexp_tok_err(err, PIPE), 0);	
	if (*tokens == NULL) 
		return (1);
	last = (t_token *)(ft_lstlast(*tokens))->content;
	if (tok->type != WORD && last->type != WORD)
		return (set_unexp_tok_err(err, last->type), 0);
	return (1);
}

void	last_token_check(t_list *tokens, t_err *err)
{
	t_token	*last;

	last = (t_token *)(ft_lstlast(tokens))->content;
	if (last->type == WORD)
		return ;
	if (last->type == PIPE)
		set_end_pipe_err(err);
	set_end_redir_err(err);
}
