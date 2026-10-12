/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 18:48:06 by psoe              #+#    #+#             */
/*   Updated: 2026/10/10 18:48:06 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

/*
** True when PATH is an absolute path to the directory we are in now.
*/
static int	is_current_dir(char *path)
{
	struct stat	path_info;
	struct stat	dot_info;

	if (path == NULL || path[0] != '/')
		return (0);
	if (stat(path, &path_info) == -1 || stat(".", &dot_info) == -1)
		return (0);
	return (path_info.st_dev == dot_info.st_dev
		&& path_info.st_ino == dot_info.st_ino);
}

static int	is_dir(char *path)
{
	struct stat	info;

	if (stat(path, &info) == -1)
		return (0);
	return (S_ISDIR(info.st_mode));
}

/*
** Keeps PWD if it is correct, otherwise sets it to the real directory.
*/
int	update_pwd(t_list **env)
{
	char	*cwd;
	int		status;

	if (is_current_dir(env_get(*env, "PWD")))
		return (0);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("minishell: shell-init: getcwd");
		return (0);
	}
	status = env_set(env, "PWD", cwd);
	free(cwd);
	return (status);
}

/*
** Like bash: a missing OLDPWD is added without a value,
** and an OLDPWD that is not a directory is removed.
*/
int	update_oldpwd(t_list **env)
{
	char	*oldpwd;

	if (env_find(*env, "OLDPWD") == NULL)
		return (env_set(env, "OLDPWD", NULL));
	oldpwd = env_get(*env, "OLDPWD");
	if (oldpwd != NULL && !is_dir(oldpwd))
		env_unset(env, "OLDPWD");
	return (0);
}
