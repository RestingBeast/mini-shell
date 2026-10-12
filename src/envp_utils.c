/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 18:22:48 by psoe              #+#    #+#             */
/*   Updated: 2026/10/10 18:22:48 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Returns the node holding KEY, or NULL if there is none.
** "PATH" matches "PATH=..." and "PATH", but not "PATHX=...".
*/
t_list	*env_find(t_list *env, char *key)
{
	size_t	len;
	char	*entry;

	len = ft_strlen(key);
	while (env != NULL)
	{
		entry = env->content;
		if (ft_strncmp(entry, key, len) == 0
			&& (entry[len] == '=' || entry[len] == '\0'))
			return (env);
		env = env->next;
	}
	return (NULL);
}

/*
** Removes KEY from the list. Does nothing if KEY is not set.
*/
void	env_unset(t_list **env, char *key)
{
	t_list	*node;
	t_list	*prev;

	node = env_find(*env, key);
	if (node == NULL)
		return ;
	if (*env == node)
		*env = node->next;
	else
	{
		prev = *env;
		while (prev->next != node)
			prev = prev->next;
		prev->next = node->next;
	}
	ft_lstdelone(node, free);
}

/*
** The env builtin: prints every variable that has a value.
** Bash sets _ to the path of the program it runs, which for env
** is always /usr/bin/env, so we set the same value by hand.
** Returns 0, or -1 if malloc failed.
*/
int	env_print(t_list **env)
{
	t_list	*node;

	if (env_set(env, "_", "/usr/bin/env") == -1)
		return (-1);
	node = *env;
	while (node != NULL)
	{
		if (ft_strchr(node->content, '=') != NULL)
			ft_putendl_fd(node->content, STDOUT_FILENO);
		node = node->next;
	}
	return (0);
}

/*
** Makes a NULL-terminated copy of the list to pass to execve().
** Variables without a value are skipped, like bash does.
** Free the result with free_array().
*/
char	**env_to_array(t_list *env)
{
	char	**array;
	int		i;

	array = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		if (ft_strchr(env->content, '=') != NULL)
		{
			array[i] = ft_strdup(env->content);
			if (array[i] == NULL)
			{
				free_array(array);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	return (array);
}

/*
** Frees a NULL-terminated array of strings,
** such as the result of env_to_array() or ft_split().
*/
void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
