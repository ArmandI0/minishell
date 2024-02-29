/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_exec_bt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/02/29 21:12:41 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bloc_cmd	*init_cmd1(t_bloc_cmd *prev_el, t_sh_data *sh)
{
	t_bloc_cmd *el_new;
	int			i;

	i = 0;
	el_new = ft_calloc(1, sizeof(t_bloc_cmd));
	if (prev_el != NULL)
		prev_el->next = el_new;
	el_new->cmd->name = ft_strdup(sh->av[1]);
	el_new->cmd->path = ft_strdup("");
	el_new->cmd->args = ft_calloc(sh->ac, sizeof(char *));
	while (i < sh->ac - 1)
	{
		el_new->cmd->args[i] = ft_strdup(sh->av[i + 1]);
		el_new->cmd->argc = i;
		i++;
	}

	if (ft_strncmp(sh->av[1], "echo", 5) == 0)
		el_new->builtin = BT_ECHO;
	else if (ft_strncmp(sh->av[1], "pwd", 4) == 0)
		el_new->builtin = BT_PWD;
	else if (ft_strncmp(sh->av[1], "env", 4) == 0)
		el_new->builtin = BT_ENV;
		
	el_new->id = 0;
	
/* 	el_new->redir = ft_calloc(1, sizeof(t_redir));
	el_new->redir->in_out = 1;
	el_new->redir->app_mod_hdoc = 0;
	el_new->redir->file_path = ft_strdup("outfile"); */

/* 	el_new->redir = ft_calloc(1, sizeof(t_redir));
	el_new->redir->in_out = 0;
	el_new->redir->app_mod_hdoc = 1;
	el_new->redir->lim_hdoc = ft_strdup("123");
	el_new->redir->next = NULL; */
	
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

	if (argc == 1)
		return (1);
	init_shell_data(argc, argv, envp, &sh_data);
	envp_to_list(&sh_data);
	el1 = NULL;
	el1 = init_cmd1(NULL, &sh_data);
	sh_data.cmd_bloc1 = el1;
	exec_bt(&sh_data, el1);
	del_tmp_hdocs(&sh_data);
	free_list_cmd(el1);
	free_env_var(sh_data.env_var1);
	return (0);
}
