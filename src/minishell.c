/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/07 20:44:16 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/08/12 22:54:58 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc,char** argv, char** envp)
{
	t_list* head;
	argc++;
	(void)argv;
	head = copy_envp(envp);
	print_list(head);
	ft_lstclear(&head, free);
	return(0);
}
