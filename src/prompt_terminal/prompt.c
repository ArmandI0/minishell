/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/15 17:52:59 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	prompt_rl(void)
{
	char	*line;

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
