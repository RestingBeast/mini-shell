/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints a value between double quotes. Like bash, the characters
** " \ $ and ` get a backslash first, so the line can be pasted back.
*/
static void	print_quoted(char *value)
{
	int	i;

	ft_putchar_fd('"', STDOUT_FILENO);
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '"' || value[i] == '\\'
			|| value[i] == '$' || value[i] == '`')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(value[i], STDOUT_FILENO);
		i++;
	}
	ft_putchar_fd('"', STDOUT_FILENO);
}

/*
** Prints one entry the way bash does:
**   "KEY=value" -> declare -x KEY="value"
**   "KEY"       -> declare -x KEY
*/
static void	print_entry(char *entry)
{
	int	i;

	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	i = 0;
	while (entry[i] != '\0' && entry[i] != '=')
	{
		ft_putchar_fd(entry[i], STDOUT_FILENO);
		i++;
	}
	if (entry[i] == '=')
	{
		ft_putchar_fd('=', STDOUT_FILENO);
		print_quoted(entry + i + 1);
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

/*
** True for the variable _ ("_=value" or "_"). bash hides it in export.
*/
static int	is_underscore(char *entry)
{
	return (entry[0] == '_' && (entry[1] == '=' || entry[1] == '\0'));
}

/*
** "export" with no arguments: prints every variable sorted by name,
** including the ones without a value. Returns the exit status.
*/
int	print_exported(t_list *env)
{
	char	**array;
	int		i;

	array = sort_env(env);
	if (array == NULL)
	{
		print_error("export", NULL, "out of memory");
		return (1);
	}
	i = 0;
	while (array[i] != NULL)
	{
		if (!is_underscore(array[i]))
			print_entry(array[i]);
		i++;
	}
	free(array);
	return (0);
}
