/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/25 21:41:36 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	upd_r_value_if_sigint(t_sh_data *sh_data)
{
	if (g_sign_received == 1)
	{
		g_sign_received = 0;
		sh_data->return_value = 130;
	}
}

int	prompt_rl(t_sh_data *sh_data)
{
	char		*line;

	line = NULL;
	while (1)
	{
		sh_data->bloc = NULL;
		line = readline("minishell>");
		if (line == NULL)
			break ;
		upd_r_value_if_sigint(sh_data);
		add_history(line);
		if (parsing(line, sh_data) == TRUE)
			exec_cmds_loop(sh_data);
		init_signals();
		free (line);
	}
	if (line != NULL)
		free(line);
	if (g_sign_received == 1)
		return (130);
	return (0);
}
