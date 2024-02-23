/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/23 15:04:57 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static void	prepare_new_env(t_sh_data *sh_data)
{
	
} */

static void	pipes_trsf(int id, int p_out[2], int p_in[2])
{
	if (id > 0)
		close_pipes(p_in);
	p_in[0] = p_out[0];
	p_in[1] = p_out[1];
}

static int	child_management(t_sh_data *sh_data, int p_out[2],
							int p_in[2], t_list_cmd	*bloc_data)
{
	int	i;
	//char	**new_env;

	i = bloc_data->id;
	pipes_redir(sh_data, p_out, p_in, bloc_data);
	if (bloc_data->id > 0)
		close_pipes(p_in);
	close_pipes(p_out);
	if (bloc_data->cmd.name != NULL && bloc_data->cmd.name[0] != 0)
	{
		//new_env = prepare_new_env(sh_data);
		execve(bloc_data->cmd.path, bloc_data->cmd.args, sh_data->envp);
		perror("Error execve");
	}
	else if (bloc_data->cmd.name != NULL && bloc_data->cmd.name[0] == 0)
		print_error(ER_CMD_N_FOUND, bloc_data);
	free_list_cmd(sh_data->cmd_bloc1);
	free_env_var(sh_data->env_var1);
	exit (1);
}

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
