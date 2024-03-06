/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/06 21:58:12 by nledent          ###   ########.fr       */
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
	//int			r_exec;
	
	//r_exec = 2;
	line = NULL;
	while (1)
	{
		line = readline("minishell>");
		if (line == NULL)
			break;
		add_history(line);
		ign_sigint();
		if (init_bloc_cmds(sh_data, line) == 0)
			exec_cmds_loop(sh_data);
		init_signals();
		free (line);
	}
	if (line != NULL)
		free(line);
	return (0);	
}
