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

char	*find_command(char *cmd, t_data *data, t_list *env)
{
	char	*res;
	struct stat	statbuf;

	res = find_path(cmd, data, env);
	if (!res)
		return (NULL);
	if (stat(res, &statbuf) == -1)
		return (set_cmd_not_found_err(&(data->err), cmd), NULL);
	if (S_ISDIR(statbuf.st_mode))
		return (set_dir_err(&(data->err), cmd), NULL);
	return (res);
}
