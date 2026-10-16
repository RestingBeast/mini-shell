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

#ifndef EXEC_H
# define EXEC_H

// exec.c
void	wait_child(pid_t pid, int *status);
void	execute_tree(t_node *root, t_data *data, t_list **env, int *status);

// exec_path.c
char	*find_command(char *cmd, t_data *data, t_list *env);

// exec_builtin.c
void	exec_builtin(t_cmd *cmd, t_data *data, t_list **env, int *status);

#endif
