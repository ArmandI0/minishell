/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tmp_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/02/24 17:32:15 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_tmp_hdocs(t_sh_data *sh)
{
	t_list_cmd	*next_cmd;
	t_redir		*next_redir;

	next_cmd = sh->cmd_bloc1;
	while (next_cmd != NULL)
	{
		next_redir = next_cmd->redir;
		while (next_redir != NULL)
		{
			if (next_redir->in_out == 0 && next_redir->app_mod_hdoc == 1
				&& ft_strncmp("tmp_hdoc_", next_redir->file_path, 9) == 0)
					unlink(next_redir->file_path);
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	}	
}
