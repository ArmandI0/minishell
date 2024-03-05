/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/03/05 17:30:54 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_cmd	*init_cmd(int argc, char **argv)
{
	t_cmd	*cmd;
	int	i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_cmd));
	cmd->argc = argc - 1;
	if (argc > 1)
	{
		cmd->name = ft_strdup(argv[1]);
		cmd->args = ft_calloc(argc, sizeof(char *));
		while (i < argc - 1)
		{
			cmd->args[i] = ft_strdup(argv[i + 1]);
			i++;
		}
	}
	cmd->path = ft_strdup("");
	return (cmd);
}

static void	init_shell_data(int ac, char **av, char **envp, t_sh_data *sh_data)
{
	sh_data->ac = ac;
	sh_data->av = av;
	sh_data->envp = envp;
	sh_data->n_env_var = 0;
	sh_data->env_var1 = NULL;
	sh_data->env_var1 = NULL;
	sh_data->bloc = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_cmd		*cd;
	t_sh_data	sh;

	init_shell_data(argc, argv, envp, &sh);
	cd = init_cmd(argc, argv);
	add_env_var(&sh, "OLDPWD", "xx");
	add_env_var(&sh, "PWD", "x");
	print_env(&sh);
	bt_cd(&sh, cd);
	print_env(&sh);
	free_cmd(cd);
	free_env_var(sh.env_var1);
	return (0);
}
