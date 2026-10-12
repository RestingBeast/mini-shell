/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints: minishell: export: `ARG': not a valid identifier
*/
static void	print_invalid_name(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

/*
** Handles one argument of export:
**   "KEY=value" -> sets KEY to value (the value may contain '=')
**   "KEY"       -> adds KEY without a value, or keeps its old value
** Returns 0 if it worked, 1 for a bad name, -1 if malloc failed.
*/
static int	export_one(char *arg, t_list **env)
{
	char	*equal;
	char	*key;
	int		status;

	if (!is_valid_name(arg))
	{
		print_invalid_name(arg);
		return (1);
	}
	equal = ft_strchr(arg, '=');
	if (equal == NULL)
		return (env_set(env, arg, NULL));
	key = ft_substr(arg, 0, equal - arg);
	if (key == NULL)
		return (-1);
	status = env_set(env, key, equal + 1);
	free(key);
	return (status);
}

/*
** The export builtin.
** With no arguments it prints all variables, sorted.
** Otherwise it exports each argument. A bad name does not stop the
** others, but the final status is then 1.
*/
int	builtin_export(char **argv, t_list **env)
{
	int	i;
	int	result;
	int	status;

	if (argv[1] == NULL)
		return (print_exported(*env));
	status = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		result = export_one(argv[i], env);
		if (result == -1)
		{
			print_error("export", NULL, "out of memory");
			return (1);
		}
		if (result == 1)
			status = 1;
		i++;
	}
	return (status);
}
