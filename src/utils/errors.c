/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/02/29 21:56:21 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(t_errors error, t_cmd *cmd)
{
	if (error == ER_CMD_N_FOUND)
	{
		ft_putstr_fd("Error : command '", 2);
		ft_putstr_fd(cmd->name, 2);
		ft_putendl_fd("' not found", 2);
	}
	else if (error == ER_NO_ARG)
		ft_putendl_fd("Error : No arguments are required", 2);
	else if (error == ER_CD_DIR_FILE_N_FOUND)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}	
	else if (error == ER_CD_TOO_MANY_ARGS)
		ft_putendl_fd("bash: cd: Too many arguments", 2);
}		
