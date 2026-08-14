#include "test.h"
#include <criterion/criterion.h>

Test(Parser, basic_test)
{
	char	*cmd1[] = {"echo", "helloworld", NULL};
	t_node	expected = NODE((void *) cmd1, COMMAND, NULL, NULL);

	t_segment	seg1 = SEG("echo", NONE);
	t_list	lexeme1 = LST((void *) &seg1, NULL);

	t_segment	seg2 = SEG("hell", NONE);
	t_segment	seg3 = SEG("o wo", SINGLE);
	t_segment	seg4 = SEG("rld", DOUBLE);
	t_list	lexeme2_3 = LST((void *) &seg4, NULL);
	t_list	lexeme2_2 = LST((void *) &seg3, &lexeme2_3);
	t_list	lexeme2_1 = LST((void *) &seg2, &lexeme2_2);

	t_token	tok1 = TOK(&lexeme1, WORD);
	t_token	tok2 = TOK(&lexeme2_1, WORD);

	t_list	lst = LST((void *) &tok2, NULL);
	t_list	tokens = LST((void *) &tok1, &lst);

	t_node *root = parse_tokens(&tokens);
	cr_assert(compare_trees(&expected, root));
	ft_nodeclear(root, free);
}
