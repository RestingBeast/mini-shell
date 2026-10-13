/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:34:39 by psoe              #+#    #+#             */
/*   Updated: 2026/10/13 12:34:39 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** How many chars at the start of STR form a variable name:
** a letter or '_' first, then letters, digits or '_'.
** Returns 0 when STR does not start with a name.
*/
static int	name_len(char *str)
{
	int	len;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	len = 1;
	while (ft_isalnum(str[len]) || str[len] == '_')
		len++;
	return (len);
}

/*
** The name is the first LEN chars of STR.
** Returns a malloc'd copy of its value, or "" when it is not set.
*/
static char	*get_value(char *str, int len, t_list *env)
{
	char	*name;
	char	*value;

	name = ft_substr(str, 0, len);
	if (name == NULL)
		return (NULL);
	value = env_get(env, name);
	free(name);
	if (value == NULL)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

/*
** WORD[*i] is a '$'. Returns a malloc'd copy of the text that
** replaces it, and moves *i to the first char after it:
**   $?      -> the exit status of the last command, like "0"
**   $USER   -> the value of USER, or "" when USER is not set
**   $1      -> "" (a digit is a script argument: we have none)
**   $       -> "$" when no name follows, like "$" alone or "$."
** Returns NULL if malloc failed.
*/
char	*expand_dollar(char *word, int *i, t_list *env, int status)
{
	char	*value;
	int		len;

	(*i)++;
	if (word[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(status));
	}
	if (ft_isdigit(word[*i]))
	{
		(*i)++;
		return (ft_strdup(""));
	}
	len = name_len(word + *i);
	if (len == 0)
		return (ft_strdup("$"));
	value = get_value(word + *i, len, env);
	*i += len;
	return (value);
}
