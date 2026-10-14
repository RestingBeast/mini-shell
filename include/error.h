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
typedef union u_payload	t_payload;
typedef struct s_err	t_err;

enum	e_err_no
{
	OK = 0,
	MALLOC_ERROR,
	UNCLOSED_QUOTE,
	UNEXPECTED_TOK,
	END_PIPE,
	END_REDIR,
	HEREDOC_ABORT,
	SYSCALL_ERR,
	CMD_ERROR,
	CMD_NOT_FOUND,
	IS_DIR_ERR,
};

union u_payload
{
	char	*msg;
	int		err_no;
};

struct	s_err
{
	t_err_no	err_no;
	t_payload	payload;
};

// errors.c
int		check_error(t_data *data, t_list *env);

// syscall_err.c
void	set_malloc_err(t_err *err);
void	set_syscall_err(t_err *err);
void	set_cmd_err(t_err *err);
void	set_cmd_not_found_err(t_err *err);
void	set_dir_err(t_err *err);

// syntac_err.c
void	set_quote_err(t_err *err, char quote);
void	set_unexp_tok_err(t_err *err, t_type tok);
void	set_end_pipe_err(t_err *err);
void	set_end_redir_err(t_err *err);

#endif
