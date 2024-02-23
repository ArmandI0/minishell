/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/02/23 17:12:40 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list_cmd	*init_cmd1(t_list_cmd *prev_el)
{
	t_list_cmd *el_new;

	el_new = ft_calloc(1, sizeof(t_list_cmd));
	if (prev_el != NULL)
		prev_el->next = el_new;
	el_new->cmd.name = ft_strdup("cat");
	el_new->cmd.path = ft_strdup("/bin/cat");
	el_new->cmd.args = ft_calloc(2, sizeof(char *));
	el_new->cmd.args[0] = ft_strdup("/bin/cat");
	el_new->cmd.argc = 1;

	el_new->builtin = BT_NO;

	el_new->id = 0;
	
	el_new->redir = ft_calloc(1, sizeof(t_redir));
	//el_new->redir->in_out = 0;
	el_new->redir->in_out = 1;
	el_new->redir->app_mod_hdoc = 0;
	el_new->redir->file_path = ft_strdup("outfile");
	//el_new->redir->lim_hdoc = ft_strdup("123");
	el_new->redir->next = NULL;
	
	el_new->next = NULL;
	return(el_new);
}

static void	init_shell_data(int ac, char **av, char **envp, t_sh_data *sh_data)
{
	sh_data->ac = ac;
	sh_data->av = av;
	sh_data->envp = envp;
	sh_data->env_var1 = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_sh_data	sh_data;
	t_list_cmd	*el1;
/* 	t_list_cmd	*el2;
	t_list_cmd	*el3; */

	init_shell_data(argc, argv, envp, &sh_data);
	el1 = NULL;
	el1 = init_cmd1(NULL);
	sh_data.cmd_bloc1 = el1;
/* 	el2=init_cmd2(el1);
	el3=init_cmd3(el2);
	(void)el2;
	(void)el3; */
	exec_cmds_loop(&sh_data, el1);
	free_list_cmd(el1);
	return (0);
}
