/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/03/02 16:58:07 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* static t_bloc_cmd	*init_cmd3(t_bloc_cmd *prev_el)
{
	t_bloc_cmd *el_new;

	el_new = ft_calloc(1, sizeof(t_bloc_cmd));
	if (prev_el != NULL)
		prev_el->next = el_new;

	el_new->cmd = ft_calloc(1, sizeof(t_cmd));	
	el_new->cmd->name = ft_strdup("cat");
	el_new->cmd->path = ft_strdup("/bin/cat");
	el_new->cmd->args = ft_calloc(3, sizeof(char *));
	el_new->cmd->args[0] = ft_strdup("cat");
	el_new->cmd->args[1] = ft_strdup("-e");
	el_new->cmd->argc = 2;

	el_new->builtin = BT_NO;

	el_new->id = 2;
	
	el_new->redir = ft_calloc(1, sizeof(t_redir));
	el_new->redir->in_out = 1;
	el_new->redir->app_mod_hdoc = 0;
	el_new->redir->file_path = ft_strdup("outfile_cat");

  	el_new->redir->next = ft_calloc(1, sizeof(t_redir));
	el_new->redir->next->in_out = 1;
	el_new->redir->next->app_mod_hdoc = 1;
	el_new->redir->next->file_path = ft_strdup("outfile2");
	el_new->redir->next->next = NULL;
	
	el_new->next = NULL;

	return(el_new);
}

static t_bloc_cmd	*init_cmd2(t_bloc_cmd *prev_el)
{
	t_bloc_cmd *el_new;

	el_new = ft_calloc(1, sizeof(t_bloc_cmd));
	if (prev_el != NULL)
		prev_el->next = el_new;
	el_new->cmd = ft_calloc(1, sizeof(t_cmd));	
	el_new->cmd->name = ft_strdup("cd");
	el_new->cmd->path = ft_strdup("");
	el_new->cmd->args = ft_calloc(3, sizeof(char *));
	el_new->cmd->args[0] = ft_strdup("cd");
	el_new->cmd->args[1] = ft_strdup("..");
	el_new->cmd->argc = 2;

	el_new->builtin = BT_CD;

	el_new->id = 1;
	
 	el_new->redir = ft_calloc(1, sizeof(t_redir));
	el_new->redir->in_out = 1;
	el_new->redir->app_mod_hdoc = 0;
	el_new->redir->file_path = ft_strdup("outfile");

 	el_new->redir->next = ft_calloc(1, sizeof(t_redir));
	el_new->redir->next->in_out = 1;
	el_new->redir->next->app_mod_hdoc = 1;
	el_new->redir->next->file_path = ft_strdup("outfile2");
	el_new->redir->next->next = NULL; 
	
	el_new->next = NULL;

	return(el_new);
} */

static t_bloc_cmd	*init_cmd1(t_bloc_cmd *prev_el)
{
	t_bloc_cmd *el_new;

	el_new = ft_calloc(1, sizeof(t_bloc_cmd));
	if (prev_el != NULL)
		prev_el->next = el_new;
	el_new->cmd = ft_calloc(1, sizeof(t_cmd));	
	el_new->cmd->name = ft_strdup("cd");
	el_new->cmd->path = ft_strdup("");
	el_new->cmd->args = ft_calloc(3, sizeof(char *));
	el_new->cmd->args[0] = ft_strdup("cd");
	el_new->cmd->args[1] = ft_strdup("~");
	el_new->cmd->argc = 2;

	el_new->builtin = BT_CD;

	el_new->id = 0;
	
 	el_new->redir = ft_calloc(1, sizeof(t_redir));
	el_new->redir->in_out = 0;
	el_new->redir->app_mod_hdoc = 1;
	el_new->redir->lim_hdoc = ft_strdup("123");

/* 	el_new->redir = ft_calloc(1, sizeof(t_redir));
	el_new->redir->in_out = 0;
	el_new->redir->app_mod_hdoc = 1;
	el_new->redir->next = NULL;*/
	
	el_new->next = NULL;

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
	t_sh_data	sh_data;
	t_bloc_cmd	*el1;
 	t_bloc_cmd	*el2;
	t_bloc_cmd	*el3;

	init_shell_data(argc, argv, envp, &sh_data);
	envp_to_list(&sh_data);
	el1 = init_cmd1(NULL);
/* 	el2 = init_cmd2(el1);
	el3 = init_cmd3(el2); */
	(void)el2;
	(void)el3;
	sh_data.cmd_bloc1 = el1;
	exec_cmds_loop(&sh_data);
	free_list_cmd(el1);
	free_env_var(sh_data.env_var1);
	printf("retour value : %d\n", sh_data.return_value);
	return (0);
}
