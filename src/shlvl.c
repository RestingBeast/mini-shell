/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 18:22:48 by psoe              #+#    #+#             */
/*   Updated: 2026/10/10 18:22:48 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	return (str);
}

/*
** Reads the old SHLVL the same way bash does: spaces around the number
** and a + or - sign are fine. Anything else counts as 0, and so does
** INT_MAX, because adding 1 to it would overflow.
*/
static int	parse_shlvl(char *str)
{
	long	number;
	int		sign;

	str = skip_spaces(str);
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		return (0);
	number = 0;
	while (ft_isdigit(*str) && number < INT_MAX)
	{
		number = number * 10 + (*str - '0');
		str++;
	}
	if (number > INT_MAX || (number == INT_MAX && sign == 1)
		|| *skip_spaces(str) != '\0')
		return (0);
	return (number * sign);
}

/*
** Every shell adds 1 to SHLVL when it starts.
** Missing or invalid -> 1, negative -> 0, 1000 or more -> warning and 1.
*/
int	update_shlvl(t_list **env)
{
	char	*old_value;
	char	*new_value;
	int		level;
	int		status;

	old_value = env_get(*env, "SHLVL");
	level = 1;
	if (old_value != NULL)
		level = parse_shlvl(old_value) + 1;
	if (level < 0)
		level = 0;
	if (level >= 1000)
	{
		ft_putstr_fd("minishell: warning: shell level (", STDERR_FILENO);
		ft_putnbr_fd(level, STDERR_FILENO);
		ft_putendl_fd(") too high, resetting to 1", STDERR_FILENO);
		level = 1;
	}
	new_value = ft_itoa(level);
	if (new_value == NULL)
		return (-1);
	status = env_set(env, "SHLVL", new_value);
	free(new_value);
	return (status);
}
