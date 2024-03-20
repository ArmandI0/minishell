/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/20 13:33:03 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_r_exit_digit(char *str)
{
	int	i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != 0)
		{
			if (str[i] < '0' || str[i] > '9')
				return (0);
			i++;
		}
	}
	return (1);
}

int	bt_exit(t_sh_data *sh, t_cmd *cmd)
{
	int	r_value;

	r_value = 1;
	if (cmd->argc > 1 && is_r_exit_digit(cmd->args[1]) == 0)
		r_value = 2;
	else if (cmd->argc > 2 && is_r_exit_digit(cmd->args[1]))
		print_error(ER_TOO_MANY_ARGS, cmd, NULL);
	else if (cmd->argc == 1)
		r_value = 0;
	else if (cmd->argc == 2)
	{
		if (is_r_exit_digit(cmd->args[1]))
			r_value = ft_atoi(cmd->args[1]);
		else
			r_value = 2;
	}
	ft_printf_fd(1, "exit\n");
	if (r_value == 1)
		return (r_value);
	if (r_value == 2)
		print_error(ER_EXIT, cmd, NULL);
	free_sh_data(sh);
	exit (r_value);
}
