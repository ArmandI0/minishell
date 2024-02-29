/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_launchhdocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/02/29 21:12:38 by nledent          ###   ########.fr       */
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
	if (cmd->name != NULL)
		free(cmd->name);
	if (cmd->path != NULL)
		free(cmd->path);
	if (cmd->args != NULL)
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

static t_bloc_cmd	*init_cmd(t_bloc_cmd *el1, char *limiter)
{
	t_bloc_cmd *el_new;
	t_bloc_cmd *next;
	int	i;

	i=0;
	el_new = malloc(sizeof(t_bloc_cmd));
	next = el1;
	if (next != NULL)
	{
		i++;
		while (next->next != NULL)
		{
			next=next->next;
			i++;
		}
		next->next = el_new;
	}
	el_new->id=i;
	if (limiter !=NULL)
	{
		el_new->redir = malloc(sizeof(t_redir) * 1);
		el_new->redir->lim_hdoc=ft_strdup(limiter);
		el_new->redir->next=NULL;
		el_new->redir->in_out=0;
		el_new->redir->app_mod_hdoc=1;
	}
	else
		el_new->redir = NULL;
	el_new->cmd->args = NULL;
	el_new->cmd->name = NULL;
	el_new->cmd->path = NULL;
	el_new->next = NULL;
	return(el_new);
}

int main(void)
{
	t_bloc_cmd	*el1;
	t_bloc_cmd	*el2;
	t_bloc_cmd	*el3;
	t_bloc_cmd	*next_cmd;
	t_redir		*next_redir;

	el1=NULL;
	el1=init_cmd(el1, "000");
	el2=init_cmd(el1, NULL);
	el3=init_cmd(el1, "123");
	(void)el2;
	(void)el3;
	launch_hdocs(el1);
	next_cmd = el1;
	while (next_cmd != NULL)
	{
		next_redir = next_cmd->redir;
		while (next_redir != NULL)
		{
			if (next_redir->in_out == 0 && next_redir->app_mod_hdoc == 1)
			{
				printf("\ncmd id %d : here doc : ", next_cmd->id);
				printf("%s", next_redir->file_path);
			}
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	}
	free_list_cmd(el1);
	return (0);
}
