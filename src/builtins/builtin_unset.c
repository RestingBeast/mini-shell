/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The unset builtin: removes every variable named in argv.
** Like bash, names that are not valid ("1A", "A=1") are skipped
** without an error message, so unset always returns 0.
** The '=' check matters: env_unset("A=1") would remove A.
*/
int	builtin_unset(char **argv, t_list **env)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (is_valid_name(argv[i]) && ft_strchr(argv[i], '=') == NULL)
			env_unset(env, argv[i]);
		i++;
	}
	return (0);
}
