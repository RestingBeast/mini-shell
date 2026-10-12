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

int	main(void)
{
	t_data	data;

	while (1)
	{
		init_shell(&data);
		data.line = readline("minishell$ ");
		if (!data.line)
			break;
		if (*(data.line))
			add_history(data.line);
		data.tokens = lexer(data.line, &(data.err));
		if (!check_error(&data))
			continue ;
		data.tree = parse_tokens(data.tokens, &(data.err));
		clean_up(&data);
	}
	printf("exit\n");
	rl_clear_history();
	return (0);
}
