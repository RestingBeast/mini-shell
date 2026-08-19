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
	t_segment	seg1 = SEG("echo", NONE);
	t_list	lexeme1 = LST((void *) &seg1, NULL);

	t_segment	seg2 = SEG("hell", NONE);
	t_segment	seg3 = SEG("owo", SINGLE);
	t_segment	seg4 = SEG("rld", DOUBLE);
	t_list	lexeme2_3 = LST((void *) &seg4, NULL);
	t_list	lexeme2_2 = LST((void *) &seg3, &lexeme2_3);
	t_list	lexeme2_1 = LST((void *) &seg2, &lexeme2_2);

	t_segment	seg5 = SEG("grep", NONE);
	t_list	lexeme3 = LST((void *) &seg5, NULL);

	t_segment	seg6 = SEG("hello", NONE);
	t_list	lexeme4 = LST((void *) &seg6, NULL);

	t_token	tok1 = TOK(&lexeme1, WORD);
	t_token	tok2 = TOK(&lexeme2_1, WORD);
	t_token tok3 = TOK(NULL, PIPE);
	t_token tok4 = TOK(&lexeme3, WORD);
	t_token tok5 = TOK(&lexeme4, WORD);

	t_list	lst4 = LST((void *) &tok5, NULL);
	t_list	lst3 = LST((void *) &tok4, &lst4);
	t_list	lst2 = LST((void *) &tok3, &lst3);
	t_list	lst1 = LST((void *) &tok2, &lst2);
	t_list	toks = LST((void *) &tok1, &lst1);

	t_node *root = parse_tokens(&toks);
	ft_nodeclear(root);
	return (0);
}
