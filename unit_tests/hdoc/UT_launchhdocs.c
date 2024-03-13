/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_launchhdocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/03/12 11:44:55 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bloc_cmd	*init_cmd(t_bloc_cmd *prev_el, char *limiter)
{
	t_bloc_cmd *el_new;
	int	i;

	i=0;
	el_new = ft_calloc(1, sizeof(t_bloc_cmd));
	el_new->cmd = ft_calloc(1, sizeof(t_cmd));
	if (prev_el != NULL)
		prev_el->next = el_new;
	el_new->id=i;
	if (limiter != NULL)
	{
		el_new->redir = ft_calloc(1, sizeof(t_redir));
		el_new->redir->lim_hdoc=ft_strdup(limiter);
		el_new->redir->next=NULL;
		el_new->redir->type=HEREDOC;
	}
	return(el_new);
}
static void	init_shell_data(int ac, char **av, char **envp, t_sh_data *sh_data)
{
	sh_data->ac = ac;
	sh_data->av = av;
	sh_data->envp = envp;
	sh_data->n_env_var = 0;
	sh_data->env_var1 = NULL;
	
}

int main(int argc, char **argv, char **envp)
{
	t_bloc_cmd	*el1;
	t_bloc_cmd	*el2;
	t_bloc_cmd	*el3;
	t_bloc_cmd	*next_cmd;
	t_redir		*next_redir;
	t_sh_data	sh;

	init_shell_data(argc, argv, envp, &sh);
	el1=NULL;
	el1=init_cmd(NULL, "000");
	el2=init_cmd(el1, NULL);
	el3=init_cmd(el2, "123");
	(void)el2;
	(void)el3;
	sh.bloc = el1;
	sigint_hdoc();
	launch_hdocs(&sh, el1);
	next_cmd = el1;
	(void)next_redir;
	(void)next_cmd;
/* 	while (next_cmd != NULL)
	{
		next_redir = next_cmd->redir;
		while (next_redir != NULL)
		{
			if (next_redir->in_out == 0 && next_redir->app_mod_hdoc == 1)
			{
				printf("\ncmd id %d : here doc : ", next_cmd->id);
				printf("%s", next_redir->file_path);
			}
			next_redir = next_redir->next;
		}
		next_cmd = next_cmd->next;
	} */
	del_tmp_hdocs(&sh);
	free_list_cmd(el1);
	free(sh.dir_tmp_files);
	return (0);
}
