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

/*
if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	filename = ft_strjoin("/", cmd);
	path = get_env_path(envp);
	while (path[i] != NULL)
	{
		res = ft_strjoin(path[i], filename);
		if (access(res, F_OK | X_OK) == 0)
			return (free(filename), free_double_ptr(path), res);
		free(res);
		i++;
	}
*/

static int	access_file(char *file, t_err *err)
{
	if (!res)
		return (set_malloc_err(err), 0);
	if (access(file, F_OK | X_OK) == 0)
		return (err->err_no = OK, 1);
	else
	{
		if (errno =
	}
	return (0);
}

static char	*find_path(t_list *env, char *cmd, t_err *err)
{
	char	*file;
	char	**path_env;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	file = ft_strjoin("/", cmd);
	if (!file)
		return (set_malloc_err(err), NULL);
	path_env = ft_split(env_get(env, "PATH"), ':');
	if (!path_env)
		return (set_malloc_err(err), free(file), NULL);
	i = -1;
	while (path_env[++i] != NULL)
	{
		res = ft_strjoin(path_env[i], file);
		if (access_file(res, err) == 1)
			return (free(file), ft_argclear(path_env), res);
	}
	return (free(file), ft_argclear(path_env), free(res), NULL);
}

static void	exe_other_cmd(t_cmd *cmd, t_data *data, t_list *env)
{
	pid_t	pid;

	find_path(env, cmd->args[0], &(data->err));
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
