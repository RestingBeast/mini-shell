#include "minishell.h"

static int	is_one_cmd(t_data *data)
{
	if (data->tree->left == NULL && data->tree->right == NULL)
		return (1);
	return (0);
}

static void	fork_builtin(t_cmd *cmd, t_data *data, t_list **env, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		set_child_sig();
		*status = run_builtin(cmd->args, env, *status, &(data->should_exit));
		clean_up(data);
		ft_lstclear(env, free);
		exit(*status);
	}
	if (pid == -1)
		set_syscall_err(&(data->err));
	else
		wait_child(pid, status);
}

void	exec_builtin(t_cmd *cmd, t_data *data, t_list **env, int *status)
{
	if (is_one_cmd(data))
		*status = run_builtin(cmd->args, env,
								*status, &(data->should_exit));
	else
		fork_builtin(cmd, data, env, status);
}
