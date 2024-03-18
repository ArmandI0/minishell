/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:09:19 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 15:14:11 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	re_init_fds(int fdin, int fdout)
{
	dup2(fdin, STDIN_FILENO);
	dup2(fdout, STDOUT_FILENO);
}

static void	save_fds(int *fdin, int *fdout)
{
	*fdin = dup(STDIN_FILENO);
	*fdout = dup(STDOUT_FILENO);
}

int	exec_bt(t_sh_data *sh_data, t_bloc_cmd *cmd_bloc)
{
	int	r_value;

	r_value = 0;
	if (cmd_bloc->builtin == BT_ECHO)
		bt_echo((cmd_bloc->cmd));
	else if (cmd_bloc->builtin == BT_ENV)
		bt_env(sh_data);
	else if (cmd_bloc->builtin == BT_PWD)
		r_value = bt_pwd();
	else if (cmd_bloc->builtin == BT_CD)
		r_value = bt_cd(sh_data, cmd_bloc->cmd);
	else if (cmd_bloc->builtin == BT_EXPORT)
		r_value = bt_export(sh_data, cmd_bloc->cmd);
 	else if (cmd_bloc->builtin == BT_UNSET)
		r_value = bt_unset(sh_data, cmd_bloc->cmd);
	else if (cmd_bloc->builtin == BT_EXIT)
		r_value = bt_exit(sh_data, cmd_bloc->cmd);
	return (r_value);
}

int	one_bloc_bt(t_sh_data *sh_data, t_bloc_cmd *cmd_bloc)
{
	int	r_value;
	int	fdin;
	int	fdout;

	r_value = 0;
	if (cmd_bloc->builtin == BT_EXIT)
		r_value = exec_bt(sh_data, cmd_bloc);
	else
	{
		save_fds(&fdin, &fdout);
		if (redirections(cmd_bloc) >= 4)
			r_value = 1;
		else
			r_value = exec_bt(sh_data, cmd_bloc);	
		re_init_fds(fdin, fdout);
	}
	return (r_value);
}
