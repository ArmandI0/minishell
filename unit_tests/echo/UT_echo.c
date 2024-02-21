/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/02/21 12:02:18 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tabchar(char **tabchar)
{
	int	i;

	i = 0;
	if (tabchar != NULL)
	{
		while (tabchar[i] != NULL)
		{
			free(tabchar[i]);
			i++;
		}
		free(tabchar);
	}
}

void free_cmd(t_cmd *cmd)
{
	free(cmd->name);
	free(cmd->path);
	free_tabchar(cmd->args);
}

static void	init_cmd(t_cmd *cmd)
{
	cmd->argc = 4;
	cmd->name = ft_strdup("echo");
	cmd->args = malloc(sizeof(char *) * (cmd->argc + 1));
	cmd->args[0] = ft_strdup("echo");
	cmd->args[1] = ft_strdup("-n");
	cmd->args[2] = ft_strdup("sdfsdfsdf");
	cmd->args[3] = ft_strdup("-n");
	cmd->args[cmd->argc] = NULL;
	cmd->path = ft_strdup("");
}

int main(void)
{
	t_cmd	echo;

	init_cmd(&echo);
	bt_echo(&echo);
	free_cmd(&echo);
	return (0);
}
