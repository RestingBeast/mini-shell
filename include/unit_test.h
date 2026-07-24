#include "minishell.h"
#include <criterion/criterion.h>
#include <string.h>

#define SEG(txt, qte) ((t_segment){ .text = txt, .quote = qte })
#define TOK(lex, t) ((t_token){ .lexeme = lex, .type = t})

const char	*quote_name(enum Quote q);
const char	*type_name(enum Type t);
int			compare_segment(t_segment **out, t_segment **exp);
int			compare_token(t_token **out, t_token **exp);

#define NODE(con, t, l, r) ((t_node){ .content = con, .type = t, .left = l, .right = r})
const char	*node_type_name(t_node_type type);
