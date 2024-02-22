/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:19:19 by aranger           #+#    #+#             */
/*   Updated: 2024/02/21 09:29:50 by aranger          ###   ########.fr       */
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
	int			r_value;

	r_value = 1;
	init_shell_data(argc, argv, envp, &sh_data);
	if (check_args(argc) == 0) //a verifier selon que mode script ou non
		r_value = prompt_rl();
	else
		print_error(0);
	return (r_value);
}
