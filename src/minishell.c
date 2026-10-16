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
** Ctrl-D at the prompt or the exit builtin. Like bash, "exit" is
** printed only when someone is typing (stdin is a terminal), and on stderr.
** stdin and stdout are closed so valgrind --track-fds does not report
** stdout after a builtin redirection restored it with dup2().
** stderr stays open: ASan prints its leak report there at exit.
*/
static void	end_shell(t_list **env)
{
	if (isatty(STDIN_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	ft_lstclear(env, free);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}

/*
** Lexes, parses, expands and runs one line.
** Returns 0 when the exit builtin says the shell must stop.
*/
static int	run_line(t_data *data, t_list **env, int *status)
{
	data->tokens = lexer(data->line, &(data->err));
	if (!check_error(data, *env, status))
		return (1);
	data->tree = parse_tokens(data->tokens, &(data->err));
	if (!check_error(data, *env, status))
		return (1);
	expand_tree(data->tree, *env, *status, &(data->err));
	if (!check_error(data, *env, status))
		return (1);
	execute_tree(data->tree, data, env, status);
	if (data->should_exit)
		return (clean_up(data), 0);
	if (!check_error(data, *env, status))
		return (1);
	clean_up(data);
	return (1);
}

int	main(void)
{
	int		status;
	t_data	data;
	t_list	*env;

	if (init_envlst(&env) == 1)
		return (1);
	status = 0;
	data.should_exit = 0;
	while (1)
	{
		init_shell(&data);
		data.line = readline("minishell$ ");
		if (!data.line)
			break ;
		if (*(data.line))
			add_history(data.line);
		if (!run_line(&data, &env, &status))
			break ;
	}
	end_shell(&env);
	return (status);
}
