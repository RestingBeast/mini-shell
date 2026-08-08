#include "unit_test.h"

const char	*node_type_name(t_node_type type)
{
	switch (type)
	{
		case COMMAND: return ("COMMAND");
		case REDIR: return ("REDIR");
		case CTRL: return ("CTRL");
		case TARGET: return ("TARGET");
	}
	return (NULL);
}

// Morris Inorder Traversal
t_node	*next_node(t_node *node, t_node **next)
{
	t_node	*pred;

	if (!node)
		return (NULL);
	if (node->left == NULL)
	{
		*next = node;
		return (node->right);
	}
	else
	{
		pred = node->left;
		while (pred->right != NULL && pred->right != node)
			pred = pred->right;
		if (pred->right == NULL)
		{
			pred->right = node;
			*next = NULL;
			return (node->left);
		}
		else
		{
			pred->right = NULL;
			*next = node;
			return (node->right);
		}
	}
}

int	compare_node(t_node *node1, t_node *node2)
{
	if ((node1 && !node2) || (!node1 && node2))
		return (0);
	if (node1 != NULL && node2 != NULL)
		printf("%d = %d\n", node1->data, node2->data);
	return (1);
}

int	compare_trees(t_node *node1, t_node *node2)
{
	t_node	*curr1 = NULL;
	t_node	*curr2 = NULL;

	while (node1 && node2)
	{
		node1 = next_node(node1, &curr1);
		node2 = next_node(node2, &curr2);
		if (!compare_node(curr1, curr2))
			return (0);
	}
	return (1);
}

int	main(void)
{
	/*
	t_node node1 = NODE(1, COMMAND, NULL, NULL);
	t_node node2 = NODE(3, COMMAND, NULL, NULL);
	t_node root1 = NODE(2, COMMAND, &node1, &node2);

	t_node node3 = NODE(1, COMMAND, NULL, NULL);
	t_node node4 = NODE(3, COMMAND, NULL, NULL);
	t_node root2 = NODE(2, COMMAND, &node3, &node4);
	*/

	/* Tree 1 */
t_node node11 = NODE(99, COMMAND, NULL, NULL);
t_node node10 = NODE(1, COMMAND, NULL, &node11);

t_node node7  = NODE(7, COMMAND, NULL, NULL);
t_node node9  = NODE(4, COMMAND, NULL, NULL);
node9.right = &node10;
node9.left = &node7;

t_node node6  = NODE(2, COMMAND, NULL, NULL);
t_node node8  = NODE(5, COMMAND, NULL, NULL);
node7.right = &node8;

t_node node4  = NODE(8, COMMAND, NULL, &node6);

t_node node1  = NODE(11, COMMAND, NULL, NULL);
t_node node2  = NODE(0, COMMAND, NULL, NULL);
node1.right = &node2;

t_node node3  = NODE(7, COMMAND, &node1, &node4);
t_node root   = NODE(4, COMMAND, &node3, &node9);


/* Tree 2 */

t_node node11_b = NODE(95, COMMAND, NULL, NULL);
t_node node10_b = NODE(3, COMMAND, NULL, &node11_b);

t_node node7_b  = NODE(6, COMMAND, NULL, NULL);
t_node node9_b  = NODE(5, COMMAND, NULL, NULL);
node9_b.right = &node10_b;
node9_b.left = &node7_b;

t_node node6_b  = NODE(2, COMMAND, NULL, NULL);
t_node node8_b  = NODE(9, COMMAND, NULL, NULL);
node7_b.right = &node8_b;

t_node node4_b  = NODE(8, COMMAND, NULL, &node6_b);

t_node node1_b  = NODE(12, COMMAND, NULL, NULL);
//t_node node2_b  = NODE(0, COMMAND, NULL, NULL);
//node1_b.right = &node2_b;

t_node node3_b  = NODE(7, COMMAND, &node1_b, &node4_b);
t_node root_b   = NODE(4, COMMAND, &node3_b, &node9_b);
	compare_trees(&root, &root_b);
	return (0);
}
