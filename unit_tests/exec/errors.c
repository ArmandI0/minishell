/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/02/26 17:53:19 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(t_errors error, t_bloc_cmd *cmd_data)
{
	if (error == ER_CMD_N_FOUND)
	{
		ft_putstr_fd("Error command '", 2);
		ft_putstr_fd(cmd_data->cmd.name, 2);
		ft_putstr_fd("' not found\n", 2);
	}
}
