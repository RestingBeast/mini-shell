#ifndef LEXER_H
# define LEXER_H
# include "type.h"
# include "libft.h"

typedef struct s_token t_token;
typedef enum e_lex_err t_lex_err;

enum e_lex_err
{
	LEX_OK,
	LEX_UNCLOSED_QUOTE,
	LEX_ALLOC,
};

struct s_token
{
t_type	type;
char		*lexeme;
};

// lexer.c
t_list	*lexer(char *line, t_lex_err *err);
t_token	*new_token(t_type type, char *lexeme);

// lexer_word.c
t_token	*read_word(char *line, int *i, t_lex_err *err);

// lexer_utils.c
int		is_space(char c);
int		is_operator(char c);
void	free_token(void *content);
void	free_tokens(t_list *tokens);

#endif
