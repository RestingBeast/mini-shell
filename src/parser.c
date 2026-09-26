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

static int	count_args(t_list *tokens)
{
	int	res;
	t_token	*tok;

	res = 0;
	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->lexeme != NULL)
			res++;
		tokens = tokens->next;
	}
	return (res);
}

static char	**make_args(t_list *tokens)
{
	int		count;
	int		i;
	t_token	*tok;
	char	**res;

	count = count_args(tokens);
	res = ft_calloc(count + 1, sizeof(char *));
	if (!res)
		return (NULL);
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

t_node	*parse_tokens(t_list *tokens)
{
	t_node	*root;
	t_cmd	*cmd;
	char	**args;

	args = make_args(tokens);
	cmd = ft_cmdnew(args, NULL);
	root = ft_nodenew((void *)cmd, COMMAND);
/*
	while (*args != NULL)
	{
		printf("%s\n", *args);
		args++;
	}
*/
	return (root);
}
