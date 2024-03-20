/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/20 17:07:09 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env_export(t_sh_data *sh_data)
{
	t_env_var	*next;

	next = sh_data->env_var1;
	while (next != NULL)
	{
		ft_printf_fd(1, "declare -x ");
		ft_printf_fd(1, "%s=%s\n", next->name, next->value);
		next = next->next;
	}
}

void	print_env(t_sh_data *sh_data)
{
	t_env_var	*next;

	next = sh_data->env_var1;
	while (next != NULL)
	{
		ft_printf_fd(1, "%s=%s\n", next->name, next->value);
		next = next->next;
	}
}

void	print_tabchar(char **tabchar)
{
	int	i;

	i = 0;
	if (tabchar != NULL)
	{
		while (tabchar[i] != NULL)
		{
			ft_printf("%s\n", tabchar[i]);
			i++;
		}
	}
}
