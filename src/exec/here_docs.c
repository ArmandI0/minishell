/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/12 19:23:30 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*loop_hdoc(char * limiter, t_sh_data *data)
{
	char	*line;
	char	*here_doc;

	here_doc = ft_strdup("");
	line = ft_strdup("");
	while (sign_received != 1 && ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		if (line[0] != 0)
			ft_putstr_fd(">", STDOUT_FILENO);
		here_doc = ft_fstrjoin(here_doc, line);
		line = get_next_line(0);
		if (line == NULL && sign_received != 1)
		{
			line = ft_strdup(limiter);
			print_error(ER_HDOC_EOF, NULL, NULL);
		}
		line = expand_heredoc(line, data);
	}
	if (line != NULL)
		free(line);	
	return (here_doc);
}

/* NB : possibility of implementing variables in here docs */
static char	*ft_here_doc(char *limiter, t_sh_data *data)
{
	char	*here_doc;
	char	*lim_backn;

	here_doc = NULL;
	if (sign_received != 1)
	{
		lim_backn = ft_strjoin(limiter, "\n", 0);
		ft_putstr_fd(">", STDOUT_FILENO);
		here_doc = loop_hdoc(lim_backn, data);
		free(lim_backn);
	}
	return (here_doc);
}

static void	launch_hdocs(t_bloc_cmd *cmds, t_sh_data *data)
{
	char		*hdoc;
	t_bloc_cmd	*next_cmd;
	t_redir		*next_redir;

	next_cmd = cmds;
	while (next_cmd != NULL)
	{
		next_redir = next_cmd->redir;
		while (next_redir != NULL)
		{
			if (next_redir->type == HEREDOC)
			{
				hdoc = ft_here_doc(next_redir->lim_hdoc, data);
				hdoc_to_file(hdoc, next_redir->file_path);
			}
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	}
}

void	fork_hdocs(t_sh_data *sh, t_bloc_cmd *cmds)
{
	pid_t	pid;
	int		r;

	r = 0;	
	sh->dir_tmp_files = ft_getcwd();
	create_hdocs_files(cmds);
	pid = fork();
	if (pid == 0)
	{
		sigint_hdoc();
		launch_hdocs(cmds, sh);
		free_sh_data(sh);
		if (sign_received == 1)
			r = 130;
		exit (r);
	}
	else if (pid > 0)
		check_r_values(pid, sh);
}
