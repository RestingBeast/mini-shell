/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** True when the two strings are exactly the same.
*/
static int	is_same(char *str1, char *str2)
{
	return (ft_strncmp(str1, str2, ft_strlen(str2) + 1) == 0);
}

/*
** True when NAME is one of our builtins, for example "echo".
*/
int	is_builtin(char *name)
{
	if (name == NULL)
		return (0);
	return (is_same(name, "echo") || is_same(name, "cd")
		|| is_same(name, "pwd") || is_same(name, "export")
		|| is_same(name, "unset") || is_same(name, "env")
		|| is_same(name, "exit"));
}

/*
** Runs the builtin named argv[0] and returns its exit status.
** Check is_builtin(argv[0]) first.
** last_status is $?, the status of the previous command: exit needs it.
** *should_exit is set to 1 only when exit says the shell must stop.
*/
int	run_builtin(char **argv, t_list **env, int last_status, int *should_exit)
{
	*should_exit = 0;
	if (is_same(argv[0], "echo"))
		return (builtin_echo(argv));
	if (is_same(argv[0], "cd"))
		return (builtin_cd(argv, env));
	if (is_same(argv[0], "pwd"))
		return (builtin_pwd(*env));
	if (is_same(argv[0], "export"))
		return (builtin_export(argv, env));
	if (is_same(argv[0], "unset"))
		return (builtin_unset(argv, env));
	if (is_same(argv[0], "env"))
		return (builtin_env(argv, env));
	if (is_same(argv[0], "exit"))
		return (builtin_exit(argv, last_status, should_exit));
	return (1);
}
