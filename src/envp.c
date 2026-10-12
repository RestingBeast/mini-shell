/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 18:22:48 by psoe              #+#    #+#             */
/*   Updated: 2026/10/10 18:22:48 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Puts an already malloc'd "KEY=value" string at the end of the list.
** The list now owns the string. If anything fails, the string is freed.
*/
static int	env_add(t_list **env, char *entry)
{
	t_list	*node;

	if (entry == NULL)
		return (-1);
	node = ft_lstnew(entry);
	if (node == NULL)
	{
		free(entry);
		return (-1);
	}
	ft_lstadd_back(env, node);
	return (0);
}

/*
** Builds "KEY=value", or just "KEY" when value is NULL.
*/
static char	*make_entry(char *key, char *value)
{
	char	*key_equal;
	char	*entry;

	if (value == NULL)
		return (ft_strdup(key));
	key_equal = ft_strjoin(key, "=");
	if (key_equal == NULL)
		return (NULL);
	entry = ft_strjoin(key_equal, value);
	free(key_equal);
	return (entry);
}

/*
** Returns the value of KEY, or NULL if KEY is not set.
** The string belongs to the list: do not free it.
*/
char	*env_get(t_list *env, char *key)
{
	t_list	*node;
	char	*equal;

	node = env_find(env, key);
	if (node == NULL)
		return (NULL);
	equal = ft_strchr(node->content, '=');
	if (equal == NULL)
		return (NULL);
	return (equal + 1);
}

/*
** Adds KEY=value, or replaces the value if KEY already exists.
** With value NULL, KEY is added without a value (like "export KEY"),
** and an existing value is kept. Returns 0, or -1 if malloc failed.
*/
int	env_set(t_list **env, char *key, char *value)
{
	t_list	*node;
	char	*entry;

	node = env_find(*env, key);
	if (node != NULL && value == NULL)
		return (0);
	entry = make_entry(key, value);
	if (node == NULL)
		return (env_add(env, entry));
	if (entry == NULL)
		return (-1);
	free(node->content);
	node->content = entry;
	return (0);
}
