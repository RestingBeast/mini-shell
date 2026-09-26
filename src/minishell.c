/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapor      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:44:16 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/06/07 20:44:17 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	/*
	// Test Case 1
	t_token	tok1 = TOK(WORD, "echo");
	t_token	tok2 = TOK(WORD, "hell\'o wo\'\"rld\"");

	t_list		lst = LST((void *) &tok2, NULL);
	t_list		tokens = LST((void *) &tok1, &lst);
	*/

	/*
	// Test Case 2
	t_token	tok1 = TOK(WORD, "echo");
	t_token	tok2 = TOK(WORD, "hello");
	t_token	tok3 = TOK(REDIR_OUT, NULL);
	t_token	tok4 = TOK(WORD, "out");

	t_list	lst3 = LST((void *)&tok4, NULL);
	t_list	lst2 = LST((void *)&tok3, &lst3);
	t_list	lst1 = LST((void *)&tok2, &lst2);
	t_list	tokens = LST((void *)&tok1, &lst1);
	*/

	t_token	tok1 = TOK(HEREDOC, NULL);
	t_token	tok2 = TOK(WORD, "abc");
	
	t_list	lst1 = LST((void *)&tok2, NULL);
	t_list	tokens = LST((void *)&tok1, &lst1);

	handle_heredoc(&tokens);
	// t_node *root = parse_tokens(&tokens);
	// ft_nodeclear(root);
	return (0);
}
