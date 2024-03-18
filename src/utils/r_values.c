/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_values.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 14:58:37 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_r_values(int pid, t_sh_data *sh)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		sh->return_value =	WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sh->return_value =	128 + WTERMSIG(status);
		ft_printf_fd(1,"\n");
	}
}
