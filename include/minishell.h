/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:43:58 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/12 19:29:29 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "envp.h"
# include "builtins.h"
# include "expand.h"
# include "error.h"
# include "exe.h"

extern volatile sig_atomic_t	g_sig_captured;

typedef struct s_data			t_data;

struct s_data
{
	int	status;
	char	*line;
	t_list	*tokens;
	t_node	*tree;
	t_err	err;
};

// signals.c
void	set_sigaction(void);
void	set_heredoc_sig(void);
int		rl_check(void);

// utils.c
int		is_space(char c);
int		is_redir(t_type type);
void	init_shell(t_data *data);
void	clean_up(t_data *data);

// quotes.c
int		is_quote_mark(char c, char *quote);
char	*strip_quotes(char *str);

#endif
