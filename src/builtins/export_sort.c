/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/12 10:36:10 by psoe              #+#    #+#             */
/*   Updated: 2026/10/12 10:36:10 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** In an entry, the name ends at '=' or at '\0'.
** Both count as 0, so a shorter name comes first: "A" before "A1".
*/
static int	name_char(char c)
{
	if (c == '=')
		return (0);
	return ((unsigned char)c);
}

/*
** Compares only the names of two entries, like strcmp():
** negative if a comes first, 0 if same name, positive if b comes first.
*/
static int	compare_names(char *a, char *b)
{
	int	i;

	i = 0;
	while (name_char(a[i]) != 0 && name_char(a[i]) == name_char(b[i]))
		i++;
	return (name_char(a[i]) - name_char(b[i]));
}

/*
** Bubble sort: walks through the array swapping neighbours that are
** in the wrong order, and starts again until nothing was swapped.
*/
static void	bubble_sort(char **array)
{
	int		i;
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		i = 0;
		while (array[i] != NULL && array[i + 1] != NULL)
		{
			if (compare_names(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				swapped = 1;
			}
			i++;
		}
	}
}

/*
** Returns an array of the env strings sorted by name, ending with NULL.
** The strings are NOT copied, they still belong to the list:
** free only the array itself, with free(array).
** Returns NULL if malloc failed.
*/
char	**sort_env(t_list *env)
{
	char	**array;
	int		i;

	array = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (env != NULL)
	{
		array[i] = env->content;
		env = env->next;
		i++;
	}
	bubble_sort(array);
	return (array);
}
