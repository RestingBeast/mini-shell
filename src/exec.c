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
** Only reached in the child when execve() failed.
** Like bash: 127 if the file is gone, 126 for any other reason.
*/
static void	child_fail(char *full_cmd, char **env_arr, t_data *data,
		t_list *env)
{
	int	err_no;

	err_no = errno;
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	print_cmd_err_msg(CMD_ERROR, err_no, full_cmd);
	free(full_cmd);
	ft_argclear(env_arr);
	clean_up(data);
	ft_lstclear(&env, free);
	rl_clear_history();
	if (err_no == ENOENT)
		exit(127);
	exit(126);
}

/*
** The shell ignores Ctrl-C while it waits, so only the child is killed.
*/
static void	wait_child(pid_t pid, t_data *data)
{
	int	wstatus;

	set_wait_sig();
	waitpid(pid, &wstatus, 0);
	set_sigaction();
	if (WIFEXITED(wstatus))
		data->status = WEXITSTATUS(wstatus);
	else if (WIFSIGNALED(wstatus))
	{
		data->status = 128 + WTERMSIG(wstatus);
		if (WTERMSIG(wstatus) == SIGINT)
			ft_putstr_fd("\n", STDOUT_FILENO);
		else if (WTERMSIG(wstatus) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

static void	exe_other_cmd(t_cmd *cmd, t_data *data, t_list *env)
{
	pid_t	pid;
	char	*full_cmd;
	char	**env_arr;

	full_cmd = find_command(cmd->args[0], data, env);
	if (!full_cmd)
		return ;
	env_arr = env_to_array(env);
	if (!env_arr)
		return (free(full_cmd), set_malloc_err(&(data->err)));
	pid = fork();
	if (pid == 0)
	{
		set_child_sig();
		execve(full_cmd, cmd->args, env_arr);
		child_fail(full_cmd, env_arr, data, env);
	}
	if (pid == -1)
		set_syscall_err(&(data->err));
	else
		wait_child(pid, data);
	free(full_cmd);
	ft_argclear(env_arr);
}

static void	exe_cmd(t_node *root, t_data *data, t_list *env)
{
	t_cmd	*cmd;

	if (root->type != COMMAND)
		return ;
	cmd = (t_cmd *)root->data;
	if (!cmd->args || !cmd->args[0])
	{
		data->status = 0;
		return ;
	}
	if (is_builtin(cmd->args[0]))
		printf("Built In\n");
	else
		exe_other_cmd(cmd, data, env);
}

void	execute_tree(t_node *root, t_data *data, t_list *env)
{
	if (root == NULL)
		return ;
	execute_tree(root->left, data, env);
	exe_cmd(root, data, env);
	execute_tree(root->right, data, env);
}
