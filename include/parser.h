/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 02:11:54 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/07/25 02:11:55 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_node		t_node;
typedef enum e_node_type	t_node_type;

enum e_node_type
{
	COMMAND,
	REDIR,
	CTRL,
	TARGET,
};

struct s_node
{
	int			data;
	t_node_type	type;
	t_node		*left;
	t_node		*right;
};

#endif
