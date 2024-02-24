/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/24 15:45:17 by nledent          ###   ########.fr       */
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
			redir = next;
			next = next->next;
			free(redir);
		}
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->name != NULL)
		free(cmd->name);
	if (cmd->path != NULL)
		free(cmd->path);
	if (cmd->args != NULL)
		free_tabchar(cmd->args);
}

void	free_env_var(t_env_var *var1)
{
	t_env_var	*next;

	if (var1 != NULL)
	{
		next = var1;
		while (next != NULL)
		{
			if (next->name != NULL)
				free(next->name);
			if (next->value != NULL)
				free(next->value);
			next->name = NULL;
			next->value = NULL;
			var1 = next;
			next = next->next;
			free (var1);
		}
	}
}

void	free_list_cmd(t_list_cmd *cmd_data)
{
	t_list_cmd	*next;

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
