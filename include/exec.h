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

typedef struct s_exec	t_exec;

struct s_exec
{
	int		in_fd;
	int		out_fd;
	char	**args;
};

// exec.c
void	wait_child(pid_t pid, int *status);
void	execute_tree(t_node *root, t_data *data, t_list **env, int *status);

// exec_path.c
char	*find_command(char *cmd, t_data *data, t_list *env);

// exec_ext.c
void	exec_external(t_exec *exec, t_data *data, t_list *env, int *status);

// exec_builtin.c
void	exec_builtin(t_exec *exec, t_data *data, t_list **env, int *status);

// exec_redir.c
void	close_fds(int in_fd, int out_fd);
int		resolve_redir(t_list *redir, t_err *err, int *in_fd, int *out_fd);

#endif
