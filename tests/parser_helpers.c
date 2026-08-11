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
	int		i;
	char	*s1;
	char	*s2;
	char	**arr1;
	char	**arr2;

	if (node1->type == PIPE)
		return (1);
	else if (node1->type == COMMAND)
	{
		arr1 = (char **)node1->data;
		arr2 = (char **)node2->data;
		i = 0;
		while (arr1[i] || arr2[i])
		{
			if ((arr1[i] && !arr2[i]) || (!arr1[i] && arr2[i]))
				return (0);
			if (ft_strncmp(arr1[i], arr2[i], ft_strlen(arr1[i])) != 0)
				return (0);
			i++;
		}
	}
	else
	{
		s1 = (char *)node1->data;
		s2 = (char *)node2->data;
		if (ft_strncmp(s1, s2, ft_strlen(s1)) != 0)
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
	t_node node1 = NODE(1, COMMAND, NULL, NULL);
	t_node node2 = NODE(2, COMMAND, NULL, NULL);
	t_node root = NODE(3, COMMAND, &node1, &node2);

	t_node node4 = NODE(1, COMMAND, NULL, NULL);
	t_node node5 = NODE(2, COMMAND, NULL, NULL);
	t_node root_b = NODE(3, COMMAND, &node4, &node5);

	compare_trees(&root, &root_b);
	return (0);
}
