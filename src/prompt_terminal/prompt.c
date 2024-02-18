/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/18 16:06:33 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prompt_rl(t_sh_data *sh_data)
{
	char	*line;

	(void)sh_data;
	line = readline("minishell>");
	while (1)
	{
		add_history(line);
		//send line to parsing here
		//send line to exec here
		if (line != NULL)
			free(line);
		line = readline("minishell>");
	}
	if (line != NULL)
		free(line);
}
