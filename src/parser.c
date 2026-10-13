/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 15:15:02 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/13 15:15:04 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**make_args(t_list **tokens, t_err *err)
{
	int		count;
	int		i;
	t_token	*tok;
	char	**res;

	count = count_args(*tokens);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (set_malloc_err(err), NULL);
	i = 0;
	while (*tokens != NULL)
	{
		tok = (t_token *)(*tokens)->content;
		if (tok->type == PIPE)
			break ;
		if (tok->lexeme != NULL)
			res[i++] = tok->lexeme;
		tok->lexeme = NULL;
		*tokens = (*tokens)->next;
	}
	return (res);
}

static t_list	*make_redir(t_list *tok, t_type type, t_err *err)
{
	t_redir	*redir;
	t_list	*res;

	if (type == HEREDOC)
		redir = handle_heredoc(tok, err);
	else
		redir = handle_redir(tok, err);
	if (err->err_no != OK)
		return (ft_redirclear(redir), NULL);
	res = ft_lstnew((void *)redir);
	if (!res)
		return (ft_redirclear((void *) redir), set_malloc_err(err), NULL);
	return (res);
}

static t_list	*make_redirs(t_list *tokens, t_err *err)
{
	t_token	*tok;
	t_list	*lst;
	t_list	*tmp;

	lst = NULL;
	err->err_no = OK;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == PIPE)
			break ;
		if (is_redir(tok->type))
		{
			tmp = make_redir(tokens, tok->type, err);
			if (!tmp)
				return (ft_lstclear(&lst, ft_redirclear), NULL);
			ft_lstadd_back(&lst, tmp);
		}
		tokens = tokens->next;
	}
	return (lst);
}

static t_node	*make_cmd_node(t_list **tokens, t_err *err)
{
	t_node	*root;
	t_cmd	*cmd;
	char	**args;
	t_list	*redirs;

	redirs = make_redirs(*tokens, err);
	if (err->err_no != OK)
		return (NULL);
	args = make_args(tokens, err);
	if (!args)
		return (ft_lstclear(&redirs, ft_redirclear), NULL);
	cmd = ft_cmdnew(args, redirs);
	if (!cmd)
		return (set_malloc_err(err), ft_lstclear(&redirs, ft_redirclear),
			ft_argclear(args), NULL);
	root = ft_nodenew((void *)cmd, COMMAND);
	if (!root)
		return (ft_cmdclear(cmd), free(cmd), set_malloc_err(err), NULL);
	return (root);
}

t_node	*parse_tokens(t_list *tokens, t_err *err)
{
	t_node	*root;
	t_node	*tmp;

	root = NULL;
	err->err_no = OK;
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type == PIPE)
		{
			tmp = ft_nodenew(NULL, PIPE);
			if (!tmp)
				return (ft_nodeclear(root), set_malloc_err(err), NULL);
			tmp->left = root;
			root = tmp;
			tokens = tokens->next;
			continue ;
		}
		if (!root)
			root = make_cmd_node(&tokens, err);
		else
			root->right = make_cmd_node(&tokens, err);
		if (err->err_no != OK)
			return (ft_nodeclear(root), NULL);
	}
	return (root);
}
