/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/24 21:02:31 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_sh_data(t_sh_data *sh)
{
	if (sh->bloc != NULL)
		free_list_cmd(sh->bloc);
	if (sh->env_var1 != NULL)
		free_env_var(sh->env_var1);
}

void	free_one_env_var(t_env_var *var)
{
	if (var != NULL)
	{
		free(var->name);
		if (var->value != NULL)
			free(var->value);
		ft_memset(var, 0, sizeof(t_env_var));
		free(var);
	}
}
