/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/27 12:23:52 by aranger          ###   ########.fr       */
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

void	free_redir(t_redir *redir)
{
	t_redir	*next;

	if (redir != NULL)
	{
		next = redir;
		while (next != NULL)
		{
			if (next->file_path != NULL)
				free(next->file_path);
			next = next->next;
		}
		free(redir);
	}
}

void	free_cmd(t_cmd *cmd)
{
	free(cmd->name);
	free(cmd->path);
	free_tabchar(cmd->args);
}

void	free_list_cmd(t_bloc_cmd *cmd_data)
{
	t_bloc_cmd	*next;

	if (cmd_data != NULL)
	{
		next = cmd_data;
		while (next != NULL)
		{	
			free_cmd(&(next->cmd));
			free_redir(next->redir);
			cmd_data = next;
			next = next->next;
			free(cmd_data);
		}
	}
}
