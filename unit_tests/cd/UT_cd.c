/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/02/29 22:05:13 by nledent          ###   ########.fr       */
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
	free(cmd);
}

static t_cmd	*init_cmd(int argc, char **argv)
{
	t_cmd	*cmd;
	int	i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->argc = argc - 1;
	if (argc > 1)
	{
		cmd->name = ft_strdup(argv[1]);
		cmd->args = ft_calloc(argc, sizeof(char *));
		while (i < argc - 1)
		{
			cmd->args[i] = ft_strdup(argv[i + 1]);
			i++;
		}
	}
	cmd->path = ft_strdup("");
	return (cmd);
}

int main(int argc, char **argv)
{
	t_cmd	*cd;

	cd = init_cmd(argc, argv);
	bt_cd(cd);
	free_cmd(cd);
	return (0);
}
