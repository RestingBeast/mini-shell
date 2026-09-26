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

static char	**make_args(t_list *tokens)
{
	int		count;
	int		i;
	t_token	*tok;
	char	**res;

	count = count_args(tokens);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL); // Error-handling should be here
	i = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->lexeme != NULL)
			res[i++] = tok->lexeme;
		tok->lexeme = NULL;
		tokens = tokens->next;
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
		if (is_redir(tok->type))
		{
			tmp = ft_lstnew((void *)handle_redir(tokens));
			if (!tmp)
				return (NULL); // Error-handling should be here
			ft_lstadd_back(&lst, tmp);
		}
		tokens = tokens->next;
	}
	return (lst);
}

t_node	*parse_tokens(t_list *tokens)
{
	t_node	*root;
	t_cmd	*cmd;
	char	**args;
	t_list	*redirs;

	redirs = make_redirs(tokens);
	args = make_args(tokens);
	cmd = ft_cmdnew(args, redirs);
	root = ft_nodenew((void *)cmd, COMMAND);
	return (root);
}
