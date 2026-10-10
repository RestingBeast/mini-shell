/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:44:16 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/10 19:38:39 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	set_sigaction();
	while (1)
	{
		data.line = readline("minishell$ ");
		if (!data.line)
			break;
		if (*(data.line))
			add_history(data.line);
		free(data.line);
	}
	rl_clear_history();
	return (0);
}
