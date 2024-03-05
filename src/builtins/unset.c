/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/05 17:51:13 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	bt_unset(t_sh_data *sh,char *path_dir, t_cmd *unset)
{
    t_env_var	*env_var;

	env_var = sh->env_var1;
	if (var == NULL)
		return (1);
	while (var != NULL)
    {
        if (var->name != NULL && unset-> != NULL)
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
