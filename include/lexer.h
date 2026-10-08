#ifndef LEXER_H
# define LEXER_H
# include "type.h"
# include "libft.h"

typedef struct s_segment t_segment;
typedef struct s_token t_token;
typedef enum e_quote t_quote;

enum e_quote
{
	NONE,
	SINGLE,
	DOUBLE,
};

struct s_segment
{
	char	*text;
	t_quote	quote;
};

struct s_token
{
	t_list	*lexeme;
	t_type	type;
typedef struct s_token t_token;

struct s_token
{
t_type	type;
char		*lexeme;
};

// lexer.c
t_list	*lexer(char *line);
t_token	*new_token(t_type type, char *lexeme);

// lexer_word.c
t_token	*read_word(char *line, int *i);

// lexer_utils.c
int		is_space(char c);
int		is_operator(char c);
void	free_token(void *content);
void	free_tokens(t_list *tokens);

#endif
