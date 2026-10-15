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

static int	try_execve(char *full_cmd, char **args, char **env_arr)
{
	if (execve(full_cmd, args, env_arr) == -1)
	{
		print_cmd_err_msg(CMD_ERROR, errno, "");
		ft_argclear(env_arr);
		free(full_cmd);
		return (-1);
	}
	return (0);
}

static void	exe_other_cmd(t_cmd *cmd, t_data *data, t_list *env)
{
	pid_t		pid;
	char		*full_cmd;
	char	**env_arr;

	data->err.type = OK;
	full_cmd = find_command(cmd->args[0], data, env);
	if (!full_cmd)
		return ;
	env_arr = env_to_array(env);
	if (!env_arr)
		return (set_malloc_err(&(data->err)));
	pid = fork();
	if (pid == -1)
		set_syscall_err(&(data->err));
	if (pid == 0)
	{
		if (try_execve(full_cmd, cmd->args, env_arr) != 0)
		{
			clean_up(data);
			ft_lstclear(&env, free);
			exit(126);
		}
	}
	else
		waitpid(pid, &(data->status), 0);
	free(full_cmd);
	ft_argclear(env_arr);
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
