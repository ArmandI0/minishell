/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/18 20:55:10 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_env_var(t_sh_data *sh, char *name, char *value)
{
	t_env_var	*new_var;
	t_env_var	*next;

	new_var = ft_calloc(1, sizeof(t_env_var));
	if (new_var == NULL)
		return (1);
	if (sh->env_var1 == NULL)
		sh->env_var1 = new_var;
	else
	{
		next = sh->env_var1;
		while (next->next != NULL)
			next = next->next;
		next->next = new_var;
	}
	new_var->name = ft_strdup(name);
	new_var->value = ft_strdup(value);
	(sh->n_env_var)++;
	return (0);
}

void	envp_to_list(t_sh_data *sh_data)
{
	char	**env;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	env = sh_data->envp;
	while (env[i] != NULL)
	{
		name = ft_strdup(env[i]);
		(ft_strchr(name, '='))[0] = 0;
		value = ft_strdup(ft_strchr(env[i], '=') + 1);
		add_env_var(sh_data, name, value);
		i++;
		free(name);
		free(value);
	}
}

char	**list_to_envp(t_sh_data *sh_data)
{
	char		**new_env;
	int			i;
	t_env_var	*next;

	i = 0;
	next = sh_data->env_var1;
	new_env = ft_calloc((sh_data->n_env_var + 1), sizeof(char *));
	if (new_env == NULL)
		return (NULL);
	while (next != NULL && i < sh_data->n_env_var)
	{
		new_env[i] = ft_strdup(next->name);
		new_env[i] = ft_fstrjoin(new_env[i], ft_strdup("="));
		new_env[i] = ft_fstrjoin(new_env[i], ft_strdup(next->value));
		i++;
		next = next->next;
	}
	return (new_env);
}

int	upd_env_var(t_sh_data *sh, char *name_var, char *new_value)
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
