/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/06 14:41:39 by nledent          ###   ########.fr       */
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

static int	child_management(t_sh_data *sh_data, int p_out[2],
							int p_in[2], t_bloc_cmd	*bloc_data)
{
	char	**new_env;
	int		r_value;

	r_value = 1;
	pipes_redir(sh_data, p_out, p_in, bloc_data);
	if (bloc_data->id > 0)
		close_pipes(p_in);
	close_pipes(p_out);
	if (bloc_data->cmd != NULL)
	{
		if (bloc_data->builtin != BT_NO)
			r_value = exec_bt(sh_data, bloc_data);
		else if (bloc_data->cmd->name != NULL && bloc_data->cmd->name[0] != 0)
		{
			new_env = list_to_envp(sh_data);
			execve(bloc_data->cmd->path, bloc_data->cmd->args, new_env);
			perror("Error execve");
			free_tabchar(new_env);
		}
		else if (bloc_data->cmd->name != NULL && bloc_data->cmd->name[0] == 0)
			print_error(ER_CMD_N_FOUND, bloc_data->cmd, NULL);
	}
	free_sh_data(sh_data);
	exit (r_value);
}

static void	wait_all_sons(t_sh_data *sh,t_bloc_cmd *list_cmds)
{
	t_bloc_cmd	*next;
	int			status;

	next = list_cmds;
	while (next != NULL)
	{
		waitpid(-1, &status, 0);
		sh->return_value = status;
		next = next->next;
	}
}

static int	loop_pipes_exec(t_sh_data *sh_data, t_bloc_cmd	*next)
{
	int		pipe_out[2];
	int		pipe_in[2];
	int		r_pipe;
	pid_t	pid;

	pid = 0;
	r_pipe = 0;
	while (next != NULL)
	{
		r_pipe = pipe(pipe_out);
		pid = fork();
		if (pid < 0 || r_pipe < 0)
			return (1);
		else if (pid == 0)
			child_management(sh_data, pipe_out, pipe_in, next);
		pipes_trsf(next->id, pipe_out, pipe_in);
		next = next->next;
	}
	close_pipes(pipe_out);
	wait_all_sons(sh_data, sh_data->bloc);	
	return (0);
}

int	exec_cmds_loop(t_sh_data *sh_data)
{
	t_bloc_cmd	*next;

	if (sh_data->bloc == NULL)
		return (2);
	next = sh_data->bloc;
	launch_hdocs(sh_data, sh_data->bloc);
	if (next->next == NULL && next->builtin != BT_NO)
		sh_data->return_value = one_bloc_bt(sh_data, next);
	else
		loop_pipes_exec(sh_data, next);
	del_tmp_hdocs(sh_data);
	if (sh_data->bloc != NULL)
	{
		free_list_cmd(sh_data->bloc);
		sh_data->bloc = NULL;
	}
	if (sh_data->dir_tmp_files != NULL)
	{
		free (sh_data->dir_tmp_files);	
		sh_data->dir_tmp_files = NULL;
	}
	return (2);
}
