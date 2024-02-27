/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/27 12:23:52 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	init_bloc_cmds(t_bloc_cmd **cmds)
// {
// 	(void)cmds;
// 	return (0);
// }

int	prompt_rl(void)
{
	char		*line;
	//t_bloc_cmd	**list_cmds = NULL;
	int			r_exec;
	t_lexer		*lx;
	
	r_exec = 2;
	line = NULL;
	while (r_exec == 2)
	{
		if (line != NULL)
			free(line);
		line = readline("minishell>");
		lx = lexing(line);
		//parsing(lx);
		add_history(line);
		//if (init_bloc_cmds(list_cmds) == 0)	//send line to parsing here
	}
	if (line != NULL)
		free(line);
	return (r_exec);	
}
