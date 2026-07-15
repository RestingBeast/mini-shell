/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:43:58 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/07/15 20:51:54 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>

typedef struct s_segment t_segment;
typedef struct s_token t_token;

enum Quote
{
	NONE,
	SINGLE,
	DOUBLE,
};

enum Type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND,
};

struct s_segment
{
	char		*text;
	enum Quote	quote;
};

struct s_token
{
	t_segment	**lexeme;
	enum Type	type;
};

t_token	**lexer(char *line);

#endif
