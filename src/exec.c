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

/*
** The shell ignores Ctrl-C while it waits, so only the child is killed.
*/
void	wait_child(pid_t pid, int *status)
{
	int	wstatus;

	set_wait_sig();
	waitpid(pid, &wstatus, 0);
	set_sigaction();
	if (WIFEXITED(wstatus))
		*status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		*status = 128 + WTERMSIG(wstatus);
		if (WTERMSIG(wstatus) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(wstatus) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

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

static void	exec_cmd(t_node *root, t_data *data, t_list **env, int *status)
{
	t_cmd	*cmd;
	t_exec	exec;

	if (root->type != COMMAND)
		return ;
	cmd = (t_cmd *)root->data;
	if (!resolve_redir(cmd->redir, &(data->err), &(exec.in_fd), &(exec.out_fd)))
		return ;
	if (!set_up_exec(&exec, cmd->args, status))
		return ;
	if (is_builtin(exec.args[0]))
		exec_builtin(&exec, data, env, status);
	else
		exec_external(&exec, data, *env, status);
}

void	execute_tree(t_node *root, t_data *data, t_list **env, int *status)
{
	int	fds[2];

	if (root == NULL)
		return ;
	if (root->type == PIPE)
	{
		if (pipe(fds) == -1)
			return (set_syscall_err(&(data->err)));
	}
	execute_tree(root->left, data, env, status);
	exec_cmd(root, data, env, status);
	execute_tree(root->right, data, env, status);
}
