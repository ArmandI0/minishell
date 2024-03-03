/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/03 15:22:01 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    upd_env_var(t_sh_data *sh, char *name_var, char *new_value)
{
    t_env_var	*var;

	var = sh->env_var1;
	if (var == NULL)
		return (1);
	while (var != NULL)
    {
        if (var->name != NULL && name_var != NULL)
        {
			if (ft_strncmp(name_var, var->name, ft_strlen(name_var) + 1) == 0)
            {
				if (var->value != NULL)
					free (var->value);
				if (new_value == NULL)
					var->value = NULL;
				else
					var->value = ft_strdup(new_value);
				return (0);
			}
        }
		var = var->next;
    }
    return (1);
}
