#ifndef LEXER_H
# define LEXER_H
# include "type.h"

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
	t_segment	**lexeme;
	t_type		type;
};

t_token	**lexer(char *line);

#endif
