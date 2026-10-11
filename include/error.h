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
	MALLOC_ERROR = 1,
	SYNTAX_ERROR = 2,
};

struct	s_err
{
	t_err_no	err_no;
	char		*msg;
};

void	set_syntax_err(t_err *err, char *lexeme);
int		check_error(t_data *data);

#endif
