#include "test.h"

Test(Parser, basic_test)
{
	char	*cmd[] = {"hello", "1", NULL};
	t_node node1 = NODE((void *) cmd, COMMAND, NULL, NULL);
	t_node node2 = NODE((void *) "hello", APPEND, NULL, NULL);
	t_node expected = NODE((void *) "hello", APPEND, &node1, &node2);

	char	*cmd2[] = {"hello", "2", NULL};
	t_node node4 = NODE((void *) cmd2, COMMAND, NULL, NULL);
	t_node node5 = NODE((void *) "hell2", APPEND, NULL, NULL);
	t_node root = NODE((void *) "hello", APPEND, &node4, &node5);

	cr_assert(compare_trees(&expected, &root));
}
