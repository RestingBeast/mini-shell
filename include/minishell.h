/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:43:58 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/10 19:39:43 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "error.h"

extern volatile sig_atomic_t sig_captured;

typedef struct s_data	t_data;

struct s_data
{
	char		*line;
	t_list		*tokens;
	t_node		*tree;
	t_err_no	err_no;
};

void	set_sigaction(void);
void	clean_up(t_data *data);
void	fatal_error(int err);

#endif
