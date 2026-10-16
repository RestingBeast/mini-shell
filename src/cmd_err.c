#include "minishell.h"

void	print_cmd_err_msg(t_err_type type, int err_no, char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (type == IS_DIR_ERR)
		ft_putstr_fd("Is a directory", STDERR_FILENO);
	else if (ft_strchr(msg, '/') == NULL)
		ft_putstr_fd("command not found...", STDERR_FILENO);
	else
		ft_putstr_fd(strerror(err_no), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	set_cmd_err(t_err *err, char *cmd)
{
	err->type = CMD_ERROR;
	err->err_no = errno;
	err->msg = cmd;
}

void	set_cmd_not_found_err(t_err *err, char *cmd)
{
	err->type = CMD_NOT_FOUND;
	err->err_no = errno;
	err->msg = cmd;
}

void	set_dir_err(t_err *err, char *cmd)
{
	err->type = IS_DIR_ERR;
	err->msg = cmd;
}
