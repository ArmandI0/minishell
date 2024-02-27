/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UT_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:43:48 by nledent           #+#    #+#             */
/*   Updated: 2024/02/24 19:22:47 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	char **new_env;
	char **args;

	args=ft_calloc(2, sizeof(char *));
	args[0] = ft_strdup("bash");
	init_shell_data(argc, argv, envp, &sh_data);
	envp_to_list(&sh_data);
	add_env_var(&sh_data, "ABC", "COUCOU");
	add_env_var(&sh_data, "LOL", "tres drole");
	print_env(&sh_data);
	new_env = list_to_envp(&sh_data);
	print_tabchar(new_env);
	//execve("/bin/bash", args, new_env);

	free_tabchar (new_env);
	free_tabchar (args);
	free_env_var(sh_data.env_var1);
	return (0);
}
