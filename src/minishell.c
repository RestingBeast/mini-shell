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

static int	init_envlst(t_list **env)
{
	extern char	**environ;

	if (env_init(env, environ) == -1)
	{
		ft_putendl_fd("minishell: malloc: failed to allocate memory",
			STDERR_FILENO);
		return (1);
	}
	return (0);
}

/*
** Ctrl-D at the prompt. Like bash, "exit" is printed only when
** someone is typing (stdin is a terminal), and on stderr.
*/
static void	end_shell(t_list **env)
{
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	ft_lstclear(env, free);
	rl_clear_history();
}

int	main(void)
{
	t_data	data;
	t_list	*env;

	if (init_envlst(&env) == 1)
		return (1);
	while (1)
	{
		init_shell(&data);
		data.line = readline("minishell$ ");
		if (!data.line)
			break ;
		if (*(data.line))
			add_history(data.line);
		data.tokens = lexer(data.line, &(data.err));
		if (!check_error(&data, env))
			continue ;
		data.tree = parse_tokens(data.tokens, &(data.err));
		if (!check_error(&data, env))
			continue ;
		expand_tree(data.tree, env, 0, &(data.err));
		if (!check_error(&data, env))
			continue ;
		clean_up(&data);
	}
	end_shell(&env);
	return (0);
}
