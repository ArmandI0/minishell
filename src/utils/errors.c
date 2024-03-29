/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/03/26 15:36:58 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_error_cd(t_cmd *cmd)
{
	if (errno == EACCES)
	{
		ft_printf_fd(2, "minishell: %s: %s", cmd->name, cmd->args[1]);
		ft_putendl_fd(": Permission denied", 2);
	}
	else
	{
		ft_printf_fd(2, "minishell: %s: %s", cmd->name, cmd->args[1]);
		ft_putendl_fd(": No such file or directory", 2);
	}
}

void	print_error(t_errors error, t_cmd *cmd, char *str)
{
	if (error == ER_CMD_N_FOUND)
		ft_printf_fd(2, "Error : command '%s' not found\n", cmd->name);
	else if (error == ER_NO_ARG)
		ft_putendl_fd("Error : No arguments are required", 2);
	else if (error == ER_CD_DIR_FILE_N_FOUND)
		print_error_cd(cmd);
	else if (error == ER_TOO_MANY_ARGS)
		ft_printf_fd(2, "minishell: %s: too many arguments\n", cmd->name);
	else if (error == ER_HDOC_EOF)
		ft_putendl_fd("\nminishell : here_doc stopped by EOF (ctrl+d)", 2);
	else if (error == ER_EXPORT)
		ft_printf_fd(2, "minishell : export: %s not a valid identifier: \n",
			str);
	else if (error == ER_UNSET)
		ft_printf_fd(2, "unset: %s: invalid parameter name\n", str);
	else if (error == ER_EXIT)
		ft_printf_fd(2, "minishell: %s: %s: numeric argument required\n",
			cmd->name, cmd->args[1]);
}
