/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:45:23 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 20:31:11 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_names_unset(char **args)
{
	int	i;

	i = 1;
	if (args != NULL)
	{
		while (args[i] != NULL)
		{
			if (ft_strchr(args[i], '=') != 0)
				return (1);
			else if (check_var_name(args[i]) != 0)
				return (1);
			i++;
		}
	}
	return (0);
}

static int	del_env_var(t_sh_data *sh, t_env_var *env_var, char *name)
{
	t_env_var	*tmp;
	int			len;

	len = ft_strlen(name);
	if (env_var == NULL)
		return (0);
	if (ft_strncmp(env_var->name, name, len + 1) == 0)
	{
		sh->env_var1 = env_var->next;
		free_one_env_var(env_var);
		return (0);
	}
	while (env_var->next != NULL)
	{
		if (ft_strncmp(env_var->next->name, name, len + 1) == 0)
		{
			tmp = env_var->next;
			env_var->next = tmp->next;
			free_one_env_var(tmp);
			return (0);
		}
		env_var = env_var->next;
	}
	return (0);
}

int	bt_unset(t_sh_data *sh, t_cmd *unset)
{
	int	i;

	i = 1;
	if (unset->argc == 1)
		return (0);
	else if (unset->argc > 1 && unset->args != NULL)
	{
		if (check_names_unset(unset->args) == 1)
			return (1);
		else
		{
			while (unset->args[i] != NULL)
			{
				del_env_var(sh, sh->env_var1, unset->args[i]);
				i++;
			}
			return (0);
		}
	}
	else
		return (1);
}
