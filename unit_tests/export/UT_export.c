/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/03/03 21:35:00 by nledent          ###   ########.fr       */
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
	t_cmd		*cmd;
	t_sh_data	sh;

	if (ft_strncmp(argv[1], "export", 7) != 0)
		printf("ajouter export en 1er arg");
	else
	{
		init_shell_data(argc, argv, envp, &sh);
		cmd = init_cmd(argc, argv);
		bt_export(&sh, cmd);
		print_env(&sh);
		free_cmd(cmd);
		free_env_var(sh.env_var1);
	}
	return (0);
}
