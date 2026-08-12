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
# include "libft.h"
# include "lexer.h"
# include "parser.h"

void print_list(t_list* node);
t_list *copy_envp(char** envp);
#endif
