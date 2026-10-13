/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoe <psoe@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 12:34:39 by psoe              #+#    #+#             */
/*   Updated: 2026/10/13 12:34:39 by psoe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** True when STR has a ' or a " in it.
*/
static int	has_quotes(char *str)
{
	return (ft_strchr(str, '\'') != NULL || ft_strchr(str, '"') != NULL);
}

/*
** Counts the strings of a NULL-terminated array.
*/
static int	count_strs(char **strs)
{
	int	count;

	count = 0;
	while (strs[count] != NULL)
		count++;
	return (count);
}

/*
** Expands every argument of CMD into a new array.
** Like bash, an argument without quotes that becomes empty is removed:
** "$NOPE ls" runs ls. But "" and "$NOPE" stay as empty arguments.
** The old array is freed only when everything worked, so after an
** error CMD is unchanged and can be freed as usual.
*/
static int	expand_args(t_cmd *cmd, t_list *env, int status)
{
	char	**new_args;
	char	*arg;
	int		i;
	int		j;

	new_args = ft_calloc(count_strs(cmd->args) + 1, sizeof(char *));
	if (new_args == NULL)
		return (-1);
	i = 0;
	j = 0;
	while (cmd->args[i] != NULL)
	{
		arg = expand_word(cmd->args[i], env, status);
		if (arg == NULL)
			return (free_array(new_args), -1);
		if (arg[0] == '\0' && !has_quotes(cmd->args[i]))
			free(arg);
		else
			new_args[j++] = arg;
		i++;
	}
	free_array(cmd->args);
	cmd->args = new_args;
	return (0);
}

/*
** Expands the file name of every redirection of the list.
** A heredoc is skipped: the parser has already read its text,
** and bash never expands a heredoc delimiter.
*/
static int	expand_redirs(t_list *redirs, t_list *env, int status)
{
	t_redir	*redir;
	char	*file;

	while (redirs != NULL)
	{
		redir = (t_redir *)redirs->content;
		if (redir->type != HEREDOC)
		{
			file = expand_word(redir->target.file, env, status);
			if (file == NULL)
				return (-1);
			free(redir->target.file);
			redir->target.file = file;
		}
		redirs = redirs->next;
	}
	return (0);
}

/*
** Expands every command of the tree. STATUS is the exit status of the
** last command: it is what $? becomes.
** Returns 0, or -1 if malloc failed. Even then, the tree is still
** valid and is freed as usual with ft_nodeclear().
*/
int	expand_tree(t_node *root, t_list *env, int status)
{
	t_cmd	*cmd;

	if (root == NULL)
		return (0);
	if (expand_tree(root->left, env, status) == -1
		|| expand_tree(root->right, env, status) == -1)
		return (-1);
	if (root->type != COMMAND)
		return (0);
	cmd = (t_cmd *)root->data;
	if (expand_args(cmd, env, status) == -1
		|| expand_redirs(cmd->redir, env, status) == -1)
		return (-1);
	return (0);
}
