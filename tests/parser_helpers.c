#include "test.h"

// Morris Inorder Traversal
static t_node	*morris_step(t_node *node, t_node **curr)
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

static int	compare_data(t_node *node1, t_node *node2, int *index)
{
	int		i;
	int		len;
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
			len = ft_strlen(arr1[i]) > ft_strlen(arr2[i]) ? ft_strlen(arr1[i]) : ft_strlen(arr2[i]);
			if (ft_strncmp(arr1[i], arr2[i], len) != 0)
			{
				printf(
					"Node #%d\n"
					"Expected data: %s\n"
					"Actual data:   %s\n",
					*index,
					arr1[i],
					arr2[i]
				);
				return (0);

			}
			i++;
		}
	}
	else
	{
		s1 = (char *)node1->data;
		s2 = (char *)node2->data;
		len = ft_strlen(s1) > ft_strlen(s2) ? ft_strlen(s1) : ft_strlen(s2);
		if (ft_strncmp(s1, s2, len) != 0)
		{
			printf(
				"Node #%d\n"
				"Expected data: %s\n"
				"Actual data:   %s\n",
				*index,
				s1,
				s2
			);
			return (0);
		}
	}
	return (1);
}

static int	compare_node(t_node *node1, t_node *node2, int *index)
{
	if ((node1 && !node2) || (!node1 && node2))
		return (0);
	if (node1 != NULL && node2 != NULL)
	{
		(*index)++;
		if (node1->type != node2->type)
		{
			printf(
				"Node #%d\n"
				"Expected type: %s\n"
				"Actual type:   %s\n",
				*index,
				type_name(node1->type),
				type_name(node2->type)
			);
			return (0);
		} else {
			if (!compare_data(node1, node2, index))
				return (0);
		}
	}
	return (1);
}

int compare_trees(t_node *node1, t_node *node2)
{
	t_node	*curr1 = NULL;
	t_node	*curr2 = NULL;
	int		index;
	int		res;

	res = 1;
	index = 0;
	while (node1 || node2)
	{
		node1 = morris_step(node1, &curr1);
		node2 = morris_step(node2, &curr2);
		if (compare_node(curr1, curr2, &index) == 0)
			res = 0;
	}
	return (res);
}
