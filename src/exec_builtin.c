#include "minishell.h"

static int	is_one_cmd(t_data *data)
{
	if (data->tree->left == NULL && data->tree->right == NULL)
		return (1);
	return (0);
}

static void	fork_builtin(t_exec *exec, t_data *data, t_list **env, int *status)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		set_child_sig();
		if (dup2(exec->out_fd, STDOUT_FILENO) == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			close_fds(exec->in_fd, exec->out_fd);
		}
		else
			*status = run_builtin(exec->args, env, *status, &(data->should_exit));
		clean_up(data);
		ft_lstclear(env, free);
		close_fds(exec->in_fd, exec->out_fd);
		exit(*status);
	}
	if (pid == -1)
		set_syscall_err(&(data->err));
	else
		wait_child(pid, status);
}

void	exec_builtin(t_exec *exec, t_data *data, t_list **env, int *status)
{
	int	fd;

	if (!is_one_cmd(data))
		return (fork_builtin(exec, data, env, status));
	fd = dup(STDOUT_FILENO);
	if (fd == -1)
		return (close_fds(exec->in_fd, exec->out_fd),
					set_syscall_err(&(data->err)));
	if (exec->out_fd >= 0 && dup2(exec->out_fd, STDOUT_FILENO) == -1)
		return (close_fds(exec->in_fd, exec->out_fd),
					close(fd), set_syscall_err(&(data->err)));
	*status = run_builtin(exec->args, env,
						*status, &(data->should_exit));
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), set_syscall_err(&(data->err)));
	close(fd);
	close_fds(exec->in_fd, exec->out_fd);
}
