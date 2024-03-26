/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/26 12:35:22 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error_execve(char *cmd, char *path)
{
	if (errno == ENOENT && ft_strchr(path, '/') == 0)
		ft_printf_fd(2, "minishell: %s : command not found\n", path);
	else if (errno == ENOENT && access(path, F_OK) == -1)
		ft_printf_fd(2, "minishell: %s : No such file or directory\n", cmd);
	else if (errno == EISDIR)
		ft_printf_fd(2, "minishell: %s : Is a directory\n", path);
	else if (errno == EACCES)
		ft_printf_fd(2, "minishell: %s : Permission denied\n", path);
	else if (errno == EFAULT)
		ft_printf_fd(2, "minishell: %s : Bad address\n", path);
	else if (errno == ENAMETOOLONG)
		ft_printf_fd(2, "minishell: %s : File name too long\n", cmd);
	else if (errno == EPERM)
		ft_printf_fd(2, "minishell: %s : Operation not permitted\n", path);
	else if (errno == E2BIG)
		ft_printf_fd(2, "minishell: Arg list too long\n");
	else if (errno == ENOEXEC)
		ft_printf_fd(2, "minishell: Exec format error\n");
	else if (errno == ELIBEXEC)
		ft_printf_fd(2, "minishell: Cannot execute binary file\n");
	else if (errno == ENOTDIR)
		ft_printf_fd(2, "minishell: %s : Not a directory\n", path);
}

static int	upd_errno(struct stat *st, char *path)
{
	char	*cpy_path;
	int		r_value;

	r_value = 0;
	cpy_path = ft_strdup(path);
	if (cpy_path[ft_strlen(cpy_path) - 1] == '/')
		cpy_path[ft_strlen(cpy_path) - 1] = 0;
	if (ft_strchr(path, '/') == NULL)
		errno = ENOENT;
	else if (path[ft_strlen(path) - 1] == '/'
		&& !(S_ISDIR(st->st_mode)) && access(cpy_path, F_OK) != -1)
		errno = ENOTDIR;
	else if (access(path, F_OK) == -1)
		errno = ENOENT;
	else if (S_ISDIR(st->st_mode))
		errno = EISDIR;
	else if (access(path, X_OK) == -1)
		errno = EACCES;
	else
		r_value = 1;
	free(cpy_path);
	return (r_value);
}

void	launch_execve(t_sh_data *sh, char *path, char **args)
{
	char		**new_env;
	struct stat	*st;

	st = ft_calloc(1, sizeof(struct stat));
	if (st == NULL)
		return ;
	new_env = list_to_envp(sh);
	re_init_def_signals();
	stat(path, st);
	if (upd_errno(st, path) == 1)
		execve(path, args, new_env);
	else
		print_error_execve(args[0], path);
	free_tabchar(new_env);
	free(st);
}

int	child_management(t_sh_data *sh_data, int p_out[2],
							int p_in[2], t_bloc_cmd	*bloc_data)
{
	int		r_value;

	r_value = 127;
	pipes_redir(sh_data, p_out, p_in, bloc_data);
	if (bloc_data->id > 0)
		close_pipes(p_in);
	close_pipes(p_out);
	if (bloc_data->cmd != NULL)
	{
		if (bloc_data->builtin != BT_NO)
			r_value = exec_bt(sh_data, bloc_data);
		else if (bloc_data->cmd->name != NULL && bloc_data->cmd->name[0] != 0)
			launch_execve(sh_data, bloc_data->cmd->path, bloc_data->cmd->args);
		else if (bloc_data->cmd->name != NULL && bloc_data->cmd->name[0] == 0)
			print_error(ER_CMD_N_FOUND, bloc_data->cmd, NULL);
		if (errno == EACCES || errno == EISDIR || errno == ENOTDIR)
			r_value = 126;
	}
	else
		r_value = 0;
	free_sh_data(sh_data);
	close(1);
	close(2);
	exit (r_value);
}
