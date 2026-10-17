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
# include "libft.h"

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

/*
** AMBIGUOUS is set by the expander when the file name became empty
** without quotes, like "> $NOPE". FILE then keeps the word as it was
** typed, so the executor can print "minishell: $NOPE: ambiguous redirect".
*/
struct s_redir
{
	t_type	type;
	t_tgt	target;
	int		ambiguous;
};

// parser.c
t_node	*parse_tokens(t_list *tokens, t_data *data);

// parser_utils.c
int		count_args(t_list *tokens);
t_redir	*handle_redir(t_list *tok, t_err *err);

// heredoc.c
t_redir	*handle_heredoc(t_list *tok, t_data *data);

// heredoc_utils.c
void	warn_eof(char *delimiter);
char	*make_tmp_path(int n);

// node.c
t_cmd	*ft_cmdnew(char **args, t_list *redir);
t_redir	*ft_redirnew_fd(t_type type, int fd);
t_redir	*ft_redirnew_file(t_type type, char *file);
t_node	*ft_nodenew(void *data, t_type type);

// node_utils.c
void	ft_redirclear(void *rdr);
void	ft_heredoc_clear(t_node *tree);
void	ft_argclear(char **args);
void	ft_cmdclear(t_cmd *cmd);
void	ft_nodeclear(t_node *root);

#endif
