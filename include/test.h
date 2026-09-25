#include "minishell.h"
#include <string.h>

#define LST(con, nex) ((t_list){.content = con, .next = nex})
#define TOK(t, str) ((t_token){.type = t, .lexeme = str})
#define NODE(d, t, l, r) ((t_node){.data = d, .type = t, .left = l, .right = r})
#define REDIR(t, tgt) ((t_redir){.type = t, .target = tgt})
#define CMD(a, r) ((t_cmd){.args = a, .redir = r})

const char	*type_name(t_type t);
int			compare_tokens(t_list *out, t_list *exp);
int compare_trees(t_node *node1, t_node *node2);
t_node	*morris_next(t_node *node, t_node **curr);
