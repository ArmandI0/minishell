/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@42angouleme.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/12 11:34:24 by nledent          ###   ########.fr       */
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
	sh_data->n_env_var = 0;
	sh_data->bloc = NULL;
	sh_data->return_value = 0;
	envp_to_list(sh_data);
}

int main(int argc, char **argv, char **envp)
{
	t_sh_data	sh_data;
	int			r_value;

	r_value = 1;
	if (check_args(argc) == 0)
	{
		init_shell_data(argc, argv, envp, &sh_data);
		init_signals();
		r_value = prompt_rl(&sh_data);
		free_env_var(sh_data.env_var1);
		ft_printf_fd(1, "exit\n");
	}
	else
		print_error(ER_NO_ARG, NULL, NULL);
	return (r_value);
}
