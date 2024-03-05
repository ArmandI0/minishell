/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/05 12:32:39 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Fonction de parsing de test simple */
static int	init_bloc_cmds(t_sh_data *sh, char *line)
{

	if(parsing(line, sh) == FALSE)
		return (1);
	return (0);
}

int	prompt_rl(t_sh_data *sh_data)
{
	char		*line;
	int			r_exec;
	
	r_exec = 2;
	line = NULL;
	while (1)
	{
		line = readline("minishell>");
		if (line == NULL)
			break;
		add_history(line);
		if (init_bloc_cmds(sh_data, line) == 0)	//send line to parsing here
			r_exec = exec_cmds_loop(sh_data);
		if (sh_data->bloc != NULL)
		{
			free_list_cmd(sh_data->bloc);	
			sh_data->bloc = NULL;
		}
		free (line);
	}
	if (line != NULL)
		free(line);
	return (r_exec);	
}
