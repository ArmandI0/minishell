/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/18 21:02:13 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	init_list_cmds()
{
	return (0);
}

int	prompt_rl(t_sh_data *sh_data)
{
	char		*line;
	t_list_cmd	*list_cmds;
	int			r_exec;
	
	r_exec = 2;
	line = NULL;
	while (r_exec == 2)
	{
		if (line != NULL)
			free(line);
		line = readline("minishell>");
		add_history(line);
		if (init_list_cmds(&list_cmds) == 0);	//send line to parsing here
			r_exec = exec_cmds_loop(sh_data, list_cmds);
	}
	if (line != NULL)
		free(line);
	return (r_exec);	
}
