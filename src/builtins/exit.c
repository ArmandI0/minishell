/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/06 21:51:24 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    bt_exit(t_sh_data *sh, t_cmd *cmd)
{
	int	r_value;

	r_value = 1;
	if (cmd->argc > 2)
		print_error(ER_TOO_MANY_ARGS, cmd, NULL);
	else if (cmd->argc == 1)
		r_value = 0;
	else if (cmd->argc == 2)
		r_value = ft_atoi(cmd->args[1]);
	if (r_value == 1)
		return (r_value);
	else
	{
		ft_printf_fd(1, "exit\n");
		free_sh_data(sh);
		exit (r_value);
	}
}
