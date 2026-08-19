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

void	ft_nodeclear(t_node *root)
{
	char	**arr;

	if (root == NULL)
		return ;
	ft_nodeclear(root->left);
	ft_nodeclear(root->right);
	if (root->type == COMMAND)
	{
		arr = (char **)root->data;
		while (*arr)
		{
			free(*arr);
			arr++;
		}
	}
	free(root->data);
	free(root);
}
