/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/18 21:43:11 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/* 
void	close_pipes(int pipe_x[2])
{
	close(pipe_x[0]);
	close(pipe_x[1]);
}

static void	init_input(t_pipex *p, int pipe1[2], int pipe2[2])
{
	int	input;

	input = open(p->argv[1], O_RDONLY);
	if (input == -1)
	{
		perror("Error");
		if (p->cmd_nb > 0)
			close_pipes(pipe1);
		close_pipes(pipe2);
		ft_free_split(p->cmds);
		exit(1);
	}
	else
	{
		dup2(input, STDIN_FILENO);
		dup2(pipe2[1], STDOUT_FILENO);
		close(input);
	}
}

static void	init_output(t_pipex *p, int pipe1[2], int pipe2[2])
{
	int		output;
	char	*path;

	path = p->argv[p->argc - 1];
	if (ft_strncmp(p->argv[1], "here_doc", 9) == 0)
		output = open(path, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		output = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (output == -1)
	{
		perror("Error");
		if (p->cmd_nb > 0)
			close_pipes(pipe1);
		close_pipes(pipe2);
		ft_free_split(p->cmds);
		exit(1);
	}
	else
	{
		dup2(pipe1[0], STDIN_FILENO);
		dup2(output, STDOUT_FILENO);
		close(output);
	}
}

void	pipes_management(int pipe1[2], int pipe2[2], t_pipex *p)
{
	if (p->cmd_nb == 0 && ft_strncmp(p->argv[1], "here_doc", 9) != 0)
		init_input(p, pipe1, pipe2);
	else if (p->cmd_nb == 0 && ft_strncmp(p->argv[1], "here_doc", 9) == 0)
		dup2(pipe2[1], STDOUT_FILENO);
	else if (p->cmd_nb == (p->tot_cmds - 1))
		init_output(p, pipe1, pipe2);
	else
	{
		dup2(pipe1[0], STDIN_FILENO);
		dup2(pipe2[1], STDOUT_FILENO);
	}
}
 */