/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/03/02 16:18:35 by nledent          ###   ########.fr       */
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
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
	}	
	else if (error == ER_CD_TOO_MANY_ARGS)
		ft_putendl_fd("minishell: cd: Too many arguments", 2);
}		
