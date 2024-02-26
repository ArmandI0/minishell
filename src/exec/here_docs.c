/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/26 17:53:19 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* NB : possibility of implementing variables in here docs */
static char	*ft_here_doc(char *limiter)
{
	char	*here_doc;
	char	*line;

	here_doc = ft_strdup("");
	limiter = ft_fstrjoin(limiter, ft_strdup("\n"));
	line = ft_strdup("");
	ft_putstr_fd(">", STDOUT_FILENO);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		if (line[0] != 0)
			ft_putstr_fd(">", STDOUT_FILENO);
		here_doc = ft_fstrjoin(here_doc, line);
		line = get_next_line(0);
		if (line == NULL)
		{
			line = ft_strdup(limiter);
			printf("\nminishell warning : here_doc stopped by EOF (ctrl+d)\n");
		}
	}
	free(line);
	free(limiter);
	return (here_doc);
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

static char	*hdoc_to_file(char *hdoc)
{
	int		output;
	char	*filename;
	int		len;

	filename = ft_strdup("tmp_hdoc_A");
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
	output = open(filename, O_WRONLY | O_CREAT, 0777);
	ft_putstr_fd(hdoc, output);
	close (output);
	free(hdoc);
	return (filename);
}

void	launch_hdocs(t_bloc_cmd *cmds)
{
	char		*path_hdoc;
	char		*hdoc;
	t_bloc_cmd	*next_cmd;
	t_redir		*next_redir;

	next_cmd = cmds;
	while (next_cmd != NULL)
	{
		next_redir = next_cmd->redir;
		while (next_redir != NULL)
		{
			if (next_redir->in_out == 0 && next_redir->app_mod_hdoc == 1)
			{
				hdoc = ft_here_doc(next_redir->lim_hdoc);
				path_hdoc = hdoc_to_file(hdoc);
				next_redir->file_path = path_hdoc;
			}
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	}
}
