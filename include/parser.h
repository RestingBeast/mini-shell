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
# include "type.h"

typedef struct s_node		t_node;

struct s_node
{
	t_type	type;
	void	*data;
	t_node	*left;
	t_node	*right;
};

t_node *parse_tokens(t_list *head);
t_node	*morris_next(t_node *node, t_node **curr);
t_node	*ft_nodenew(void *data, t_type type);
void	ft_nodeclear(t_node *root);

#endif
