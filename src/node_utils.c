/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 20:17:32 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/09/25 22:18:00 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cmdclear(t_cmd *cmd)
{
	i = 0;
	while (cmd->args[i] != NULL)
	{
		free(cmd->args[i]);
		i++;
	}
	free(cmd->args);
	ft_lstclear(cmd, free);
}

void	ft_nodeclear(t_node *root)
{
	t_cmd	*cmd;
	int	i;

	if (root == NULL)
		return ;
	ft_nodeclear(root->left);
	ft_nodeclear(root->right);
	if (root->type == COMMAND)
		ft_cmdclear((t_cmd *)root->data);
	free(root->data);
	free(root);
}
