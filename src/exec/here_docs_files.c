/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/24 21:00:30 by nledent          ###   ########.fr       */
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
			if (next_redir->type == HEREDOC && next_redir->file_path != NULL
				&& ft_strncmp("/tmp/tmp_hdoc_", next_redir->file_path, 14) == 0)
			{
				fpath = ft_strdup(next_redir->file_path);
				unlink(fpath);
				free(fpath);
			}
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	}
}

static char	*add_char_str(char *str, char c)
{
	char	*str_char;
	int		i;

	i = 0;
	str_char = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (str[i] != 0)
	{
		str_char[i] = str[i];
		i++;
	}
	str_char[i] = c;
	str_char[i + 1] = 0;
	free(str);
	return (str_char);
}

static char	*search_av_filename(void)
{
	char	*filename;
	int		len;

	filename = ft_strdup("/tmp/tmp_hdoc_A");
	len = ft_strlen(filename);
	while (access(filename, F_OK) == 0)
	{
		if (filename[len - 1] == 'Z')
		{
			filename = add_char_str(filename, 'A');
			len++;
		}
		else if (filename[len - 1] >= 'A' && filename[len - 1] < 'Z')
			(filename[len - 1])++;
	}
	return (filename);
}

void	create_hdocs_files(t_bloc_cmd *cmds)
{
	t_bloc_cmd	*next_cmd;
	t_redir		*next_redir;
	int			fhdoc;

	next_cmd = cmds;
	while (next_cmd != NULL)
	{
		next_redir = next_cmd->redir;
		while (next_redir != NULL)
		{
			if (next_redir->type == HEREDOC)
			{
				next_redir->file_path = search_av_filename();
				fhdoc = open(next_redir->file_path, O_WRONLY | O_CREAT, 0777);
				close (fhdoc);
			}
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	}
}

void	hdoc_to_file(char *hdoc, char *file_path)
{
	int		output;

	output = open(file_path, O_WRONLY | O_CREAT, 0777);
	ft_putstr_fd(hdoc, output);
	close (output);
	free(hdoc);
}
