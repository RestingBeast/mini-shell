/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/30 18:01:25 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/09/30 18:01:27 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef struct s_data	t_data;
typedef enum e_err_no	t_err_no;
typedef struct s_err	t_err;

enum	e_err_no
{
	OK = 0,
	MALLOC_ERROR,
	UNCLOSED_QUOTE,
	UNEXPECTED_TOK,
	END_PIPE,
	END_REDIR,
	PIPE_ERROR,
	HEREDOC_ABORT,
};

struct	s_err
{
	t_err_no	err_no;
	char		*msg;
};

// errors.c
void	set_malloc_err(t_err *err);
void	set_pipe_err(t_err *err);
int		check_error(t_data *data, t_list *env);

// syntac_err.c
void	set_quote_err(t_err *err, char quote);
void	set_unexp_tok_err(t_err *err, t_type tok);
void	set_end_pipe_err(t_err *err);
void	set_end_redir_err(t_err *err);

#endif
