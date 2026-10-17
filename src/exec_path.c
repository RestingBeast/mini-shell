#include "minishell.h"

static int	is_exec_file(char *file)
{
	struct stat	statbuf;

	if (access(file, X_OK) != 0)
		return (0);
	if (stat(file, &statbuf) == -1 || S_ISDIR(statbuf.st_mode))
		return (0);
	return (1);
}

static char	*search_path(char *cmd, char *path, t_err *err)
{
	char	**dirs;
	char	*dir;
	char	*res;
	int		i;

	dirs = ft_split(path, ':');
	if (!dirs)
		return (set_malloc_err(err), NULL);
	i = -1;
	while (dirs[++i] != NULL)
	{
		dir = ft_strjoin(dirs[i], "/");
		if (!dir)
			return (ft_argclear(dirs), set_malloc_err(err), NULL);
		res = ft_strjoin(dir, cmd);
		free(dir);
		if (!res)
			return (ft_argclear(dirs), set_malloc_err(err), NULL);
		if (is_exec_file(res))
			return (ft_argclear(dirs), res);
		free(res);
	}
	ft_argclear(dirs);
	return (set_cmd_not_found_err(err, cmd), NULL);
}

/*
** A command with a '/' is used as it is, no PATH search.
** Returns a copy, so the caller can always free the result.
*/
static char	*check_slash_cmd(char *cmd, t_err *err)
{
	struct stat	statbuf;
	char		*res;

	if (stat(cmd, &statbuf) == -1)
	{
		if (errno == ENOENT)
			return (set_cmd_not_found_err(err, cmd), NULL);
		return (set_cmd_err(err, cmd), NULL);
	}
	if (S_ISDIR(statbuf.st_mode))
		return (set_dir_err(err, cmd), NULL);
	res = ft_strdup(cmd);
	if (!res)
		return (set_malloc_err(err), NULL);
	return (res);
}

char	*find_command(char *cmd, t_data *data)
{
	char	*path;

	if (cmd[0] == '\0')
		return (set_cmd_not_found_err(&(data->err), cmd), NULL);
	if (ft_strchr(cmd, '/') != NULL)
		return (check_slash_cmd(cmd, &(data->err)));
	path = env_get(data->env, "PATH");
	if (!path)
		return (set_cmd_not_found_err(&(data->err), cmd), NULL);
	return (search_path(cmd, path, &(data->err)));
}
