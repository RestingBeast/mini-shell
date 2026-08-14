/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 16:19:07 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/13 16:19:08 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*ft_nodenew(void *data, t_type type)
{
	t_node	*root;

	root = malloc(sizeof(t_node));
	if (!root)
		return (NULL);
	root->data = data;
	root->type = type;
	root->left = NULL;
	root->right = NULL;
	return (root);
}

void	ft_nodeclear(t_node *root, void (*del)(void *))
{
	t_node	*curr;
	while (root != NULL)
	{
		root = morris_next(root, &curr);
		del(curr->data);
		free(curr);
	}
}

static t_node	*morris_link_pred(t_node *node, t_node **curr)
{
	t_node	*pred;

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

t_node	*morris_next(t_node *node, t_node **curr)
{
	if (!node)
		return (NULL);
	if (node->left == NULL)
	{
		*curr = node;
		return (node->right);
	}
	else
		return (morris_link_pred(node, curr));
}
