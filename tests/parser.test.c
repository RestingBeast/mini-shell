#include "unit_test.h"

// Test(Parser, basic_test)
// {
// 	t_node node1 = NODE(1, COMMAND, NULL, NULL);
// 	t_node node2 = NODE(2, COMMAND, NULL, NULL);
// 	t_node node3 = NODE(3, COMMAND, &node1, &node2);

// 	cr_assert(4 + 3 == 7, "Expected 3 + 4 to be equal to 7");
// }

void	postorder_morris(t_node *root)
{
	t_node	*curr = root;
	t_node	*prev;

	while (curr)
	{
		if (curr->left == NULL)
		{
			printf("%d ", curr->data);
			curr = curr->right;
		} else {
			prev = curr->right;
			if (prev->right == NULL)
			{
				prev->right = curr;
				curr = curr->left;
			} else {
				printf("%d ", curr->data);
				prev->right = NULL;
				curr = curr->right;
			}
		}
	}
}

int	main(void)
{
	t_node node1 = NODE(1, COMMAND, NULL, NULL);
	t_node node2 = NODE(2, COMMAND, NULL, NULL);
	t_node node3 = NODE(3, COMMAND, &node1, &node2);

	postorder_morris(&node3);
	return (0);
}
