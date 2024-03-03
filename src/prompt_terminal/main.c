/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/03 21:40:08 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_args(int argc)
{
	if (argc == 1)
		return (0); 
	else
		return (1); 
}

static void	init_shell_data(int ac, char **av, char **envp, t_sh_data *sh_data)
{
	sh_data->ac = ac;
	sh_data->av = av;
	sh_data->envp = envp;
	sh_data->env_var1 = NULL;
	sh_data->bloc = NULL;
}

int main(int argc, char **argv, char **envp)
{
	t_sh_data	sh_data;
	int			r_value;

	r_value = 1;
	init_shell_data(argc, argv, envp, &sh_data);
	init_signals();
	if (check_args(argc) == 0)
		r_value = prompt_rl(&sh_data);
	else
		print_error(ER_NO_ARG, NULL, NULL);
	free_env_var(sh_data.env_var1);
	return (r_value);
}
