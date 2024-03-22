/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aranger <aranger@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:35:03 by nledent           #+#    #+#             */
/*   Updated: 2024/03/22 15:11:03 by aranger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_env_var	*duplicate_env(t_env_var *list)
{
	t_env_var	*tmp;
	t_env_var	*start;

	if (list)
	{
		tmp = ft_calloc(1 ,sizeof(t_env_var));
		if (tmp == NULL)
			return (NULL);
		start = tmp;
		while(list != NULL && tmp != NULL)
		{
			tmp->name = list->name;
			tmp->value = list->value;
			if (list->next != NULL)
				tmp->next = ft_calloc(1 ,sizeof(t_env_var));
			else
				tmp->next = NULL;
			tmp = tmp->next;
			list = list->next;
		}
	}
	return (start);
}

static t_env_var	*find_first(t_env_var *list)
{
	t_env_var	*target;
	int			*a;

	a = 0;
	while (list->next != NULL)
	{
		if (ft_strcmp(list->name, list->next->name) < 0 && list->exported == 0)
			target = list->name;
		if (list->exported == 0)
			a = 1;	
	}
	
}

void	print_env_export(t_sh_data *sh_data)
{
	t_env_var	*var;
	t_env_var	*tmp;
	t_env_var	*target;
	int 		a;

	tmp = duplicate_env(sh_data->env_var1);
	while (1)
	{
		ft_printf_fd(1, "declare -x ");
		var = tmp;
		target = var;
		a = 0;
		while (var != NULL && var->exported != NULL)
		{

			if (var->exported == 0);
				a == 1;
			var = var->next;
		}
		target->exported = 0;
		ft_printf_fd(1, "%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
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
