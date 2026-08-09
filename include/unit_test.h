#include "minishell.h"
// #include <criterion/criterion.h>
#include <string.h>

#define SEG(txt, qte) ((t_segment){ .text = txt, .quote = qte })
#define TOK(lex, t) ((t_token){ .lexeme = lex, .type = t})

const char	*quote_name(t_quote q);
const char	*type_name(t_type t);
int			compare_segment(t_segment **out, t_segment **exp);
int			compare_token(t_token **out, t_token **exp);

#define NODE(d, t, l, r) ((t_node){ .data = d, .type = t, .left = l, .right = r})
