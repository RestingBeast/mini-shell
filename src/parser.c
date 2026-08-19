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

char	*combine_segments(t_token *tok)
{
	t_segment	*seg;
	t_list		*segs;
	char		*res;
	char		*tmp;

	res = ft_calloc(1, sizeof(char));
	if (!res)
		fatal_error(1);
	segs = tok->lexeme;
	while (segs)
	{
		seg = (t_segment *)segs->content;
		tmp = ft_strjoin(res, seg->text);
		free(res);
		res = tmp;
		segs = segs->next;
	}
	return (res);
}

int	count_words(t_list *lst)
{
	int	count;

	count = 0;
	while (lst && ((t_token *)lst->content)->type == WORD)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

char	**make_command(t_list **lst)
{
	char	**cmd;
	char	*str;
	int		i;
	int		words;
	t_token	*tok;

	words = count_words(*lst);
	cmd = malloc((words + 1) * sizeof(char *));
	if (!cmd)
		fatal_error(1);
	i = 0;
	while (i < words)
	{
		tok = (*lst)->content;
		str = combine_segments(tok);
		cmd[i] = str;
		if (++i != words)
			*lst = (*lst)->next;
	}
	cmd[i] = NULL;
	return (cmd);
}

t_node	*parse_tokens(t_list *head)
{
	t_token	*tok;
	t_node	*node;
	t_node	*root;

	root = NULL;
	while (head)
	{
		tok = (t_token *)head->content;
		if (tok->type == WORD)
		{
			if (!root)
				root = ft_nodenew((void *)make_command(&head), COMMAND);
			else
				root->right = ft_nodenew((void *)make_command(&head), COMMAND);

		}
		else
		{
			node = root;
			root = ft_nodenew(NULL, tok->type);
			if (!root)
				exit(1);
			root->left = node;
		}
		if (head)
			head = head->next;
	}
	return (root);
}
