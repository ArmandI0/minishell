/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_tmp_hdoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:59:30 by nledent           #+#    #+#             */
/*   Updated: 2024/03/03 18:28:42 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_tmp_hdocs(t_sh_data *sh)
{
	t_bloc_cmd	*next_cmd;
	t_redir		*next_redir;
	char		*fpath;

	fpath = NULL;
	next_cmd = sh->bloc;
	while (next_cmd != NULL)
	{
		next_redir = next_cmd->redir;
		while (next_redir != NULL)
		{
			if (next_redir->type == HEREDOC
				&& ft_strncmp("tmp_hdoc_", next_redir->file_path, 9) == 0)
				{
					fpath = ft_strdup(next_redir->file_path);
					fpath = ft_fstrjoin(ft_strdup("/"), fpath);
					fpath = ft_fstrjoin(ft_strdup(sh->dir_tmp_files), fpath);
					unlink(fpath);
					free(fpath);
				}
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	}
}
