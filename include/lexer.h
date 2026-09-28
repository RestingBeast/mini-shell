#ifndef LEXER_H
# define LEXER_H
# include "type.h"
# include "libft.h"

typedef struct s_token t_token;

struct s_token
{
	t_type	type;
	char	*lexeme;
};

t_list *lexer(char *line);

#endif
