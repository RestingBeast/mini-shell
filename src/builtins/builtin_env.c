/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The env builtin: prints every variable that has a value.
** The subject asks for no arguments. The real env would run argv[1]
** as a command; we don't, so we answer like env does when that
** command does not exist.
*/
int	builtin_env(char **argv, t_list **env)
{
	if (argv[1] != NULL)
	{
		print_error("env", argv[1], "No such file or directory");
		return (127);
	}
	if (env_print(env) == -1)
	{
		print_error("env", NULL, "out of memory");
		return (1);
	}
	return (0);
}
