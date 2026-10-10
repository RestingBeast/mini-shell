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

t_cmd	*ft_cmdnew(char	**args, t_list	*redir)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = args;
	cmd->redir = redir;
	return (cmd);
}

t_redir	*ft_redirnew_fd(t_type type, int fd)
{
	t_redir	*rdr;

	rdr = malloc(sizeof(t_redir));
	if (!rdr)
		return (NULL);
	rdr->type = type;
	rdr->target.fd = fd;
	return (rdr);
}

t_redir	*ft_redirnew_file(t_type type, char *file)
{
	t_redir	*rdr;

	rdr = malloc(sizeof(t_redir));
	if (!rdr)
		return (NULL);
	rdr->type = type;
	rdr->target.file = file;
	return (rdr);
}

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
