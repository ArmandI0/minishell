/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/14 18:52:11 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	launch_execve(t_sh_data *sh, char *path, char **args)
{
	char		**new_env;
	struct stat	st;

	new_env = list_to_envp(sh);
	re_init_def_signals();
	stat(path, &st);
	if (S_ISDIR(st.st_mode))
		errno = EISDIR;
	else
		execve(path, args, new_env);
	perror("Error execve");
	free_tabchar(new_env);
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
		if (errno == EACCES || errno == EISDIR)
			r_value = 126;
	}
	else
		r_value = 0;
	free_sh_data(sh_data);
	close(1);
	close(2);
	exit (r_value);
}
