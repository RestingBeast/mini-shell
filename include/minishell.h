/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:43:58 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/12 22:50:55 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "lexer.h"
# include "parser.h"
# include "envp.h"
# include "builtins.h"

void	clean_up(t_list *tokens, t_node *tree);
void	fatal_error(int err);

#endif
