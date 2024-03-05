/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/03/03 21:38:15 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(t_errors error, t_cmd *cmd, char *str)
{
	if (error == ER_CMD_N_FOUND)
		ft_printf_fd(2, "Error : command '%s' not found\n", cmd->name);
	else if (error == ER_NO_ARG)
		ft_putendl_fd("Error : No arguments are required", 2);
	else if (error == ER_CD_DIR_FILE_N_FOUND)
	{
		ft_printf_fd(2, "minishell: %s: %s", cmd->name, cmd->args[1]);
		ft_putendl_fd(": No such file or directory", 2);
	}	
	else if (error == ER_CD_TOO_MANY_ARGS)
		ft_putendl_fd("minishell: cd: Too many arguments", 2);
	else if (error == ER_HDOC_EOF)
		ft_putendl_fd("\nminishell warning : here_doc stopped by EOF (ctrl+d)", 2);
	else if (error == ER_EXPORT)	
		ft_printf_fd(2, "export: not an identifier: %s\n", str);
}		
