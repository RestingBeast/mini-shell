/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 17:59:53 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/14 17:59:54 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_up_exec(t_exec *exec, char **args, int *status)
{
	if (!args || !args[0])
	{
		close_fds(exec->in_fd, exec->out_fd);
		*status = 0;
		return (0);
	}
	exec->args = args;
	return (1);
}

static void	exec_cmd(t_node *root, t_data *data, t_exec *exec)
{
	t_cmd	*cmd;

	if (root->type != COMMAND)
		return ;
	cmd = (t_cmd *)root->data;
	if (!resolve_redir(cmd->redir, &(data->err), exec))
		return ;
	if (!set_up_exec(exec, cmd->args, &(data->status)))
		return ;
	if (is_builtin(exec->args[0]))
		exec_builtin(exec, data);
	else
		exec_external(exec, data);
}

void	execute_tree(t_node *root, t_data *data, t_exec *exec, int to_pipe)
{
	int		fds[2];

	if (root == NULL)
		return ;
	if (root->type == PIPE)
	{
		execute_tree(root->left, data, exec, 1);
		execute_tree(root->right, data, exec, to_pipe);
		return ;
	}
	if (to_pipe)
	{
		if (pipe(fds) == -1)
			return (set_syscall_err(&(data->err)));
		exec->close_fd = fds[0];
		exec->out_fd = fds[1];
	}
	exec_cmd(root, data, exec);
	if (to_pipe)
	{
		exec->in_fd = fds[0];
		exec->out_fd = -1;
		exec->close_fd = -1;
	}
}
