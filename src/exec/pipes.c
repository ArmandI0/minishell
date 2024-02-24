/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/24 17:29:18 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes(int pipe_x[2])
{
	close(pipe_x[0]);
	close(pipe_x[1]);
}

static int	init_input(t_redir *redir)
{
	int	input;

	input = open(redir->file_path, O_RDONLY);
	if (input == -1)
	{
		perror("Error");
		return (4);
	}
	else
	{
		dup2(input, STDIN_FILENO);
		close(input);
		return (2);
	}
}

static int	init_output(t_redir *redir)
{
	int		output;

	if (redir->app_mod_hdoc == 1)
		output = open(redir->file_path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		output = open(redir->file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output == -1)
	{
		perror("Error");
		return (4);
	}
	else
	{
		dup2(output, STDOUT_FILENO);
		close(output);
		return (1);
	}
}

/* redirections function
case 1 : no redirections : 				return 0
case 2 : only output redirection : 		return 1
case 3 : only input redirection : 		return 2
case 4 : output & input redirection : 	return 1 + 2 = 3
case 5 : error redirections :		 	return 4 | 5 | 6
*/
static int	redirections(t_list_cmd *bloc_data)
{
	int		r_redir_in;
	int		r_redir_out;
	t_redir	*next;

	r_redir_in = 0;
	r_redir_out = 0;
	next = bloc_data->redir;
	while (next != NULL)
	{
		if (next->in_out == 0)
			r_redir_in = init_input(next);
		else if (next->in_out == 1)
			r_redir_out = init_output(next);
		if (r_redir_in == 4 || r_redir_out == 4)
			break ;
		next = next->next;
	}
	return (r_redir_in + r_redir_out);
}

void	pipes_redir(t_sh_data *sh, int p_out[2], int p_in[2], t_list_cmd *bloc)
{
	if (bloc->next != NULL)
		dup2(p_out[1], STDOUT_FILENO);
	else
	{
		dup2(p_out[1], STDOUT_FILENO);
		dup2(p_in[0], STDIN_FILENO);
	}
	if (redirections(bloc) >= 4)
	{
		if (bloc->id == 0)
			close_pipes(p_in);
		close_pipes(p_out);
		free_list_cmd(sh->cmd_bloc1);
		free_env_var(sh->env_var1);
		exit(1);
	}
}

/*
void	pipes_redir(t_sh_data *sh, int p_out[2], int p_in[2], t_list_cmd *bloc)
{
	int	r_redir;

	r_redir = redirections(bloc);
	if (r_redir >= 4)
	{
		if (bloc->id == 0)
			close_pipes(p_in);
		close_pipes(p_out);
		free_list_cmd(sh->cmd_bloc1);
		free_env_var(sh->env_var1);
		exit(1);
	}
	else if (bloc->id == 0)
	{
		if ((r_redir == 0 || r_redir == 2) && bloc->next != NULL)
			dup2(p_out[1], STDOUT_FILENO);
	}
	else
	{
		if (r_redir == 0 || r_redir == 2)
			dup2(p_out[1], STDOUT_FILENO);
		if (r_redir == 0 || r_redir == 1)
			dup2(p_in[0], STDIN_FILENO);
	}
}
 */