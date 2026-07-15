/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:44:16 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/09/28 13:42:20 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break;
		if (*line)
			add_history(line);
		free(line);
	}
	printf("exit\n");
	return (0);
}
