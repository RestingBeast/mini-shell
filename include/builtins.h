/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "libft.h"

/*
** Every builtin returns its exit status (0 = success), like a program.
** They change the env only through envp.h (env_get, env_set...).
** Only sort_env() walks the list itself, and it only reads it.
*/

/* builtin.c: find and run a builtin by its name */
int		is_builtin(char *name);
int		run_builtin(char **argv, t_list **env, int last_status,
			int *should_exit);

/* one function per builtin */
int		builtin_echo(char **argv);
int		builtin_cd(char **argv, t_list **env);
int		builtin_pwd(t_list *env);
int		builtin_export(char **argv, t_list **env);
int		builtin_unset(char **argv, t_list **env);
int		builtin_env(char **argv, t_list **env);
int		builtin_exit(char **argv, int last_status, int *should_exit);

/* builtin_utils.c */
int		is_valid_name(char *str);
void	print_error(char *command, char *arg, char *message);

/* export_sort.c and export_print.c: "export" with no arguments */
char	**sort_env(t_list *env);
int		print_exported(t_list *env);

#endif
