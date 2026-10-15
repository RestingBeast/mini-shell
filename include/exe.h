/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkhant-z <kkhant-z@student.42singapore.sg  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 18:53:53 by kkhant-z          #+#    #+#             */
/*   Updated: 2026/10/14 18:53:55 by kkhant-z         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXE_H
# define EXE_H

// exec.c
void	execute_tree(t_node *root, t_data *data, t_list *env);

// exec_path.c
char	*find_command(char *cmd, t_data *data, t_list *env);

#endif
