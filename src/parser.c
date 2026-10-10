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

int	is_redir(t_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT ||
			type == APPEND || type == HEREDOC);
}

static char	**make_args(t_list **tokens)
{
	int		count;
	int		i;
	t_token	*tok;
	char	**res;

	count = count_args(*tokens);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
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

static t_list	*make_redirs(t_list *tokens)
{
	t_token	*tok;
	t_list	*lst;
	t_list	*tmp;

	lst = NULL;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == PIPE)
			break ;
		if (is_redir(tok->type))
		{
			if (tok->type == HEREDOC)
				tmp = ft_lstnew((void *)handle_heredoc(tokens));
			else
				tmp = ft_lstnew((void *)handle_redir(tokens));
			if (!tmp)
				return (NULL);
			ft_lstadd_back(&lst, tmp);
		}
		tokens = tokens->next;
	}
	return (lst);
}

static t_node	*make_cmd_node(t_list **tokens)
{
	t_node	*root;
	t_cmd	*cmd;
	char	**args;
	t_list	*redirs;

	redirs = make_redirs(*tokens);
	if (!redirs)
		return (NULL); // Error
	args = make_args(tokens);
	if (!args)
		return (NULL); // Error
	cmd = ft_cmdnew(args, redirs);
	if (!cmd)
		return (NULL); // Error
	root = ft_nodenew((void *)cmd, COMMAND);
	if (!root)
		return (NULL); // Error handling should be here
	return (root);
}

t_node	*parse_tokens(t_list *tokens)
{
	t_node	*root;
	t_node	*tmp;

	root = NULL;
	while (tokens != NULL)
	{
		if (((t_token *)tokens->content)->type == PIPE)
		{
			tmp = ft_nodenew(NULL, PIPE);
			if (!tmp)
				return (NULL); // Error should be handle here
			tmp->left = root;
			root = tmp;
			tokens = tokens->next;
			continue ;
		}
		if (!root)
			root = make_cmd_node(&tokens);
		else
			root->right = make_cmd_node(&tokens);
	}
	return (root);
}
