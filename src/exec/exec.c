/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 15:43:07 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	pipes_trsf(int id, int p_out[2], int p_in[2])
{
	if (id > 0)
		close_pipes(p_in);
	p_in[0] = p_out[0];
	p_in[1] = p_out[1];
}

static void	wait_all_sons(t_sh_data *sh,t_bloc_cmd *list_cmds)
{
	t_bloc_cmd	*bloc;

	bloc = list_cmds;
	while (bloc != NULL)
	{
		check_r_values(bloc->pid, sh);
		bloc = bloc->next;
	}
}

static int	loop_pipes_exec(t_sh_data *sh_data, t_bloc_cmd	*bloc)
{
	int		pipe_out[2];
	int		pipe_in[2];
	int		r_pipe;
	pid_t	pid;

	pid = 0;
	r_pipe = 0;
	signal(SIGINT, SIG_IGN);
	while (bloc != NULL)
	{
		r_pipe = pipe(pipe_out);
		pid = fork();
		if (pid < 0 || r_pipe < 0)
			return (1);
		else if (pid == 0)
			child_management(sh_data, pipe_out, pipe_in, bloc);
		else
			bloc->pid = pid;
		pipes_trsf(bloc->id, pipe_out, pipe_in);
		bloc = bloc->next;
	}
	close_pipes(pipe_out);
	wait_all_sons(sh_data, sh_data->bloc);
	init_signals();
	return (0);
}

int	exec_cmds_loop(t_sh_data *sh_data)
{
	t_bloc_cmd	*next;

	if (sh_data->bloc == NULL)
		return (2);
	next = sh_data->bloc;
	fork_hdocs(sh_data, sh_data->bloc);
	if (sh_data->return_value != 0)
		sign_received = 1;
	if (next->next == NULL && next->builtin != BT_NO && sign_received != 1)
		sh_data->return_value = one_bloc_bt(sh_data, next);
	else if (sign_received != 1)
		loop_pipes_exec(sh_data, next);
	del_tmp_hdocs(sh_data);
	free_list_cmd(sh_data->bloc);
	if (sh_data->dir_tmp_files != NULL)
	{
		free (sh_data->dir_tmp_files);	
		sh_data->dir_tmp_files = NULL;
	}
	sign_received = 0;
	return (2);
}
