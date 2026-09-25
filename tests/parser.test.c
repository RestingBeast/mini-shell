#include "test.h"
#include <criterion/criterion.h>

Test(Parser, WORD_test)
{
	char		*arg1[] = {"echo", "helloworld", NULL};
	t_cmd		cmd1 = CMD(arg1, NULL);
	t_node		expected = NODE((void *) &cmd1, COMMAND, NULL, NULL);


	t_segment	seg1 = SEG("echo", NONE);
	t_list		lexeme1 = LST((void *) &seg1, NULL);

	t_segment	seg2 = SEG("hell", NONE);
	t_segment	seg3 = SEG("owo", SINGLE);
	t_segment	seg4 = SEG("rld", DOUBLE);
	t_list		lexeme2_3 = LST((void *) &seg4, NULL);
	t_list		lexeme2_2 = LST((void *) &seg3, &lexeme2_3);
	t_list		lexeme2_1 = LST((void *) &seg2, &lexeme2_2);

	t_token		tok1 = TOK(&lexeme1, WORD);
	t_token		tok2 = TOK(&lexeme2_1, WORD);

	t_list		lst = LST((void *) &tok2, NULL);
	t_list		tokens = LST((void *) &tok1, &lst);

	t_node		*root = parse_tokens(&tokens);
	cr_assert(compare_trees(&expected, root));
	ft_nodeclear(root);
}

Test(Parser, REDIR_test)
{
	char	*arg1[] = {"cat", NULL};
	t_redir	redir1 = REDIR(REDIR_IN, (t_tgt){.file = "in.txt"});
	t_list	redir_lst1 = LST((void *) &redir1, NULL);
	t_cmd	cmd1 = CMD(arg1, &redir_lst1);
	t_node	expected = NODE((void *) &cmd1, COMMAND, NULL, NULL);

	char	*arg2[] = {"cat", NULL};
	t_redir	redir2 = REDIR(REDIR_IN, (t_tgt){.file = "in.txt"});
	t_list	redir_lst2 = LST((void *) 0, NULL);
	t_cmd	cmd2 = CMD(arg2, &redir_lst2);
	t_node	actual = NODE((void *) &cmd2, COMMAND, NULL, NULL);

	cr_assert(compare_trees(&expected, &actual));
}

/*
Test(Parser, PIPE_test)
{
	char	*cmd1[] = {"echo", "helloworld", NULL};
	t_node	left = NODE((void *) cmd1, COMMAND, NULL, NULL);

	char	*cmd2[] = {"grep", "hello", NULL};
	t_node	right = NODE((void *) cmd2, COMMAND, NULL, NULL);

	t_node	expected = NODE(NULL, PIPE, &left, &right);

	t_segment	seg1 = SEG("echo", NONE);
	t_list	lexeme1 = LST((void *) &seg1, NULL);

	t_segment	seg2 = SEG("hell", NONE);
	t_segment	seg3 = SEG("owo", SINGLE);
	t_segment	seg4 = SEG("rld", DOUBLE);
	t_list	lexeme2_3 = LST((void *) &seg4, NULL);
	t_list	lexeme2_2 = LST((void *) &seg3, &lexeme2_3);
	t_list	lexeme2_1 = LST((void *) &seg2, &lexeme2_2);

	t_segment	seg5 = SEG("grep", NONE);
	t_list	lexeme3 = LST((void *) &seg5, NULL);

	t_segment	seg6 = SEG("hello", NONE);
	t_list	lexeme4 = LST((void *) &seg6, NULL);

	t_token	tok1 = TOK(&lexeme1, WORD);
	t_token	tok2 = TOK(&lexeme2_1, WORD);
	t_token tok3 = TOK(NULL, PIPE);
	t_token tok4 = TOK(&lexeme3, WORD);
	t_token tok5 = TOK(&lexeme4, WORD);

	t_list	lst4 = LST((void *) &tok5, NULL);
	t_list	lst3 = LST((void *) &tok4, &lst4);
	t_list	lst2 = LST((void *) &tok3, &lst3);
	t_list	lst1 = LST((void *) &tok2, &lst2);
	t_list	lst = LST((void *) &tok1, &lst1);

	t_node *root = parse_tokens(&lst);
	cr_assert(compare_trees(&expected, root));
	ft_nodeclear(root);
}
*/
