#include "minishell.h"
#include <criterion/criterion.h>
#include <string.h>
#define SEG(txt, qte) ((t_segment){ .text = txt, .quote = qte })
#define TOK(lex, t) ((t_token){ .lexeme = lex, .type = t})

const char	*quote_name(enum Quote q);
const char	*type_name(enum Type t);
int	compare_segment(t_segment **out, t_segment **exp);
int	compare_token(t_token **out, t_token **exp);
