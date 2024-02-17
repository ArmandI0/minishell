/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/17 21:06:05 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_error(int error)
{
	if (error == 0)
		printf("No arguments are required");
}

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
}

int main(int argc, char **argv, char **envp)
{
	t_sh_data	sh_data;

	init_shell_data(argc, argv, envp, &sh_data);
	init_signals(&sh_data);
	if (check_args == 0) //a verifier selon que mode script ou non
		prompt_rl(&sh_data);
	else
		print_error(0);
	return (0);
}
