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

static int	access_file(char *file, t_err *err, char *cmd)
{
	int	perm_denied;

	perm_denied = 0;
	if (!file)
		return (set_malloc_err(err), 0);
	if (access(file, F_OK | X_OK) == 0)
		return (err->type = OK, 1);
	else
	{
		set_cmd_err(err, cmd);
		if (errno == EACCES)
			perm_denied = 1;
		if (!perm_denied && errno == ENOENT)
			return (set_cmd_not_found_err(err, cmd), 0);
	}
	return (0);
}

static char	*find_path(char *cmd, t_data *data, t_list *env)
{
	char	*res;
	char	*file;
	char	**path_env;
	int		i;

	if (ft_strchr(cmd, '/') != NULL)
		return (cmd);
	file = ft_strjoin("/", cmd);
	if (!file)
		return (set_malloc_err(&(data->err)), NULL);
	path_env = ft_split(env_get(env, "PATH"), ':');
	if (!path_env)
		return (set_malloc_err(&(data->err)), free(file), NULL);
	i = -1;
	while (path_env[++i] != NULL)
	{
		res = ft_strjoin(path_env[i], file);
		if (access_file(res, &(data->err), cmd) == 1)
			return (free(file), ft_argclear(path_env), res);
		free(res);
	}
	return (free(file), ft_argclear(path_env), NULL);
}

static void	exe_other_cmd(t_cmd *cmd, t_data *data, t_list *env)
{
	pid_t		pid;
	char		*full_path;
	struct stat	statbuf;

	full_path = find_path(cmd->args[0], data, env);
	if (!full_path)
		return ;
	if (stat(full_path, &statbuf) == -1)
	{
		set_cmd_not_found_err(&(data->err), cmd->args[0]);
		return ;
	}
	if (S_ISDIR(statbuf.st_mode))
	{
		set_dir_err(&(data->err), cmd->args[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
		set_syscall_err(&(data->err));
	if (pid == 0)
	{
		if (execve(full_path, cmd->args, env_to_array(env)) == -1)
			return ; // Should handle error
	}
	else
	{
		waitpid(pid, &(data->status), 0);
	}
	free(full_path);
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
