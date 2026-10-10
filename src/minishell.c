/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:44:16 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/12 22:54:58 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err_no = OK;
	set_sigaction();
}

int	main(void)
{
	t_data	data;

	init_shell(&data);
	while (1)
	{
		data.line = readline("minishell$ ");
		if (!data.line)
			break;
		if (*(data.line))
			add_history(data.line);
		data.tokens = lexer(data.line, &(data.err_no));
		data.tree = parse_tokens(data.tokens, &(data.err_no));
		clean_up(&data);
	}
	rl_clear_history();
	return (0);
}
