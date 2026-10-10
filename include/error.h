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

typedef enum e_err_no t_err_no;

enum	e_err_no
{
	OK = 0,
	SYNTAX_ERROR = 2,
	MALLOC_ERROR = -1,
};

#endif
