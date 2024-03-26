/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/03/26 16:11:15 by nledent          ###   ########.fr       */
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

static void	init_shell_data(char **envp, t_sh_data *sh_data)
{
	sh_data->env_var1 = NULL;
	sh_data->n_env_var = 0;
	sh_data->bloc = NULL;
	sh_data->return_value = 0;
	envp_to_list(sh_data, envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_sh_data	sh_data;
	int			r_value;

	(void)argv;
	r_value = 1;
	if (check_args(argc) == 0)
	{
		init_shell_data(envp, &sh_data);
		init_signals();
		prompt_rl(&sh_data);
		r_value = sh_data.return_value;
		free_env_var(sh_data.env_var1);
		ft_printf_fd(1, "exit\n");
	}
	else
		print_error(ER_NO_ARG, NULL, NULL);
	return (r_value);
}
