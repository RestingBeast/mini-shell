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

/*
int	count_commands(t_list	*toks)
{
	t_token		*tok;
	t_segment	*seg;
	t_list		*segs;

	while (toks)
	{
		tok = (t_token *)toks->content;
		if (tok->type != WORD)
			break ;
		segs = tok->lexeme;
		while (segs)
		{
			seg = (t_segment *)segs->content;
			printf("%s\n", seg->text);
			segs = segs->next;
		}
		toks = toks->next;
	}
	return (0);
}
*/

// crashing
/*
int	count_segments(t_token *tok)
{
	t_list	*lst;
	int		count;

	count = 0;
	lst = tok->lexeme;
	while (lst)
	{
		count += ft_strlen(((t_segment *)lst->content)->text);
		lst = lst->next;
	}
	return (count);
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
*/

/*
char	**combine_words(t_list **lst)
{
	int		segs;
	int		i;
	char	**cmd;

	words = count_words(*lst);
	cmd = malloc(words * sizeof(char *));
	if (!cmd)
		return (NULL);
	printf("Word count: %d\n", words);
	cmd = NULL;
	i = -1;
	while (++i < words)
	{
		printf("Total Seg length: %d\n", count_segments((t_token *)(*lst)->content));
		*lst = (*lst)->next;
	}
	return (cmd);
}
*/

t_node	*parse_tokens(t_list *head)
{
	t_token	*tok;
	char	*str;

	while (head)
	{
		tok = (t_token *)head->content;
		if (tok->type == WORD)
		{
			str = combine_segments(tok);
			printf("%s\n", str);
			free(str);
		}
		head = head->next;
	}
	return (NULL);
}
