#include "minishell.h"
#include <string.h>

#define LST(con, nex) ((t_list){.content = con, .next = nex})
#define SEG(txt, qte) ((t_segment){ .text = txt, .quote = qte })
#define TOK(lex, t) ((t_token){ .lexeme = lex, .type = t})
#define NODE(d, t, l, r) ((t_node){ .data = d, .type = t, .left = l, .right = r})

const char	*type_name(t_type t);
int			compare_tokens(t_list *out, t_list *exp);
int compare_trees(t_node *node1, t_node *node2);
t_node	*morris_next(t_node *node, t_node **curr);
