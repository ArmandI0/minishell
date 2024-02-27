/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 13:49:21 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Fonction de parsing de test simple */
static int	init_bloc_cmds(t_sh_data *sh, char *line)
{
	(void)sh;
	(void)line;

	sh->cmd_bloc1 = ft_calloc(1, sizeof(t_bloc_cmd));

	sh->cmd_bloc1->builtin = BT_ECHO;
	sh->cmd_bloc1->cmd.name = ft_strdup("echo");
	sh->cmd_bloc1->cmd.path = ft_strdup("");
	sh->cmd_bloc1->cmd.args = ft_calloc(4, sizeof(char *));
	sh->cmd_bloc1->cmd.args[0] = ft_strdup("echo");
	sh->cmd_bloc1->cmd.args[1] = ft_strdup("sdsd");
	sh->cmd_bloc1->cmd.args[2] = ft_strdup("-n");
	return (0);
}

int	prompt_rl(void)
{
	char		*line;
	int			r_exec;
	t_lexer		*lx;
	
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
		free_list_cmd(sh_data->cmd_bloc1);	
		free (line);
	}
	if (line != NULL)
		free(line);
	return (r_exec);	
}
