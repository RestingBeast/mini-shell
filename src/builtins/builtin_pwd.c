/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <string.h>

/*
** The pwd builtin: prints the directory we are in.
** Arguments are ignored, like bash does.
** getcwd() fails when our directory was deleted. bash then still
** prints the path it remembers, so we print $PWD instead.
*/
int	builtin_pwd(t_list *env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		free(cwd);
		return (0);
	}
	if (env_get(env, "PWD") != NULL)
	{
		ft_putendl_fd(env_get(env, "PWD"), STDOUT_FILENO);
		return (0);
	}
	print_error("pwd", "error retrieving current directory: getcwd",
		strerror(errno));
	return (1);
}
