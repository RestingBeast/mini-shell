/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 17:59:53 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/14 17:59:54 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exe_other_cmd(t_cmd *cmd, t_data *data, t_list *env)
{
	pid_t	pid;

	(void) data;
	pid = fork();
	if (pid == -1)
		set_fork_err(&(data->err));
	if (pid == 0)
	{
		if (execve("/usr/bin/cat", cmd->args, env_to_array(env)) == -1)
			return ; // Should handle error
	}
	else
	{
		waitpid(pid, &(data->status), 0);
	}
}

static int	exe_cmd(t_node *root, t_data *data, t_list *env)
{
	t_cmd	*cmd;

	(void) data;
	(void) env;
	cmd = (t_cmd *)root->data;
	if (is_builtin(cmd->args[0]))
		printf("Built In\n");
	else
		exe_other_cmd(cmd, data, env);
	return (0);
}

void	execute_tree(t_node *root, t_data *data, t_list *env)
{
	if (root == NULL)
		return ;
	execute_tree(root->left, data, env);
	exe_cmd(root, data, env);
	execute_tree(root->right, data, env);
}
