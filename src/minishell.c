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
	t_token	tok1 = TOK(WORD, "echo");
	t_token	tok2 = TOK(WORD, "hell\'o wo\'\"rld\"");

	t_list		lst = LST((void *) &tok2, NULL);
	t_list		tokens = LST((void *) &tok1, &lst);

	t_node *root = parse_tokens(&tokens);
	ft_nodeclear(root);
	return (0);
}
