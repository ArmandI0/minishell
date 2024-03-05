/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 12:09:19 by nledent           #+#    #+#             */
/*   Updated: 2024/03/05 15:54:36 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
/* 	else if (cmd_bloc->builtin == BT_UNSET)
		r_value = bt_cd(sh_data, cmd_bloc->cmd);
	else if (cmd_bloc->builtin == BT_EXIT)
		r_value = bt_cd(sh_data, cmd_bloc->cmd); */
	return (r_value);
}
