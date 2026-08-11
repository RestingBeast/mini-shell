#include "test.h"

/*
Test(Parser, basic_test)
{
	char	*cmd1[] = {"cat", "file", NULL};
	char	*cmd2[] = {"grep", "hello", NULL};
	t_node node1 = NODE((void *) cmd1, COMMAND, NULL, NULL);
	t_node node2 = NODE((void *) cmd2, COMMAND, NULL, NULL);
	t_node expected = NODE((void *) 0, PIPE, &node1, &node2);

	//t_node *root = parser();
	cr_assert(compare_trees(&expected, root));
	//free_tree(root);
}
*/
