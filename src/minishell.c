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

static void	init_shell(t_data *data)
{
	data->line = NULL;
	data->tokens = NULL;
	data->tree = NULL;
	data->err_no = OK;
	// set_sigaction();
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
		if (data.tokens == NULL)
			printf("token's NULL\n");
		printf("Lexing done...\n");
		data.tree = parse_tokens(data.tokens, &(data.err_no));
		printf("Parsing done...\n");
		clean_up(&data);
		printf("Cleaning up...\n");
	}
	rl_clear_history();
	return (0);
}
