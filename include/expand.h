/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:34:39 by psoe              #+#    #+#             */
/*   Updated: 2026/10/13 12:34:39 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "libft.h"
# include "parser.h"

/*
** Expansion runs on the tree, after the parser and before the executor.
** In every word it replaces $NAME and $? by their values and removes
** the quotes, like bash. Every function returns NULL or -1 only when
** malloc failed.
*/

// expand.c
int		expand_tree(t_node *root, t_list *env, int status);

// expand_word.c
char	*expand_word(char *word, t_list *env, int status);

// expand_dollar.c
char	*expand_dollar(char *word, int *i, t_list *env, int status);

#endif
