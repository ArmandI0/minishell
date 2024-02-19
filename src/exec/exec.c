/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/18 21:35:53 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static void	exec_cmd(t_pipex *pip)
{
	char	**args;
	int		i;

	i = pip->cmd_nb;
	args = 0;
	args = ft_split(pip->argv[i + 2], ' ');
	if (args == NULL)
		ft_exit2(6, pip->cmds);
	if (ft_strncmp(pip->argv[1], "here_doc", 9) == 0)
		execve(pip->cmds[i - 1], args, pip->env);
	else
		execve(pip->cmds[i], args, pip->env);
	ft_free_split(pip->cmds);
	ft_free_split(args);
}

static void	pipes_trsf(t_pipex *pip, int pipe1[2], int pipe2[2])
{
	if (pip->cmd_nb > 0)
		close_pipes(pipe1);
	pipe1[0] = pipe2[0];
	pipe1[1] = pipe2[1];
}

static void	child_management(t_pipex *pip, int p1[2], int p2[2], char *hdoc)
{
	int	i;

	if (ft_strncmp(pip->argv[1], "here_doc", 9) == 0)
		i = pip->cmd_nb - 1;
	else
		i = pip->cmd_nb;
	pipes_management(p1, p2, pip);
	if (pip->cmd_nb > 0)
		close_pipes(p1);
	close_pipes(p2);
	if (ft_strncmp(pip->argv[1], "here_doc", 9) == 0 && pip->cmd_nb == 0)
		put_here_doc(hdoc, STDOUT_FILENO, pip);
	else if (pip->cmds[i][0] != 0)
		exec_cmd(pip);
	else if (pip->cmds[i][0] == 0)
		ft_putstr_fd("Error command not found\n", 2);
	else
		perror("Error execve");
	ft_free_split(pip->cmds);
	exit(1);
} */

static void	wait_all_sons(t_list_cmd *list_cmds)
{
	t_list_cmd	*next;

	next = list_cmds;
	while (next != NULL)
	{
		waitpid(-1, NULL, 0);
		next = next->next;
	}
}

int	exec_cmds_loop(t_sh_data *sh_data, t_list_cmd *list_cmds)
{
	int			pipe_out[2];
	int			pipe_in[2];
	t_list_cmd	*next;
	pid_t		pid;

	pid = 0;
	next = list_cmds;
	launch_hdocs(list_cmds);
	while (next != NULL)
	{
		pipe(pipe_out);
		pid = fork();
		if (pid < 0 || pipe_out < 0)
			return (1);
		else if (pid == 0)
			child_management(sh_data, pipe_out, pipe_in, next);
		pipes_trsf(next->id, pipe_out, pipe_in);
		next = next->next;
	}
	close_pipes(pipe_out);
	wait_all_sons(list_cmds);
	return (2);
}
