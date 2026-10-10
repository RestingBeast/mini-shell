#ifndef LEXER_H
# define LEXER_H
# include "type.h"
# include "libft.h"
# include "error.h"

typedef struct s_token t_token;

struct s_token
{
	t_type	type;
	char	*lexeme;
};

// lexer.c
t_list	*lexer(char *line, t_err_no *err);
t_token	*new_token(t_type type, char *lexeme);

// lexer_word.c
t_token	*read_word(char *line, int *i, t_err_no *err);

// lexer_utils.c
int		is_space(char c);
int		is_operator(char c);
void	free_token(void *content);
void	free_tokens(t_list *tokens);

#endif
