/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nledent <nledent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/02/24 18:52:55 by nledent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	add_env_var(t_sh_data *sh, char *name, char *value)
{
	t_env_var	*next;

	next = sh->env_var1;
	if (next == NULL)
		next = ft_calloc(1, sizeof(t_env_var));
	else
	{
		while (next->next != NULL)
			next = next->next;
		next->next = ft_calloc(1, sizeof(t_env_var));
		next = next->next;
	}
	if (next == NULL)
		return (1);
	next->name = ft_strdup(name);
	next->value = ft_strdup(value);
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

void	print_env(t_sh_data *sh_data)
{
	t_env_var	*next;

	next = sh_data->env_var1;
	while (next != NULL)
	{
		printf("%s=%s\n", next->name, next->value);
		next = next->next;
	}
}
