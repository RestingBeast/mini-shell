/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/25 02:11:54 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/09/25 22:17:11 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "type.h"

typedef struct s_node		t_node;
typedef struct s_cmd		t_cmd;
typedef union u_tgt			t_tgt;
typedef struct s_redir		t_redir;

struct s_node
{
	t_type	type;
	void	*data;
	t_node	*left;
	t_node	*right;
};

struct s_cmd
{
	char	**args;
	t_list	*redir;
};

union u_tgt
{
	int		fd;
	char	*file;
};

struct s_redir
{
	t_type	type;
	t_tgt	target;
};

// parser.c
t_node	*parse_tokens(t_list *head);
int		is_redir(t_type type);
int		count_args(t_list *tokens);
t_redir	*handle_redir(t_list *tok);
t_redir	*handle_heredoc(t_list *tok);
// node.c
t_cmd	*ft_cmdnew(char **args, t_list *redir);
t_redir	*ft_redirnew_fd(t_type type, int fd);
t_redir	*ft_redirnew_file(t_type type, char *file);
t_node	*ft_nodenew(void *data, t_type type);
void	ft_nodeclear(t_node *root);

#endif
