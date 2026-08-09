#include "unit_test.h"

// Morris Inorder Traversal
t_node	*morris_step(t_node *node, t_node **curr)
{
	t_node	*pred;

	if (!node)
		return (NULL);
	if (node->left == NULL)
	{
		*curr = node;
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
			*curr = NULL;
			return (node->left);
		}
		else
		{
			pred->right = NULL;
			*curr = node;
			return (node->right);
		}
	}
}

int	compare_data(t_node *node1, t_node *node2)
{
	if (node1->type == COMMAND)
	{
		return (0);
	}
	else
	{
		return (0);
	}
	return (1);
}

int	compare_node(t_node *node1, t_node *node2)
{
	if ((node1 && !node2) || (!node1 && node2))
		return (0);
	if (node1 != NULL && node2 != NULL)
	{
		if (node1->type != node2->type)
		{
			printf(
				"Expected type: %s\n"
				"Actual type:   %s\n",
				type_name(exp[i]->type),
				type_name(out[i]->type)
			);
			return (0);
		} else {
			if (!compare_data(node1, node2))
				return (0);
		}
	}
	return (1);
}

int	compare_trees(t_node *node1, t_node *node2)
{
	t_node	*curr1 = NULL;
	t_node	*curr2 = NULL;

	while (node1 || node2)
	{
		node1 = morris_step(node1, &curr1);
		node2 = morris_step(node2, &curr2);
		if (!compare_node(curr1, curr2))
			return (0);
	}
	return (1);
}

int	main(void)
{
	compare_trees(&root, &root_b);
	return (0);
}
